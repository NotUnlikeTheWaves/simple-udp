#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
//#include <stdexcept>

namespace simple_udp {
    class sender {
        public:
            sender(const std::string& addr, const int port);
            ~sender();

            int                 send(const char* msg, size_t size);
            int                 send(const std::string& msg);
        
        private:
            int                 i_socket;
            int                 net_port;
            std::string         net_addr;
            struct addrinfo*    s_addrinfo;
    };

    class receiver {
        public:
            receiver(const std::string& addr, const int port);
            ~receiver();

            int                 listen(char* msg, size_t len);
        
        private:
            int                 i_socket;
            int                 net_port;
            std::string         net_addr;
            struct addrinfo*    s_addrinfo;
    };
}