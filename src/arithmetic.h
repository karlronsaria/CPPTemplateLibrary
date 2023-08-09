#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

namespace arithmetic {
    template <typename N>
    N PostIncr(N& n) {
        N temp = n;
        ++n;
        return temp;
    }

    template <typename N>
    N PostDecr(N& n) {
        N temp = n;
        --n;
        return temp;
    }

    template <typename N, typename I>
    N Plus(const N& n, const I& pos) {
        N temp(n);
        temp += pos;
        return temp;
    }
}

#endif /* ARITHMETIC_H_ */
