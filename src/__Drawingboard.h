#include <initializer_list>

template <typename T>
class List {
private:
    struct Node {
        T payload = T();
        Node* prev = nullptr;
        Node* next = nullptr;
    };

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

    List(const List& other) {
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

    List(const std::initializer_list<T>& list) {
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
        return _size;
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
private:
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
public:
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

    class Iterator {
    private:
        Node* _pointer;
        Node* (*_prev)(Node*);
        Node* (*_next)(Node*);

        static Node* default_next(Node* n) {
            return n->next;
        }

        static Node* default_prev(Node* n) {
            return n->prev;
        }

        Iterator(Node* n):
            _pointer(n),
            _prev(&default_prev),
            _next(&default_next) {}

        Iterator(Node* n, Node* (*prev)(Node*), Node* (*next)(Node*)) :
            _pointer(n),
            _prev(prev),
            _next(next) {}

        static Iterator reverse(Node* n) {
            return Iterator(n, &default_next, &default_prev);
        }
    public:
        friend class List;

        Iterator():
            _pointer(nullptr),
            _prev(&default_prev),
            _next(&default_next) {}

        virtual ~Iterator() = default;
        Iterator(const Iterator&) = default;
        Iterator& operator=(const Iterator&) = default;

        const T& operator*() const {
            // fails fast
            return _pointer->payload;
        }

        T& operator*() {
            // fails fast
            return _pointer->payload;
        }

        const T* operator->() const {
            // fails fast
            return &_pointer->payload;
        }

        T* operator->() {
            // fails fast
            return &_pointer->payload;
        }

        Iterator& operator++() {
            // fails fast
            _pointer = _next(_pointer);
            return *this;
        }

        Iterator operator++(int) {
            // fails fast
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            // fails fast
            _pointer = _prev(_pointer);
            return *this;
        }

        Iterator operator--(int) {
            // fails fast
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        Iterator& operator+=(int pos) {
            int i = 0;

            while (i < pos)
                ++(*this);

            while (i > pos)
                ++(*this);

            return *this;
        }

        Iterator& operator-=(int pos) {
            *this += -pos;
        }

        const Iterator operator+(int pos) const {
            Iterator temp(*this);
            temp += pos;
            return pos;
        }

        Iterator operator+(int pos) {
            Iterator temp(*this);
            temp += pos;
            return pos;
        }

        const Iterator operator-(int pos) const {
            Iterator temp(*this);
            temp -= pos;
            return pos;
        }

        Iterator operator-(int pos) {
            Iterator temp(*this);
            temp -= pos;
            return pos;
        }

        bool operator==(const Iterator& other) const {
            return _pointer == other._pointer;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    const Iterator begin() const {
        return Iterator(_head);
    }

    Iterator begin() {
        return Iterator(_head);
    }

    const Iterator begin_reverse() const {
        return Iterator::reverse(_tail);
    }

    Iterator begin_reverse() {
        return Iterator::reverse(_tail);
    }

    const Iterator end() const {
        return Iterator();
    }
};































