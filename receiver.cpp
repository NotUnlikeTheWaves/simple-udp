#include "udp.h"
#include <iostream>

// Example program for receiving UDP data.

int main(int argc, char** argv) {
    simple_udp::receiver listener("127.0.0.1", 12080);
    char msg[20];
    int a = listener.listen(msg, sizeof msg);
    std::cout << "Received a message:" << msg << std::endl;
    std::cout << "Msg len: " << a << std::endl;
    return 0;
}
