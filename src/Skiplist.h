#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

#include "sort.h"
#include "Array.h"
#include <stdlib.h>
#include <time.h>

#define SORTED_SET_TEMPLATE_WITH_DEFAULTS(Type, Compare, Default_Compare, Allocator, Default_Allocator) \
template < \
    typename Type, \
    int (*Compare)(const Type&, const Type&) = Default_Compare, \
    template <typename> class Allocator = Default_Allocator \
>

#define SORTED_SET_TEMPLATE(Type, Compare, Allocator) \
template < \
    typename Type, \
    int (*Compare)(const Type&, const Type&), \
    template <typename> class Allocator \
>

#define SORTED_MAP_TEMPLATE_WITH_DEFAULTS(Key_Type, Value_Type, Compare, Default_Compare, Allocator, Default_Allocator) \
template < \
    typename Key_Type, \
    typename Value_Type, \
    int (*Compare)(const Key_Type&, const Key_Type&) = Default_Compare, \
    template <typename> class Allocator = Default_Allocator \
>

#define SORTED_MAP_TEMPLATE(Key_Type, Value_Type, Compare, Allocator) \
template < \
    typename Key_Type, \
    typename Value_Type, \
    int (*Compare)(const Key_Type&, const Key_Type&), \
    template <typename> class Allocator \
>

namespace skiplist {
    template <typename T, template <typename> class Alloc>
    struct Node {
        T payload;
        Alloc<Node*> next;

        Node(size_t size) :
            next(size, nullptr) {}

        Node(const T& p, size_t size) :
            payload(p),
            next(size, nullptr) {}
    };

    inline static size_t next_random(size_t levels) {
        size_t level = 0;
        size_t r = rand();

        while (r & 1 && level != levels) {
            ++level;
            r >>= 1;
        }

        return level;
    }

    SORTED_SET_TEMPLATE(T, C, A)
    static bool push(Node<T, A>* cursor, Node<T, A>* newNode, int level) {
        // fix
        if (level < 0)
            return true;

        // orbit precondition
        int phi = -1;

        while (
            cursor->next[level]
            && 1 == (phi = C(newNode->payload, cursor->next[level]->payload))
            )
            cursor = cursor->next[level];

        // iterate
        if (!phi || !push<T, C, A>(cursor, newNode, level - 1))
            return false;

        // orbit postcondition
        if (level <= newNode->next.size()) {
            newNode->next[level] = cursor->next[level];
            cursor->next[level] = newNode;
        }

        return true;
    }

    SORTED_SET_TEMPLATE(T, C, A)
    static Node<T, A>* remove(Node<T, A>* cursor, const T& p, int level) {
        // fix
        if (level < 0)
            return nullptr;

        // orbit precondition
        int phi = -1;

        while (
            cursor->next[level]
            && 1 == (phi = C(p, cursor->next[level]->payload))
            )
            cursor = cursor->next[level];

        // iterate
        if (phi && !remove<T, C, A>(cursor, p, level - 1))
            return nullptr;

        // orbit postcondition
        Node<T, A>* temp = nullptr;

        if (level < cursor->next.size()) {
            temp = cursor->next[level];
            cursor->next[level] = cursor->next[level]->next[level];
        }

        return temp;
    }

    template <typename T, template <typename> class A>
    static Node<T, A>* clear(Node<T, A>* n) {
        // fix
        if (!n)
            return nullptr;

        for (size_t i = 0; i < n->next.size(); ++i)
            // iterate
            n->next[i] = clear<T, A>(n->next[i]);

        // orbit
        delete n;
        return nullptr;
    }

    SORTED_SET_TEMPLATE_WITH_DEFAULTS(T, R, sort::Compare<T>, Alloc, Array)
    class SortedSet: public Collection {
    public:
    private:
        static void (*_singleton)();

        static void set_seed() {
            srand(time(nullptr));
            _singleton = []() {};
        }

        Node<T, Alloc>* _head;
        size_t _size;
        size_t _levels;

        void init() {
            _head = new Node<T, Alloc>(SortedSet::MAX_LEVELS);
            _size = 0;
            _levels = SortedSet::INIT_LEVELS;
            _singleton();
        }
    public:
        static const int INIT_LEVELS;
        static const int MAX_LEVELS;

        virtual ~SortedSet() {
            _head = skiplist::clear(_head);
        }

        SortedSet() {
            init();
        }

        SortedSet& operator=(const SortedSet& other) {
            _head = skiplist::clear<T, Alloc>(_head);
            init();

            for (auto& item : other)
                skiplist::push<T, R, Alloc>(item);

            return *this;
        }

        SortedSet(const SortedSet& other) {
            *this = other;
        }

