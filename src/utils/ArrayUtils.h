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
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] == element) {
                return;
            }
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
