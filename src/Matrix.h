/*
 * Matrix.h
 *
 *  Created on: Jul 9, 2014
 *      Author: Drew
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <sstream>
#include "modular_int.h"
#include "Rational.h"
#include "Table.h"
#include "Specialize/NumericClass.h"

template<
    typename Content_Type,
    template<typename> class Table_Class = Table>
class Matrix:
    public Table_Class<Content_Type>,
    private ExpandedNumericClass<Content_Type>
{
public:
    /*************************************
     * --- Constructors & Destructor --- *
     *************************************/

    virtual ~Matrix() = default;
    Matrix() = default;

    Matrix(size_t rows, size_t cols):
        Table_Class<Content_Type>(rows, cols) {}

    Matrix(size_t rows, size_t cols, const Content_Type& input):
        Table_Class<Content_Type>(rows, cols, input) {}

    Matrix(const Matrix& object):
        Table_Class<Content_Type>(object) {}

    template <typename Second_Type>
    Matrix(const Matrix<Second_Type, Table_Class> &);

    Matrix(
        size_t rows,
        size_t cols,
        std::initializer_list
            <std::initializer_list<Content_Type>>&
        components
    ): Table_Class<Content_Type>(rows, cols, components) {}

    Matrix(
        const std::initializer_list
			<std::initializer_list<Content_Type>>&
        components
    ): Table_Class<Content_Type>(components) {}

    /*********************
     * --- Accessors --- *
     *********************/

    Matrix         congruent           () const;
    Matrix         complement          () const;
    Matrix         transpose           () const;
    Matrix         partial             (size_t, size_t) const;
    Matrix         reduction           () const;
    Content_Type   determinant_recurse () const throw(const char *);
    Rational<long> determinant         () const;
    Matrix         cofactor            () const;
    Matrix         adjoint             () const;

    Matrix <float,       Table_Class>  inverse              () const;
    Matrix <double,      Table_Class>  precise_inverse      () const;
    Matrix <long double, Table_Class>  very_precise_inverse () const;

    using Table_Class<Content_Type>::rows;
    using Table_Class<Content_Type>::cols;

    /******************************
     * --- Operator Overloads --- *
     ******************************/

    template <typename Second_Type>
    Matrix & operator=(
        const Matrix<Second_Type, Table_Class> &
    );

    template <typename Second_Type>
    Matrix & operator=(
        const std::initializer_list
            <std::initializer_list<Second_Type>>&
    );

    bool operator==(const Matrix &) const;
    bool operator!=(const Matrix &) const;

    /**************************
     * --- Static Methods --- *
     **************************/

    // Calculations

    template <typename Type_2>
    static const Matrix sum(
        const Matrix &,
        const Matrix<Type_2, Table_Class> &
    );

    template <typename Second_Type>
    static const Matrix scalar_product(
        const Content_Type &,
        const Matrix<Second_Type, Table_Class> &
    );

    template <typename Type_2>
    static Content_Type dot_product(
        const Matrix &, size_t,
        const Matrix<Type_2, Table_Class> &, size_t
    );

    template <typename Type_2>
    static Content_Type dot_product(
        const Matrix &,
        const Matrix<Type_2, Table_Class> &
    );

    template <typename Type_2>
    static const Matrix cross_product(
        const Matrix &,
        const Matrix<Type_2, Table_Class> &
    );

    // Named Constructors

    static const Matrix  square     (size_t);
    static const Matrix  square     (size_t, const Content_Type &);
    static const Matrix  single_row (size_t);
    static const Matrix  single_row (size_t, const Content_Type &);
    static const Matrix  single_col (size_t);
    static const Matrix  single_col (size_t, const Content_Type &);
    static const Matrix  identity   (size_t);

    /*********************
     * --- To String --- *
     *********************/

    std::string to_string() const;

    std::ostream& operator<<(std::ostream& out) const {
        return out << to_string();
    }

    template <typename C, template<typename> class T>
    friend std::ostream& operator<<(std::ostream&, const Matrix<C, T>&);
};

template <typename C, template<typename> class T>
std::string Matrix<C, T>::to_string() const {
    std::ostringstream oss;

    for (auto& row : *this) {
        for (auto& col : row)
            oss << ' ' << col;

        oss << '\n';
    }

    return oss.str();
}

template <typename C, template<typename> class T>
std::ostream& operator<<(std::ostream& out, const Matrix<C, T>& o) {
    return out << o.to_string();
}


/*********************
 * --- Functions --- *
 *********************/

// Named Constructors

const Matrix<int, Table> identity_matrix(size_t);

// Queries

template <typename A, typename B, template<typename> class T>
bool are_congruent(const Matrix<A, T> &, const Matrix<B, T> &);

template <typename A, typename B, template<typename> class T>
bool are_multiplicable(const Matrix<A, T> &, const Matrix<B, T> &);

template <typename A, template<typename> class T>
bool is_square(const Matrix<A, T> &);

template <typename A, template<typename> class T>
bool is_singular(const Matrix<A, T> &);


// Matrix Methods --------------------------------------------------------


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

