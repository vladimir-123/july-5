#include "vector_algorithms.h"

std::vector<int> GenerateMyRandomVector(size_t fSize, int fMin, int fMax) {
    std::vector<int> randVector(fSize);
    std::random_device rd;
    for (int i = 0; i < fSize; ++i) {
        randVector[i] = rd() % (1 + fMax - fMin) + fMin;
    }
    return randVector;
}

std::ostream& operator<< (std::ostream& os, const std::vector<int>& v) { // отобразить вектор
    os << '[';
    for (int i = 0; i < v.size(); ++i)
    {
        if (i < v.size() - 1) {
            os << v[i] << ", ";
        } else {
            os << v[i] << ']';
        }
    }
    return os;
}

int LinearSearch(const std::vector<int>& numbers, int value) { // поиск значения
    for (int i = 0; i < numbers.size(); ++i) {
        if (numbers[i] == value) {
            return i;
        }
    }
    return -1;
}

void BubbleSortDescending(std::vector<int>& fVector) {
    for (int i = 0; i < fVector.size() - 1; ++i) {
        if (fVector[i] > fVector[i + 1]) {
            std::swap(fVector[i], fVector[i + 1]);
            i = -1; 
        }
    }
}

void BubbleSortAscending(std::vector<int>& fVector) {
    for (int i = 0; i < fVector.size() - 1; ++i) {
        if (fVector[i] < fVector[i + 1]) {
            std::swap(fVector[i], fVector[i + 1]);
            i = -1; 
        }
    }
}

bool CheckSortDescending(const std::vector<int>& fVector) {
    for (int i = 0; i < fVector.size() - 1; ++i) { 
        if (fVector[i] > fVector[i + 1]) {
            return false;
        }
    }
    return true;
}

int BinarySearch(const std::vector<int>& numbers, int value) {
    int max = numbers.size();
    int min = 0;
    int guess = numbers.size()/2;
    int range;

    if (numbers[guess] == value) { return guess; } 

    while(range > 1) { 
        bool less = value < numbers[guess];
        if (less) {
            max = guess;
            range = max - min;
            guess = min + range / 2;
        } else {
            min = guess;
            range = max - min;
            guess += range / 2;
        }

        if (numbers[guess] == value) {
            while (numbers[guess] == numbers[guess - 1]) {
                guess -= 1;
            }
            return guess;
        }
    } 
    return -1;
} 









