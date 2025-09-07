#include <stdio.h>

void addressCalculationSort(int arr[], int n) {
    int addr[n];  // Address array to store indices
    int i, j, temp;

    // Initialize the address array with indices
    for (i = 0; i < n; i++) {
        addr[i] = i;
    }

    // Sort the address array based on the values in arr
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[addr[i]] > arr[addr[j]]) {
                // Swap indices in addr array
                temp = addr[i];
                addr[i] = addr[j];
                addr[j] = temp;
            }
        }
    }

    // Print the sorted array using the address array
    printf("Sorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[addr[i]]);
    }
    printf("\n");
}

int main() {
    int arr[] = {50, 20, 40, 10, 30};
    int n = sizeof(arr) / sizeof(arr[0]);

    addressCalculationSort(arr, n);

    return 0;
}
