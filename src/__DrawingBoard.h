#include "Array.h"

// todo: remove
#include <functional>
#include <stack>

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
public:
    struct NodeInfo
    {
        bool any = false;
        int factor = 0;
        T payload = T();
    };
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

        void for_each(std::function<void(const T&)> doThis) {
            if (_children[0])
                _children[0]->for_each(doThis);

            doThis(_payload);

            if (_children[1])
                _children[1]->for_each(doThis);
        }
    };

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

    static int factor(Node* n) {
        return n == nullptr ? 0 : n->_factor;
    }

    static Node* rotate(Node* in, int order) {
        Node* out = in->child(order);
        in->child(order) = out->child(-order);
        out->child(-order) = in;
        in->_factor = out->_factor = 0;
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

    static Node* rebalance(Node* n, int phi, int prevFactor, bool reverse) {
        int nextFactor = factor(n->child(phi));

        if (!reverse == (bool)(nextFactor && (nextFactor - prevFactor)))
            n->_factor += phi;

        return abs(n->_factor) > 1
            ? rotate(n, phi, nextFactor ? nextFactor : phi)
            : n;
    }

    static Node* replace(Node* n, int phi, T& c) {
        if (!n)
            return nullptr;

        if (n->child(phi)) {
            int factor = SortedSet::factor(n->child(phi));
            n->child(phi) = replace(n->child(phi), phi, c);
            return rebalance(n, -phi, factor, true);
        }

		c = n->_payload;

		if (!n->child(-phi)) {
			delete n;
            return nullptr;
		}

		n->_payload = n->child(-phi)->_payload;
		n->_factor = 0;
		delete n->child(-phi);
		n->child(-phi) = nullptr;
		return n;
    }

    static bool remove(Node* n, const T& z, Node*& m) {
        if (!n) {
            m = nullptr;
            return false;
        }

        int factor = 0;
        int phi = Order_Relation(z, n->_payload);

        if (!phi) {
            int lean = -1;

            if (!n->child(lean)) {
                delete n;
                m = nullptr;
                return true;
            }

            factor = SortedSet::factor(n->child(lean));
            n->child(lean) = replace(n->child(lean), -lean, n->_payload);
        }
        else {
            factor = SortedSet::factor(n->child(phi));

            if (!remove(n->child(phi), z, m))
                return false;

            n->child(phi) = m;
        }

        m = rebalance(n, -phi, factor, true);
        return true;
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
        return rebalance(n, phi, factor, false);
    }

    static void to_vector(
        Node* n,
        int index,
        std::vector<NodeInfo>& list
    ) {
        list.resize(2 * (index + 1) + 1);

        if (!n) {
            list[index] = NodeInfo{false, 0, T()};
            return;
        }

        list[index] = NodeInfo{true, n->_factor, n->_payload};
        index = 2 * (index + 1);
        to_vector(n->_children[0], index - 1, list);
        to_vector(n->_children[1], index, list);
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

    bool remove(const T& needle) {
        if (!_size)
            return false;

        Node* newRoot = nullptr;

        if (!remove(_root, needle, newRoot))
            return false;

        _size--;
        _root = newRoot;
        return true;
    }

    bool pop(T& top) {
        if (!any())
            return false;

        top = _root->_payload;
		int factor = SortedSet::factor(_root->child(-1));
		_root->child(-1) = replace(_root->child(-1), 1, _root->_payload);
        _root = rebalance(_root, -1, factor, true);
        return true;
    }

    bool pop() {
        if (!any())
            return false;

        T temp;
        _root = replace(_root, -1, temp);
        return true;
    }

    void for_each(std::function<void(const T&)> doThis) const {
        if (!any())
            return;

        _root->for_each(doThis);
    }

    std::vector<NodeInfo>
    to_vector() const {
        std::vector<NodeInfo> list;
        to_vector(_root, 0, list);
        return list;
    }
};
