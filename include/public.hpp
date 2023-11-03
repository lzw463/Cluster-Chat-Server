#pragma once

/*
server和client的公共文件
*/
enum EnMsgType
{
    LOGIN_MSG = 1,
    REG_MSG,  //注册消息
    REG_MSG_ACK //注册相应消息
};