/*======== 认知模型类 ========*/

#ifndef COGMODEL_H
#define COFMODEL_H
#include <string>
using namespace std;

class cogmodel
{
public:
    cogmodel();
    ~cogmodel();
    void setCogform(string);
    void setStrategy(string);
    void setCogstyle(string);
    void setCogstructure(string);
    string getCogform();
    string getStrategy();
    string getCogstyle();
    string getCogstructure();

private:
    string cogform;
    string strategy;
    string cogstyle;
    string cogstructure;
};

#endif

