#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

int main(){
	int i;

	int mutex = sem_init(1);
	int gsem = sem_init(2);
	int usem = sem_init(2);

	// Grad(mutex, gsem);
	//while(i<1){
		if(fork() == 0){
			Grad(mutex, gsem);
			UGrad(mutex, usem);
		}
		else{
			
		}
		//i++;
	//}

	sem_release(mutex);
	sem_release(gsem);
	sem_release(usem);
	return 0;
}


void UGrad(int mutex, int usem){
	int i = 0, k;
	while(i<1){ // change to run forever
		sem_down(mutex);
		printf("---Only Undergrads can eat\n");
		for(k=1; k<=2; k++){
			if(fork() == 0){
				UGradEat(usem, k);
			}
		}
		sem_up(mutex);
		printf("---Undergrads done eating\n");
		i++;
	}
	return;
}

void UGradEat(int usem, int k){
	sem_down(usem);
	printf("-------UGrad%d is eating...\n", k);
	sleep(5);
	sem_up(usem);
	printf("-------UGrad%d is done\n", k);
	return;
}

void Grad(int mutex, int gsem){
	int i = 0;
	while(i<1){ // change to run forever
		sem_down(mutex);
		int k;
		printf("+++Only grads can eat\n");
		for(k=1; k<=6; k++){
			if(fork() == 0)
				GradEat(gsem, k);
		}
		sem_up(mutex);	
		printf("+++Grads are done eating\n");
		i++;
	}
	return;
}

void GradEat(int gsem, int k){
	sem_down(gsem);
	printf("+++++++++++Grad%d is eating...\n", k);
	sleep(5);
	sem_up(gsem);
	printf("+++++++++++Grad%d is done\n", k);
	return;
}