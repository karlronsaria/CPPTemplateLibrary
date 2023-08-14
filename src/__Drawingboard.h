
#include "sort.h"
#include "Array.h"
#include <stdlib.h>
#include <time.h>

#define SORTED_SET_TEMPLATE_WITH_DEFAULTS(Type, Bottom, Compare, Default_Compare, Allocator, Default_Allocator) \
template < \
    typename Type, \
    Type Bottom, \
    int (*Compare)(const Type&, const Type&) = Default_Compare, \
    template <typename> class Allocator = Default_Allocator \
>

#define SORTED_SET_TEMPLATE(Type, Bottom, Compare, Allocator) \
template < \
    typename Type, \
    Type Bottom, \
    int (*Compare)(const Type&, const Type&), \
    template <typename> class Allocator \
>

SORTED_SET_TEMPLATE_WITH_DEFAULTS(T, Bottom, Compare, sort::Compare, Alloc, Array)
class SortedSet {
private:
    struct Node {
        T payload = Bottom;
        Alloc<Node*> next;

        Node(size_t size) :
            payload(Bottom),
            next(size, nullptr) {}
    };

    static void (*_singleton)();

    static void set_seed() {
        srand(time(NULL));
        _singleton = []() {};
    }

    Node* _head;
    size_t _size;
    size_t _levels;

    void init() {
        _head = new Node(SortedSet::MAX_LEVELS);
        _size = 0;
        _levels = SortedSet::INIT_LEVELS;
        _singleton();
    }

    static int next_random(int levels) {
        int level = 0;
        int r = rand();

        while (r & 1 && level != levels) {
            ++level;
            r >>= 1;
        }

        return level;
    }

    static bool push(Node* cursor, Node* newNode, int level) {
        // fix
        if (level < 0)
            return true;

        // orbit precondition
        int phi;

        while (1 == (phi = Compare(newNode->payload, cursor->next[level]->payload)))
            cursor = cursor->next[level];

        // iterate
        if (!phi || !push(cursor, newNode, level - 1))
            return false;

        // orbit postcondition
        if (level <= newNode->next.size()) {
            newNode->next[level] = cursor->next[level];
            cursor->next[level] = newNode;
        }

        return true;
    }

    static Node* remove(Node* cursor, const T& p, int level) {
        // fix
        if (level < 0)
            return nullptr;

        // orbit precondition
        int phi;

        while (1 == (phi = Compare(p, cursor->next[level]->payload)))
            cursor = cursor->next[level];

        // iterate
        if (phi || !remove(cursor, p, level - 1))
            return nullptr;

        // orbit postcondition
        Node* temp = nullptr;

        if (level < cursor->next.size()) {
            temp = cursor->next[level];
            cursor->next[level] = cursor->next[level]->next[level];
        }

        return temp;
    }

    Node* clear(Node* n) {
        // fix
        if (!n)
            return nullptr;

        for (size_t i = 0; i < n->next.size(); ++i)
            // iterate
            n->next[i] = clear(n->next[i]);

        // orbit
        delete n;
        return nullptr;
    }
public:
    static const int INIT_LEVELS;
    static const int MAX_LEVELS;

    virtual ~SortedSet() {
        _head = clear(_head);
    }

    SortedSet() {
        init();
    }

    SortedSet(const SortedSet& other) {
        *this = other;
    }

    SortedSet& operator=(const SortedSet& other) {
        _head = clear(_head);
        init();

        for (auto& item : other)
            push(item);

        return *this;
    }

    SortedSet(const std::initializer_list<T>& list) {
        *this = list;
    }

    SortedSet& operator=(const std::initializer_list<T>& list) {
        _head = clear(_head);
        init();

        for (auto& item : list)
            push(item);

        return *this;
    }

    size_t size() const { return _size; }
    bool any() const { return _size; }

    bool push(const T& payload) {
        Node* n = new Node(next_random(_levels) + 1);

        if (!push(_head, n, _levels - 1)) {
            delete n;
            return false;
        }

        ++_size;
        return true;
    }

    bool remove(const T& payload) {
        Node* n = remove(_head, payload, _levels - 1);

        if (!n)
            return false;

        delete n;
        --_size;
        return true;
    }

    bool contains(const T& payload) const {
        Node* cursor = _head;
        int phi;

        for (int i = _levels - 1; i >= 0; --i)
            while (cursor->next[i]
                && 1 == (phi = Compare(payload, cursor->next[i]->payload))
            )
                if (phi == 0)
                    return true;

        return false;
    }

    class Enumerator {
    private:
        Node* _ptr;

        Enumerator(Node* ptr) :
            _ptr(ptr) {}
    public:
        friend class SortedSet;

        Enumerator() : _ptr(nullptr) {}
        Enumerator(const Enumerator&) = default;
        virtual ~Enumerator() = default;
        Enumerator& operator=(const Enumerator&) = default;

        const T& operator*() const {
            return _ptr->payload;
        }

        const T* operator->() const {
            return &_ptr->payload;
        }

        Enumerator& operator++() {
            _ptr = _ptr->next[0];
            return *this;
        }

        Enumerator& operator++(int) {
            return arithmetic::PostIncr(*this);
        }

        Enumerator& operator+=(size_t len) {
            for (size_t i = 1; i <= len; ++i)
                ++(*this);

            return *this;
        }

        const Enumerator operator+(int len) const {
            return arithmetic::Plus(*this, len);
        }

        Enumerator operator+(int len) {
            return arithmetic::Plus(*this, len);
        }

        bool operator==(const Enumerator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const Enumerator& other) const {
            return !(*this == other);
        }
    };

    const Enumerator begin() const {
        return Enumerator(_head);
    }

    Enumerator begin() {
        return Enumerator(_head);
    }

    const Enumerator end() const {
        return Enumerator(nullptr);
    }

    const T& operator[](size_t index) const {
        auto it = begin();

        for (size_t i = 0; i < index; ++i)
            ++it;

        return it->payload;
    }

    std::string to_string(const std::string& delim = " ") const {
        return enumerable::ToString(*this, delim);
    }

    std::ostream& operator<<(std::ostream& out) const {
        return out << to_string();
    }

    SORTED_SET_TEMPLATE(T, B, C, A)
    friend std::ostream& operator<<(std::ostream&, const SortedSet<T, B, C, A>&);
};

SORTED_SET_TEMPLATE(T, B, C, A)
std::ostream& operator<<(std::ostream& out, const SortedSet<T, B, C, A>& o) {
    return out << o.to_string();
}

SORTED_SET_TEMPLATE(T, B, C, A)
void (*SortedSet<T, B, C, A>::_singleton)() = SortedSet<T, B, C, A>::set_seed;

SORTED_SET_TEMPLATE(T, B, C, A)
const int SortedSet<T, B, C, A>::INIT_LEVELS = 1;

SORTED_SET_TEMPLATE(T, B, C, A)
const int SortedSet<T, B, C, A>::MAX_LEVELS = 33;

#undef SORTED_SET_TEMPLATE_WITH_DEFAULTS
#undef SORTED_SET_TEMPLATE

