#ifndef LIST_H_
#define LIST_H_

#include "Aggregate.h"
#include "Collection.h"
#include <initializer_list>

template <typename T>
class List: public Collection, Aggregate<T> {
private:
    struct Node {
        T payload = T();
        Node* prev = nullptr;
        Node* next = nullptr;
    };

    Node* at(int pos) const {
        Node* n = nullptr;
        int i = 0;

        if (pos < 0) {
            i = -1;
            n = _tail;

            while (i-- > pos)
                n = n->prev;
        }
        else {
            n = _head;

            while (i++ < pos)
                n = n->next;
        }

        return n;
    }

    Node* _head;
    Node* _tail;
    size_t _size;
public:
    List():
        _head(nullptr),
        _tail(nullptr),
        _size(0) {}

    virtual ~List() {
        clear();
    }

    List(const List& other):
        _head(nullptr),
        _tail(nullptr),
        _size(0)
    {
        *this = other;
    }

    List& operator=(const List& other) {
        clear();
        auto n = other._head;

        while (n) {
            push_back(n->payload);
            n = n->next;
        }

        return *this;
    }

    List(const std::initializer_list<T>& list):
        _head(nullptr),
        _tail(nullptr),
        _size(0)
    {
        *this = list;
    }

    List& operator=(const std::initializer_list<T>& list) {
        clear();

        for (auto& item : list)
            push_back(item);

        return *this;
    }

    size_t size() const {
        return _size;
    }

    bool any() const {
        return size();
    }

    const T& front() const {
        // fails fast
        return _head->payload;
    }

    T& front() {
        // fails fast
        return _head->payload;
    }

    const T& back() const {
        // fails fast
        return _tail->payload;
    }

    T& back() {
        // fails fast
        return _tail->payload;
    }

    List& push_back(const T& t) {
        bool hasAny = any();
        ++_size;

        if (!hasAny) {
            _head = new Node{ t, nullptr, nullptr };
            _tail = _head;
            return *this;
        }

        auto n = new Node{ t, _tail, nullptr };
        _tail->next = n;
        _tail = n;
        return *this;
    }

    List& push_back() {
        return push_back(T());
    }

    List& push_front(const T& t) {
        bool hasAny = any();
        ++_size;

        if (!hasAny) {
            _head = new Node{ t, nullptr, nullptr };
            _tail = _head;
            return *this;
        }

        auto n = new Node{ t, nullptr, _head };
        _head->prev = n;
        _tail = n;
        return *this;
    }

    List& push_front() {
        return push_front(T());
    }

    bool pop_back() {
        if (!any())
            return false;

        auto n = _head;
        _head = n->next;
        _head->prev = nullptr;
        delete n;
        --_size;
        return true;
    }

    bool pop_front() {
        if (!any())
            return false;

        auto n = _tail;
        _tail = n->prev;
        _tail->next = nullptr;
        delete n;
        --_size;
        return false;
    }

    List& insert(const T& t, size_t pos) {
        if (!any() || pos == _size) {
            push_back(t);
            return *this;
        }

        if (!pos) {
            push_front(t);
            return *this;
        }

        if (pos > _size)
            return *this;

        auto next = _head;
        size_t i = 0;

        while (i++ < pos)
            next = next->next;

        auto prev = next->prev;
        auto n = new Node{ t, prev, next };
        prev->next = n;
        next->prev = n;
        ++_size;
        return *this;
    }

    bool remove(size_t pos) {
        if (pos >= _size)
            return false;

        if (!pos) {
            return pop_front();
        }

        if (pos == _size - 1) {
            return pop_back();
        }

        auto n = _head;
        size_t i = 0;

        while (i++ < pos)
            n = n->next;

        n->prev->next = n->next;
        n->next->prev = n->prev;
        delete n;
        --_size;
        return true;
    }

    List& clear() {
        switch (_size) {
        case 0:
            break;
        case 1:
            delete _head;
            break;
        default:
            auto n = _head->next;

            while (n->next) {
                delete n->prev;
                n = n->next;
            }

            delete n->prev;
            delete n;
            break;
        }

        _size = 0;
        _head = nullptr;
        _tail = nullptr;
        return *this;
    }

    const T& operator[](int pos) const {
        // fails fast
        return at(pos)->payload;
    }

    T& operator[](int pos) {
        // fails fast
        return at(pos)->payload;
    }

    List& resize(size_t pos) {
        while (_size < pos)
            push_back();

        while (_size > pos)
            pop_back();

        return *this;
    }

