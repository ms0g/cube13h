#ifndef VECTOR_H
#define VECTOR_H

#include <iostream.h>
#include <stdlib.h>
#include <stddef.h>

template <class T>
class vector {
public:
    vector();

    vector(int size);

    ~vector();

    void reserve(int size);
    
    int size(void) const;

    int capacity(void) const;

    int isEmpty(void) const;

    void clear(void);

    T& begin(void);

    T& end(void);

    const T& cbegin(void) const;
    
    const T& cend(void) const;

    T& get(int index) const;

    void set(int index, T& value);

    void insert(int index, T& value);
    
    void remove(int index);

    void push_back(T& value);
    
    T& operator[](int index) const;

private:
    T* mData;
    int mCount;
    int mCapacity;
};

template <class T>
vector<T>::vector(): 
    mData(NULL), 
    mCount(0), 
    mCapacity(1) {
    reserve(mCapacity);
}

template <class T>
vector<T>::vector(int size) {
    reserve(size);
}

template <class T>
vector<T>::~vector() {
    if (mData != NULL) {
        delete[] mData;
        mData = NULL;
    }
}

template <class T>
void vector<T>::reserve(int size) {
    delete[] mData;
    
    mData = new T[size];
    
    mCapacity = size;
    mCount = 0;
}

template <class T>
int vector<T>::size(void) const {
    return mCount;
}

template <class T>
int vector<T>::capacity(void) const {
    return mCapacity;
}

template <class T>
int vector<T>::isEmpty(void) const {
    return mCount == 0;
}

template <class T>
void vector<T>::clear(void) {
    memset(mData, 0, sizeof(T) * mCount);
    
    mCount = 0;
}

template <class T>
T& vector<T>::begin(void) {
    return mData[0];
}

template <class T>
T& vector<T>::end(void) {
    return mData[mCount - 1];
}

template <class T>
const T& vector<T>::cbegin(void) const {
    return mData[0];
}

template <class T>
const T& vector<T>::cend(void) const {
    return mData[mCount - 1];
}

template <class T>
T& vector<T>::get(int index) const {
    if (index < 0 || index > mCount) {
        cerr << "get:Index out of bounds";
        exit(1);
    }

    return mData[index];
}

template <class T>
void vector<T>::set(int index, T& value) {
    if (index < 0 || index > mCount) {
        cerr << "set:Index out of bounds";
        exit(1);
    }

    mData[index] = value;
}

template <class T>
void vector<T>::insert(int index, T& value) {
    if (index < 0 || index > mCount) {
        cerr << "insert:Index out of bounds";
        exit(1);
    }

    if (mCount == mCapacity) {
        T* temp = new T[2 * mCapacity];
 
        // copying old array elements to new array
        for (int i = 0; i < mCapacity; i++) {
            temp[i] = mData[i];
        }
 
        // deleting previous array
        delete[] mData;
        mCapacity *= 2;
        mData = temp;
    }

    mData[index] = value;
    ++mCount;
}

template <class T>
void vector<T>::remove(int index) {
    if (index < 0 || index > mCount) {
        cerr << "remove:Index out of bounds";
        exit(1);
    }
    
    for (int i = index; i < mCount - 1; i++) {
        mData[i] = mData[i + 1];
    }

    --mCount;
}

template <class T>
void vector<T>::push_back(T& value) {
    insert(mCount, value);
}

template <class T>
T& vector<T>::operator[](int index) const {
    return mData[index];
}

#endif
