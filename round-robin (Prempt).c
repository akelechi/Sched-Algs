
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void sortProcessesByArrivalTime(int n);
void GanttChart();
//Create a struct to be like a container for the individual processes.
//unsigned integers are only utilized because they dont include the negative integer values and we expect the process' properties to be positives

struct Process {
	unsigned int id;
	unsigned int arrivalTime;
	unsigned int burstTime;
	unsigned int responseTime;
	bool entered;
	
};

//Create an array able to hold 26 processes since the number of processes is less than 25

struct Process process[26];
int  totalBurstTime = 0, number, temp[26], tQuantum, switches = 0;
unsigned int t_width = 3;

FILE *f;

void printGCStart() {
	int i;
	fprintf(f, " --");
	for (i = 1; i < totalBurstTime; i++) {
		fprintf(f, "---");
	}
	fprintf(f, "\n|");
}

void printGCEnd() {
	int i;
	fprintf(f, "\n");
	for (i = 0; i < totalBurstTime; i++) {
		fprintf(f, "|--");
	}
	fprintf(f, "|\n");
	for (i = 0; i <= totalBurstTime; i++) {
		fprintf(f, "%-*u", t_width, i);
	}
	fprintf(f, "\n\n");
}

int main() {
	//Create the file for the storing the output
	f = fopen("output.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}


	int i, total = 0, x, counter = 0;
	int waitTime = 0, turnaroundTime = 0;
	float avWaitTime, avTurnaroundTime;
	printf("\nEnter Total Number of Processes:\t");
	scanf("%d", &number);
	x = number;
	for (i = 0; i < number; i++)
	{
		printf("\nEnter Details of Process[%d]\n", i + 1);
		printf("ID:\t");
		scanf("%d", &process[i].id);
		printf("Arrival Time:\t");
		scanf("%d", &process[i].arrivalTime);
		printf("Burst Time:\t");
		scanf("%d", &process[i].burstTime);
		temp[i] = process[i].burstTime;
		totalBurstTime += temp[i];
	}

	sortProcessesByArrivalTime(number);
	printf("\nEnter Time Quantum:\t");
	scanf("%d", &tQuantum);
	fprintf(f, "\nProcess\t|Turnaround Time| Waiting Time | Response Time | Completion Time");
	fprintf(f, "\n+-------+---------------+----------------+------------+----------------");
	for (total = 0, i = 0; x != 0;)
	{
		switches++;
		//checks flag to see if it has visited queue , else current length of execution equals the response time 
		if (process[i].entered == false) {

			process[i].responseTime = total;
			process[i].entered = true;
		}
		
		//when process is in its final stage of execution
		if (temp[i] <= tQuantum && temp[i] > 0)
		{
			total = total + temp[i];
			temp[i] = 0;
			counter = 1;
		}

		//When the temp[i] value is greater than the time quantum
		else if (temp[i] > 0)
		{
			temp[i] = temp[i] - tQuantum;
			total = total + tQuantum;
		}
		//Once process executes completely
		if (temp[i] == 0 && counter == 1)
		{
			x--;//Decrement the counter. i.e. x processes are still in execution
			fprintf(f, "\nP[%u]\t|\t%d\t|\t%d\t|\t%d\t|\t%d", process[i].id, total - process[i].arrivalTime, total - process[i].burstTime - process[i].arrivalTime, process[i].responseTime, total);
			waitTime = waitTime + total - process[i].arrivalTime - process[i].burstTime;
			turnaroundTime = turnaroundTime + total - process[i].arrivalTime;
			counter = 0;
		}
		//Make sure it restarts from the beginning, in a linear fashion of execution without going out of index
		if (i == number - 1)
		{
			i = 0;
		}
		//Move to the next process if it is yet waiting to be executed
		else if (process[i + 1].arrivalTime <= total)
		{
			i++;
		}
		//Else go to the beginning and continue in a round
		else
		{
			i = 0;
		}
	}
	avWaitTime = waitTime * 1.0 / number;
	avTurnaroundTime = turnaroundTime * 1.0 / number;
	fprintf(f,"\n\nAverage Waiting Time:\t%f", avWaitTime);
	fprintf(f,"\nAvg Turnaround Time:\t%f\n", avTurnaroundTime);


	GanttChart();




	//Close the file that was opened before
	fclose(f);

	printf("\nYou output has been successful written to the file output.txt");
	return 0;
}
	
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

void GanttChart() {

	fprintf(f, "\n\nGANTT CHART\n\n");
	printGCStart();

	int i, total = 0, x, y, counter = 0;
	//reset variables
	for (i = 0; i < number; i++)
	{
		temp[i] = process[i].burstTime;

	}
	for (total = 0, i = 0; x != 0; )
	{


		//when process is in its final stage of execution
		if (temp[i] <= tQuantum && temp[i] > 0)
		{
			total = total + temp[i];

			y = temp[i] * t_width;
			fprintf(f, "%*u", y - (y / 2), process[i].id);
			fprintf(f, "%*c", y / 2, '|');
			temp[i] = 0;
			counter = 1;
			
		}

		//When the temp[i] value is greater than the time quantum
		else if (temp[i] > 0)
		{
			y = tQuantum* t_width;
			fprintf(f, "%*u", y - (y / 2), process[i].id);
			fprintf(f, "%*c", y / 2, '|');
			temp[i] = temp[i] - tQuantum;
			total = total + tQuantum;
			
		}
		//Once process executes completely
		if (temp[i] == 0 && counter == 1)
		{
			x--;   //Decrement the counter. i.e. x processes are still in execution
			counter = 0;
		}
		//Make sure it restarts from the beginning, in a linear fashion of execution without going out of index
		if (i == number - 1)
		{
			i = 0;
		}
		//Move to the next process if it is yet waiting to be executed
		else if (process[i + 1].arrivalTime <= total)
		{
			i++;
		}
		//Else go to the beginning and continue in a round
		else
		{
			i = 0;
		}
		
		
	}
	
	printGCEnd();

	fprintf(f, "\n\nNumber of context switches: %d\n", switches);
}

