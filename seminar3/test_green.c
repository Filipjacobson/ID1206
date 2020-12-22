#include <stdio.h>
#include <stdlib.h>
#include "green.h"

void *test(void *arg){
	int i = *(int*)arg;
	int loop = 4;
	while(loop > 0){
		printf("\tthread %d: %d\n", i, loop);
		loop--;
		green_yield();
	}
}

void *test_B(void *arg){
	printf("A (arg: %p)\n", arg);
}


int main(){
	green_t g0, g1, g2;
	
	//int *retval_b;
	
	int a0 = 0;
	int a1 = 1;

	green_create(&g0, test, &a0);
	green_create(&g1, test, &a1);
	green_create(&g2, test, &a1);
	
	green_join(&g0, NULL);
	green_join(&g1, NULL);
	green_join(&g2, NULL);
	
	
	printf("Done with everything!\n");
	
	return 0;
}
