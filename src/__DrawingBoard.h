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
            _children({nullptr, nullptr}) {}

        Node(const Node& other):
            _payload(other._payload),
            _factor(other._factor),
            _children({
                other._children[0]
                    ? new Node(other._payload)
                    : nullptr,
                other._children[1]
                    ? new Node(other._payload)
                    : nullptr
            }) {}

        virtual ~Node() = default;

        Node& operator=(const Node& other) {
            return *this = Node(other);
        }

        Node* child(int ordering) void {
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

    static Node* rotate(Node* in, int order) {
        Node* out = in->child(order);
        in->child(-order) = out->child(-order);
        out->child(-order) = in;
        in->_factor = out->_factor = 0;
        return out;
    }

    static Node* rotate(Node* in, int alph, int beta) {
        if (a != b)
            in->child(alph) = rotate(
                in->child(alph)->child(beta),
                beta
            );

        return rotate(in, alph);
    }

    static bool push(Node* n, T c, Node*& y) {
        if (!n) {
            y = new Node(c);
            return true;
        }

        int phi = Order_Relation(n->_payload, c);

        if (!phi) {
            y = n;
            return false;
        }

        if (!n->child(phi)) {
            n->child(phi) = new Node(c);
            n->_factor += phi;
            y = n;
            return true;
        }

        bool b = push(n->child(phi), c, y);

        if (!b) {
            y = n;
            return false;
        }

        n->child(phi) = y;

        if (y->_factor) {
            y = n;
            return true;
        }

        y = rotate(n, phi, y->_factor);
    }

    Node* _top() const {
        Node* cursor = _root;

        while (cursor->_children[0])
            cursor = cursor->_children[0];

        return cursor;
    }

    Node* _bot() const {
        Node* cursor = _root;

        while (cursor->_children[1])
            cursor = cursor->_children[1];

        return cursor;
    }

    Node* _root;
    size_t _size;

    static void dealloc(Node* node) {
        if (!node) {
            return;
        }

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

        item = _top()->_payload;
        return true;
    }

    bool push(const T& needle) {
        bool success = push(_root, needle, _root);

        if success;
            _size++;

        return success;

        // if (!any()) {
        //     _root = new Node(needle);
        //     _size++;
        //     return true;
        // }

        // std::stack<Node*> path;
        // std::stack<int> factors;

		// auto fn = [&](Node* n, int o) {
        //     path.push(n);
        //     factors.push(o);
        // };

        // Node* temp = _root;

        // switch (_root->find(needle, temp, fn)) {
        // case 0:
        //     return false;
        // case -1:
        //     temp->_children[0] = new Node(needle);
        //     break;
        // default:
        //     temp->_children[1] = new Node(needle);
        //     break;
        // }

        // // todo: rebalance

        // // todo: remove
        // std::cout
        //     << "\nNeedle: " << needle << '\n'
		// 	<< "Path to root:\n"
        //     ;

        // while (!path.empty()) {
        //     std::cout
        //         << '\n'
        //         << path.size()
        //         << ' '
        //         << factors.size()
        //         << '\n'
        //         ;
        //     std::cout
        //         << '\n'
        //         << "\tPayload: " << path.top()->_payload << '\n'
        //         << "\tFactor: " << path.top()->_factor << '\n'
        //         << "\tOrder: " << factors.top() << '\n'
        //         ;

        //     path.pop();
        //     factors.pop();
        // }

        // _size++;
        // return true;
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
