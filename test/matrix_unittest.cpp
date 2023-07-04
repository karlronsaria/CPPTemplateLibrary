#include "../src/Matrix.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

template <typename C, template <typename> class T = Table>
Matrix<C, T>
NextMatrix(std::istream &);

template <typename C>
Rational<C>
NextRational(std::istream &);

std::wstring
ExePath();

namespace {
	TEST(Matrix, Arithmetic) {
		std::ifstream file;
		file.open(ExePath() + std::wstring(L"/../../../../lib/test/res/int_matrix_001.txt"));

		Matrix<int> op1, op2, sum, cross, tra, red;
		Matrix<float> inv, quo;
		Rational<int> det;
		op1 = NextMatrix<int>(file);

		while (file && op1.rows() > 0) {
			op2 = NextMatrix<int>(file);
			sum = NextMatrix<int>(file);
			cross = NextMatrix<int>(file);
			det = NextRational<long>(file);
			tra = NextMatrix<int>(file);
			red = NextMatrix<int>(file);
			inv = NextMatrix<long double>(file);
			quo = NextMatrix<long double>(file);

			EXPECT_EQ(sum, Matrix<int>::sum(op1, op2));
			EXPECT_EQ(cross, Matrix<int>::cross_product(op1, op2));
			EXPECT_EQ(det, op2.determinant());
			EXPECT_EQ(tra, op2.transpose());
			EXPECT_EQ(red, op2.reduction());
			EXPECT_EQ(inv, op2.very_precise_inverse());
			EXPECT_EQ(quo, Matrix<double>::cross_product(op2.very_precise_inverse(), op1));
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

std::wstring
ExePath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}




