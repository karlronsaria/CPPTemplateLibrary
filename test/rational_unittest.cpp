#include "../src/Rational.h"
#include <gtest/gtest.h>
#include <vector>

namespace {
	std::vector<std::vector<int>>
	DATA_001 =
	{
		//       r1        r2   product
		{     3, 17,    5, 11,  15, 187 }
	};

	TEST(RationalTest, Multiply) {
		for (auto & row : DATA_001) {
			Rational<int> r
				= Rational<int>(row[0], row[1])
				* Rational<int>(row[2], row[3])
				;

			EXPECT_EQ(row[4], r.numerator());
			EXPECT_EQ(row[5], r.denominator());
		}
	}
}