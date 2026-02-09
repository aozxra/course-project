#include <iostream>
#include <vector>
#include <iomanip>

#include <chrono>
#include "sorts.h"

using namespace std;

void selection_sort(vector<int>& arr)
{   
    unsigned long long int swaps = 0;
    unsigned long long int compares = 0;
    auto start = chrono::high_resolution_clock::now();
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
            compares += 2;
        }
        if (min_idx != i)
        {
            swap(arr[i],arr[min_idx]);
            swaps += 1;
        }
        compares += 2;
        if (n <= 15)
        {
            cout <<"[Info] " <<i+1 << ". ";
            for(int k = 0; k < n; k++)
            {
                cout << arr[k] << " ";
            }
            cout << endl;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    seconds *= 1e-9;
    cout << "[Info] Number of permutations: " << swaps << endl;
    cout << "[Info] Number of comparisons: " << compares << endl;
    if (n > 15)
    {
        cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds"<< endl;
    }
    
}

void shell_sort(vector<int>& arr)
{
    unsigned long long int swaps = 0;
    unsigned long long int compares = 0;
    auto start = chrono::high_resolution_clock::now();
    int n = arr.size();
    int gap = n / 2;
    int numb = 0;
    while(gap > 0)
    {
        for (int i = gap; i < n; i++)
        {
            numb++;
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j-gap];
                j -= gap;
                compares += 2;
            }
            arr[j] = temp;
            if (n <= 15)
            {
                cout <<"[Info] " << numb << ". ";
                for(int k = 0; k < n; k++)
                {
                    cout << arr[k] << " ";
                }
                cout << endl;
            }
            swaps += 1;
            compares += 1;
            
        }
        gap /= 2;
        compares += 1;
    }
    auto end = chrono::high_resolution_clock::now();
    double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    seconds *= 1e-9;
    cout << "[Info] Number of permutations: " << swaps << endl;
    cout << "[Info] Number of comparisons: " << compares << endl;
    if (n > 15)
    {
        cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds" << endl;
    }
}
