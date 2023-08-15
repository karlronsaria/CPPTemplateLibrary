#ifndef ENUMERABLE_H_
#define ENUMERABLE_H_

#include <sstream>

namespace enumerable {
    template <typename C, typename T>
    std::string ToString(
        const C& c,
        const std::string& delim,
        std::string (*toString)(const T&)
    ) {
        if (!c.any())
            return "";

        std::ostringstream oss;
        auto it = c.begin();
        oss << toString(*it);

        while (++it != c.end())
            oss << delim << toString(*it);

        return oss.str();
    }

    template <typename C>
    std::string ToString(const C& c, const std::string& delim) {
        if (!c.any())
            return "";

        std::ostringstream oss;
        auto it = c.begin();
        oss << *it;

        while (++it != c.end())
            oss << delim << *it;

        return oss.str();
    }
}

#endif /* ENUMERABLE_H_ */
