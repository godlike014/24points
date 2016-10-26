#include "Number.h"
Number::Number()
{
    num = rand()%10+1;
}
Number::~Number()
{
    //dtor
}
int Number::getnum(){
    return num;
}
