#ifndef SEARCH_H
#define SEARCH_H
#include <vector>

int linear_search(const std::vector<int>& arr, int a);
int linear_barrier_search(std::vector<int>& arr, int a);
int binary_search(std::vector<int>& arr, int a);
int sorted_linear_search(std::vector<int>& arr, int a);

#endif //SEARCH_H