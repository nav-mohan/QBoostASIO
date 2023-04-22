#include "http_client.h"

session::session(boost::asio::io_context& ioc)
    :   resolver_(boost::asio::make_strand(ioc))
    ,   stream_(boost::asio::make_strand(ioc))
    {}

void session::run(const char *host, const char *port, const char *target)
{
    printf("Running HttpClient\n");
    req_.version(11);
    req_.method(boost::beast::http::verb::get);
    req_.target(target);
    req_.set(boost::beast::http::field::host, host);
    req_.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    do_resolve(host,port);
}

void session::do_resolve(const char *host, const char *port)
{
    printf("resolving...\n");
    resolver_.async_resolve(
        host,
        port,
        [&](boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type results)
        {
            if(ec){
                printf("ERROR: %s\n",ec.what().c_str());
                return;
            }
            do_connect(results);
        }
    );
}

void session::do_connect(boost::asio::ip::tcp::resolver::results_type results)
{
    printf("connecitng...");
    stream_.expires_after(std::chrono::seconds(30));
    stream_.async_connect(
        results,
        [&](boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type::endpoint_type ep)
        {
            if(ec){
                printf("ERROR: %s\n",ec.what().c_str());
                return;
            }
            printf("connected!\n");
            do_write();
        }
    );
}

void session::do_write()
{
    printf("writing...");
    boost::beast::http::async_write(
        stream_,
        req_,
        [&](boost::beast::error_code ec, std::size_t bt)
        {
            if(ec){
                printf("ERROR: %s\n",ec.what().c_str());
                return;
            }
            printf("wrote\n");
            do_read();
        }
    );
}

void session::do_read()
{
    printf("reading...");
    boost::beast::http::async_read(
        stream_,
        buffer_,
        res_,
        [&](boost::beast::error_code ec, std::size_t bt)
        {
            if(ec){
                printf("ERROR: %s\n",ec.what().c_str());
                return;
            }
            printf("read!\n");
            std::cout << res_ << std::endl;
            stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both,ec);
            if(ec){
                printf("ERROR: %s\n",ec.what().c_str());
                return;
            }
        }
    );
}