#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Proc {
	int id;
	int arTime;
	int cpu;
	int startTime;
	int endTime;
	int numTickets;
}procReady[10];

int main(){

FILE * file;
char * line = NULL;
size_t len = 0;
ssize_t read;
int quantum;
int tickets;
int totalProc = 0;

file = fopen("./Input1.in", "r");

if (file == NULL){
    exit(EXIT_FAILURE);
}

//read first 2 lines
if((read = getline(&line, &len, file)) != -1) {
	quantum = atoi(line);
}
if((read = getline(&line, &len, file)) != -1) {
	tickets = atoi(line);
}

int i = 0;
while ((read = getline(&line, &len, file)) != -1) {
	char * word = strtok (line, ",");
	char * splittedStringProc[4];
	int j = 0;
	while(word != NULL) {
		splittedStringProc[j++] = word;
		word = strtok (NULL, ",");
	}
	procReady[i].id = splittedStringProc[0];
	procReady[i].arTime = splittedStringProc[1];
	procReady[i].cpu = splittedStringProc[2];
	procReady[i].numTickets = splittedStringProc[3];
	i++;
}

totalProc = i;

while(i > 0) {
	
	if(procReady[0].cpu >= quantum){
		time_t startTime = clock();
		while(difftime(clock(), startTime) < (quantum*1000)) {}
		procReady[0].cpu -= quantum;
	}
	else{
		time_t startTime = clock();
		while(difftime(clock(), startTime) < (procReady[0].cpu*1000)) {}
		procReady[0].cpu = 0;
	}
	if(procReady[0].cpu != 0)
		procReady[i] = procReady[0];
	else
		i -= 1;

	for(int j = 0; j<i; j++) {
		procReady[j] = procReady[j+1];
	}
}

fclose(file);

if (line)
    free(line);

exit(EXIT_SUCCESS);

}
