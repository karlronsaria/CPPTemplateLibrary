#include "gtest/gtest.h"
#include "avlsortedset_demo.h"

namespace {
    TEST(SortedSet, SevenCharacterArrangements) {
        std::vector<char> listInOrder
            = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };

        for (const auto& list : Arrangements(listInOrder)) {
            for (const auto& item : list) {
                SortedSet<char> tree;
                char item;
                int i = 0;

                while (i < list.size()) {
                    item = list[i];
                    EXPECT_TRUE(tree.push(item));
                    EXPECT_EQ(FactorErrors(tree).size(), 0);
                    EXPECT_EQ(tree.size(), (size_t)(i + 1));
                    EXPECT_TRUE(InOrder(ToList(tree)));
                    i = i + 1;
                }

                i = 0;

                while (i < listInOrder.size()) {
                    item = listInOrder[i];
                    EXPECT_TRUE(tree.remove(item));
                    EXPECT_EQ(FactorErrors(tree).size(), 0);
                    EXPECT_EQ(tree.size(), (size_t)(listInOrder.size() - i - 1));
                    EXPECT_TRUE(InOrder(ToList(tree)));
                    i = i + 1;
                }
            }
        }
    }
}
