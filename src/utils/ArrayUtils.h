#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <cstddef>

using namespace std;

/**
 * Utilities for arrays.
*/
namespace ArrayUtils {
/**
 * Resizes an array.
 * 
 * @param arr The array to resize.
 * @param size The size of the array.
*/
template <typename T> void resizeArray(T *arr, size_t &size) {
    // Make the new array twice as big to avoid frequent reallocations.
    size_t newSize = size * 2;
    T *newArr = new T[newSize];

    // Move the contents of the old array to the new one.
    for (size_t i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }

    // Free the allocated memory for the old array.
    delete[] arr;

    // Reassign the pointer to point to the new array.
    arr = newArr;

    // Assign the new size.
    size = newSize;
}

/**
 * Binary searches an ascendingly-sorted array to find the index of an element.
 *
 * @note
 * The binary search algorithm narrows the index of the element by comparing it against the middle
 * element of the given range. If the element is on the left side of the range (`left`), the range will be shrunk
 * to the left side of the array. If the element is on the right side of the range (`right`), the range will be
 * shrunk to the right side of the array. This operation is repeated until the range becomes invalid
 * (`left > right`) or the element is found. The binary search algorithm requires the array to be sorted.
 * This algorithm in particular requires the array to be sorted ascendingly.
 *
 * @param arr The array to search on.
 * @param element The element to search the location for.
 * @param left The leftmost position in the array in which the search will be performed.
 * @param right The rightmost position in the array in which the search will be performed.
 * @returns The index of the element. If the element is not found,
 * the function will return the index where the element would be.
*/
template <typename T> size_t binarySearch(T *arr, const T &element, size_t left, size_t right) {
    while (left <= right) {
        // Get the middle point of the range.
        const size_t mid = left + (right - left) / 2;
        const T &midElement = arr[mid];

        if (element == midElement) {
            // Element is found, return the current middle point.
            return mid;
        } else if (element > midElement) {
            // Element is on the right side of the array, move towards the right side of the array.
            left = mid + 1;
        } else {
            // 0 - 1 on an unsigned number will cause an underflow, so we need to avoid that.
            // This can happen when the array size is 1.
            if (mid == 0) {
                return mid;
            }

            // Element is on the left side of the array, move towards the left side of the array.
            right = mid - 1;
        }
    }

    // The algorithm fails. Return the index where the element would be if it existed.
    return left;
}

/**
 * Adds an element at the specified index to the array.
 * 
 * @note
 * The array will be resized when needed.
 * 
 * @param arr The array to add to.
 * @param element The element to add.
 * @param index The index at which to add the element to.
 * @param size The size of the array.
 * @param capacity The capacity of the array.
*/
template <typename T>
void addAtIndex(T *arr, const T &element, size_t index, size_t &size,
                size_t &capacity) {
    if (size == capacity - 1) {
        // Resize the array if it does not fit.
        resizeArray(arr, capacity);
    }

    // Shift the contents to the right to make room for the element.
    for (size_t i = size; i > index; --i) {
        arr[i] = arr[i - 1];
    }

    ++size;

    arr[index] = element;
}

/**
 * Appends an element to an array.
 * 
 * @note
 * The array will be resized when needed.
 * 
 * @param arr The array to append to.
 * @param element The element to append.
 * @param size The size of the array.
 * @param capacity The capacity of the array.
 * @param ensureUniqueness Whether to ensure that the element does not exist in the array yet. Defaults to `false`.
*/
template <typename T>
void addElement(T *arr, const T &element, size_t &size, size_t &capacity,
                const bool ensureUniqueness = false) {
    if (ensureUniqueness) {
        size_t idx = binarySearch(arr, element, 0, size - 1);

        if (idx < size && arr[idx] == element) {
            return;
        }
    }

    addAtIndex(arr, element, size, size, capacity);
}

/**
 * Removes an element from an array at the specified index.
 * 
 * @param arr The array to remove from.
 * @param index The index to remove.
 * @param size The size of the array.
*/
template <typename T>
void removeAtIndex(T *arr, const size_t index, size_t &size) {
    --size;

    // Offset the array to make it seem like the item is removed from the array.
    for (size_t i = index; i < size; ++i) {
        arr[i] = arr[i + 1];
    }
}

/**
 * Removes an element from an array.
 * 
 * @param arr The array to remove from.
 * @param element The element to remove.
 * @param size The size of the array.
 * @returns Whether the element was removed from the array.
*/
template <typename T>
bool removeElement(T *arr, const T &element, size_t &size) {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == element) {
            removeAtIndex(arr, i, size);

            return true;
        }
    }

    return false;
}

/**
 * Reverses an array.
 * 
 * @param arr The array to reverse.
 * @param size The size of the array.
*/
template <typename T> void reverseArray(T *arr, const size_t size) {
    for (size_t i = 0, j = size - 1; i < size / 2; ++i, ++j) {
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
} // namespace ArrayUtils

#endif
