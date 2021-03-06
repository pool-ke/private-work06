#ifndef MYSQLPOOL_H
#define MYSQLPOOL_H

#include <iostream>
#include <mysql/mysql.h>
#include <queue>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <mutex>
#include <thread>

class MysqlPool{

public:
    ~MysqlPool();
    std::map<const std::string,std::vector<const char*>>executeSql(const char* sql);
    static MysqlPool* getMysqlPoolObject();
    void setParameter(const char* mysqlhost,
                      const char* mysqluser,
                      const char* mysqlpwd,
                      const char* databasename,
                      unsigned int port,
                      const char* socket=NULL,
                      unsigned long client_flag=0,
                      unsigned int max_connect=50);

private:
    MysqlPool();
    MYSQL* createOneConnect();
    MYSQL* getOneConnect();
    void close(MYSQL* conn);
    bool isEmpty();
    MYSQL* poolFront();
    unsigned int poolSize();
    void poolPop();
private:
    std::queue<MYSQL*> mysqlpool;
    const char* _mysqlhost;
    const char* _mysqluser;
    const char* _mysqlpwd;
    const char* _databasename;
    unsigned int _port;
    const char* _socket;
    unsigned long _client_flag;
    unsigned int MAX_CONNECT;
    unsigned int connect_count;
    static std::mutex objectlock;
    static std::mutex poollock;
    static MysqlPool* mysqlpool_object;

};
#endif