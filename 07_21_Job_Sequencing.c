#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
typedef struct {
    char id;       // Job ID (A, B, C, ...)
    int deadline;  // Deadline of job
    int profit;    // Profit of job
} Job;

// Compare function for sorting jobs in descending order of profit
int compare(const void *a, const void *b) {
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;
    return j2->profit - j1->profit;  // descending by profit
}

// Function to find maximum deadline
int findMaxDeadline(Job jobs[], int n) {
    int max = jobs[0].deadline;
    for (int i = 1; i < n; i++) {
        if (jobs[i].deadline > max)
            max = jobs[i].deadline;
    }
    return max;
}

// Function to schedule jobs
void jobSequencing(Job jobs[], int n) {
    // Sort jobs by descending profit
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = findMaxDeadline(jobs, n);

    // Create array to store time slots
    int slot[maxDeadline + 1];
    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = -1; // -1 means empty slot

    int totalProfit = 0;

    printf("\nJob sequence selected: ");
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (starting from its deadline and moving backwards)
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i; // store job index in slot
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Print scheduled jobs
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != -1)
            printf("%c ", jobs[slot[i]].id);
    }

    printf("\nTotal Profit: %d\n", totalProfit);
}

int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];
    printf("Enter job details (ID Deadline Profit):\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobSequencing(jobs, n);

    return 0;
}

OUTPUT:
Enter number of jobs: 5
Enter job details (ID Deadline Profit):
A 2 100
B 1 19
C 2 27
D 1 25
E 3 15

Job sequence selected: C A E 
Total Profit: 142

