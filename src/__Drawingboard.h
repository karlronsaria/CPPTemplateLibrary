
#include "sort.h"
#include "Array.h"
#include <stdlib.h>
#include <time.h>

/*
class Latt:
    Latt()
    static bot: -> Latt
    static compare: Latt -> Latt -> int
*/

template <typename Latt, template <typename Latt> class Alloc = Array>
class SortedSet {
private:
    struct Node {
        Latt payload = Latt();
        Alloc<Node*> next;
    };

    static void (*_singleton)();

    void set_seed() {
        srand(time(NULL));
        _singleton = []() {};
    }

    void init() {
        _head = new Node{ Latt::bot(), SortedSet::MAX_LEVELS };
        _levels = SortedSet::INIT_LEVELS;
        _singleton();
    }

    Node* _head;
    size_t _levels;

    static int next_random(int levels) {
        int level = 0;
        int r = rand();

        while (r & 1 && level != levels) {
            ++level;
            r >>= 1;
        }

        return level;
    }

    static bool push(Node* cursor, Node* newNode, int level, int levels) {
        // fix
        if (level < 0)
            return true;

        // orbit precondition
        int phi;

        while (1 == (phi = Latt::compare(newNode->payload, cursor->next[level]->payload)))
            cursor = cursor->next[level];

        // iterate
        if (!phi || !push(cursor, newNode, level - 1, levels))
            return false;

        // orbit postcondition
        if (level <= levels) {
            newNode->next[level] = cursor->next[level];
            cursor->next[level] = newNode;
        }

        return true;
    }

    static Node* remove(Node* cursor, const Latt& p, int level) {
        // fix
        if (level < 0)
            return nullptr;

        // orbit precondition
        int phi;

        while (1 == (phi = Latt::compare(p, cursor->next[level]->payload)))
            cursor = cursor->next[level];

        // iterate
        if (phi || !remove(cursor, p, level - 1))
            return nullptr;

        Node* temp = nullptr;

        if (level < cursor->next.size()) {
            temp = cursor->next[level];
            cursor->next[level] = cursor->next[level]->next[level];
        }

        return temp;
    }
public:
    static const int INIT_LEVELS;
    static const int MAX_LEVELS;

    virtual ~SortedSet() {
        // todo
    }

    SortedSet() {
        init();
    }

    SortedSet(const SortedSet& other) {
        // todo
    }

    SortedSet& operator=(const SortedSet& other) {
        // todo
    }

    bool push(const Latt& payload) {
        Node* n = new Node{ payload, level + 1 };

        if (!push(_head, n, _levels - 1, next_random(_levels))) {
            delete n;
            return false;
        }

        return true;
    }

    bool remove(const Latt& paylaod) {
        Node* n = remove(_head, payload, _levels - 1);

        if (!n)
            return false;

        delete n;
        return true;
    }

    bool contains(const Latt& payload) const {
        Node* cursor = _head;
        int phi;

        for (int i = _levels - 1; i >= 0; --i)
            while (cursor->next[i]
                && 1 == (phi = Latt::compare(payload, cursor->next[i]->payload))
            )
                if (phi == 0)
                    return true;

        return false;
    }
};

template <typename T, template <typename T> class Alloc>
void (SortedSet<T, Alloc>::*_singleton)() = Sorted<T, Alloc>::set_seed;

template <typename T, template <typename T> class Alloc>
static const int SortedSet<T, Alloc>::INIT_LEVELS = 1;

template <typename T, template <typename T> class Alloc>
static const int SortedSet<T, Alloc>::MAX_LEVELS = 33;





