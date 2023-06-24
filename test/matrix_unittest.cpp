#include "../src/Matrix.h"
#include <gtest/gtest.h>

// todo
int main() {
	std::cout << "Hello, world!\n";

	scoped_ptr<int> ptr1(new int[1]);
	scoped_ptr<Array<int>> ptr2(new Array<int>[0]);
	Array<int> a1(0);
	Array<Array<int>> a2(0);
	Array<Array<int>> a3(1);
	Table<char> t1(0, 0);
	Table<char> t2(1, 1);
	Table<char> t3;
	Matrix<int> m1(0, 0);
	Matrix<int> m2;
}