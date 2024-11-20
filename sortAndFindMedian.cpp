#include <vector>
#include <iostream>

void merge(std::vector<int> &original_vec, int left, int mid, int right) {
    int left_subarray_size = mid - left + 1;
    int right_subarray_size = right - mid;
    std::vector<int> left_subarray(left_subarray_size);
    std::vector<int> right_subarray(right_subarray_size);

    // populate subarrays with data from orig vecotr
    for (int i = 0; i < left_subarray_size; i++) {
        left_subarray[i] = original_vec[left + i];
    }
    for (int j = 0; j < right_subarray_size; j++) {
        right_subarray[j] = original_vec[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // 3 ptrs to compare the smallest element of left subarray and right subarray, writing to orig vector
    while (i < left_subarray_size || j < right_subarray_size) {
        if (i < left_subarray_size && (j >= right_subarray_size || left_subarray[i] <= right_subarray[j])) {
            original_vec[k++] = left_subarray[i++];
        } else {
            original_vec[k++] = right_subarray[j++];
        }
    }
}

void mergeSort(std::vector<int> &original_vec, int left, int right) {
    // base case; current subarray consists of just one element
    if (left >= right) {
        return;
    }

    int mid = left + (right - left)/2;
    // recursive steps to divide subarrays
    mergeSort(original_vec, left, mid);
    mergeSort(original_vec, mid+1, right);
    // merge two sorted subarrays into one subarray
    merge(original_vec, left, mid, right);
}

double sortAndFindMedian(std::vector<int> &numbers) {
    mergeSort(numbers, 0, numbers.size()-1);
    int n = numbers.size();
    if (n % 2 == 0) {
        return ((double)numbers[(n/2) - 1] + (double)numbers[n/2])/2.0;
    }
    else {
        return (double)numbers[n/2];
    }
}

int main() {
    std::vector<std::vector<int>> test_cases = {
        {3, 1, 4, 1, 5, 9},     // Unsorted, odd len
        {10, 20, 30, 40},       // Unsorted, even len
        {42},                   // Single elem
        {1, 2, 3, 4, 5},        // Sorted, odd len
        {7, 7, 8, 5, 7},        // Duplicates
    };

    std::vector<double> expected_results = {
        3.5,
        25.0,
        42.0,
        3.0,
        7.0
    };

    // Run test cases
    for (size_t i = 0; i < test_cases.size(); i++) {
        try {
            std::vector<int> test_case = test_cases[i];
            double result = sortAndFindMedian(test_case);
            std::cout << "Test case " << i + 1 << ": ";
            if (result == expected_results[i]) {
                std::cout << "Passed (Median: " << result << ")" << std::endl;
            } else {
                std::cout << "Failed (Expected: " << expected_results[i]
                          << ", Got: " << result << ")" << std::endl;
            }
        } catch (const std::exception &e) {
            std::cout << "Test case " << i + 1 << " encountered an error: " << e.what() << std::endl;
        }
    }
    return 0;
}
