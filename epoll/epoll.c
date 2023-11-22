#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int listen_fd, ep_fd;

    struct sockaddr_in server_add;
    memset(&server_add, 0, sizeof(server_add));
    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = htonl(INADDR_ANY);
    server_add.sin_port = htons(8888);

    bind(listen_fd, (struct sockaddr_in*)&server_add, sizeof(server_add));
    listen(listen_fd, 100);

    struct epoll_event events[500];
    struct epoll_event ev;

    ep_fd = epoll_create(500);
    ev.data.fd = listen_fd;
    ev.events = EPOLLIN;

    epoll_ctl(ep_fd, EPOLL_CTL_ADD, listen_fd, &ev);

    while (1) {
        int ep_cnt = epoll_wait(ep_fd, events, 500, -1);
        if (ep_cnt < 0) {
            break;
        }
        for (int i = 0; i < ep_cnt; i++) {
            int sockfd = events[i].data.fd;
            if (sockfd == listen_fd) {
                printf("aaa\n");
            }
        }
    }
    
    close(listen_fd);
    close(ep_fd);
    return 0;
}