// gcc -o CCProject CCProject.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Load xentop command line into file pointer
FILE * fp = NULL;
char check_name[20];

typedef struct _CpuState{
	char name[10];
	char state[8];
	int cpu_time;
	double cpu_usage;
} CpuState;

void* save_xentop(void* n){
	fp = popen("xentop -b -d 1", "r");
	while(1){
		//Do nothing
	}
	pclose(fp);
}

void print_time(){
	time_t timer;
	struct tm *t;
	char* day_kor[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	
	
	timer = time(NULL);
	t = localtime(&timer);
	
	printf("=======================================\n");
	printf("[time] %d-%d-%d (%s) %d:%d:%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, day_kor[t->tm_wday], t->tm_hour, t->tm_min, t->tm_sec);
}

void* print_xentop(void* n){
	// xentop info
	char line[10240];
	int vpm_count = -1;
	CpuState cpu_state;
	
	while(1){
		while(fp == NULL){
			//Do nothing
		}
		while(fgets(line, 10240, fp) != NULL){
			//printf("%s", line);
			
			memset(check_name, 0, sizeof(check_name));
			sscanf(line, "%s", check_name);
			if(strcmp(check_name, "NAME") == 0){
				if(vpm_count != -1) 
					printf("[VM count] : %d\n", ++vpm_count);
				print_time();
				vpm_count = 0;
				continue;
			}
			
			else if(strcmp(check_name, "Domain-0") == 0) continue;

			sscanf(line, "%s %s %d %lf", cpu_state.name, cpu_state.state, &cpu_state.cpu_time, &cpu_state.cpu_usage);
			printf("[VM] %s %s %d %.1lf\n", cpu_state.name, cpu_state.state, cpu_state.cpu_time, cpu_state.cpu_usage);
			vpm_count++;
			
			
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
