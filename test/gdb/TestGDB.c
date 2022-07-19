//
// Created by root on 2022.07.19.
//
#include <stdio.h>



int method1(){
    printf("method1\n");
}

int method2(int parameter){
    int local0;
    int local1 = 1;
    printf("method2\n");
}


int main(){

   printf("main\n");

   method1();
   method2(3);

   methodInOtherFile();

}

