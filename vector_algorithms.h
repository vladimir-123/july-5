#pragma once

#include <iostream>
#include <cstdlib> // rand, NULL
#include <vector>
#include <ctime> // time
#include <random>
#include <cmath>
#include <utility>

void CheckEmpty(int fSize);
std::vector<int> GenerateMyRandomVector(size_t fSize, int fMin, int fMax);
std::ostream& operator<< (std::ostream& os, const std::vector<int>& v);
int LinearSearch(const std::vector<int>& numbers, int value);
int BinarySearch(const std::vector<int>& numbers, const int value);
void BubbleSortDescending(std::vector<int>& fVector);
void BubbleSortAscending(std::vector<int>& fVector);
bool CheckSortDescending(const std::vector<int>& fVector);