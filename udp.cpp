#include "udp.h"
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace simple_udp;

/*****************************************************************************************
 * 
 * Receiver
 * 
*****************************************************************************************/

receiver::receiver(const std::string& addr, const int port)
    :   net_port(port)
    ,   net_addr(addr)
{
    char port_c[6];
    snprintf(port_c, sizeof(port_c), "%d", net_port); // already adds a null terminator

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    int result = getaddrinfo(net_addr.c_str(), port_c, &hints, &s_addrinfo);
    if(result != 0 || s_addrinfo == NULL) {
        // std::cout << "Error startings sending socket: " << result << std::endl;
        throw std::runtime_error("Couldn't perform getaddrinfo correctly on receiver socket.");
    }
        // Proceed to make the socket
    i_socket = socket(s_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    if(i_socket == -1) {
        freeaddrinfo(s_addrinfo);
        // std::cout << "Couldn't create socket: " << i_socket << std::endl;
        throw std::runtime_error("Couldn't create receiver socket");
    }
    result = bind(i_socket, s_addrinfo->ai_addr, s_addrinfo->ai_addrlen);
    if(result != 0) {
        freeaddrinfo(s_addrinfo);
        close(i_socket);
        //std::cout << "Couldn't bind: " << result << std::endl;
        throw std::runtime_error("Couldn't bind receiver socket");
    }
}

receiver::~receiver() {
    freeaddrinfo(s_addrinfo);
    close(i_socket);
}

int receiver::listen(char* msg, size_t len) {
    return ::recv(i_socket, msg, len, 0);
}

/*****************************************************************************************
 * 
 * Sender
 * 
*****************************************************************************************/

sender::sender(const std::string& addr, const int port) 
    :   net_port(port)
    ,   net_addr(addr)
{
    char port_c[6];
    snprintf(port_c, sizeof(port_c), "%d", net_port); // already adds a null terminator

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    int gai_result = getaddrinfo(net_addr.c_str(), port_c, &hints, &s_addrinfo);
    if(gai_result != 0 || s_addrinfo == NULL) {
        // std::cout << "Error startings sending socket: " << gai_result << std::endl;
        throw std::runtime_error("Couldn't perform getaddrinfo correctly on sender socket.");
    }
        // Proceed to make the socket
    i_socket = socket(s_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    if(i_socket == -1) {
        freeaddrinfo(s_addrinfo);
        throw std::runtime_error("Couldn't create sender socket");
    }
}

sender::~sender() {
    freeaddrinfo(s_addrinfo);
    close(i_socket);
}

int sender::send(const char* msg, size_t size) {
    return sendto(i_socket, msg, size, 0, s_addrinfo->ai_addr, s_addrinfo->ai_addrlen);
}

int sender::send(const std::string& msg) {
    return send(msg.c_str(), msg.length());
}
