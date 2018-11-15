// gcc -o CCProject CCProject.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Load xentop command line into file pointer
FILE * fp = NULL;
char check_name[20];

// CpuState
typedef struct _CpuState{
	char name[10];
	char state[8];
	int cpu_time;
	int vcpu_num;
	double cpu_usage;
} CpuState;

void print_time();
void* open_xentop(void*);
void* print_xentop(void*);
void dvam_xentop();

int main(int argc, char *argv[]){
	printf("--PROGRAM START--\n");
	
	pthread_t p_thread[2];
	pthread_create(&p_thread[0], NULL, open_xentop, NULL);
	pthread_create(&p_thread[1], NULL, print_xentop, NULL);
	
	pthread_join(p_thread[0], NULL);
	pthread_join(p_thread[1], NULL);

	return 0;
  
}

// Print time
void print_time(){
	time_t timer;
	struct tm *t;
	char* day_kor[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	
	
	timer = time(NULL);
	t = localtime(&timer);
	
	printf("=======================================\n");
	printf("[time] %d-%d-%d (%s) %d:%d:%d\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, day_kor[t->tm_wday], t->tm_hour, t->tm_min, t->tm_sec);
}

// Change vcpu with DVAM
void change_xentop(CpuState cpu_state){
	int new_vcpu = 0;
	char cmd[10240] = "xl vcpu-set ";
	strcat(cmd, cpu_state.name);
	// Change the number of VCPUs using CPU usage
	// 190% ~ 270% --> 3 VCPUs
	if(strcmp(cpu_state.state, "-----r") == 0 || strcmp(cpu_state.state, "------") == 0){
		if(cpu_state.cpu_usage <= 101.0 && cpu_state.vcpu_num != 1){
			strcat(cmd, " 1");
			new_vcpu = 1;
			system(cmd);
			printf("[DVAM] %s --> %d\n", cpu_state.name, new_vcpu);
		}
		else if(cpu_state.cpu_usage <= 190.0 && cpu_state.cpu_usage > 101.0 && cpu_state.vcpu_num != 2){
			strcat(cmd, " 2");
			new_vcpu = 2;
			system(cmd);
			printf("[DVAM] %s --> %d\n", cpu_state.name, new_vcpu);
		}
		else if(cpu_state.cpu_usage <= 270.0 && cpu_state.cpu_usage > 190.0 && cpu_state.vcpu_num != 3){
			strcat(cmd, " 3");
			new_vcpu = 3;
			system(cmd);
			printf("[DVAM] %s --> %d\n", cpu_state.name, new_vcpu);
		}
		else if(cpu_state.cpu_usage > 270.0 && cpu_state.vcpu_num != 4){
			strcat(cmd, " 4");
			new_vcpu = 4;
			system(cmd);
			printf("[DVAM] %s --> %d\n", cpu_state.name, new_vcpu);		
		}
	}
	else{
		strcat(cmd, " 2");
		//printf("%s\n", cmd);
		system(cmd);
	}
}

// Read xentop batch(using thread)
void* open_xentop(void* n){
	fp = popen("xentop -b -d 1 -v", "r");
	while(1){
		//Do nothing
	}
	pclose(fp);
}

// Print xentop info
void* print_xentop(void* n){
	// xentop info
	char line[10240];
	char line_count[10240]; // for counting VMs
	int init_count = -1;
	int vpm_count = -1; // VM count
	int vcpu_count = -1; // VCPU count
	int vcpu_num = 0; // Current the number of VCPUs
	FILE* fp_count = NULL;
	char null_string[100];

	// string array for pvm
	CpuState* vpm_list; // VM list
	
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
				// Init counts
				init_count = -1;
				vcpu_count = -1;
				// for counting the number of VMs
				fp_count = popen("xl vm-list", "r");
				while(fgets(line_count, 10240, fp_count) != NULL){
					init_count++;
				}
				vpm_list = malloc(init_count * sizeof(CpuState));
				
				// Print time
				print_time();
				vpm_count = 0;
			}
			
			else if(strcmp(check_name, "Domain-0") == 0){
				// do nothing
			}
			
			else if(strcmp(check_name, "VCPUs(sec):") == 0){
			    vcpu_count++;
			    vcpu_num = 0;
				if(vcpu_count > 0){
					char* ptr;
					ptr = strtok(line, " ");
					while(ptr = strtok(NULL, " ")){
						//printf("%s\n", ptr);
						vcpu_num++;
					}
					vcpu_num /= 2;
					// Save current VCPUs
					cpu_state.vcpu_num = vcpu_num;
					
					// Print CPU state
					printf("[VM] %s %s %d %.1lf %d\n", cpu_state.name, cpu_state.state, cpu_state.cpu_time, cpu_state.cpu_usage, cpu_state.vcpu_num);
			
					// vpm into vpm_list
					vpm_list[vpm_count] = cpu_state;
			
					vpm_count++;
					
					// All of VM's CPU state is listed
					if(vpm_count == init_count){
						for(int i = 0;i < init_count;i++){
							change_xentop(vpm_list[i]);
						}
				
						printf("[VM count] : %d\n", vpm_count);
						free(vpm_list);
					}
				}
			}

			else{
				// Set CPU state
				sscanf(line, "%s %s %d %lf %s %s %s %s %s", cpu_state.name, cpu_state.state, &cpu_state.cpu_time, &cpu_state.cpu_usage, null_string, null_string, null_string, null_string, null_string);
			}
		}
		
	}
}
