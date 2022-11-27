#include "../skip.h"
#include <stdio.h>




int main(){

    skip_t* skip = skip_init(10,sizeof(int));
    skip_insert(skip,1,11);
    skip_insert(skip,2,22);
    skip_insert(skip,3,33);
    skip_insert(skip,4,44);
    skip_insert(skip,5,55);
    int level = skip_get_level(skip);
    printf("level = %d \n",level);
    int a = 44;
    skip_find(skip,4,&a);
    skip_modify(skip,4,44);
    skip_delete(skip,4);
    skip_destroy(skip);


    return 0;
}
