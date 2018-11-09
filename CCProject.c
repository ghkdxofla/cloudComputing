// gcc -o CCProject CCProject.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

FILE * fp = NULL;

void* save_xentop(void* n){
	fp = popen("xentop -b -d 1", "r");
	while(1){
		//Do nothing
	}
	pclose(fp);
}

void* print_xentop(void* n){
	char line[10240]; // 10240

	while(1){
		while(fp == NULL){
			//Do nothing
		}
		while(fgets(line, 10240, fp) != NULL){
			printf("%s", line);
		}
	}
}

int main(int argc, char *argv[]){
	printf("--PROGRAM START--\n");
	
	pthread_t p_thread[2];
	pthread_create(&p_thread[0], NULL, save_xentop, NULL);
	pthread_create(&p_thread[1], NULL, print_xentop, NULL);
	
	pthread_join(p_thread[0], NULL);
	pthread_join(p_thread[1], NULL);

	return 0;
  
}
