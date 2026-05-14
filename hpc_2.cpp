#include <iostream>
#include <omp.h>
#include <ctime>

using namespace std;

// -------------------- SEQUENTIAL BUBBLE SORT --------------------

void sequentialBubbleSort(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// -------------------- PARALLEL BUBBLE SORT --------------------

void parallelBubbleSort(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        #pragma omp parallel for
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// -------------------- MERGE FUNCTION --------------------

void merge(int arr[], int low, int mid, int high)
{
    int temp[1000];

    int left = low;
    int right = mid + 1;
    int k = 0;

    while(left <= mid && right <= high)
    {
        if(arr[left] < arr[right])
        {
            temp[k] = arr[left];
            left++;
        }
        else
        {
            temp[k] = arr[right];
            right++;
        }

        k++;
    }

    while(left <= mid)
    {
        temp[k] = arr[left];
        left++;
        k++;
    }

    while(right <= high)
    {
        temp[k] = arr[right];
        right++;
        k++;
    }

    for(int i = low; i <= high; i++)
    {
        arr[i] = temp[i - low];
    }
}

// -------------------- SEQUENTIAL MERGE SORT --------------------

void sequentialMergeSort(int arr[], int low, int high)
{
    if(low >= high)
        return;

    int mid = (low + high) / 2;

    sequentialMergeSort(arr, low, mid);

    sequentialMergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}

// -------------------- PARALLEL MERGE SORT --------------------

void parallelMergeSort(int arr[], int low, int high)
{
    if(low >= high)
        return;

    int mid = (low + high) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            parallelMergeSort(arr, low, mid);
        }

        #pragma omp section
        {
            parallelMergeSort(arr, mid + 1, high);
        }
    }

    merge(arr, low, mid, high);
}

// -------------------- PRINT ARRAY --------------------

void printArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

// -------------------- MAIN FUNCTION --------------------

int main()
{
    int n;

    cout << "Enter size of array: ";
    cin >> n;

    int arr1[100], arr2[100], arr3[100], arr4[100];

    cout << "Enter array elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> arr1[i];

        // Copy same data into all arrays
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
    }

    // -------------------- SEQUENTIAL BUBBLE SORT --------------------

    clock_t start = clock();

    sequentialBubbleSort(arr1, n);

    clock_t end = clock();

    double sequentialBubbleTime =
    double(end - start) / CLOCKS_PER_SEC;

    // -------------------- PARALLEL BUBBLE SORT --------------------

    start = clock();

    parallelBubbleSort(arr2, n);

    end = clock();

    double parallelBubbleTime =
    double(end - start) / CLOCKS_PER_SEC;

    // -------------------- SEQUENTIAL MERGE SORT --------------------

    start = clock();

    sequentialMergeSort(arr3, 0, n - 1);

    end = clock();

    double sequentialMergeTime =
    double(end - start) / CLOCKS_PER_SEC;

    // -------------------- PARALLEL MERGE SORT --------------------

    start = clock();

    parallelMergeSort(arr4, 0, n - 1);

    end = clock();

    double parallelMergeTime =
    double(end - start) / CLOCKS_PER_SEC;

    // -------------------- OUTPUT --------------------

    cout << "\nSequential Bubble Sort:\n";
    printArray(arr1, n);

    cout << "\nParallel Bubble Sort:\n";
    printArray(arr2, n);

    cout << "\nSequential Merge Sort:\n";
    printArray(arr3, n);

    cout << "\nParallel Merge Sort:\n";
    printArray(arr4, n);

    cout << "\nExecution Time:\n";

    cout << "Sequential Bubble Sort Time = "
         << sequentialBubbleTime
         << " seconds\n";

    cout << "Parallel Bubble Sort Time = "
         << parallelBubbleTime
         << " seconds\n";

    cout << "Sequential Merge Sort Time = "
         << sequentialMergeTime
         << " seconds\n";

    cout << "Parallel Merge Sort Time = "
         << parallelMergeTime
         << " seconds\n";

    return 0;
}