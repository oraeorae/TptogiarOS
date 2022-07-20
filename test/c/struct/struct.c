//
// Created by root on 2022.07.21.
//
#include <stdio.h>
#include "struct.h"

struct TestStruct structName;



int main(){

   struct TestStruct test ={252,525};
   structName.a = 111;
   structName.b = 222;

   printf(" address = %x \n",&structName);
   printf(" address = %x \n",structName);
   printf(" address = %x \n",&structName);
   printf(" address a = %x  value a = %d ;address b = %x value b = %d\n",&structName.a,structName.a,&structName.b,structName.b);



   printf(" address = %x \n",test);
   printf(" address = %x \n",&test);
   printf(" address a = %x  value a = %d ;address b = %x value b = %d\n",&test.a,test.a,&test.b,test.b);



}