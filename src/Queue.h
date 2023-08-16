#ifndef QUEUE_H_
#define QUEUE_H_

#include "Array.h"

template <typename T, template <typename> class Alloc = Array>
class Queue: public Alloc<T> {
private:
    size_t _head;
    size_t _tail;
protected:
    virtual size_t first_pos() const { return _head; }
    virtual size_t last_pos() const { return _tail + 1; }
public:
    virtual ~Queue() = default;
    Queue& operator=(const Queue&) = default;
    Queue(const Queue&) = default;

    Queue():
        _head(0),
        _tail(0) {}

    Queue(size_t size):
        Alloc<T>(size),
        _head(0),
        _tail(0) {}

    size_t count() const { return _tail - _head; }
    bool any() const { return _head != _tail; }

    bool top(T& payload) {
        if (!any())
            return false;

        payload = (*this)[_head];
        return true;
    }

    Queue& push(const T& payload) {
        if (_tail == Queue::size()) {
            Queue temp(2 * (count() + 1));

            for (int i = (int)_head; i < (int)_tail; ++i)
                temp[i - _head] = (*this)[i];

            temp._head = 0;
            temp._tail = _tail - _head;
            *this = temp;
        }

        (*this)[_tail++] = payload;
        return *this;
    }

    bool pop(T& payload) {
        if (!any())
            return false;

        payload = (*this)[_head++];
        return true;
    }

    bool pop() {
        T temp;
        return pop(temp);
    }
};

#endif /* QUEUE_H_ */
