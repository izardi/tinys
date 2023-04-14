#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>
#include <cstdio>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>

namespace utility {
namespace Socket {

using SA = struct sockaddr;
using SAI = struct sockaddr_in;


class Socket {
public:

    Socket(): m_sockfd(0){}

    Socket(const char* ip, int port): m_port(port), m_sockfd(0) {
        memcpy(m_ip, ip, strlen(ip));
    }

    bool bind(const char* ip, int port) {
        SAI sai;
        memset(&sai, 0, sizeof(sai));
        sai.sin_family = AF_INET;

        if (strcmp(ip, "") != 0) {
            sai.sin_addr.s_addr = inet_addr(ip);
        } else {
            sai.sin_addr.s_addr = htonl(INADDR_ANY);
        }

        if(::bind(m_sockfd, (SA*)&sai, sizeof(sai))) {
            perror("::bind");
            return false;
        }
        return true;
    }

    bool connect(SA * sa, socklen_t salen) {
        if(::connect(m_sockfd, (SA*)sa, salen)){
            perror("::connect");
            return false;
        }
        return true;
    }

    bool connect(const char* ip, int port) {

        SAI sai;
        memset(&sai, 0, sizeof(sai));
        sai.sin_family = AF_INET;
        inet_pton(AF_INET, ip, &sai.sin_addr.s_addr);
        sai.sin_port = htons(port);

        // connect 成功返回0 失败返回-1
        if(::connect(m_sockfd, (SA*)&sai, sizeof(sai))) {
            perror("::connect");
            return false;
        }
        return true;
    }

    void close() {
        if (m_sockfd > 0) {
            ::close(m_sockfd);
        }
        m_sockfd = 0;
    }

    int accept(SA* sa = nullptr, socklen_t* len = nullptr) {
        int sfd = ::accept(m_sockfd, sa, len);
        // accept 返回-1错误 正常返回非负整数
        if (sfd < 0) {
            perror("::accept()");
            sfd = -1;
        }
        return sfd;
    }

    int recv(char* buf, int len, int flags = 0) {
        return ::recv(m_sockfd, buf, len, flags);
    }

    int send(const char* buf, int len, int flags = 0) {
        return ::send(m_sockfd, buf, len, flags);
    }

    bool set_nonblock() {
        int flags = fcntl(m_sockfd, F_GETFL);
        if (flags < 0) {
            perror("::fcntl");
            return false;
        }

        flags |= O_NONBLOCK;

        if(fcntl(m_sockfd, F_SETFL, flags) < 0) {
            perror("::fcntl");
            return false;
        }
        return true;
    }

    bool set_send_buf(int size);

    bool set_recv_buf(int size) {

    }

    bool set_linger(bool active, int seconds);

    bool set_keep_alive() {
        int flag = 1;
        if (::setsockopt(m_sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag) < 0)){
            perror("::setsockopt keep_alive");
            return false;
        }
        return true;
    }

    bool set_reuse_addr() {
        int flag = 1;
        if(::setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0) {
            perror("::setsockopt reuse addr");
            return false;
        }
        return true;

    }

    bool set_reuse_port() {
        int flag = 1;
        if(::setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) < 0) {
            perror("::setsockopt reuse addr");
            return false;
        }
        return true;
    }


protected:
    char m_ip[20];
    int m_port;
    int m_sockfd;
};



}
}

#endif
