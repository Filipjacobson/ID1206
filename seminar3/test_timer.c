#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "green.h"

int flag = 0;
green_cond_t cond;

int fib(int num){
	if (num <= 1){
		return num;
	} else {
		return fib(num - 1) + fib(num - 2);
	}
}


void *test(void *arg){
	int id = *(int*)arg;
	int loop = 4;
	while(loop > 0){
		if(flag == id){
			printf("thread %d: %d\n", id, loop);
			loop--;
			flag = (id + 1) % 2;
			int f = fib(30);
			printf("fib(30) = %i\n", f);
			printf("->>signaling\n\n");
			green_cond_signal(&cond);
		} else {
			printf("->>waiting\n\n");
			green_cond_wait(&cond, NULL);
		}
	}
}



int main(){

	green_cond_init(&cond);
	
	green_t g0, g1, g2;
	
	int a0 = 0;
	int a1 = 1;
	//int a2 = 2;
	
	green_cond_init(&cond);

	green_create(&g0, test, &a0);
	green_create(&g1, test, &a1);
	//green_create(&g2, test, &a2);
	
	green_join(&g0, NULL);
	green_join(&g1, NULL);
	//green_join(&g2, NULL);
	
	printf("Done with everything!\n");
	
	return 0;
}
