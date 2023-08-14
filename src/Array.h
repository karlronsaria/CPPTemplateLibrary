/*
 * Array.h
 *
 *  Created on: Oct 14, 2014
 *      Author: adaniels4
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include "arithmetic.h"
#include "enumerable.h"
#include "scoped_ptr.h"
#include "Aggregate.h"
#include "Collection.h"

template <typename T>
class Array: public Collection, Aggregate<T> {
private:
    scoped_ptr<T> _array_list;
    size_t _size;
public:
    template <typename Type>
    static void copy_values(
        Type* to,
        Type* from,
        size_t toSize,
        size_t fromSize
    ) {
        Type* toIt = to;
        Type* fromIt = from;

        for (size_t index = 0; index < toSize && index < fromSize; index++) {
            *toIt = *fromIt;
            toIt++;
            fromIt++;
        }
    }

    virtual ~Array() = default;

    Array():
        _array_list(nullptr, true),
        _size(0) {}

    Array(size_t arraySize):
        _array_list(new T[arraySize], true),
        _size(arraySize) {}

    Array(const std::initializer_list<T>& list):
        _array_list(list),
        _size(list.size())
    {
        for (size_t i = 0; i < _size; ++i)
            _array_list[i] = list[i];
    }

    Array(size_t arraySize, const T& content):
        _array_list(new T[arraySize], true),
        _size(arraySize)
    {
        for (size_t i = 0; i < _size; ++i)
            (*this)[i] = content;
    }

    Array(const Array& object):
         _array_list(new T[object.size()], true),
         _size(object.size())
    {
        Array::copy_values(
            _array_list.ref(),
            object._array_list.ref(),
            _size,
            object._size
        );
    }

    virtual size_t size() const { return _size; }
    virtual bool any() const { return _size; }

    virtual void resize(size_t newSize) {
        if (newSize < _size)
            return;

        Array temp(newSize);

        Array::copy_values(
            temp._array_list.ref(),
            _array_list.ref(),
            temp._size,
            _size
        );

        swap(_array_list, temp._array_list);
        _size = temp._size;
    }

    virtual void resize() {
        resize(2 * _size);
    }

    virtual const T& operator[](int index) const {
        return _array_list[((index < 0) * _size) + index];
    }

    virtual T& operator[](int index) {
        return _array_list[((index < 0) * _size) + index];
    }

    virtual Array& operator=(const Array& object) {
        if (_array_list.any())
            _array_list.release();

        _array_list = new T[object._size];
        _size = object._size;

        for (size_t index = 0; index < _size; index++)
            _array_list[index] = object._array_list[index];

        return *this;
    }

    class Enumerator {
    private:
        typename scoped_ptr<T>::locator _array_loc;
        size_t _size;
        size_t _pos;

        Enumerator(const Array& a, size_t pos):
            _array_loc(a._array_list.loc()),
            _size(a._size),
            _pos(pos) {}
    public:
        friend class Array;

        Enumerator(): _pos(0) {}
        Enumerator(const Enumerator&) = default;
        virtual ~Enumerator() = default;
        Enumerator& operator=(const Enumerator&) = default;

        const T& operator*() const {
            return _array_loc[_pos];
        }

        T& operator*() {
            return _array_loc[_pos];
        }

        const T* operator->() const {
            return &_array_loc[_pos];
        }

        T* operator->() {
            return &_array_loc[_pos];
        }

        Enumerator& operator++() {
            ++_pos;
            return *this;
        }

        Enumerator operator++(int) {
            return arithmetic::PostIncr(*this);
        }

        Enumerator& operator--() {
            _pos = _pos ? _size : _pos - 1;
        }

        Enumerator operator--(int) {
            return arithmetic::PostDecr(*this);
        }

        Enumerator& operator+=(int len) {
            _pos = _pos + len <= 0 ? _size : _pos + len;
        }

        const Enumerator operator+(int len) const {
            return arithmetic::Plus(*this, len);
        }

        Enumerator operator+(int len) {
            return arithmetic::Plus(*this, len);
        }

        Enumerator& operator-=(int len) {
            *this += -len;
        }

        const Enumerator operator-(int len) const {
            return arithmetic::Plus(*this, -len);
        }

        Enumerator operator-(int len) {
            return arithmetic::Plus(*this, -len);
        }

        bool operator==(const Enumerator& other) const {
            return _array_loc == other._array_loc
                && ((_pos >= _size && other._pos >= _size) || _pos == other._pos);
        }

        bool operator!=(const Enumerator& other) const {
            return !(*this == other);
        }
    };

    const Enumerator begin() const {
        return Enumerator(*this, 0);
    }

    Enumerator begin() {
        return Enumerator(*this, 0);
    }

    const Enumerator end() const {
        return Enumerator(*this, _size);
    }

    std::string to_string(const std::string& delim = " ") const {
        return enumerable::ToString(*this, delim);
    }

    std::ostream& operator<<(std::ostream& out) const {
        return out << to_string();
    }

    template <typename S>
    friend std::ostream& operator<<(std::ostream&, const Array<S>&);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Array<T>& o) {
    return out << o.to_string();
}

#endif /* ARRAY_H_ */
