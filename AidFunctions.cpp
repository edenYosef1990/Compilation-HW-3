#include "AidFunctions.h"
#include <math.h>
#include <cmath>

int CharPointerToInt(char * str){
    int i=1;
    int val=0;
    while(str[i] != '\0'){
        val += (int)(str[i]-'0')*pow(10,i);
    }
    return val;
}