// Type-Conversion Copy Constructor
template <typename C, template<typename> class T>
template <typename D>
Matrix<C, T>::Matrix(const Matrix<D, T> & object):
    T<C> (object.rows(), object.cols())
{
    for (size_t row = 0; row < rows(); ++row)
        for (size_t col = 0; col < cols(); ++col)
            (*this)[row][col] = (C)object[row][col];
}


/*********************
 * --- Accessors --- *
 *********************/

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::congruent() const {
    return Matrix(rows(), cols());
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::complement() const {
    return Matrix(cols(), rows());
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::transpose() const {
    size_t rows = Matrix::cols();
    size_t cols = Matrix::rows();
    Matrix transposeMatrix(rows, cols);

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < cols; col++)
            transposeMatrix[row][col] = (*this)[col][row];

    return transposeMatrix;
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::partial(size_t ROW, size_t COL) const {
    Matrix partialMatrix(rows() - 1, cols() - 1);

    if (partialMatrix.rows() > 0 && partialMatrix.cols() > 0) {
        modular_int rowCount(0, partialMatrix.rows() + 1);
        modular_int colCount(0, partialMatrix.cols() + 1);
        int partialRowIndex = 0;

        for (rowCount = ROW + 1; rowCount != ROW; rowCount++) {
            int partialColIndex = 0;

            for (colCount = COL + 1; colCount != COL; colCount++) {
                partialMatrix[partialRowIndex][partialColIndex]
                    = (*this)[rowCount.value()][colCount.value()];

                partialColIndex++;
            }

            partialRowIndex++;
        }
    }

    return partialMatrix;
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::reduction() const {
    Matrix temp = *this;
    C tempFactor;
    size_t i, j, k, size = temp.size();

    for (i = 0; i < size; ++i) {
        for (k = i + 1; k < size; ++k) {
            tempFactor = temp[k][i];

            for (j = i;
                j < size
                && tempFactor != (C)0
                // && temp[i][i] != 0
                // && temp[i][j] != 0
                ;
                ++j
            ) {
                temp[k][j]
                    -= temp[i][j]
                    * tempFactor
                    / temp[i][i];
            }
        }
    }

    return temp;
}

template <typename C, template<typename> class T>
C Matrix<C, T>::determinant_recurse() const throw(const char *) {
	size_t cols = cols();

    switch (cols) {
    case 0:
        return 0;
    case 1:
		return (*this)[0][0];
    case 2:
		return (*this)[0][0] * (*this)[1][1]
			 - (*this)[1][0] * (*this)[0][1];
    default:
        break;
    }

	if (cols > 6)
		throw "The size of this matrix is impractical "
			  "for recursive determinant calculation.";

    C determ = 0;
	int coefficient = 1;

	for (size_t col = 0; col < cols; col++) {
		determ += coefficient
            * (*this)[0][col]
            * partial(0, col).determinant_recurse();

		if (cols % 2 == 0)
			coefficient *= -1;
	}

    return determ;
}

template <typename C, template<typename> class T>
Rational<long> Matrix<C, T>::determinant() const {
	Rational<long> determ = 1;
	Matrix<Rational<long>, T> temp = *this;
	temp = temp.reduction();

	for (size_t i = 0; i < temp.size(); ++i)
		determ *= temp[i][i];

	return determ;
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::cofactor() const {
    if (Matrix::size() == 0)
        return Matrix();

	int rowCoeff = 1;
	int colCoeff = 1;
	size_t size = Matrix::size();
	Matrix cofactorMatrix = square(size);

	for (size_t row = 0; row < size; row++) {
		for (size_t col = 0; col < size; col++) {
			cofactorMatrix[row][col]
                = rowCoeff
                * colCoeff
                * partial(row, col).determinant();

			if (size % 2 == 0)
				colCoeff *= -1;
		}

		if (size % 2 == 0)
			rowCoeff *= -1;
	}

    return cofactorMatrix;
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::adjoint() const {
    Matrix cofactorMatrix = cofactor();

    if (cofactorMatrix.size() == 0)
        return Matrix();

	return cofactorMatrix.transpose();
}

template <typename C, template<typename> class T>
Matrix<float, T> Matrix<C, T>::inverse() const {
	int determ = determinant();

	if (determ == 0)
		return Matrix();

    return Matrix<float, T>::scalar_product(
		1.0/float(determ),
		adjoint()
	);
}

template <typename C, template<typename> class T>
Matrix<double, T> Matrix<C, T>::precise_inverse() const {
	int determ = determinant();

	if (determ == 0)
		return Matrix();

    return Matrix<double, T>::scalar_product(
		1.0/double(determ),
		adjoint()
	);
}

template <typename C, template<typename> class T>
Matrix<long double, T> Matrix<C, T>::very_precise_inverse() const {
	int determ = determinant();

	if (determ == 0)
		return Matrix();

    return Matrix<long double, T>::scalar_product(
		1.0/(long double)(determ),
		adjoint()
	);
}


/******************************
 * --- Operator Overloads --- *
 ******************************/

// Assignment Operator
template <typename C, template<typename> class T>
template <typename D>
Matrix<C, T> & Matrix<C, T>::operator=(const Matrix<D, T> & object) {
    return *this = Matrix(object);
}

template <typename C, template<typename> class T>
template <typename D>
Matrix<C, T> & Matrix<C, T>::operator=(
    const std::initializer_list
        <std::initializer_list<D>>& list
) {
    size_t rows = list.size();
    auto it = list.begin();
    size_t cols = it->size();

    while (++it != list.end())
        if (it->size() < cols)
            cols = it->size();

    return *this = Matrix(rows, cols, list);
}

template <typename C, template<typename> class T>
bool Matrix<C, T>::operator==(const Matrix & other) const {
    return T<C>::operator==(other);
}

template <typename C, template<typename> class T>
bool Matrix<C, T>::operator!=(const Matrix & other) const {
    return T<C>::operator!=(other);
}


/**************************
 * --- Static Methods --- *
 **************************/

// Calculations

template <typename C, template<typename> class T>
template <typename Type_2>
const Matrix<C, T> Matrix<C, T>::sum(
    const Matrix & summand1,
    const Matrix<Type_2, T> & summand2
) {
    if (!are_congruent(summand1, summand2))
        return Matrix();

	size_t rows = summand1.rows();
	size_t cols = summand1.cols();
	Matrix sumMatrix(rows, cols);

	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
			sumMatrix[row][col]
                = (C)(summand1[row][col] + summand2[row][col]);

    return sumMatrix;
}

template <typename C, template<typename> class T>
template <typename D>
const Matrix<C, T> Matrix<C, T>::scalar_product(
    const C & scalar,
    const Matrix<D, T> & factor
) {
    size_t rows = factor.rows();
    size_t cols = factor.cols();
    Matrix productMatrix(rows, cols);

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < cols; col++)
            productMatrix[row][col] = scalar * factor[row][col];

    return productMatrix;
}

template <typename C, template<typename> class T>
template <typename B>
C Matrix<C, T>::dot_product(
    const Matrix & factor1,
    size_t row,
    const Matrix<B, T> & factor2,
    size_t col
) {
    if (!are_multiplicable(factor1, factor2))
        return (C)0;

    double product = 0;

	for (size_t count = 0; count < factor1.cols(); count++)
		product += factor1[row][count] * factor2[count][col];

    return (C)product;
}

template <typename C, template<typename> class T>
template <typename B>
C Matrix<C, T>::dot_product(
    const Matrix & factor1,
    const Matrix<B, T> & factor2
) {
    if (factor1.cols() != factor2.rows())
        return (C)0;

    double product = 0;
	size_t cols = factor1.cols();

	for (size_t count = 0; count < cols; count++)
		product += factor1[0][count] * factor2[count][0];

    return (C)product;
}

template <typename C, template<typename> class T>
template <typename B>
const Matrix<C, T> Matrix<C, T>::cross_product(
    const Matrix & factor1,
	const Matrix<B, T> & factor2
) {
	if (!are_multiplicable(factor1, factor2))
		return Matrix();

	size_t rows = factor1.rows();
	size_t cols = factor2.cols();
	Matrix productMatrix(rows, cols);

	for (size_t row = 0; row < rows; row++)
		for (size_t col = 0; col < cols; col++)
            productMatrix[row][col] = (C)round(
				Matrix<double, T>::dot_product(
					factor1, row,
					factor2, col
				)
			);

    return productMatrix;
}

// Named Constructors

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::square(size_t size) {
    return Matrix(size, size);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::square(size_t size, const C & content) {
    return Matrix(size, size, content);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::single_row(size_t cols) {
    return Matrix(1, cols);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::single_row(
    size_t cols,
    const C & content
) {
    return Matrix(1, cols, content);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::single_col(size_t rows) {
    return Matrix(rows, 1);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::single_col(
    size_t rows,
    const C & content
) {
    return Matrix(rows, 1, content);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::identity(size_t size) {
    Matrix id = square(size, 0);

    for (size_t count = 0; count < size; count++)
        id[count][count] = (C)1;

    return id;
}


/*********************
 * --- Functions --- *
 *********************/

// Named Constructors

const Matrix<int, Table> identity_matrix(size_t size) {
    return Matrix<int, Table>::identity(size);
}

// Queries

template <typename A, typename B, template<typename> class T>
bool are_congruent(
    const Matrix<A, T> & factor1,
    const Matrix<B, T> & factor2
) {
    return factor1.rows() == factor2.rows()
        && factor1.cols() == factor2.cols();
}

template <typename A, typename B, template<typename> class T>
bool are_multiplicable(
    const Matrix<A, T> & factor1,
    const Matrix<B, T> & factor2
) {
    return factor1.cols() == factor2.rows();
}

template <typename A, template<typename> class T>
bool is_square(const Matrix<A, T> & object) {
    return object.rows() == object.cols();
}

template <typename A, template<typename> class T>
bool is_singular(const Matrix<A, T> & object) {
    return is_square(object) && object.determinant() == 0;
}

template <typename A, template<typename> class T>
bool is_unimodular(const Matrix<A, T> & object) {
    return is_square(object)
        && (object.determinant() == 1 || object.determinant() == -1);
}

#endif /* MATRIX_H_ */
