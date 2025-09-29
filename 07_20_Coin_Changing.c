#include <stdio.h>

// Function to implement Greedy Coin Change
void coinChange(int coins[], int n, int amount) {
    int count[50] = {0};  // To store count of each coin
    int i;

    printf("Coins used to make change for %d:\n", amount);

    for (i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            count[i]++;
        }
    }

    for (i = 0; i < n; i++) {
        if (count[i] != 0)
            printf("Coin %d: %d times\n", coins[i], count[i]);
    }
}

int main() {
    int n, amount, i;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter the coin denominations (in descending order):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter the amount to make change for: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}
OUTPUT:

Enter number of coin denominations: 6
Enter the coin denominations (in descending order):
2000 500 200 100 50 10
Enter the amount to make change for: 2890

Coins used to make change for 2890:
Coin 2000: 1 times
Coin 500: 1 times
Coin 200: 1 times
Coin 100: 1 times
Coin 50: 1 times
Coin 10: 4 times

