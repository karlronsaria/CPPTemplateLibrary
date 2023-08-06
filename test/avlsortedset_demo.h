#pragma once

#include "../src/AvlSortedSet.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// # link
// - url: https://stackoverflow.com/questions/2710713/algorithm-to-generate-all-possible-permutations-of-a-list
// - retrieved: 2023_08_05
template <typename T>
void
Arrangements(
    std::vector<T>& list,
    std::vector<std::vector<T>>& result,
    int low = 0
) {
    if (low + 1 >= list.size()) {
        result.push_back(list);
        return;
    }

    Arrangements(list, result, low + 1);
    T temp;

    for (int i = low + 1; i < list.size(); ++i) {
        temp = list[low];
        list[low] = list[i];
        list[i] = temp;

        Arrangements(list, result, low + 1);

        temp = list[low];
        list[low] = list[i];
        list[i] = temp;
    }
}

template <typename T>
std::vector<std::vector<T>>
Arrangements(
    const std::vector<T>& list
) {
    std::vector<std::vector<T>> result;
    auto listCopy = list;
    Arrangements(listCopy, result);
    return result;
}

template <typename T>
std::vector<avltree::NodeInfo<T>>
FactorErrors(const SortedSet<T>& tree) {
    auto list = tree.to_vector();

    std::vector<avltree::NodeInfo<T>>
    errors;

    for (auto& item : list)
        if (item.any && abs(item.factor) > 1)
            errors.push_back(item);

    return errors;
}

template <
    typename T,
    int (*R)(const T &, const T &)
        = Compare<T>
>
bool
InOrder(const std::vector<T>& list) {
    bool inOrder = true;

    for (size_t i = 0; i + 1 < list.size(); ++i)
        inOrder &= R(list[i], list[i + 1]) == -1;

    return inOrder;
}

template <typename T>
std::vector<T>
ToList(const SortedSet<T>& tree) {
    std::vector<T> list;

    tree.for_each([&](const T& item) -> void {
        list.push_back(item);
    });

    return list;
}

/*
def verify:
    get itemsInOrder

    for each arr in arrangements(itemsInOrder)
        new tree
        i <- 0

        while i < count(arr)
            verify(push(tree, arr[i]))
            verify(i + 1 == count(tree))
            verify(not any(FactorErrors(tree)))
            verify(InOrder(ToList(tree)))
            i <- i + 1

        i <- 0

        while i < count(itemsInOrder)
            verify(remove(tree, itemsInOrder[i]))
            verify(i + 1 == count(tree))
            verify(not any(FactorErrors(tree)))
            verify(InOrder(ToList(tree)))
            i <- i + 1
*/

template <
    typename T,
    int (*R)(const T &, const T &)
        = Compare<T>
>
bool
Verify(
    const std::vector<T>& inOrderList,
    const std::vector<T>& arrangement,
    void (*onPushComplete)(const SortedSet<T, R>&),
    void (*onRemoveComplete)(const SortedSet<T, R>&),
    void (*onPushFail)(const SortedSet<T, R>&, const T&),
    void (*onRemoveFail)(const SortedSet<T, R>&, const T&),
    void (*onFactorErrors)(const SortedSet<T, R>&, const T&),
    void (*onWrongSize)(const SortedSet<T, R>&, const T&, size_t size),
    void (*onWrongOrder)(const SortedSet<T, R>&, const T&, const std::vector<T>&)
) {
    bool wellFormed = true;
    SortedSet<T, R> tree;
    size_t size;
    T item;
    int i = 0;

    while (i < arrangement.size()) {
        item = arrangement[i];

        if (!tree.push(item)) {
            onPushFail(tree, item);
            wellFormed = false;
        }

        if (FactorErrors(tree).size() > 0) {
            onFactorErrors(tree, item);
            wellFormed = false;
        }

        size = (size_t)(i + 1);

        if (tree.size() != size) {
            onWrongSize(tree, item, size);
            wellFormed = false;
        }

        auto list = ToList(tree);

        if (!InOrder(list)) {
            onWrongOrder(tree, item, list);
            wellFormed = false;
        }

        i = i + 1;
    }

    onPushComplete(tree);
    i = 0;

    while (i < inOrderList.size()) {
        item = inOrderList[i];

        if (!tree.remove(item)) {
            onRemoveFail(tree, item);
            wellFormed = false;
        }

        if (FactorErrors(tree).size() > 0) {
            onFactorErrors(tree, item);
            wellFormed = false;
        }

        size = (size_t)(inOrderList.size() - i - 1);

        if (tree.size() != size) {
            onWrongSize(tree, item, size);
            wellFormed = false;
        }

        auto list = ToList(tree);

        if (!InOrder(list)) {
            onWrongOrder(tree, item, list);
            wellFormed = false;
        }

        i = i + 1;
    }

    onRemoveComplete(tree);
    return wellFormed;
}

template <typename T>
void StructureToStream(std::ostream& out, const SortedSet<T>& tree) {
    auto list = tree.to_vector();
    avltree::NodeInfo<T> c;
    size_t len = (size_t)log2(list.size());
    size_t index;
    size_t width;
    size_t size = tree.size();
    size_t nodes = 0;

    for (size_t i = 0; i < len; ++i) {
        width = (size_t)pow(2, len - i);

        for (size_t j = 0; j < (size_t)pow(2, i); ++j) {
            index = (size_t)pow(2, i) + j - 1;
            c = list[index];

            out << std::setw(width)
                << '(';

            if (c.any) {
                out << c.payload
                    << ", "
                    << c.factor;

                ++nodes;
            }

            out << ')';
        }

        out << "\n\n";

        if (nodes >= size)
            return;
    }
}

template <typename T>
std::string StructureToString(const SortedSet<T>& tree) {
    std::ostringstream oss;
    StructureToStream(oss, tree);
    return oss.str();
}

template <typename T>
std::string ToString(const SortedSet<T>& tree, const char* delim = " ") {
    std::ostringstream oss;

    tree.for_each([&](const T& t) -> void {
        oss << t << delim;
    });

    return oss.str();
}

template <typename T>
void ToConsole(const SortedSet<T>& tree) {
    std::cout
        << "Set in order: "
        << ToString(tree, " ")
        << "\n\n"
        << "Structure:\n\n"
        << StructureToString(tree)
        << "\n\n"
        ;
}

