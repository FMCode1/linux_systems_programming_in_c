#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main(int argc, char *argv[])
{
    int *array;       // Pointer to dynamically allocated array
    int max = -9999;  // Variable to store the maximum value
    int size = 0;     // Size of the array

    // Prompt the user for the array size
    printf("How big is the array? ");
    scanf("%i", &size);

    // Allocate memory for the array using calloc (initialized to 0)
    array = (int *) calloc(size, sizeof(int));
    if (array == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize the array with random values
    if (initialize(array, size) != 0)
    {
        printf("Initialization error\n");
        free(array);
        exit(1);
    }

    // Find the maximum value in the array
    if (findMax(array, size, &max) != 0)
    {
        printf("Error finding maximum value\n");
        free(array);
        exit(1);
    }

    // Print the maximum value
    printf("The max value in the array is: %d\n", max);

    // Free allocated memory and exit
    free(array);
    exit(0);
}