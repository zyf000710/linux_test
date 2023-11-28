#include <stdio.h>
#include <unistd.h>
#include <systemd/sd-daemon.h>
#include <signal.h>
#include <syslog.h>

// 持续喂狗，service文件中WatchdogSec
void epoll_KeepAlive()
{
    do {
        sleep(1);
        sd_notify(0, "WATCHDOG=1");
        syslog(LOG_NOTICE, "a");
    } while(1);
    
    return;
}

// 信号量回调
void epoll_SigHandler(int sig)
{
    switch (sig) {
        case SIGUSR1:
            abort();
            break;
        
        default:
            return;
    }
}


int main()
{
    signal(SIGUSR1, epoll_SigHandler);
    sd_notify(0, "READY=1");
    epoll_KeepAlive();
    return 0;
}