#ifndef GRAPH_H_
#define GRAPH_H_

#include "Array.h"
#include "VectorBitset.h"

template <template <typename> class Alloc = Array>
class GraphSet: public Alloc<vector_bitset<>> {
public:
    virtual ~GraphSet() = default;
    GraphSet() = default;
    GraphSet& operator=(const GraphSet&) = default;
    GraphSet(const GraphSet&) = default;
    GraphSet(size_t size):
        Alloc<vector_bitset<>>(size)
    {
        for (auto& row : *this)
            row.raise_size(size);
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
        (*this)[(int)from].set[to];
        return *this;
    }

    std::string to_string() const {
        return Alloc<vector_bitset<>>::to_string("\n");
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

