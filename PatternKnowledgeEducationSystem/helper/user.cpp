#include "user.h"


user::user()
{
}


user::~user()
{
}

void user::setSid(int _sid)
{
    sid = _sid;
}

void user::setName(string _name)
{
    name = _name;
}

void user::setPassword(string _password)
{
    password = _password;
}

void user::setSex(string _sex)
{
    sex = _sex;
}

void user::setAge(int _age)
{
    age = _age;
}

void user::setEducation(string _education)
{
    education = _education;
}

void user::setModel(cogmodel &_model)
{
    model = _model;
}

int user::getSid()
{
    return sid;
}

string user::getName()
{
    return name;
}

string user::getPassword()
{
    return password;
}

string user::getSex()
{
    return sex;
}

int user::getAge()
{
    return age;
}

string user::getEducation()
{
    return education;
}

cogmodel user::getModel()
{
    return model;
}








