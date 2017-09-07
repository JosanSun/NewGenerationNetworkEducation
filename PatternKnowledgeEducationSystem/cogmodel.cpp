#include "cogmodel.h"


cogmodel::cogmodel()
{
}


cogmodel::~cogmodel()
{
}

void cogmodel::setCogform(string _cogform){ cogform = _cogform; }

void cogmodel::setStrategy(string _strategy){ strategy = _strategy; }

void cogmodel::setCogstyle(string _cogstyle){ cogstyle = _cogstyle; }

void cogmodel::setCogstructure(string _cogstructure){ cogstructure = _cogstructure; }

string cogmodel::getCogform(){ return cogform; }

string cogmodel::getStrategy(){ return strategy; }

string cogmodel::getCogstyle(){ return cogstyle; }

string cogmodel::getCogstructure(){ return cogstructure; }