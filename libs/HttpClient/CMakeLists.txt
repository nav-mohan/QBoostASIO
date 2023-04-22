find_package(Boost REQUIRED COMPONENTS headers)
set(BOOST_LIBS Boost::headers)
add_library(HttpClient http_client.cpp)

target_link_libraries(
    HttpClient
    ${BOOST_LIBS} 
    )
