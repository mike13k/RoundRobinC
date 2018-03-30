#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Proc {
	int id;
	int arTime;
	int cpu;
	int rem;
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
int totalProcRunning = 0;
float avgWait = 0;
float avgTurn = 0;

FILE *fp = NULL;
FILE *fp2 = NULL;
fp = fopen("outputLottery.txt" ,"w");
fp2 = fopen("outputLottery" ,"w");
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
	(procReady[i]).arTime = atoi(splittedStringProc[1]);
	(procReady[i]).cpu = atoi(splittedStringProc[2]);
	(procReady[i]).rem = atoi(splittedStringProc[2]);
	(procReady[i]).numTickets = atoi(splittedStringProc[3]);
	i++;
}

totalProc = i;
totalProcRunning = i;

clock_t totalStart = clock();
srand(time(NULL));
while(totalProcRunning > 0) {
	
	int lotteryTicket = (rand() % tickets);
	int index;
	
	printf("lotteryTicket %d \n" , lotteryTicket);
	
	
	for(int x = 0; x < totalProcRunning; x++){
		
		if(procReady[x].numTickets < lotteryTicket){
			lotteryTicket = lotteryTicket - procReady[x].numTickets;
		}
		else{
			index = x;
			printf("X UPDATED \n");
			printf("__\n");
			x = totalProcRunning;
		}
	}
	printf("index %d \n" , index);

	if(totalProcRunning != 0) {
		char procLine[255] = "";
		char currentTime[255] = "" ;
		int procID = (procReady[index]).id;
		char procIDString[255];

	       	sprintf(currentTime, "%.f", ((((float)(clock() - totalStart))/CLOCKS_PER_SEC)*1000)); 
	       	sprintf(procIDString, "%d", procID);

		strcat(procLine, "Time ");
	       	strcat(procLine,currentTime);
	       	strcat(procLine,": P");
	       	strcat(procLine,procIDString);
	       	strcat(procLine," Entering quantum");

		fputs(procLine, fp);
		putc('\n', fp);
		fputs(procLine, fp2);
		putc('\n', fp2);
	}


	if(procReady[index].rem > quantum){

		clock_t startTime = clock();
	
		printf("enter loop1 \n");
		while( ((((float)(clock() - startTime))/CLOCKS_PER_SEC)*1000) != (quantum) ) {}
		printf("exit loop1 \n");
		procReady[index].rem -= quantum;
	}
	else{
		time_t startTime = clock();
		printf("enter loop2 \n");
		while( ((((float)(clock() - startTime))/CLOCKS_PER_SEC)*1000) != (procReady[index].rem) ) {}
		printf("exit loop2 \n");

		procReady[index].rem = 0;
		
		char procLine[255] = "";
		char currentTime[255] = "" ;
		int procID = (procReady[index]).id;
		char procIDString[255];
		char waitTimeString[255] = "";
		float waitTime = ((((float)(clock() - totalStart))/CLOCKS_PER_SEC)*1000) - (procReady[index].cpu);
		float turnTime = ((((float)(clock() - totalStart))/CLOCKS_PER_SEC)*1000);

	       	sprintf(currentTime, "%.f", turnTime);
	       	sprintf(procIDString, "%d", procID);
	       	sprintf(waitTimeString, "%.f", waitTime);

		strcat(procLine, "Time ");
		strcat(procLine,currentTime);
	       	strcat(procLine,": P");
	       	strcat(procLine,procIDString);
	       	strcat(procLine," Done Turn around: ");
		strcat(procLine,currentTime);
		strcat(procLine," Waiting time: ");
		strcat(procLine,waitTimeString);

		fputs(procLine, fp);
		putc('\n', fp);
		fputs(procLine, fp2);
		putc('\n', fp2);

		avgWait += waitTime;
		avgTurn +=  turnTime;
	}
	if(procReady[index].rem == 0){
	
		totalProcRunning -= 1;
		tickets = tickets - procReady[index].numTickets;
		for(int j = index; j<totalProcRunning; j++) {
			procReady[j] = procReady[j+1];
		}	
		
	}

}

putc('\n', fp);
putc('\n', fp2);
char avgWaitString[255] = "";
char avgTurnString[255] = "";

char waitLine[255] = "Average Waiting Time = ";
char turnLine[255] = "Average Turnaround Time = ";

sprintf(avgWaitString, "%f", (avgWait/totalProc));
sprintf(avgTurnString, "%f", (avgTurn/totalProc));

strcat(waitLine, avgWaitString);
strcat(turnLine, avgTurnString);

fputs(waitLine, fp);
putc('\n', fp);	
fputs(turnLine, fp);
putc('\n', fp);
fputs(waitLine, fp2);
putc('\n', fp2);	
fputs(turnLine, fp2);
putc('\n', fp2);	

if (fp != NULL) {
	fclose(fp);
}

if (fp2 != NULL) {
	fclose(fp2);
}

fclose(file);

if (line)
    free(line);

exit(EXIT_SUCCESS);

}
