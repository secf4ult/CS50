/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
            return true;
    }
    return false;
}

bool iterBiSearch(int value, int values[], int n)
{
    int mid, low = 0, high = n - 1;
    
    while(low <= high)
    {
        mid = (high + low) / 2;
        if(values[mid] == value)
            return true;
        else if(values[mid] > value)
            high = mid - 1;
        else if(values[mid] < value)
            low = mid + 1;
    }
    return false;
}

bool recurBiSearch(int value, int values[], int n)
{
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Selection Sort
    // TODO: implement an O(n^2) sorting algorithm
    int minIndex = 0, swap;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (values[j] < values[minIndex])
                minIndex = j;
        }
        swap = values[i];
        values[i] = values[minIndex];
        values[minIndex] = swap;
    }
    
    return;
}

void bubbleSort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int swap, counter = -1;
    while(counter != 0)
    {
        counter = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i + 1])
            {
                counter++;
                swap = values[i];
                values[i] = values[i + 1];
                values[i + 1] = swap;
            }
        }
        n--;
    }
    return;
}

void insertionsort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int element;
    for (int i = 1; i < n; i++)
    {
        element = values[i];
        int j = i;
        while (j > 0 && values[j - 1] > element)
        {
            values[j] = values[j - 1];
            j--;
        }
        values[j] = element;
    }
    
    return;
}

void mergeSort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
}