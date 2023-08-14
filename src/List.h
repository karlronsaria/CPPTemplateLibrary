#ifndef LIST_H_
#define LIST_H_

#include "arithmetic.h"
#include "enumerable.h"
#include "scoped_ptr.h"
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

    struct Deque {
        Node* _head = nullptr;
        Node* _tail = nullptr;
        size_t _size = 0L;
    };

    scoped_ptr<Deque> _list;

    static size_t to_index(size_t size, int pos) {
        return pos >= 0 ? (size_t)pos : size + (size_t)pos;
    }

    static Node* at(const Deque& list, int pos) {
        Node* n = nullptr;
        int i = 0;

        if (pos < 0) {
            i = -1;
            n = list._tail;

            while (i-- > pos)
                n = n->prev;
        }
        else {
            n = list._head;

            while (i++ < pos)
                n = n->next;
        }

        return n;
    }

    static void clear(Deque& list) {
        switch (list._size) {
        case 0:
            break;
        case 1:
            delete list._head;
            break;
        default:
            auto n = list._head->next;

            while (n->next) {
                delete n->prev;
                n = n->next;
            }

            delete n->prev;
            delete n;
            break;
        }
    }

    static void push_back(Deque& list, const T& t) {
        bool hasAny = list._size;
        ++list._size;

        if (!hasAny) {
            list._head = new Node{ t, nullptr, nullptr };
            list._tail = list._head;
            return;
        }

        auto n = new Node{ t, list._tail, nullptr };
        list._tail->next = n;
        list._tail = n;
    }

    static void push_front(Deque& list, const T& t) {
        bool hasAny = list._size;
        ++list._size;

        if (!hasAny) {
            list._head = new Node{ t, nullptr, nullptr };
            list._tail = list._head;
            return;
        }

        auto n = new Node{ t, nullptr, list._head };
        list._head->prev = n;
        list._tail = n;
    }

    static bool pop_back(Deque& list) {
        if (!list._size)
            return false;

        auto n = list._head;
        list._head = n->next;
        list._head->prev = nullptr;
        delete n;
        --list._size;
        return true;
    }

    static bool pop_front(Deque& list) {
        if (!list._size)
            return false;

        auto n = list._tail;
        list._tail = n->prev;
        list._tail->next = nullptr;
        delete n;
        --list._size;
        return false;
    }

    static void copy(Deque& list, Deque& o) {
        clear(list);
        auto n = o._head;

        while (n) {
            push_back(list, n->payload);
            n = n->next;
        }
    }

    static void insert(Deque& list, const T& t, size_t pos) {
        auto next = list._head;
        size_t i = 0;

        while (i++ < pos)
            next = next->next;

        auto prev = next->prev;
        auto n = new Node{ t, prev, next };
        prev->next = n;
        next->prev = n;
        ++list._size;
    }

    static void remove(Deque& list, size_t pos) {
        auto n = list._head;
        size_t i = 0;

        while (i++ < pos)
            n = n->next;

        n->prev->next = n->next;
        n->next->prev = n->prev;
        delete n;
        --list._size;
    }
public:
    List():
        _list(new Deque()) {}

    virtual ~List() {
        clear();
    }

    List(const List& other):
        _list(new Deque())
    {
        *this = other;
    }

    List& operator=(const List& other) {
        copy(*_list, *(Deque*)other._list);
        return *this;
    }

    List(const std::initializer_list<T>& list):
        _list(new Deque())
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

    List& push_back(const T& t) {
        push_back(*_list, t);
        return *this;
    }

    List& push_back() {
        return push_back(T());
    }

    List& push_front(const T& t) {
        push_front(*_list, t);
        return *this;
    }

    List& push_front() {
        return push_front(T());
    }

    bool pop_back() {
        return pop_back(*_list);
    }

    bool pop_front() {
        return pop_front(*_list);
    }

    List& insert(const T& t, int pos) {
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

        insert(*_list, t, p);
        return *this;
    }

    bool remove(int pos) {
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

    List& clear() {
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

    List& resize(size_t len) {
        while (size() < len)
            push_back();

        while (size() > len)
            pop_back();

        return *this;
    }

    class Enumerator {
    private:
        typedef typename scoped_ptr<Deque>::locator list_ptr;

        list_ptr _list;
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

        Enumerator(list_ptr l, Node* n):
            _list(l),
            _node(n),
            _prev(&default_prev),
            _next(&default_next) {}

        Enumerator(list_ptr l, Node* n, Node* (*prev)(Node*), Node* (*next)(Node*)):
            _list(l),
            _node(n),
            _prev(prev),
            _next(next) {}

        static Enumerator forward(list_ptr l, Node* n) {
            return Enumerator(l, n);
        }

        static Enumerator reverse(list_ptr l, Node* n) {
            return Enumerator(l, n, &default_next, &default_prev);
        }
    public:
        friend class List;

        Enumerator():
            _list(nullptr),
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
            return arithmetic::PostIncr(*this);
        }

        Enumerator& operator--() {
            // fails fast
            _node = _prev(_node);
            return *this;
        }

        Enumerator operator--(int) {
            // fails fast
            return arithmetic::PostDecr(*this);
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
            return arithmetic::Plus(*this, pos);
        }

        Enumerator operator+(int pos) {
            return arithmetic::Plus(*this, pos);
        }

        const Enumerator operator-(int pos) const {
            return arithmetic::Plus(*this, -pos);
        }

        Enumerator operator-(int pos) {
            return arithmetic::Plus(*this, -pos);
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

    const Enumerator begin_reverse() const {
        return Enumerator::reverse(_list.loc(), _list->_tail);
    }

    Enumerator begin_reverse() {
        return Enumerator::reverse(_list.loc(), _list->_tail);
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

        Node* m = new Node{ t, n, n->next };
        (n->next ? n->next->prev : _list->_tail) = m;
        n->next = m;
        ++_list->_size;
        return true;
    }

    bool insert_before(Enumerator& it, const T& t) {
        if (_list != it._list)
            return false;

        if (!any()) {
            push_front();
            it._node = _list->_head;
            return true;
        }

        Node* n = it._node;

        if (!n)
            return false;

        Node* m = new Node{ t, n->prev, n };
        (n->prev ? n->prev->next : _list->_head) = m;
        n->prev = m;
        ++_list->_size;
        return true;
    }

    bool remove(Enumerator& it) {
        if (_list != it._list || !any() || !it._node)
            return false;

        Node* n = it._node;

        if (!n->prev) {
            bool success = pop_front();
            it._node = _list->_head;
            return success;
        }

        if (!n->next) {
            bool success = pop_back();
            it._node = _list->_tail;
            return success;
        }

        n->prev->next = n->next;
        n->next->prev = n->prev;
        it._node = n->next;
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
    friend std::ostream& operator<<(std::ostream&, const List<S>&);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& o) {
    return out << o.to_string();
}

#endif /* LIST_H_ */
