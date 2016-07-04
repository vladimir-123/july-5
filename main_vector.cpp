#include "vector_algorithms.h"

static int notFound = -1;

static int getMin(const std::vector<int>& v) {
    int min = v[0];
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] < min) {
            min = v[i];
        }
    }
    return min;
}

static int getMax(const std::vector<int>& v) {
    int max = v[0];
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

static bool RandomValuesInRangeTest(size_t nTests) {
    
    int fSize = 25;
    std::random_device rd;
    int fMax = rd() % 10000;
    int fMin = rd() % 10000;

    if (fMin > fMax) {
        std::swap(fMin, fMax);
    }

    std::vector<int> temp;
    for (int i = 0; i < nTests; ++i) {
        temp = GenerateMyRandomVector(fSize, fMin, fMax);
        if (getMin(temp) >= fMin && getMax(temp) <= fMax) {
            continue;
        } else {
            std::cout << "range error\n";
            std::cout << "getMin(temp) == " << getMin(temp) << "\tfMin == " << fMin 
                        << "\ngetMax(temp) == " << getMax(temp) << "\tfMax == " << fMax << "\n";
            return false;
        }
    }
    return true;
}

static bool RandomValuesInOrderTest(size_t nTests) {
    
    int fSize = 5;
    std::random_device rd;
    int fMax = rd() % 10000;
    int fMin = rd() % 10000;

    if (fMin > fMax) {
        std::swap(fMin, fMax);
    }

    std::vector<int> temp;
    for (int i = 0; i < nTests; ++i) {
        temp = GenerateMyRandomVector(fSize, fMin, fMax);

        BubbleSortAscending(temp);
        /*if (i == (nTests - 1))
        {
            std::cout << temp << "\n";
        }*/

        BubbleSortDescending(temp);
        /*if (i == (nTests - 1))
        {
            std::cout << temp << "\n";
        }*/

        if (CheckSortDescending(temp)) {
            continue;
        } else {
            std::cout << "sort error\n";
            std::cout << temp << "\n";
            return false;
        }
    }
    return true;
}

static bool RandomValuesSearchTest(size_t nTests) {
    
    int fSize = 10;
    std::random_device rd;
    int fMax = rd() % 10000;
    int fMin = rd() % 10000;

    if (fMin > fMax) {
        std::swap(fMin, fMax);
    }

    std::vector<int> temp;
    for (int i = 0; i < nTests; ++i) {
        temp = GenerateMyRandomVector(fSize, fMin, fMax);
        
        int searchIndex = rd() % temp.size();
        if (temp[LinearSearch(temp, temp[searchIndex])] != temp[searchIndex] &&
                temp[BinarySearch(temp, temp[searchIndex])] != temp[searchIndex]) {
            std::cout << "LinearSearch error with existing value\n";
            return false;
        }

        if (LinearSearch(temp, (fMax + 1)) != notFound &&
                BinarySearch(temp, (fMax + 1)) != notFound) { // add one to get a value out of range
            std::cout << "LinearSearch error with non existing value\n";
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {

    int numberOfTests = 500;
    if (RandomValuesInRangeTest(numberOfTests))
    {
        std::cout << "RandomValuesInRangeTest is success\n";
    }

    if (RandomValuesInOrderTest(numberOfTests))
    {
        std::cout << "RandomValuesInOrderTest is success\n";
    }

    if (RandomValuesSearchTest(numberOfTests))
    {
        std::cout << "RandomValuesSearchTest is success\n";
    }
    /*
    int size, min, max; // ask for data
    std::cout << "Enter me size\n";
    std::cin >> size;
    std::cout << "Enter me min\n";
    std::cin >> min;
    std::cout << "Enter me max\n";
    std::cin >> max;

    std::vector<int> v = GenerateMyRandomVector(size, min, max);
    std::cout << "Your randomly generated vector \n";
    std::cout << v << std::endl;

    std::cout << "Enter a value to get its index in the vector\n";
    int valueFind;
    std::cin >> valueFind;

    std::cout << "Vector before sort \n";
    std::cout << v << std::endl;
    bool isSort = CheckSort(v); // reverse == false
    if (isSort) {
        std::cout << "It's sorted\n";
    } else {
        std::cout << "Not sorted\n";
    }

    BubbleSort(v);
    std::cout << "Vector after sort \n";
    std::cout << v << std::endl;
    isSort = CheckSort(v);
    if (isSort) {
        std::cout << "It's sorted\n";
    } else {
        std::cout << "Not sorted\n";
    }
    // поиск индекса
    int index = BinarySearch(v, valueFind);
    std::cout << "Index == " << index << "\n";
    */
    return 0;
}