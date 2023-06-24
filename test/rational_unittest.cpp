#include "../src/Rational.h"
#include <gtest/gtest.h>
#include <vector>

namespace {
	std::vector<std::vector<int>>
	DATA_001 =
	{
		//      r1      r2	        *        *s          +          /         %  ==  !=   >  >=   <  <=
		{   3, 17,   5, 11,   15, 187,  15, 187,  118, 187,   33,  85,  33, 187,  0,  1,  0,  0,  1,  1  },
		{   9,  5,  13,  9,  117,  45,  13,   5,  146,  45,   81,  65,  16,  45,  0,  1,  1,  1,  0,  0  },
		{  35, 15,   7,  3,  245,  45,  49,   9,  210,  45,  105, 105,   0,  45,  1,  0,  0,  1,  0,  1  }
	};

	TEST(Rational, Arithmetic) {
		for (auto & row : DATA_001) {
			Rational<int> op1(row[0], row[1]);
			Rational<int> op2(row[2], row[3]);
			Rational<int> r;

			r = op1 * op2;
			EXPECT_EQ(row[4], r.numer());
			EXPECT_EQ(row[5], r.denom());

			r = r.simplify();
			EXPECT_EQ(row[6], r.numer());
			EXPECT_EQ(row[7], r.denom());

			r = op1 + op2;
			EXPECT_EQ(row[8], r.numer());
			EXPECT_EQ(row[9], r.denom());

			r = op1 / op2;
			EXPECT_EQ(row[10], r.numer());
			EXPECT_EQ(row[11], r.denom());

			r = op1 % op2;
			EXPECT_EQ(row[12], r.numer());
			EXPECT_EQ(row[13], r.denom());

			EXPECT_EQ(op1 == op2, row[14]);
			EXPECT_EQ(op1 != op2, row[15]);
			EXPECT_EQ(op1  > op2, row[16]);
			EXPECT_EQ(op1 >= op2, row[17]);
			EXPECT_EQ(op1  < op2, row[18]);
			EXPECT_EQ(op1 <= op2, row[19]);
		}
	}
}