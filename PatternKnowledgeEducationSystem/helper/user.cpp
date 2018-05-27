#include "user.h"

User::User()
{
}


User::~User()
{
}

void User::setSid(int _sid)
{
    sid = _sid;
}

void User::setName(string _name)
{
    name = _name;
}

void User::setPassword(string _password)
{
    password = _password;
}

void User::setSex(string _sex)
{
    sex = _sex;
}

void User::setAge(int _age)
{
    age = _age;
}

void User::setEducation(string _education)
{
    education = _education;
}

void User::setModel(CogModel &_model)
{
    model = _model;
}

int User::getSid()
{
    return sid;
}

string User::getName()
{
    return name;
}

string User::getPassword()
{
    return password;
}

string User::getSex()
{
    return sex;
}

int User::getAge()
{
    return age;
}

string User::getEducation()
{
    return education;
}

CogModel& User::getModel()
{
    return model;
}