    class Enumerator {
    private:
        Node* _node;
        Node* (*_prev)(Node*);
        Node* (*_next)(Node*);

        static Node* default_next(Node* n) {
            return n->next;
        }

        static Node* default_prev(Node* n) {
            return n->prev;
        }

        static Node* ret(Node* n) {
            return n;
        }

        Enumerator(Node* n):
            _node(n),
            _prev(&default_prev),
            _next(&default_next) {}

        Enumerator(Node* n, Node* (*prev)(Node*), Node* (*next)(Node*)):
            _node(n),
            _prev(prev),
            _next(next) {}

        static Enumerator forward(Node* n) {
            return Enumerator(n);
        }

        static Enumerator reverse(Node* n) {
            return Enumerator(n, &default_next, &default_prev);
        }
    public:
        friend class List;

        Enumerator():
            _node(nullptr),
            _prev(&ret),
            _next(&ret) {}

        virtual ~Enumerator() = default;
        Enumerator(const Enumerator&) = default;
        Enumerator& operator=(const Enumerator&) = default;

        const T& operator*() const {
            // fails fast
            return _node->payload;
        }

        T& operator*() {
            // fails fast
            return _node->payload;
        }

        const T* operator->() const {
            // fails fast
            return &_node->payload;
        }

        T* operator->() {
            // fails fast
            return &_node->payload;
        }

        Enumerator& operator++() {
            // fails fast
            _node = _next(_node);
            return *this;
        }

        Enumerator operator++(int) {
            // fails fast
            Enumerator temp = *this;
            ++(*this);
            return temp;
        }

        Enumerator& operator--() {
            // fails fast
            _node = _prev(_node);
            return *this;
        }

        Enumerator operator--(int) {
            // fails fast
            Enumerator temp = *this;
            --(*this);
            return temp;
        }

        Enumerator& operator+=(int pos) {
            int i = 0;

            while (i++ < pos)
                ++(*this);

            i = 0;

            while (i-- > pos)
                ++(*this);

            return *this;
        }

        Enumerator& operator-=(int pos) {
            *this += -pos;
        }

        const Enumerator operator+(int pos) const {
            Enumerator temp(*this);
            temp += pos;
            return temp;
        }

        Enumerator operator+(int pos) {
            Enumerator temp(*this);
            temp += pos;
            return temp;
        }

        const Enumerator operator-(int pos) const {
            Enumerator temp(*this);
            temp -= pos;
            return temp;
        }

        Enumerator operator-(int pos) {
            Enumerator temp(*this);
            temp -= pos;
            return temp;
        }

        bool operator==(const Enumerator& other) const {
            return _node == other._node;
        }

        bool operator!=(const Enumerator& other) const {
            return !(*this == other);
        }
    };

    const Enumerator begin() const {
        return Enumerator::forward(_head);
    }

    Enumerator begin() {
        return Enumerator::forward(_head);
    }

    const Enumerator begin_reverse() const {
        return Enumerator::reverse(_tail);
    }

    Enumerator begin_reverse() {
        return Enumerator::reverse(_tail);
    }

    const Enumerator end() const {
        return Enumerator();
    }

    /*
    bool insert_after(Enumerator& it, const T& t) {
        if (this != it._list)
            return false;

        if (!any()) {
            push_back(t);
            it._node = _tail;
            return true;
        }

        Node* n = it._node;

        if (!n)
            return false;

        Node* m = new Node{ t, n, n->next };
        (n->next ? n->next->prev : _tail) = m;
        n->next = m;
        ++_size;
        return true;
    }

    bool insert_before(Enumerator& it, const T& t) {
        if (this != it._list)
            return false;

        if (!any()) {
            push_front();
            it._node = _head;
            return true;
        }

        Node* n = it._node;

        if (!n)
            return false;

        Node* m = new Node{ t, n->prev, n };
        (n->prev ? n->prev->next : _head) = m;
        n->prev = m;
        ++_size;
        return true;
    }

    bool remove(Enumerator& it) {
        if (this != it._list || !any() || !it._node)
            return false;

        Node* n = it._node;

        if (!n->prev) {
            bool success = pop_front();
            it._node = _head;
            return success;
        }

        if (!n->next) {
            bool success = pop_back();
            it._node = _tail;
            return success;
        }

        n->prev->next = n->next;
        n->next->prev = n->prev;
        it._node = n->next;
        delete n;
        --_size;
        return true;
    }
    */
};

#endif /* LIST_H_ */
