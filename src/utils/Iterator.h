#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>
#include <iterator>

using namespace std;

/**
 * A custom iterator.
 * 
 * Reference: https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
*/
template <typename T> struct Iterator {
    using iterator_category = forward_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    Iterator(T *ptr) { this->ptr = ptr; }

    // Reference and dereference operators are used to get the value the iterator points to.
    reference operator*() const { return *ptr; }
    pointer operator->() { return ptr; }

    // Prefix increment moves the iterator one step forward.
    Iterator &operator++() {
        ++ptr;

        return *this;
    }

    // Postfix increment moves the iterator one step forward, but returns a dereferenceable iterator.
    Iterator operator++(int) {
        Iterator tmp = *this;

        ++(*this);

        return tmp;
    }

    // Equality operators to compare with another iterator.
    friend bool operator==(const Iterator &left, const Iterator &right) {
        return left.ptr == right.ptr;
    }

    friend bool operator!=(const Iterator &left, const Iterator &right) {
        return left.ptr != right.ptr;
    }

  private:
    pointer ptr;
};

#endif
