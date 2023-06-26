#include "../src/Matrix.h"
#include <gtest/gtest.h>

// todo
int main() {
	std::cout << "Hello, world!\n";

	Matrix<int> m1(3, 3, {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	});

	Matrix<int> m2(3, 3, {
		{3, 5, 7},
		{11, 13, 17},
		{19, 23, 29}
	});

	Matrix<int> m;

	std::cout
		<< "Rows: " << m1.rows() << '\n'
		<< "Middle: " << m1[1][1] << '\n'
		<< "Full:\n" << m1 << '\n'
		;

	m = Matrix<int>::sum(m1, m2);

	std::cout
		<< "Rows: " << m.rows() << '\n'
		<< "Middle: " << m[1][1] << '\n'
		<< "Full:\n" << m << '\n'
		;


	scoped_ptr<int> ptr1(new int[1]);
	scoped_ptr<Array<int>> ptr2(new Array<int>[0]);
	Array<int> a1(0);
	Array<Array<int>> a2(0);
	Array<Array<int>> a3(1);
	Table<char> t1(0, 0);
	Table<char> t2(1, 1);
	Table<char> t3;
}

// namespace {
// 	TEST(Matrix, Addition) {
// 	}
// }





