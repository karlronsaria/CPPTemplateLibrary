#ifndef GRAPH_H_
#define GRAPH_H_

#include "Array.h"
#include "Bitset.h"

template <template <typename> class Alloc = Array>
class GraphSet: public Alloc<Bitset<>> {
public:
    virtual ~GraphSet() = default;
    GraphSet() = default;
    GraphSet& operator=(const GraphSet&) = default;
    GraphSet(const GraphSet&) = default;

    GraphSet(size_t size):
        Alloc<Bitset<>>(size)
    {
        for (auto& row : *this)
            row = Bitset<>(size);
    }

    size_t count() const {
        size_t s = 0;

        for (auto& row : *this)
            s += row.count();

        return s;
    }

    bool any() const {
        return count();
    }

    GraphSet& push(size_t from, size_t to) {
        (*this)[(int)from].set(to);
        return *this;
    }

    GraphSet& pop(size_t from, size_t to) {
        (*this)[(int)from].set(to, false);
        return *this;
    }

    bool contains(size_t from, size_t to) const {
        return *this[from][to];
    }

    std::string to_string() const {
        return Alloc<Bitset<>>::to_string("\n");
    }

    std::ostream& operator<<(std::ostream& out) const {
        return out << to_string();
    }

    template <template <typename> class A>
    friend std::ostream& operator<<(std::ostream&, const GraphSet<A>&);
};

template <template <typename> class A>
std::ostream& operator<<(std::ostream& out, const GraphSet<A>& o) {
    return out << o.to_string();
}

#endif /* GRAPH_H_ */
