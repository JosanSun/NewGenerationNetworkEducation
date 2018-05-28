#include "cogmodel.h"

CogModel::CogModel()
{
}

CogModel::~CogModel()
{
}

void CogModel::setCogApproach(string _cogApproach)
{
    cogApproach = _cogApproach;
}

void CogModel::setCogStrategy(string _cogStrategy)
{
    cogStrategy = _cogStrategy;
}

void CogModel::setCogExperience(string _cogExperience)
{
    cogExperience = _cogExperience;
}

void CogModel::setMetaCogAbility(string _metaCogAbility)
{
    metaCogAbility = _metaCogAbility;
}

string CogModel::getCogApproach()
{
    return cogApproach;
}

string CogModel::getCogStrategy()
{
    return cogStrategy;
}

string CogModel::getCogExperience()
{
    return cogExperience;
}

string CogModel::getMetaCogAbility()
{
    return metaCogAbility;
}








