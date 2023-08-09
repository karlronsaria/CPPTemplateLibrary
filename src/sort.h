#ifndef SORT_H_
#define SORT_H_

#include <sstream>

namespace sort {
    template <typename T>
    int Compare(const T& first, const T& secnd) {
        return (first > secnd) - (first < secnd);
    }
}

#endif /* SORT_H_ */
