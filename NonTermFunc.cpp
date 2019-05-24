#include "attributes.h"


NonTermFunc::NonTermFunc(std::string name , std::list<TypeNameEnum> parameters , TypeNameEnum retType) :
    DataObj(name) , Parameters(parameters) , RetType(retType) {}
