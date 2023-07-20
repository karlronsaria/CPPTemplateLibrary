#include "Array.h"

// todo: remove
#include <functional>
#include <stack>

class What {

};

template <typename T>
int Compare(
    const T & first,
    const T & secnd
) {
    return (first > secnd) - (first < secnd);
}

template <
    typename T,
    int (*Order_Relation)(const T &, const T &)
        = Compare<T>
    >
class SortedSet {
private:
    static int h(int ordering) {
        return (ordering + 1) >> 1;
    }

    class Node {
    public:
        T _payload;
        int _factor;
        Node* _children[2];

        Node(const T& payload):
            _payload(payload),
            _factor(0),
            _children{nullptr, nullptr} {}

        Node(const Node& other):
            _payload(other._payload),
            _factor(other._factor),
            _children{
                other._children[0]
                    ? new Node(other._payload)
                    : nullptr,
                other._children[1]
                    ? new Node(other._payload)
                    : nullptr
            } {}

        virtual ~Node() = default;

        Node& operator=(const Node& other) {
            return *this = Node(other);
        }

        const Node*& child(int ordering) const {
            return _children[h(ordering)];
        }

        Node*& child(int ordering) {
            return _children[h(ordering)];
        }

        int find(
            const T& needle,
            Node*& parent,
            std::function<void(Node*, int)> forEach
                = std::function<void(Node*, int)>([](Node* n, int o) {})
        ) {
            int order = Order_Relation(needle, _payload);
            forEach(parent, order);

            if (!order)
                return 0;

            Node* n = child(order);

            if (!n)
                return order;

            return n->find(needle, parent, forEach);
        }

        void for_each(void (*doThis)(const T&)) {
            if (_children[0])
                _children[0]->for_each(doThis);

            doThis(_payload);

            if (_children[1])
                _children[1]->for_each(doThis);
        }
    };

    static int factor(Node* n) {
        return (n == nullptr) * n->_factor;
    }

    static Node* rotate(Node* in, int order) {
        Node* out = in->child(order);
        in->child(order) = out->child(-order);
        out->child(-order) = in;
        in->_factor = out->_factor = 0;
        out->_factor
            = abs(factor(out->_children[1]))
            - abs(factor(out->_children[0]));
        return out;
    }

    static Node* rotate(Node* in, int alph, int beta) {
        if (alph != beta)
            in->child(alph) = rotate(
                in->child(alph)->child(beta),
                beta
            );

        return rotate(in, alph);
    }

    static Node* rebalance(Node* n, int phi, int prevFactor) {
        if (n->child(phi)->_factor - prevFactor == phi)
            n->_factor += phi;

        return abs(n->_factor) > 1
            ? rotate(n, phi, n->child(phi)->_factor)
            : n;
    }

    static Node* replace(Node* n, int phi, T& c) {
        if (!n->child(phi)) {
            c = n->_payload;

            if (!n->child(-phi)) {
                delete n;
                n = nullptr;
            }
            else {
                n->_payload = n->child(-phi)->_payload;
                n->_factor = 0;
                delete n->child(-phi);
                n->child(-phi) = nullptr;
            }

            return n;
        }

        int factor = n->child(-phi)->_factor;
        n->child(-phi) = replace(n->child(-phi), phi, c);
        return rebalance(n, -phi, factor);
    }

    static Node* push(Node* n, T c) {
        int phi = Order_Relation(c, n->_payload);

        if (!phi)
            return nullptr;

        if (!n->child(phi)) {
            n->child(phi) = new Node(c);
            n->_factor += phi;
            return n;
        }

        int factor = n->child(phi)->_factor;
        Node* y = push(n->child(phi), c);

        if (!y)
            return nullptr;

        n->child(phi) = y;
        return rebalance(n, phi, factor);
    }

    Node* top() const {
        Node* cursor = _root;

        while (cursor->_children[0])
            cursor = cursor->_children[0];

        return cursor;
    }

    Node* bot() const {
        Node* cursor = _root;

        while (cursor->_children[1])
            cursor = cursor->_children[1];

        return cursor;
    }

    Node* _root;
    size_t _size;

    static void dealloc(Node* node) {
        if (!node)
            return;

        dealloc(node->_children[0]);
        dealloc(node->_children[1]);
        delete node;
    }
public:
    SortedSet():
        _root(nullptr),
        _size(0) {}

    SortedSet(const SortedSet& other):
        _root(new Node(other._root)),
        _size(other._size) {}

    virtual ~SortedSet() {
        dealloc(_root);
    }

    SortedSet& operator=(const SortedSet& other) {
        return *this = SortedSet(other);
    }

    size_t size() const { return _size; }
    bool any() const { return _size > 0; }

    bool contains(const T& needle) const {
        Node* temp = _root;

        return _root
            ? _root->find(needle, temp) == 0
            : false;
    }

    bool peek(T& item) const {
        if (!any())
            return false;

        item = top()->_payload;
        return true;
    }

    bool push(const T& needle) {
        bool success = !any()
            && (_root = new Node(needle));

        Node* newRoot = nullptr;

        success = success
            || (newRoot = push(_root, needle))
            && (_root = newRoot);

        if (success)
            _size++;

        return success;
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
