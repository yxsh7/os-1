#include <stdio.h>
#include <stdbool.h>

struct Process
{
	int pid; // Process ID
	int at;  // Arrival Time
	int bt;  // Burst Time
	int ct, tt, wt, rt, st; // Completion Time, Turnaround Time, Waiting Time, Response Time, Start Time
};

int main()
{
	int num_processes = 0;
	printf("Enter the number of processes: ");
	scanf("%d", &num_processes);
	struct Process processes[num_processes];

	printf("\nEnter process details: \n");
	for (int i = 0; i < num_processes; ++i)
	{
		printf("Enter details for process %d: \n", i + 1);
		processes[i].pid = i + 1;

		printf("\tEnter Arrival Time: ");
		scanf("%d", &processes[i].at);

		printf("\tEnter Burst Time: ");
		scanf("%d", &processes[i].bt);
	}

	printf("\n================================\n");
	printf("PID\tAT \t BT\n");
	for (int i = 0; i < num_processes; i++)
	{
		printf("%d \t %d \t %d \n", processes[i].pid, processes[i].at, processes[i].bt);
	}
	printf("\n================================\n");

	// Input Done

	int n = num_processes;
	int completed = 0;
	int current_time = 0;
	int burst_times[n];
	bool is_completed[n];

	for (int i = 0; i < n; i++)
	{
		burst_times[i] = processes[i].bt;
		is_completed[i] = false;
	}

	float avg_wt = 0, avg_tt = 0, avg_rt = 0;

	while (completed != n)
	{
		int min_burst_time = 99999;
		int min_index = -1;

		// Find the process with the shortest remaining burst time
		for (int i = 0; i < n; i++)
		{
			if ((processes[i].at <= current_time) && !is_completed[i])
			{
				if (burst_times[i] < min_burst_time)
				{
					min_burst_time = burst_times[i];
					min_index = i;
				}
				else if (burst_times[i] == min_burst_time)
				{
					// In case of equal burst times, choose the one with the lower arrival time
					if (processes[i].at < processes[min_index].at)
					{
						min_index = i;
					}
				}
			}
		}

		if (min_index == -1)
		{
			current_time++;
		}
		else
		{
			// Update start time for the selected process
			if (burst_times[min_index] == processes[min_index].bt)
			{
				processes[min_index].st = current_time;
			}

			burst_times[min_index]--;
			current_time++;

			// If the process is completed, calculate various times and averages
			if (burst_times[min_index] == 0)
			{
				processes[min_index].ct = current_time;
				processes[min_index].tt = processes[min_index].ct - processes[min_index].at;
				processes[min_index].wt = processes[min_index].tt - processes[min_index].bt;
				processes[min_index].rt = processes[min_index].st - processes[min_index].at;

				avg_wt += processes[min_index].wt;
				avg_tt += processes[min_index].tt;
				avg_rt += processes[min_index].rt;

				completed++;
				is_completed[min_index] = true;
			}
		}
	}

	printf("PID \t AT \t BT \t CT \t TT \t WT \t RT \t\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d \t %d \t %d \t %d \t %d \t %d \t %d \t\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tt, processes[i].wt, processes[i].rt);
	}
	printf("\n================================\n");

	printf("\n AVG Waiting Time: %f", avg_wt / n);
	printf("\n AVG Turnaround Time: %f", avg_tt / n);
	printf("\n AVG Response Time: %f", avg_rt / n);
	printf("\n================================\n");
}




