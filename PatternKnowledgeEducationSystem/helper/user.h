/*======== 全局用户类 ======*/
#ifndef USER_H
#define USER_H

#include <string>
#include "cogmodel.h"
using namespace std;

class User
{
public:
    User();
    ~User();

    void setSid(int);
    void setName(string);
    void setPassword(string);
    void setSex(string);
    void setAge(int);
    void setEducation(string);
    void setModel(CogModel&);

    int getSid();
    string getName();
    string getPassword();
    string getSex();
    int getAge();
    string getEducation();
    CogModel getModel();

private:
    int sid;
    string name;
    string password;
    string sex;
    int age;
    string education;
    CogModel model;
};

#endif
