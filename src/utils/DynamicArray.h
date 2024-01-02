#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "Iterator.h"
#include <cstddef>
#include <stdexcept>

using namespace std;

/**
 * Represents a dynamically-sized array.
*/
template <typename T> class DynamicArray {
    T *arr;
    size_t _size;
    size_t _capacity;
    static const size_t initialCapacity = 10;

  public:
    DynamicArray(size_t capacity = DynamicArray::initialCapacity) {
        if (capacity == 0) {
            throw invalid_argument("The initial capacity of a DynamicArray "
                                   "must be more than zero.");
        }

        _size = 0;
        _capacity = capacity;
        arr = new T[_capacity];
    }

    DynamicArray(const DynamicArray<T> &copy) { *this = copy; }

    DynamicArray(DynamicArray<T> &&other) {
        _size = other._size;
        _capacity = other._capacity;
        arr = other.arr;

        other._size = 0;
        other._capacity = DynamicArray::initialCapacity;
        other.arr = nullptr;
    }

    ~DynamicArray() { delete[] arr; }

    /**
     * The size of this `DynamicArray`.
    */
    size_t size() const { return _size; }

    /**
     * The capacity of this `DynamicArray`.
    */
    size_t capacity() const { return _capacity; }

    /**
     * Returns a direct pointer to the memory array used internally
     * by this `DynamicArray` to store its elements.
    */
    T *data() const { return arr; }

    /**
     * Gets the reference to the first element of this `DynamicArray`.
    */
    T &first() const { return arr[0]; }

    /**
     * Gets the reference to the last element of this `DynamicArray`.
    */
    T &last() const { return arr[_size - 1]; }

    /**
     * Prepends an element into this `DynamicArray`.
     * 
     * @param element The element to prepend.
    */
    void prepend(const T &element) { add(element, 0); }

    /**
     * Appends an element into this `DynamicArray`.
     * 
     * @param element The element to append.
    */
    void append(const T &element) { add(element, _size); }

    /**
     * Adds an element to the array at the given index.
     *
     * @param element The element to add.
     * @param index The index to add on.
    */
    void add(const T &element, const size_t index) {
        if (_size == _capacity - 1) {
            // Resize the array if it does not fit.
            resize(_capacity * 2);
        }

        // Shift the contents to the right to make room for the element.
        for (size_t i = _size; i > index; --i) {
            arr[i] = arr[i - 1];
        }

        ++_size;

        arr[index] = element;
    }

    /**
     * Removes an element.
     * 
     * @param element The element to remove.
     * @returns Whether the element was removed.
    */
    bool remove(const T &element) {
        for (size_t i = 0; i < _size; ++i) {
            if (arr[i] == element) {
                remove(i);

                return true;
            }
        }

        return false;
    }

    /**
     * Removes an element at the specified index.
     * 
     * @param index The index.
     * @returns The removed element.
    */
    T remove(const size_t index) {
        if (index < 0 || index > _size - 1) {
            throw out_of_range("Index is out of bounds");
        }

        T removedElement = arr[index];

        // Offset the array to make it seem like the item is removed from the array.
        for (size_t i = index; i < _size; ++i) {
            arr[i] = arr[i + 1];
        }

        --_size;

        return removedElement;
    }

    /**
     * Whether this `DynamicArray` is empty.
    */
    bool empty() const { return _size == 0; }

    /**
     * Checks whether this `DynamicArray` has the given element.
     * 
     * @param element The element to check.
     * @returns Whether the element exists.
    */
    bool has(const T &element) const {
        for (T &el : *this) {
            if (element == el) {
                return true;
            }
        }

        return false;
    }

    /**
     * Clears this `DynamicArray`.
    */
    void clear() {
        _size = 0;

        // Trigger a resize with the current capacity so that this DynamicArray is actually emptied.
        resize(_capacity);
    }

    /**
     * Resizes this `DynamicArray`.
     * 
     * @note
     * If the new size is smaller than the size of this `DynamicArray`, any elements
     * after the new size will be removed from this `DynamicArray`.
     * 
     * @param size The new size.
    */
    void resize(const size_t size) {
        T *newArr = new T[size];

        // Assign the new size of the array.
        _size = min(_size, size);

        // Move the contents of the old array to the new one.
        for (size_t i = 0; i < _size; ++i) {
            newArr[i] = arr[i];
        }

        // Free the allocated memory for the old array.
        delete[] arr;

        // Reassign the pointer to point to the new array.
        arr = newArr;

        // Assign the new capacity.
        _capacity = size;
    }

    /**
     * Reverses this `DynamicArray`.
    */
    void reverse() {
        for (size_t i = 0, j = _size - 1; i < _size / 2; ++i, ++j) {
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &right) {
        if (&right != this) {
            T *newArr = new T[right._capacity];

            for (size_t i = 0; i < right._size; ++i) {
                newArr[i] = right[i];
            }

            delete[] arr;

            arr = newArr;
            _size = right._size;
            _capacity = right._capacity;
        }

        return *this;
    }

    DynamicArray<T> &operator=(DynamicArray<T> &&right) {
        // Reference: https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170#to-create-a-move-constructor-for-a-c-class
        if (&right != this) {
            delete[] arr;

            _size = right._size;
            _capacity = right._capacity;
            arr = right.arr;

            right._size = 0;
            right._capacity = DynamicArray::initialCapacity;
            right.arr = nullptr;
        }

        return *this;
    }

    T &operator[](const long idx) const { return arr[idx]; }
    T &operator[](const int idx) const { return arr[idx]; }
    T &operator[](const short idx) const { return arr[idx]; }
    T &operator[](const size_t idx) const { return arr[idx]; }
    T &operator[](const uint32_t idx) const { return arr[idx]; }
    T &operator[](const uint16_t idx) const { return arr[idx]; }

    Iterator<T> begin() { return Iterator<T>(&arr[0]); }
    Iterator<T> end() { return Iterator<T>(&arr[_size]); }

    Iterator<T> begin() const { return Iterator<T>(&arr[0]); }
    Iterator<T> end() const { return Iterator<T>(&arr[_size]); }
};

#endif
