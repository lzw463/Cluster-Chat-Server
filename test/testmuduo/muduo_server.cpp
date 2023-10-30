/*
muduo库的使用：
    muduo网络库给用户提供了两个主要的类
    Tcpserver Tcpclient
*/

#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include <iostream>
#include <functional>
#include <string>

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*
基于muduo网络库开发服务器程序
1.组合Tcpserver对象
2.创建Eventloop事件循环对象的指针
3.明确Tcpserver构造函数需要什么参数
4.在当前服务器类的构造函数当中，注册回调函数
5.设置合适的服务端线程数量
*/
class ChatServer
{
public:
    ChatServer(EventLoop* loop, //事件循环
            const InetAddress& listenAddr, //IP+port
            const string& nameArg) //服务器的名字
        :_server(loop, listenAddr, nameArg), _loop(loop) // #3
    { 
        //给服务器注册用户连接的创建和断开连接
        _server.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));

        //给服务器注册用户读写事件回调
        _server.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));

        //设置服务器端的线程数量 #5
        _server.setThreadNum(4);
    }

    // 开启事件循环
    void start() {
        _server.start();
    }

private:
    // 专门处理用户的连接创建和断开
    void onConnection(const TcpConnectionPtr& conn) {
        if(conn->connected()){
            cout << conn->peerAddress().toIpPort() << "->" <<
            conn->localAddress().toIpPort() << " state:online" << endl;
        }
        else {
            cout << conn->peerAddress().toIpPort() << "->" <<
            conn->localAddress().toIpPort() << " state:offline" << endl;
            conn->shutdown();
            //_loop.quit();
        }
    }
    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr& conn, //连接
                            Buffer* buffer, //缓冲区
                            Timestamp time) //时间信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data:" << "time:" << time.toString() << endl;
        // for (char& item : buf) {
        //     printf("%s", item);
        // }
        //回应http GET请求
        // string rmsg = "";
        // rmsg = "HTTP/1.1 200 OK\r\n";
        // rmsg += "Server : Xhttp\r\n";
        // rmsg += "Content-Type: text/html\r\n";
        // rmsg += "Content-Length: ";
        // rmsg += "10\r\n";
        // rmsg += "\r\n";

        // rmsg += "0123789";

        conn->send(StringPiece(buf.c_str()));
    }



    TcpServer _server;  // #1
    EventLoop *_loop;    // #2 epoll

};

int main() {
    EventLoop loop;
    InetAddress addr("127.0.0.1", 8080);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();  //listenfd 添加到epoll上
    loop.loop();     //epoll以阻塞方式等待新用户连接，已连接用户的读写事件

    return 0;
}




/*
基于VScode的配置说明
c_cpp_properties.json 配置 F1
task.json 编译 crtl+shift+b
launck.json 调试

c_cpp_properties.json
gcc -I头文件搜索路径 -L库文件搜索路径 -l库名称
"cppStandard" : "c++14",

task.json
"args": 
    "-lmuduo_net"......

launch.json

*/