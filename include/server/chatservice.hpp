#pragma once

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "offlinemessagemodel.hpp"
#include "usermodel.hpp"
#include "json.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
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
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //获取消息对应的处理器
    MsgHandler getHandler(int);
    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr& conn);
    //服务器异常退出，业务重置
    void reset();
private:
    ChatService();
    //存储消息id和对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;

    //存贮在线用户的通信连接，当a给服务器发消息想给b，服务器需要知道b的连接在哪
    //onmessage会被多个线程调用，login方法也会被多个线程调用，所以要考虑该成员变量的线程安全问题
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    //定义互斥锁，保证_userConnMap的线程安全
    mutex _connMutex;

    //数据操作类对象 服务里面只依赖model类，不做具体的数据库操作，而且model给业务层提供的都是对象
    UserModel _userModel;

    offlineMsgModel _offlineMsgModel;

    FriendModel _friendModel;

    GroupModel _groupModel;
};