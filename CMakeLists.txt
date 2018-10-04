project(Simple-UDP)
cmake_minimum_required(VERSION 2.8.0)

add_library(simple_udp udp.cpp)
target_include_directories(simple_udp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(sender sender.cpp)
add_executable(receiver receiver.cpp)
target_link_libraries(sender simple_udp)
target_link_libraries(receiver simple_udp)
#target_include_directories(sender PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(receiver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})