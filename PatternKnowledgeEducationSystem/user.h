/*======== 全局用户类 ======*/

#ifndef USER_H
#define USER_H

#include <string>
#include "cogmodel.h"
using namespace std;

class user
{
public:
	user();
	~user();
	void setSid(int);
	void setName(string);
	void setPassword(string);
	void setSex(string);
	void setAge(int);
	void setEducation(string);
	void setModel(cogmodel&);
	int getSid();
	string getName();
	string getPassword();
	string getSex();
	int getAge();
	string getEducation();
	cogmodel getModel();

private:
	int sid;
	string name;
	string password;
	string sex;
	int age;
	string education;
	cogmodel model;
};

#endif
