#pragma once
#ifndef BITSET_H_
#define BITSET_H_

#include "Array.h"
#include <sstream>

template <typename T = char>
class Bitset {
private:
    Array<T>
    _list;

    size_t
    _size;

    static size_t
    word_size() {
        return sizeof(T *);
    }

    static T
    mask(unsigned int pos) {
        return 1 << pos;
    }

    static T
    set(T word, unsigned int pos) {
        return word | mask(pos);
    }

    static T
    clear(T word, unsigned int pos) {
        return word & ~mask(pos);
    }

    static bool
    get(T word, unsigned int pos) {
        return word & mask(pos);
    }

    static T
    set(T word, unsigned int pos, bool value) {
        return value
            ? set(word, pos)
            : clear(word, pos)
            ;
    }

    static unsigned int
    count(int word) {
        unsigned int numBits = 0;

        while (word) {
            word &= word - 1;
            ++numBits;
        }

        return numBits;
    }
public:
    virtual ~Bitset() = default;
    Bitset(const Bitset &) = default;
    Bitset & operator=(const Bitset &) = default;
    Bitset();
    Bitset(size_t);
    size_t size() const;
    size_t capacity() const;
    size_t count() const;
    bool contains(size_t pos) const;
    Bitset & push(size_t pos, bool value = true);
    bool at(size_t pos) const;
    Bitset & set(size_t pos, bool value = true);
    Bitset & clear(size_t pos);
    bool operator[](size_t pos) const;
    std::string to_string() const;
    std::ostream& operator<<(std::ostream&) const;

    template <typename T>
    friend std::ostream& operator<<(std::ostream&, const Bitset<T>&);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Bitset<T>& o) {
    return out << o.to_string();
}

template <typename T>
std::ostream&
Bitset<T>::operator<<(std::ostream& out) const {
    return out << to_string();
}

template <typename T>
std::string
Bitset<T>::to_string() const {
    std::string temp;

    for (size_t i = 0; i < size(); ++i)
        temp += at(i) ? '1' : '0';

    return temp;
}

template <typename T>
Bitset<T>::Bitset():
    _size(0) {}

template <typename T>
Bitset<T>::Bitset(size_t size):
    _size(size),
    _list(size / word_size() + (int)(bool)(size % word_size()), 0) {}

template <typename T>
size_t
Bitset<T>::size() const {
    return _size;
}

template <typename T>
size_t
Bitset<T>::capacity() const {
    return _list.size() * word_size();
}

template <typename T>
size_t
Bitset<T>::count() const {
    size_t numBits = 0;

    for (const auto& word : _list)
        numBits += count(word);

    return numBits;
}

template <typename T>
bool
Bitset<T>::contains(size_t pos) const {
    return at(pos);
}


template <typename T>
Bitset<T> &
Bitset<T>::push(size_t pos, bool value) {
    while (pos / word_size() >= _list.size()) {
        _list.resize();
        _size = _list.size() * word_size();
    }

    _list[pos / word_size()]
        = set(_list[pos / word_size()], pos % word_size(), value);

    return *this;
}

template <typename T>
bool
Bitset<T>::at(size_t pos) const {
    return get(_list[pos / word_size()], pos % word_size());
}

template <typename T>
Bitset<T> &
Bitset<T>::set(size_t pos, bool value) {
    _list[pos / word_size()]
        = set(_list[pos / word_size()], pos % word_size(), value);

    return *this;
}

template <typename T>
Bitset<T> &
Bitset<T>::clear(size_t pos) {
    _list[pos / word_size()]
        = clear(_list[pos / word_size()], pos % word_size());

    return *this;
}

template <typename T>
bool
Bitset<T>::operator[](size_t pos) const {
    return at(pos);
}

#endif /* BITSET_H_ */
