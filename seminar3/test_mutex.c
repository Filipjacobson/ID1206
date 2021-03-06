#include <stdio.h>
#include <stdlib.h>
#include "green.h"
#include <unistd.h>

green_mutex_t mutex;

static int shared = 0;
int zero, one, two;

void *test(void *arg){
	int id = *(int*)arg;
	int loop = 10000;
	for(int i = 0; i < 100000; i++){
	
	}
	
	for(int i = 0; i < loop; i++){
		green_mutex_lock(&mutex);
		if(id == 0){
			zero++;
		} else if(id == 1){
			one++;
		} else {
			two++;
		}
		shared++;
		green_mutex_unlock(&mutex);
	}
	return NULL;
}



int main(){
	
	green_t g0, g1, g2;
	
	int a0 = 0;
	int a1 = 1;
	int a2 = 2;
	
	green_mutex_init(&mutex);

	green_create(&g0, test, &a0);
	green_create(&g1, test, &a1);
	green_create(&g2, test, &a2);
	
	green_join(&g0, NULL);
	green_join(&g1, NULL);
	green_join(&g2, NULL);
	
	printf("zero: %d \t one: %d \t two: %d\n", zero, one, two);
	printf("Total sum should be: %d\n", shared);
	
	printf("Done with everything!\n");
	
	return 0;
}
