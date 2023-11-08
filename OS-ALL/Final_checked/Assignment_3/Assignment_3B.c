#include <stdio.h>
#include <stdbool.h>

struct Process
{
	int pid;
	int arrival_time;
	int burst_time;
	int completion_time, turnaround_time, waiting_time, response_time, start_time;
	int remaining_time;
} processes[100];

int findMax(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int n, index;
	int cpu_utilization;
	bool visited[100] = {false};
	int current_time = 0;
	int max_completion_time;
	int completed = 0;
	int time_quantum;
	int total_idle_time = 0;
	int cycle_length;

	printf("Enter the total number of processes: ");
	scanf("%d", &n);
	int queue[100], front = -1, rear = -1;
	float sum_turnaround_time = 0, sum_waiting_time = 0, sum_response_time = 0;

	for (int i = 0; i < n; i++)
	{
		printf("Enter Arrival Time for Process %d: ", i);
		scanf("%d", &processes[i].arrival_time);
		processes[i].pid = i;
	}

	for (int i = 0; i < n; i++)
	{
		printf("Enter Burst Time for Process %d: ", i);
		scanf("%d", &processes[i].burst_time);
		processes[i].remaining_time = processes[i].burst_time;
	}

	printf("Enter time quantum: ");
	scanf("%d", &time_quantum);

	// Initialize the queue with the first process
	front = rear = 0;
	queue[rear] = 0;
	visited[0] = true;

	while (completed != n)
	{
		index = queue[front];
		front++;

		if (processes[index].remaining_time == processes[index].burst_time)
		{
			processes[index].start_time = findMax(current_time, processes[index].arrival_time);
			total_idle_time += (current_time == 0) ? 0 : processes[index].start_time - current_time;
			current_time = processes[index].start_time;
		}

		if (processes[index].remaining_time - time_quantum > 0)
		{
			processes[index].remaining_time -= time_quantum;
			current_time += time_quantum;
		}
		else
		{
			current_time += processes[index].remaining_time;
			processes[index].remaining_time = 0;
			completed++;

			processes[index].completion_time = current_time;
			processes[index].turnaround_time = processes[index].completion_time - processes[index].arrival_time;
			processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
			processes[index].response_time = processes[index].start_time - processes[index].arrival_time;

			sum_turnaround_time += processes[index].turnaround_time;
			sum_waiting_time += processes[index].waiting_time;
			sum_response_time += processes[index].response_time;
		}

		// Check which new processes need to be pushed to the ready queue from the input list
		for (int i = 1; i < n; i++)
		{
			if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time && !visited[i])
			{
				rear++;
				queue[rear] = i;
				visited[i] = true;
			}
		}

		// Check if the process on the CPU needs to be pushed back to the ready queue
		if (processes[index].remaining_time > 0)
		{
			rear++;
			queue[rear] = index;
		}

		// If the queue is empty, add one process from the list with remaining burst time > 0
		if (front > rear)
		{
			for (int i = 1; i < n; i++)
			{
				if (processes[i].remaining_time > 0)
				{
					rear++;
					queue[rear] = i;
					visited[i] = true;
					break;
				}
			}
		}
	}

	// Calculate the length of the process completion cycle
	max_completion_time = 1e-9;

	for (int i = 0; i < n; i++)
		max_completion_time = findMax(max_completion_time, processes[i].completion_time);

	cycle_length = max_completion_time - processes[0].arrival_time;

	cpu_utilization = (float)(cycle_length - total_idle_time) / cycle_length;

	// Output
	printf("\nProcess No.\tAT\tBurst Time\tStart Time\tCT\tTAT\tWT\tRT\n");
	for (int i = 0; i < n; i++)
		printf("%d\t\t%d\t%d\t\t%d\t\t%d\t%d\t%d\t%d\n", i, processes[i].arrival_time, processes[i].burst_time, processes[i].start_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time, processes[i].response_time);
	printf("\n");

	printf("\nAverage Turnaround time = %.2f", (float)sum_turnaround_time / n);
	printf("\nAverage Waiting Time = %.2f", (float)sum_waiting_time / n);
	printf("\nAverage Response Time = %.2f", (float)sum_response_time / n);
	printf("\nThroughput = %.2f", n / (float)cycle_length);
	printf("\nCPU Utilization (Percentage) = %.2f", cpu_utilization * 100);

	return 0;
}
