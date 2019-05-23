#include "attributes.h"

NonTermInt::NonTermInt(Node * numericValueNode) : NumericValue((dynamic_cast<NumVal*>(numericValueNode))->getVal()) {}

NonTermInt::NonTermInt(std::string name) : DataObj(name) {}

int NonTermInt::GetNumericValue() {return NumericValue;}