#ifndef STACK_H_
#define STACK_H_

#include "Array.h"

template <typename T, template <typename> class Alloc = Array>
class Stack: public Alloc<T> {
private:
    size_t _top;
protected:
    virtual size_t last_pos() const { return _top; }
public:
    virtual ~Stack() = default;
    Stack& operator=(const Stack&) = default;
    Stack(const Stack&) = default;

    Stack():
        _top(0) {}

    Stack(size_t size):
        Alloc<T>(size),
        _top(0) {}

    size_t count() const { return _top; }
    bool any() const { return _top; }

    bool top(T& payload) {
        if (!any())
            return false;

        payload = (*this)[_top - 1];
        return true;
    }

    Stack& push(const T& payload) {
        if (_top == Stack::size()) {
            Stack temp(2 * (count() + 1));

            for (int i = 0; i < (int)_top; ++i)
                temp[i] = (*this)[i];

            temp._top = _top;
            *this = temp;
        }

        (*this)[_top++] = payload;
        return *this;
    }

    bool pop(T& payload) {
        if (!any())
            return false;

        payload = (*this)[--_top];
        return true;
    }

    bool pop() {
        T temp;
        return pop(temp);
    }
};

#endif /* STACK_H_ */

