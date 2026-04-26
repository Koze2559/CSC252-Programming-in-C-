#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Return true if the array values[0..size-1] is sorted in non-decreasing order.
bool is_increasing(int* values, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (values[i + 1] < values[i])
        {
            return false;
        }
    }

    return true;
}

// Merge two sorted halves of values into a single sorted sequence.
// The left half is values[left..middle] and the right half is values[middle+1..right].
void merge(int* values, int left, int middle, int right)
{
    int left_size = middle - left + 1;
    int right_size = right - middle;

    int* left_array = new int[left_size];
    int* right_array = new int[right_size];

    // Copy the left half into a temporary array.
    for (int i = 0; i < left_size; i++)
    {
        left_array[i] = values[left + i];
    }

    // Copy the right half into a temporary array.
    for (int i = 0; i < right_size; i++)
    {
        right_array[i] = values[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < left_size && j < right_size)
    {
        if (left_array[i] <= right_array[j])
        {
            values[k] = left_array[i];
            i++;
        }
        else
        {
            values[k] = right_array[j];
            j++;
        }

        k++;
    }

    while (i < left_size)
    {
        values[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        values[k] = right_array[j];
        j++;
        k++;
    }

    delete[] left_array;
    delete[] right_array;
}

// Recursive merge sort that splits the array and sorts each half.
void merge_sort_recursive(int* values, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int middle = left + (right - left) / 2;

    merge_sort_recursive(values, left, middle);
    merge_sort_recursive(values, middle + 1, right);

    merge(values, left, middle, right);
}

// Public entry point for merge sort using the full array size.
void merge_sort(int* values, int size)
{
    merge_sort_recursive(values, 0, size - 1);
}

// Print all array elements separated by spaces.
void print_array(int* values, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << values[i] << " ";
    }

    cout << endl;
}

int main()
{
    const int SIZE = 100;
    int values[SIZE];

    // Seed the random number generator so the values differ each run.
    srand(time(0));

    // Fill the array with random numbers from 0 to 999.
    for (int i = 0; i < SIZE; i++)
    {
        values[i] = rand() % 1000;
    }

    cout << "Original array:" << endl;
    print_array(values, SIZE);

    cout << endl;
    cout << "Is array increasing before sorting? ";

    if (is_increasing(values, SIZE))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    merge_sort(values, SIZE);

    cout << endl;
    cout << "Sorted array:" << endl;
    print_array(values, SIZE);

    cout << endl;
    cout << "Is array increasing after sorting? ";

    if (is_increasing(values, SIZE))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    return 0;
}