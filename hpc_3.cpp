#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    // User Input
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int sum = 0;
    int minVal = arr[0];
    int maxVal = arr[0];

    // Parallel Sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    // Parallel Minimum
    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < minVal)
        {
            minVal = arr[i];
        }
    }

    // Parallel Maximum
    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
    }

    float avg = (float)sum / n;

    // Output
    cout << "\nSum = " << sum << endl;
    cout << "Minimum = " << minVal << endl;
    cout << "Maximum = " << maxVal << endl;
    cout << "Average = " << avg << endl;

    return 0;
}