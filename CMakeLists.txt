cmake_minimum_required(VERSION 3.11)
project(QBoostASIO LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON) # Commented this out because I want to place my .ui files in a different folder

set(QT_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.8_2")
set(OPENSSL_PREFIX_PATH "/opt/homebrew/Cellar/openssl@1.1/1.1.1t")
set(CMAKE_PREFIX_PATH "${OPENSSL_PREFIX_PATH}" "${QT_PREFIX_PATH}")
set(QT_REQUIRED_PACKAGES Core Gui Widgets Multimedia)
find_package(Qt5 REQUIRED COMPONENTS ${QT_REQUIRED_PACKAGES})
find_package(Boost REQUIRED COMPONENTS headers)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON) # #include "constants.h"
set(CPP_SOURCE_FILES main.cpp mainwindow.cpp)
qt_wrap_ui( UI_FILES mainwindow.ui )
add_executable(${PROJECT_NAME} ${CPP_SOURCE_FILES} ${UI_FILES} )


target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    libs/HttpClient
)

set(QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia)
set(BOOST_LIBS Boost::headers)
add_subdirectory(libs/HttpClient)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC 
    ${QT_LIBS} ${BOOST_LIBS} 
    HttpClient
)
