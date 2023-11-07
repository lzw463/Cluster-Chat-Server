#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>

using namespace std;

//处理服务器crtl+c结束后，重置user的状态信息
void resethandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main() 
{
    //接收服务端异常退出信号加以处理，重置用户登录状态
    signal(SIGINT, resethandler);

    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);

    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    return 0;
}