#include "chatservice.hpp"
#include "public.hpp"
#include <muduo/base/Logging.h>

using namespace muduo;

//获取单例对象的接口函数
ChatService* ChatService::instance()
{
    static ChatService service;
    return &service;
}

//注册消息以及对应的回调操作
ChatService::ChatService()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});
}


MsgHandler ChatService::getHandler(int msgid)
{
    //记录错误日志，msgid没有对应的事件处理回调
    auto it = _msgHandlerMap.find(msgid);
    if(it == _msgHandlerMap.end())
    {
        //返回一个默认的处理器，空操作
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time) {
            LOG_ERROR << "msgid" << msgid << "can not find handler!";
        };
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
}

//处理登录注册业务   ORM object relation map 对象关系映射=》业务层操作的都是对象=》数据层DAO层才有数据库的操作
void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "do login service!!!";
}
void ChatService::ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "do reg service!!!";
}


