//December 10, 2018
//Process Scheduler

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//Create a struct to be like a container for the individual processes.
//unsigned integers are only utilized because they dont include the negative integer values and we expect the process' properties to be positives

 struct Process {
	unsigned int id;
	unsigned int arrivalTime;
	unsigned int burstTime;
	unsigned int remainingTime;
	unsigned int responseTime;
	bool done;
} ;

//Create an array able to hold 26 processes since the number of processes is less than 25

struct Process process[26];
int  totalBurstTime = 0, n, tQuantum;
unsigned int t_width = 3;

FILE *f;


void sortProcessesByArrivalTime(int n) {
	int i, j;
	//Creates a local variable to hold a process that is temporarily being swapped
	struct Process temp;
	
	for (i = 1; i < n; i++) {
		temp = process[i];
		//Swap two processes if the arrival time of the ordinal next is lower than the arrival time of the previous
		for (j = i; j > 0 && process[j - 1].arrivalTime <= temp.arrivalTime; j--) {
			process[j] = process[j - 1];
		}
		process[j] = temp;
	}
}

void printGCStart() {
	 int i;
	fprintf(f," --");
	for (i = 1; i < totalBurstTime; i++) {
		fprintf(f,"---");
	}
	fprintf(f,"\n|");
}

void printGCEnd() {
   int i;
	fprintf(f,"\n");
	for (i = 0; i < totalBurstTime; i++) {
		fprintf(f,"|--");
	}
	fprintf(f,"|\n");
	for (i = 0; i <= totalBurstTime; i++) {
		fprintf(f,"%-*u", t_width, i);
	}
	fprintf(f,"\n\n");
}

void scheduleProcesses(){



	int x, current, time = 0 , i, countCompleted = 0;
float avgWaitingTime = 0.0, avgTurnAroundTime = 0.0;
fprintf(f,"\nProcess\t|Turnaround Time| Waiting Time | Response Time | Completion Time");
fprintf(f, "\n+-------+---------------+----------------+------------+----------------");

process[25].remainingTime = 9999;



while (countCompleted != n)
{
	current = 25;

	for (i = 0; i < n; i++)
	{
		
		if (process[i].arrivalTime <= time  && process[i].remainingTime <= process[current].remainingTime && process[i].done == false) {

			current = i;
		}
		

	}
	

	//As long as the remaining time equals the burst time, the process is just beginning first execution.

	if (process[current].remainingTime == process[current].burstTime) {

		process[current].responseTime = time;
	}
	if (process[current].remainingTime > tQuantum) {
		process[current].remainingTime = process[current].remainingTime - tQuantum;
		time = tQuantum + time;
	}
	else
		//in the case when the remaining time is less than the quantum, this is the time of last execution
	{
		time = process[current].remainingTime + time;
		process[current].remainingTime = 0;
		process[current].done = true;
		countCompleted++;
		avgTurnAroundTime += (time - process[current].arrivalTime)/n;
		avgWaitingTime += avgTurnAroundTime - process[current].burstTime / n;
		fprintf(f,"\nP[%u]\t|\t%d\t|\t%d\t|\t%d\t|\t%d", process[current].id, time - process[current].arrivalTime, time - process[current].burstTime - process[current].arrivalTime, process[current].responseTime,time);
		fprintf(f, "\n+-------+---------------+----------------+------------+----------------");
	}

}
fprintf(f,"\nAverage Waiting Time: %f\n", avgWaitingTime);
fprintf(f,"Average Turnaround Time: %f\n", avgTurnAroundTime);


}

void GanttChart() {

	fprintf(f, "\n\nGANTT CHART\n\n");
	printGCStart();

	int x, current, time = 0, i, countCompleted = 0, previous, switches = 0;
	float avgWaitingTime = 0.0, avgTurnAroundTime = 0.0;

	process[25].remainingTime = 9999;

	//reset all the flags that got changed with the previous
	for (i = 0; i < n; i++)
	{

		process[i].done = false;
		process[i].remainingTime = process[i].burstTime;

	}


	while (countCompleted != n)
	{
		current = 25;

		for (i = 0; i < n; i++)
		{

			if (process[i].arrivalTime <= time  && process[i].remainingTime <= process[current].remainingTime && process[i].done == false) {

				current = i;
			}


		}
		//for counting context switches
		if (previous != current)
			switches++;

		previous = current;

		//As long as the remaining time equals the burst time, the process is just beginning first execution.

		if (process[current].remainingTime == process[current].burstTime) {

			process[current].responseTime = time;
		}
		if (process[current].remainingTime > tQuantum) {
			x = tQuantum* t_width;
			fprintf(f, "%*u", x - (x / 2), process[current].id);
			fprintf(f, "%*c", x / 2, '|');
			process[current].remainingTime = process[current].remainingTime - tQuantum;
			time = tQuantum + time;
		}
		else
			//in the case when the remaining time is less than the quantum, this is the time of last execution
		{
			x = process[current].remainingTime* t_width;
			fprintf(f, "%*u", x - (x / 2), process[current].id);
			fprintf(f, "%*c", x / 2, '|');
			time = process[current].remainingTime + time;
			process[current].remainingTime = 0;
			process[current].done = true;
			countCompleted++;
			
		}

	}
	fprintf(f, "\n\nNumber of context switches: %d\n", switches);
	printGCEnd();
}

int main()
{

	
	//Create file that would be used to store the output
	int i;
	f = fopen("output.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	printf("Enter no of Processes : ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		printf("\n");
		printf("Process %d:\n", i + 1);
		printf("  ID: ");
		scanf("%u", &process[i].id);
		printf("  Arrival Time: ");
		scanf("%u", &process[i].arrivalTime);
		printf("  Burst Time: ");
		scanf("%u", &process[i].burstTime);
		
		process[i].remainingTime = process[i].burstTime;
		process[i].done = false;
		//The total burst time accumulates each individual burst time .
		totalBurstTime += process[i].burstTime;
	}
	printf("\nNow enter the time quantum : ");
	scanf("%d", &tQuantum);

	sortProcessesByArrivalTime(n);
	
	scheduleProcesses();
	GanttChart();

	//Close the file that was opened before
	fclose(f);

	printf("\nYou output has been successful written to the file output.txt");

	return 0;
}