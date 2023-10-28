//网络通信间数据比较复杂的时候，需要借助数据序列化反序列化
//json protobuf xml

#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

//json序列化示例1：
void func1() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello";

    string sendBuf = js.dump(); //网络发送
    cout << sendBuf.c_str() << endl;
}

//json序列化示例2
void func2() {
    json js;
    //添加数组
    js["id"] = {1, 2, 3, 4, 5};
    //添加key value
    js["name"] = "zhang san";
    //添加对象
    js["msg"]["zhang san"] ="hello world";
    js["msg"]["li si"] = "hello china";
    //上面等同于下面
    //js["msg"] = {{"zhang san", "hello world"}, {"zhang san", "hello world"}};
    cout << js << endl;
}

//json序列化示例3
void func3() {
    json js;
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    js["list"] = vec;

    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});

    js["path"] = m;

    cout << js << endl;

}

//json数据反序列化

string func4() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello";

    string sendBuf = js.dump(); //网络发送
    return sendBuf;
    
}


int main() {
    //func3();
    string recvBuf = func4();
    //数据的反序列化
    json jsbuf = json::parse(recvBuf);
    cout << jsbuf["msg_type"] << endl;
    cout << jsbuf["from"] << endl;
    return 0;
}