#include <stdio.h>

int maxProfit = 0; // Global variable to store max profit

// Backtracking function for 0/1 Knapsack
void knapsack(int W, int wt[], int val[], int n, int index, int currWeight, int currProfit) {
    // If weight exceeds capacity, return
    if (currWeight > W) 
        return;

    // Update maximum profit found so far
    if (currProfit > maxProfit) 
        maxProfit = currProfit;

    // If no more items left
    if (index == n) 
        return;

    // Choice 1: Include current item
    knapsack(W, wt, val, n, index + 1, currWeight + wt[index], currProfit + val[index]);

    // Choice 2: Exclude current item
    knapsack(W, wt, val, n, index + 1, currWeight, currProfit);
}

int main() {
    int n, W;
    
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    int val[n], wt[n];
    
    printf("Enter values of items:\n");
    for (int i = 0; i < n; i++) scanf("%d", &val[i]);
    
    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++) scanf("%d", &wt[i]);
    
    printf("Enter capacity of knapsack: ");
    scanf("%d", &W);
    
    knapsack(W, wt, val, n, 0, 0, 0);
    
    printf("Maximum profit = %d\n", maxProfit);
    
    return 0;
}

output::
Enter number of items: 4
Enter values of items:
60 100 120 90
Enter weights of items:
10 20 30 25
Enter capacity of knapsack: 50
Maximum profit = 220