        SortedSet& operator=(const std::initializer_list<T>& list) {
            _head = skiplist::clear<T, Alloc>(_head);
            init();

            for (auto& item : list)
                skiplist::push<T, R, Alloc>(item);

            return *this;
        }

        SortedSet(const std::initializer_list<T>& list) {
            *this = list;
        }

        size_t size() const { return _size; }
        bool any() const { return _size; }

        bool push(const T& payload) {
            auto n = new Node<T, Alloc>(payload, next_random(_levels) + 1);

            if (!skiplist::push<T, R, Alloc>(_head, n, _levels - 1)) {
                delete n;
                return false;
            }

            ++_size;
            return true;
        }

        bool remove(const T& payload) {
            auto n = skiplist::remove<T, R, Alloc>(
                _head,
                payload,
                _levels - 1
            );

            if (!n)
                return false;

            delete n;
            --_size;
            return true;
        }

        bool contains(const T& payload) const {
            auto cursor = _head;
            int phi = 1;

            for (int i = _levels - 1; i >= 0; --i) {
                while (cursor->next[i]
                    && 1 == (phi = R(payload, cursor->next[i]->payload))
                    )
                    cursor = cursor->next[i];

                if (!phi)
                    return true;
            }

            return false;
        }

        class Enumerator {
        private:
            Node<T, Alloc>* _ptr;

            Enumerator(Node<T, Alloc>* ptr) :
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
            return Enumerator(_head->next[0]);
        }

        Enumerator begin() {
            return Enumerator(_head->next[0]);
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

        SORTED_SET_TEMPLATE(T, C, A)
        friend std::ostream& operator<<(std::ostream&, const SortedSet<T, C, A>&);
    };

    SORTED_SET_TEMPLATE(T, C, A)
    std::ostream& operator<<(std::ostream& out, const SortedSet<T, C, A>& o) {
        return out << o.to_string();
    }

    SORTED_SET_TEMPLATE(T, C, A)
    void (*SortedSet<T, C, A>::_singleton)() = SortedSet<T, C, A>::set_seed;

    SORTED_SET_TEMPLATE(T, C, A)
    const int SortedSet<T, C, A>::INIT_LEVELS = 1;

    SORTED_SET_TEMPLATE(T, C, A)
    const int SortedSet<T, C, A>::MAX_LEVELS = 33;

    SORTED_MAP_TEMPLATE_WITH_DEFAULTS(KeyT, ValueT, R, sort::Compare, Alloc, Array)
    class SortedMap: public Collection {
    public:
        struct Pair {
            KeyT key;
            ValueT value;
        };
    private:
        static int _compare(const Pair& f, const Pair& s) {
            return R(f.key, s.key);
        }

        SortedSet<Pair, _compare, Alloc>
        _set;
    public:
        virtual ~SortedMap() = default;
        SortedMap() = default;
        SortedMap(const SortedMap&) = default;
        SortedMap& operator=(const SortedMap&) = default;

        size_t size() const { return _set.size(); }
        bool any() const { return _set.size(); }

        bool contains(const KeyT& key) const {
            return _set.contains(Pair{ key, ValueT() });
        }

        bool push(const KeyT& key, const ValueT& value) {
            return _set.push(Pair{ key, value });
        }

        bool remove(const KeyT& key) {
            return _set.remove(Pair{ key, ValueT() });
        }

        class Enumerator: public SortedSet<Pair, _compare, Alloc>::Enumerator {};

        const Enumerator begin() const {
            return _set.begin();
        }

        Enumerator begin() {
            return _set.begin();
        }

        const Enumerator end() const {
            return _set.end();
        }

        const Pair& operator[](size_t index) const {
            auto it = begin();

            for (size_t i = 0; i < index; ++i)
                ++it;

            return it->payload;
        }

        std::string to_string(const std::string& delim = " ") const {
            return enumerable::ToString<SortedSet<Pair, _compare, Alloc>, Pair>(
                _set, delim,
                [](const Pair& p) -> std::string {
					std::ostringstream oss;
					oss << p.key << ':' << p.value;
					return oss.str();
				});
        }

        std::ostream& operator<<(std::ostream& out) const {
            return out << to_string();
        }

        SORTED_MAP_TEMPLATE(K, V, R, A)
        friend std::ostream& operator<<(std::ostream&, const SortedMap<K, V, R, A>&);
    };

    SORTED_MAP_TEMPLATE(K, V, R, A)
    std::ostream& operator<<(std::ostream& out, const SortedMap<K, V, R, A>& o) {
        return out << o.to_string();
    }
}

#undef SORTED_SET_TEMPLATE_WITH_DEFAULTS
#undef SORTED_SET_TEMPLATE
#undef SORTED_MAP_TEMPLATE_WITH_DEFAULTS
#undef SORTED_MAP_TEMPLATE
#endif /* SKIPLIST_H_ */

