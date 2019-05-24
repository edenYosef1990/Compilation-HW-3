#include "attributes.h"

bool IsItConstOrExistingSymbol(DataObj * dataObject){
    if(!(dataObject->IsItVar())){
        return true;
    }
    if(dynamic_cast<IDNotExists*>(dataObject)!=nullptr){
        return true;
    }
    return false;
}