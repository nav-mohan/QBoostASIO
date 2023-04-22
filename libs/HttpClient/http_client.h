// https://www.boost.org/doc/libs/1_82_0/libs/beast/example/http/client/async/http_client_async.cpp

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

class session : public std::enable_shared_from_this<session>
{
private:
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::tcp_stream stream_;
    boost::beast::flat_buffer buffer_;
    boost::beast::http::request<boost::beast::http::empty_body> req_;
    boost::beast::http::response<boost::beast::http::string_body> res_;

public:
    explicit session(boost::asio::io_context& ioc);
    void run(const char *host, const char *port, const char *target);

private:
    void do_resolve(const char *host, const char *port);
    void do_connect(boost::asio::ip::tcp::resolver::results_type results);
    void do_write();
    void do_read();
};