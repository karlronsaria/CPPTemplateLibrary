#include "Array.h"

class What {

};

template <typename T>
int Compare(
    const T & first,
    const T & secnd
) {
    if (first > secnd)
        return 1;

    if (first < secnd)
        return -1;

    return 0;
}

template <
    typename T,
    int (*Order_Relation)(
        const T &,
        const T &
    ) = Compare<T>
    >
class SortedSet {
private:
    class Node {
    public:
        T _payload;
        Node* _left;
        Node* _right;

        Node(const T& payload):
            _payload(payload),
            _left(nullptr),
            _right(nullptr) {}

        Node(const Node& other):
            _payload(other._payload),
            _left(other._left
                ? new Node(other._payload)
                : nullptr
            ),
            _right(other._right
                ? new Node(other._payload)
                : nullptr
            ) {}

        ~Node() {
            delete _left;
            delete _right;
        }

        Node& operator=(const Node& other) {
            return *this = Node(other);
        }

        int find(const T& needle, Node*& parent) {
            switch (Order_Relation(needle, _payload)) {
            case 0:
                return 0;
            case -1:
                if (!_left)
                    return -1;

                parent = _left;
                return _left->find(needle, parent);
            default:
                if (!_right)
                    return 1;

                parent = _right;
                return _right->find(needle, parent);
            }
        }

        void for_each(void (*doThis)(const T&)) {
            if (_left)
                _left->for_each(doThis);

            doThis(_payload);

            if (_right)
                _right->for_each(doThis);
        }
    };

    Node* _top() const {
        Node* cursor = _root;

        while (cursor->_left)
            cursor = cursor->_left;

        return cursor;
    }

    Node* _bot() const {
        Node* cursor = _root;

        while (cursor->_right)
            cursor = cursor->_right;

        return cursor;
    }

    Node* _root;
    size_t _size;
public:
    SortedSet():
        _root(nullptr),
        _size(0) {}

    SortedSet(const SortedSet& other):
        _root(new Node(other._root)),
        _size(other._size) {}

    virtual ~SortedSet() {
        delete _root;
    }

    SortedSet& operator=(const SortedSet& other) {
        return *this = SortedSet(other);
    }

    size_t size() const { return _size; }
    bool any() const { return _size > 0; }

    bool contains(const T& needle) const {
        return _root
            ? _root->find(needle, nullptr) == 0
            : false;
    }

    bool peek(T& item) const {
        if (!any())
            return false;

        item = _top()->_payload;
        return true;
    }

    bool push(const T& needle) {
        bool hasAny = any();
        _size++;

        if (!hasAny) {
            _root = new Node(needle);
            return true;
        }

        Node* temp = _root;

        // todo: optional duplicates
        switch (_root->find(needle, temp)) {
        case 0:
            return false;
        case -1:
            temp->_left = new Node(needle);
            break;
        default:
            temp->_right = new Node(needle);
            break;
        }

        // todo: rebalance
        return true;
    }

    void for_each(void (*doThis)(const T&)) const {
        if (!any())
            return;

        _root->for_each(doThis);
    }

    // // todo
    // bool pop();
    // bool pop(T& item);
    // bool remove(const T&);
};















