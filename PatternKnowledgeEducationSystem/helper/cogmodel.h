/*======== 认知模型类 ========*/
#ifndef COGMODEL_H
#define COFMODEL_H

#include <string>
using namespace std;

class CogModel
{
public:
    CogModel();
    ~CogModel();
    void setCogApproach(string);
    void setCogStrategy(string);
    void setCogExperience(string);
    void setMetaCogAbility(string);
    string getCogApproach();
    string getCogStrategy();
    string getCogExperience();
    string getMetaCogAbility();

private:
    string cogApproach;
    string cogStrategy;
    string cogExperience;
    string metaCogAbility;
};

#endif

