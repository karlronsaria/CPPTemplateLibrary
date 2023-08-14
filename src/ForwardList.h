#ifndef FORWARDLIST_H_
#define FORWARDLIST_H_

#include "arithmetic.h"
#include "enumerable.h"
#include "scoped_ptr.h"
#include "Aggregate.h"
#include "Collection.h"
#include <initializer_list>

template <typename T>
class ForwardList: public Collection, Aggregate<T> {
private:
    struct Node {
        T payload = T();
        Node* next = nullptr;
    };

    struct Queue {
        Node* _head = nullptr;
        Node* _tail = nullptr;
        size_t _size = 0L;
    };

    scoped_ptr<Queue> _list;

    static size_t to_index(size_t size, int pos) {
        return pos >= 0 ? (size_t)pos : size + (size_t)pos;
    }

    static Node* at(const Queue& list, int pos) {
        Node* n = list._head;
        size_t i = 0;

        while (i++ < to_index(list._size, pos))
            n = n->next;

        return n;
    }

    static void clear(Node* n) {
        if (!n)
            return;

        clear(n->next);
        delete n;
    }

    static void clear(Queue& list) {
        clear(list._head);
        list._head = list._tail = nullptr;
    }

    static void push_back(Queue& list, const T& t) {
        bool hasAny = list._size;
        ++list._size;

        if (!hasAny) {
            list._head = new Node{ t, nullptr };
            list._tail = list._head;
            return;
        }

        auto n = new Node{ t, nullptr };
        list._tail->next = n;
        list._tail = n;
    }

    static void push_front(Queue& list, const T& t) {
        bool hasAny = list._size;
        ++list._size;

        if (!hasAny) {
            list._head = new Node{ t, nullptr };
            list._tail = list._head;
            return;
        }

        auto n = new Node{ t, list._head };
        list._tail = n;
    }

    static bool pop_back(Queue& list) {
        if (!list._size)
            return false;

        auto n = list._head;
        list._head = n->next;
        delete n;
        --list._size;
        return true;
    }

    static bool pop_front(Queue& list) {
        if (!list._size)
            return false;

        auto n = list._tail;
        list._tail->next = nullptr;
        delete n;
        --list._size;
        return false;
    }

    static void copy(Queue& list, Queue& o) {
        clear(list);
        auto n = o._head;

        while (n) {
            push_back(list, n->payload);
            n = n->next;
        }
    }

    // require: head != null, pos in range(0, size - 1)
    static void insert_after(Queue& list, const T& t, size_t pos) {
        auto n = list._head;
        size_t i = 0;

        while (i++ < pos)
            n = n->next;

        n->next = new Node{ t, n->next };
        ++list._size;
    }

    // require: head != null, pos in range(1, size - 2)
    static void remove(Queue& list, size_t pos) {
        auto n = list._head;
        size_t i = 0;

        while (i++ < pos - 1)
            n = n->next;

        auto temp = n->next;
        n->next = n->next->next;
        delete temp;
        --list._size;
    }
public:
    ForwardList():
        _list(new Queue()) {}

    virtual ~ForwardList() {
        clear();
    }

    ForwardList(const ForwardList& other):
        _list(new Queue())
    {
        *this = other;
    }

    ForwardList& operator=(const ForwardList& other) {
        copy(*_list, *(Queue*)other._list);
        return *this;
    }

    ForwardList(const std::initializer_list<T>& list):
        _list(new Queue())
    {
        *this = list;
    }

    ForwardList& operator=(const std::initializer_list<T>& list) {
        clear();

        for (auto& item : list)
            push_back(item);

        return *this;
    }

    size_t size() const {
        return _list->_size;
    }

    bool any() const {
        return size();
    }

    const T& front() const {
        // fails fast
        return _list->_head->payload;
    }

    T& front() {
        // fails fast
        return _list->_head->payload;
    }

    const T& back() const {
        // fails fast
        return _list->_tail->payload;
    }

    T& back() {
        // fails fast
        return _list->_tail->payload;
    }

    ForwardList& push_back(const T& t) {
        push_back(*_list, t);
        return *this;
    }

