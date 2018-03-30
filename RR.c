#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Proc {
	int id;
	int arTime;
	int cpu;
	int startTime;
	int endTime;
	int numTickets;
};



int main(){

struct Proc procReady[10];
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
	int * splittedStringProc[4];
	int j = 0;
	while(word != NULL) {
		splittedStringProc[j++] = word;
		word = strtok (NULL, ",");
	}
	(procReady[i]).id = atoi(splittedStringProc[0]);
	(procReady[i]).arTime = atoi(&splittedStringProc[1]);
	(procReady[i]).cpu = atoi(&splittedStringProc[2]);
	(procReady[i]).numTickets = atoi(&splittedStringProc[3]);

	printf("%d\n",(procReady[0]).id);
	printf("%d\n",(procReady[1]).id);
	printf("%d\n",(procReady[2]).id);
	printf("%d\n",(procReady[3]).id);
	printf("  \n");

	i++;
}

totalProc = i-1;

clock_t totalStart = clock();

while(totalProc > 0) {

	if(procReady[0].cpu >= quantum){

		clock_t startTime = clock();

		while( (((double)(clock() - startTime))*1000/CLOCKS_PER_SEC) < (quantum) ) {}
		procReady[0].cpu -= quantum;
	}
	else{
		time_t startTime = clock();
		while( (((double)(clock() - startTime))*1000/CLOCKS_PER_SEC) < (procReady[0].cpu) ) {}
		procReady[0].cpu = 0;
	}
	if(procReady[0].cpu != 0){
		procReady[totalProc] = procReady[0];
	}
	else{
		totalProc -= 1;
	}

	for(int j = 0; j<totalProc; j++) {
		procReady[j] = procReady[j+1];
	}

        FILE *fp = NULL;

        fp = fopen("outputRR.txt" ,"w");

	char * text = "Write this to the file";

        if (fp != NULL) {
		printf("hi2");
		fprintf(fp,"%s\n", text);
		fclose(fp);
	}

                
}

fclose(file);

if (line)
    free(line);

exit(EXIT_SUCCESS);

}
