#ifndef AVLSORTEDSET_H_
#define AVLSORTEDSET_H_

#include "avltree.h"
#include "sort.h"
#include "Collection.h"

template <
    typename T,
    int (*R)(const T&, const T&) = sort::Compare<T>
>
class SortedSet: public Collection {
private:
    typedef avltree::Node<T, R> N;
    N* _root;
    size_t _size;

    N* top() const {
        N* cursor = _root;

        while (cursor->_children[0])
            cursor = cursor->_children[0];

        return cursor;
    }

    N* bot() const {
        N* cursor = _root;

        while (cursor->_children[1])
            cursor = cursor->_children[1];

        return cursor;
    }
public:
    bool at(const T& needle, T& out) const {
        N* temp = _root;

        if (_root && !avltree::find(_root, needle, temp)) {
            out = temp->_payload;
            return true;
        }

        return false;
    }

    SortedSet():
        _root(nullptr),
        _size(0) {}

    SortedSet(const SortedSet& other):
        _root(new N(other._root)),
        _size(other._size) {}

    virtual ~SortedSet() {
        avltree::dealloc(_root);
    }

    SortedSet& operator=(const SortedSet& other) {
        return *this = SortedSet(other);
    }

    size_t size() const { return _size; }
    bool any() const { return _size > 0; }

    bool contains(const T& needle) const {
        N* temp = _root;

        return _root
            && !_root->find(needle, temp);
    }

    bool peek(T& item) const {
        if (!any())
            return false;

        item = top()->_payload;
        return true;
    }

    bool push(const T& needle) {
        bool success = !any()
            && (_root = new N(needle));

        N* newRoot = nullptr;

        success = success
            || (newRoot = avltree::push(_root, needle))
            && (_root = newRoot);

        if (success)
            _size++;

        return success;
    }

    const static int LEAN = -1;

    bool remove(const T& needle) {
        if (!_size)
            return false;

        N* newRoot = nullptr;

        if (!avltree::remove(_root, needle, newRoot, LEAN))
            return false;

        _size--;
        _root = newRoot;
        return true;
    }

    bool pop(T& top) {
        if (!any())
            return false;

        _root = avltree::pop(_root, -1, top);
        _size--;
        return true;
    }

    bool pop() {
        T temp;
        return pop(temp);
    }

    void for_each(std::function<void(const T&)> doThis) const {
        if (!any())
            return;

        _root->for_each(doThis);
    }

    List<avltree::NodeInfo<T>>
    to_list() const {
        List<avltree::NodeInfo<T>> list;
        avltree::to_list(_root, 0, list);
        return list;
    }
};

template <
    typename KeyT,
    typename ValueT,
    int (*R)(const KeyT&, const KeyT&) = sort::Compare<KeyT>
>
class SortedMap: public Collection {
private:
    struct Pair {
        KeyT key;
        ValueT value;
    };

    static int _compare(const Pair& f, const Pair& s) {
        return R(f.key, s.key);
    }
public:
    SortedSet<Pair, _compare>
    _set;
public:
    SortedMap() = default;
    SortedMap(const SortedMap&) = default;
    virtual ~SortedMap() = default;
    SortedMap& operator=(const SortedMap&) = default;

    size_t size() const { return _set.size(); }
    bool any() const { return _set.any(); }

    bool contains(const KeyT& key) const {
        return _set.contains(Pair{key, ValueT()});
    }

    bool peek(ValueT& item) const {
        Pair p;

        if (!_set.peek(p))
            return false;

        item = p.value;
        return true;
    }

    struct Maybe {
        bool success = false;
        ValueT value = ValueT();
    };

    Maybe operator[](const KeyT& key) const {
        Pair pair;
        bool success = _set.at(Pair{ key, ValueT() }, pair);
        Maybe maybe = Maybe{ success, pair.value };
        return maybe;
    }

    bool push(const KeyT& key, const ValueT& value) {
        return _set.push(Pair{ key, value });
    }

    bool remove(const KeyT& key) {
        return _set.remove(Pair{ key, ValueT() });
    }

    bool pop(KeyT& key, ValueT& value) {
        Pair p;

        if (!_set.pop(p))
            return false;

        key = p.key;
        value = p.value;
        return true;
    }

    bool pop() {
        Pair p;
        return _set.pop(p);
    }

    void for_each(std::function<void(const KeyT&, const ValueT&)> doThis) const {
        _set.for_each([&](const Pair& pair) -> void {
            doThis(pair.key, pair.value);
        });
    }

    // // todo
    // std::vector<avltree::NodeInfo<T>>
    // to_vector() const {
    //     std::vector<avltree::NodeInfo<T>> list;
    //     avltree::to_vector(_root, 0, list);
    //     return list;
    // }
};

#endif /* AVLSORTEDSET_H_ */