    ForwardList& push_back() {
        return push_back(T());
    }

    ForwardList& push_front(const T& t) {
        push_front(*_list, t);
        return *this;
    }

    ForwardList& push_front() {
        return push_front(T());
    }

    bool pop_back() {
        return pop_back(*_list);
    }

    bool pop_front() {
        return pop_front(*_list);
    }

    ForwardList& insert(const T& t, int pos) {
        size_t p = to_index(size(), pos);

        if (!any() || p == size()) {
            push_back(t);
            return *this;
        }

        if (!p) {
            push_front(t);
            return *this;
        }

        if (p > size())
            return *this;

        insert_after(*_list, t, p - 1);
        return *this;
    }

    bool remove(size_t pos) {
        size_t p = to_index(size(), pos);

        if (p >= size())
            return false;

        if (!p)
            return pop_front();

        if (p == size() - 1)
            return pop_back();

        remove(*_list, p);
        return true;
    }

    ForwardList& clear() {
        clear(*_list);
        return *this;
    }

    const T& operator[](int pos) const {
        // fails fast
        return at(*_list, pos)->payload;
    }

    T& operator[](int pos) {
        // fails fast
        return at(*_list, pos)->payload;
    }

    ForwardList& resize(size_t len) {
        while (size() < len)
            push_back();

        while (size() > len)
            pop_back();

        return *this;
    }

    class Enumerator {
    private:
        typedef typename scoped_ptr<Queue>::locator list_ptr;

        list_ptr _list;
        Node* _node;
        Node* (*_next)(Node*);

        static Node* default_next(Node* n) {
            return n->next;
        }

        static Node* ret(Node* n) {
            return n;
        }

        Enumerator(list_ptr l, Node* n):
            _list(l),
            _node(n),
            _next(&default_next) {}

        Enumerator(list_ptr l, Node* n, Node* (*next)(Node*)):
            _list(l),
            _node(n),
            _next(next) {}

        static Enumerator forward(list_ptr l, Node* n) {
            return Enumerator(l, n);
        }
    public:
        friend class ForwardList;

        Enumerator():
            _list(nullptr),
            _node(nullptr),
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
            return arithmetic::PostIncr(*this);
        }

        Enumerator& operator+=(size_t pos) {
            size_t i = 0;

            while (i++ < pos)
                ++(*this);
        }

        const Enumerator operator+(size_t pos) const {
            return arithmetic::Plus(*this, pos);
        }

        Enumerator operator+(size_t pos) {
            return arithmetic::Plus(*this, pos);
        }

        bool operator==(const Enumerator& other) const {
            return _node == other._node;
        }

        bool operator!=(const Enumerator& other) const {
            return !(*this == other);
        }
    };

    const Enumerator begin() const {
        return Enumerator::forward(_list.loc(), _list->_head);
    }

    Enumerator begin() {
        return Enumerator::forward(_list.loc(), _list->_head);
    }

    const Enumerator end() const {
        return Enumerator();
    }

    bool insert_after(Enumerator& it, const T& t) {
        if (_list != it._list)
            return false;

        if (!any()) {
            push_back(t);
            it._node = _list->_tail;
            return true;
        }

        Node* n = it._node;

        if (!n)
            return false;

        Node* m = new Node{ t, n->next };

        if (!n->next)
            _list->_tail = m;

        n->next = m;
        ++_list->_size;
        return true;
    }

    bool remove_after(Enumerator& it) {
        if (_list != it._list || !any() || !it._node || !it._node->next)
            return false;

        Node* n = it._node->next;
        it._node->next = n->next;

        if (!it._node->next)
            _list->_tail = it._node;

        delete n;
        --_list->_size;
        return true;
    }

    std::string to_string(const std::string& delim = " ") const {
        return enumerable::ToString(*this, delim);
    }

    std::ostream& operator<<(std::ostream& out) const {
        return out << to_string();
    }

    template <typename S>
    friend std::ostream& operator<<(std::ostream&, const ForwardList<S>&);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const ForwardList<T>& o) {
    return out << o.to_string();
}

#endif /* FORWARDLIST_H_ */

