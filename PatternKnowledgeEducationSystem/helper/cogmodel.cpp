#include "cogmodel.h"

CogModel::CogModel()
{
}


CogModel::~CogModel()
{
}

void CogModel::setCogform(string _cogform)
{
    cogform = _cogform;
}

void CogModel::setStrategy(string _strategy)
{
    strategy = _strategy;
}

void CogModel::setCogstyle(string _cogstyle)
{
    cogstyle = _cogstyle;
}

void CogModel::setCogstructure(string _cogstructure)
{
    cogstructure = _cogstructure;
}

string CogModel::getCogform()
{
    return cogform;
}

string CogModel::getStrategy()
{
    return strategy;
}

string CogModel::getCogstyle()
{
    return cogstyle;
}

string CogModel::getCogstructure()
{
    return cogstructure;
}








