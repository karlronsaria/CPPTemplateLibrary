#include "../src/Matrix.h"
#include <gtest/gtest.h>
#include <fstream>

template <typename C, template <typename> class T = Table>
Matrix<C, T>
NextMatrix(std::istream &);

template <typename C>
Rational<C>
NextRational(std::istream &);

namespace {
	TEST(Matrix, Arithmetic) {
		std::ifstream file;

		// // karlr (2023_06_28): I SHOULD NOT HAVE TO DO THIS!!!
		file.open("../../../lib/test/res/int_matrix_001.txt");
		Matrix<int> op1, op2, sum, cross;
		Rational<int> det;
		op1 = NextMatrix<int>(file);

		while (file && op1.rows() > 0) {
			op2 = NextMatrix<int>(file);
			sum = NextMatrix<int>(file);
			cross = NextMatrix<int>(file);
			det = NextRational<long>(file);

			// todo
			std::cout << "\n\n" << (Rational<int>(1, 2) == Rational<long>(2, 3)) << "\n\n";
			std::cout << "\n\n" << (Rational<int>(1, 2) == Rational<long>(81, 162)) << "\n\n";

			EXPECT_EQ(sum, Matrix<int>::sum(op1, op2));
			EXPECT_EQ(cross, Matrix<int>::cross_product(op1, op2));
			EXPECT_EQ(det, op2.determinant());
			// std::cout << "\nDeterminant: " << op1.determinant() << '\n';
			// std::cout << "\nTranspose:\n" << op2.transpose() << '\n';
			// std::cout << "\nReduction:\n" << op2.reduction() << '\n';
			// std::cout << "\nInverse:\n" << op2.very_precise_inverse() << '\n';
			// std::cout << "\nQuotient:\n" << Matrix<double>::cross_product(op2.very_precise_inverse(), op1) << '\n';
			op1 = NextMatrix<int>(file);
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

template <typename C>
Rational<C>
NextRational(std::istream & input) {
	C numer = (C)0, denom = (C)0;
	input >> numer >> denom;
	return Rational<C>(numer, denom);
}





