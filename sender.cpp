#include "udp.h"

// Example program for sending UDP data.

int main(int argc, char** argv) {
    simple_udp::sender client("127.0.0.1", 12080);

    client.send("Test message.");
    return 0;
}
