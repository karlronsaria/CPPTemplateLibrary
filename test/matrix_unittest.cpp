#include "../src/Matrix.h"
#include <gtest/gtest.h>
#include <fstream>

template <typename C, template <typename> class T = Table>
Matrix<C, T>
NextMatrix(std::istream &);

namespace {
	TEST(Matrix, Arithmetic) {
		std::ifstream file;
		file.open("./res/int_matrix_001.txt");
		Matrix<int> op1, op2, sum, cross;

		while (file) {
			op1 = NextMatrix<int>(file);
			op2 = NextMatrix<int>(file);
			sum = NextMatrix<int>(file);
			cross = NextMatrix<int>(file);
			EXPECT_EQ(sum, Matrix<int>::sum(op1, op2));
			EXPECT_EQ(cross, Matrix<int>::cross_product(op1, op2));
		}

		file.close();
	}
}

template <typename C, template <typename> class T>
Matrix<C, T>
NextMatrix(std::istream & input) {
	C rows = (C)0, cols = (C)0, e = (C)0;
	input >> rows >> cols;
	Matrix<C, T> myMatrix(rows, cols);

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			input >> e;
			myMatrix[row][col] = e;
		}
	}

	return myMatrix;
}





