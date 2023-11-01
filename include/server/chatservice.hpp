#pragma once

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include "json.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

//聊天服务器业务类 单例
class ChatService
{
public:
    //获取单例对象的接口函数
    static ChatService* instance();
    //处理登录注册业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //获取消息对应的处理器
    MsgHandler getHandler(int);
private:
    ChatService();
    //存储消息id和对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;
};