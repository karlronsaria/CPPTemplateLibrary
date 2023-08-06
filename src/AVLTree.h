#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <functional>

namespace avltree {
    template <
        typename T,
        int (*Order_Relation)(const T&, const T&)
    >
    class Node {
    public:
        T _payload;
        int _factor;
        Node* _children[2];

        Node(const T& payload):
            _payload(payload),
            _factor(0),
            _children{ nullptr, nullptr } {}

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

        static int h(int r) {
            return (r + 1) >> 1;
        }

        const Node*& child(int phi) const {
            return _children[h(phi)];
        }

        Node*& child(int phi) {
            return _children[h(phi)];
        }

        void for_each(std::function<void(const T&)> doThis) {
            if (_children[0])
                _children[0]->for_each(doThis);

            doThis(_payload);

            if (_children[1])
                _children[1]->for_each(doThis);
        }
    };

    template <typename T>
    struct NodeInfo
    {
        bool any = false;
        int factor = 0;
        T payload = T();
    };

    template <typename N>
    void dealloc(N* node) {
        if (!node)
            return;

        dealloc(node->_children[0]);
        dealloc(node->_children[1]);
        delete node;
    }

    template <typename N>
    int factor(N* n) {
        return n == nullptr ? 0 : n->_factor;
    }

    template <typename N>
    int factor(N* a, N* b) {
        return (!b ? -1 : abs(b->_factor))
            - (!a ? -1 : abs(a->_factor));
    }

    template <typename N>
    int new_factor(N* n) {
        return factor(n->child(-1), n->child(1));
    }

    template <typename N>
    N* rotate(N* in, int phi) {
        N* out = in->child(phi);
        in->child(phi) = out->child(-phi);
        out->child(-phi) = in;
        return out;
    }

    template <typename N>
    N* rotate(N* in, int alph, int beta) {
        auto x = in;
        auto z = in->child(alph);
        auto y = z->child(beta);

        if (alph != beta)
            in->child(alph) = rotate(
                in->child(alph),
                beta
            );

        auto out = rotate(in, alph);

        // # link
        // - url: https://en.wikipedia.org/wiki/AVL_tree#Rebalancing
        // - retrieved: 2023_08_05
        if (alph == beta) {
            x->_factor = (z->_factor == 0) * alph;
            z->_factor = -x->_factor;
        }
        else {
            if (!y->_factor) {
                x->_factor = 0;
                z->_factor = 0;
            }
            else {
                //  b       y       x       z
                //  -------------------------
                //  
                //  1       1       0      -1
                //  
                //         -1       1       0
                //  
                // -1       1      -1       0
                //  
                //         -1       0       1

                x->_factor = (beta - y->_factor) / 2;
                z->_factor = (x->_factor == 0) * -beta;
            }

            y->_factor = 0;
        }

        return out;
    }

    template <typename N>
    N* rebalance(N* n, int phi, int prevFactor, int nextFactor, int opposite, bool reverse) {
        if (!reverse == (bool)(nextFactor && (nextFactor - prevFactor)))
            n->_factor += phi;

        return abs(n->_factor) > 1
            ? rotate(n, phi, opposite ? opposite : phi)
            : n;
    }

    template <
        typename T,
        int (*R)(const T&, const T&)
    >
    Node<T, R>* pop(Node<T, R>* n, int phi, T& c) {
        if (!n)
            return nullptr;

        if (n->child(phi)) {
            int factor = avltree::factor(n->child(phi));
            n->child(phi) = pop(n->child(phi), phi, c);
            int nextFactor = avltree::factor(n->child(phi));
            int opposite = avltree::factor(n->child(-phi));

            return rebalance(
                n,
                -phi,
                factor,
                nextFactor,
                opposite,
                true
            );
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

    template <
        typename T,
        int (*R)(const T&, const T&)
    >
    bool remove(Node<T, R>* n, const T& z, Node<T, R>*& m) {
        if (!n) {
            m = nullptr;
            return false;
        }

        int factor = 0;
        int phi = R(z, n->_payload);

        if (!phi) {
            int lean = -1;

            if (!n->child(lean)) {
                if (n->child(-lean)) {
                    n->_payload = n->child(-lean)->_payload;
                    delete n->child(-lean);
                    n->child(-lean) = nullptr;
                    n->_factor = 0;
                    m = n;
                }
                else {
                    delete n;
                    m = nullptr;
                }

                return true;
            }

            factor = avltree::factor(n->child(lean));
            n->child(lean) = pop(n->child(lean), -lean, n->_payload);
        }
        else {
            factor = avltree::factor(n->child(phi));

            if (!remove(n->child(phi), z, m))
                return false;

            n->child(phi) = m;
        }

        int nextFactor = avltree::factor(n->child(phi));
        int opposite = avltree::factor(n->child(-phi));

        m = rebalance(
            n,
            -phi,
            factor,
            nextFactor,
            opposite,
            true
        );

        return true;
    }

    template <
        typename T,
        int (*R)(const T&, const T&)
    >
    Node<T, R>* push(Node<T, R>* n, T c) {
        int phi = R(c, n->_payload);

        if (!phi)
            return nullptr;

        if (!n->child(phi)) {
            n->child(phi) = new Node<T, R>(c);
            n->_factor += phi;
            return n;
        }

        int factor = n->child(phi)->_factor;
        Node<T, R>* y = push(n->child(phi), c);

        if (!y)
            return nullptr;

        n->child(phi) = y;
        int nextFactor = avltree::factor(n->child(phi));
        return rebalance(n, phi, factor, nextFactor, nextFactor, false);
    }

    template <
        typename T,
        int (*R)(const T&, const T&)
    >
    void to_vector(
        Node<T, R>* n,
        int index,
        std::vector<avltree::NodeInfo<T>>& list
    ) {
        int next = 2 * (index + 1);

        if (next + 1 > list.size())
			list.resize(next + 1);

        if (!n) {
            list[index] = avltree::NodeInfo<T>{false, 0, T()};
            return;
        }

        list[index] = avltree::NodeInfo<T>{
            true,
            n->_factor,
            n->_payload
        };

        to_vector(n->_children[0], next - 1, list);
        to_vector(n->_children[1], next, list);
    }

    template <
        typename T,
        int (*R)(const T&, const T&)
    >
    static int
    find(
        Node<T, R>* n,
        const T& needle,
        Node<T, R>*& parent,
        std::function<void(Node<T, R>*, int)> forEach
            = std::function<void(Node<T, R>*, int)>(
                [](Node<T, R>* n, int o) {}
            )
    ) {
        int phi = R(needle, n->_payload);
        forEach(parent, phi);

        if (!phi)
            return 0;

        Node<T, R>* m = n->child(phi);

        if (!m)
            return phi;

        return find(m, needle, parent, forEach);
    }
}

#endif /* AVLTREE_H_ */
