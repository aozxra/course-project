#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include "searches.h"
#include <algorithm>

using namespace std;

struct element
{
    int value;
    int key;

    bool operator<(const element& a)
    {
        return (this->value < a.value);
    }
};

int linear_search(const vector<int>& arr, int a)
{
    unsigned long long int compares = 0;
    auto start = chrono::high_resolution_clock::now();
    
    int n = arr.size();
    int i = 0;
    for (i; i < n; i++)
    {
        compares += 2;
        if (arr[i] == a)
        {
            auto end = chrono::high_resolution_clock::now();
            double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            seconds *= 1e-9;
            cout << "[Info] Number of comparisons: " << compares << endl;
            cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds" << endl;
            return i;
        }
        
    } 
    auto end = chrono::high_resolution_clock::now();
    double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    seconds *= 1e-9;
    cout << "[Info] Number of comparisons: " << compares << endl;
    cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds" << endl;
    return -1;
}

int linear_barrier_search( vector<int>& arr, int a)
{
    unsigned long long int compares = 0;
    auto start = chrono::high_resolution_clock::now();
    int i = 0;
    int n = arr.size();
    arr.push_back(a);
    while (arr[i] != a)
    {
        i = i + 1;
        compares += 1;
    }
    if (i == n)
    {
        i = -1;
        compares += 1;
    }
    auto end = chrono::high_resolution_clock::now();
    double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    seconds *= 1e-9;
    cout << "[Info] Number of comparisons: " << compares << endl;
    cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds" << endl;
    return i;
}

int binary_search(vector<int>& arr_, int a)
{
    vector<element> arr = vector<element>(arr_.size());

    for (int i = 0; i < arr.size(); i++)
    {
        arr[i].value = arr_[i];
        arr[i].key = i;
    }
    sort(arr.begin(), arr.end());
    unsigned long long int compares = 0;
    auto start = chrono::high_resolution_clock::now();

    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        compares += 2;
        if (arr[middle].value == a)
        {
            auto end = chrono::high_resolution_clock::now();
            double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            seconds *= 1e-9;
            cout << "[Info] Number of comparisons: " << compares << endl;
            cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds" << endl;
            return arr[middle].key;
        }
        else if (arr[middle].value < a)
        {
            left = middle + 1;
        }
        else if (arr[middle].value > a)
        {
            right = middle - 1;   
        }
        compares += 2;
    }
    auto end = chrono::high_resolution_clock::now();
    double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    seconds *= 1e-9;
    cout << "[Info] Number of comparisons: " << compares << endl;
    cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds" << endl;
    return -1;

}


int sorted_linear_search(vector<int>& arr_, int a)
{
    vector<element> arr = vector<element>(arr_.size());

    for (int i = 0; i < arr.size(); i++)
    {
        arr[i].value = arr_[i];
        arr[i].key = i;
    }
    sort(arr.begin(),arr.end());
    unsigned long long int compares = 0;
    auto start = chrono::high_resolution_clock::now();
    int n = arr.size();
    int i = 0;
    for (i; i < n; i++)
    {
        compares += 2;
        if (arr[i].value == a)
        {
            auto end = chrono::high_resolution_clock::now();
            double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            seconds *= 1e-9;
            cout << "[Info] Number of comparisons: " << compares << endl;
            cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds" << endl;
            return arr[i].key;
        }
        
    }
    auto end = chrono::high_resolution_clock::now();
    double seconds = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    seconds *= 1e-9;
    cout << "[Info] Number of comparisons: " << compares << endl;
    cout << "[Info] Time spent by the algorithm: " << fixed << seconds << setprecision(7) << " seconds" << endl;
    return -1;
}
