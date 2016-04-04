/*
 * Matrix.h
 *
 *  Created on: Jul 9, 2014
 *      Author: Drew
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iomanip>
#include "modular_int.h"
#include "Rational.h"
#include "Table.h"
#include "Specialize/NumericClass.h"

template < typename                 Content_Type,
		   template<typename> class Table_Class = Table >

class Matrix: public  Table_Class          <Content_Type>,
              private ExpandedNumericClass <Content_Type>
{
	public:

		static const size_t DEFAULT_WIDTH = 2;

		/*************************************
		 * --- Constructors & Destructor --- *
		 *************************************/

		Matrix();
		Matrix(size_t, size_t);
		Matrix(size_t, size_t, const Content_Type &);
		Matrix(const Matrix &);

		template <typename Second_Type>
		Matrix(const Matrix<Second_Type, Table_Class> &);

	   ~Matrix();

		/*********************
		 * --- Accessors --- *
		 *********************/

		Matrix         congruent             () const;
		Matrix         complement            () const;
		Matrix         transpose             () const;
		Matrix         partial               (size_t, size_t) const;
		Matrix         reduction             () const;
		Content_Type   recursive_determinant () const;
		Rational<long> determinant           () const;
		Matrix         cofactor              () const;
		Matrix         adjoint               () const;

		Matrix <float,       Table_Class>  inverse              () const;
		Matrix <double,      Table_Class>  precise_inverse      () const;
		Matrix <long double, Table_Class>  very_precise_inverse () const;

		/******************************
		 * --- Operator Overloads --- *
		 ******************************/

		template <typename Second_Type>
		Matrix & operator= (const Matrix<Second_Type, Table_Class> &);

		std::ostream & operator<< (std::ostream &) const;

		/**************************
		 * --- Static Methods --- *
		 **************************/

		// Calculations

		template <typename Type_1, typename Type_2>
		static const Matrix sum

					(const Matrix<Type_1, Table_Class> &,
				     const Matrix<Type_2, Table_Class> &);

		template <typename Second_Type>
		static const Matrix scalar_product

		            (const Content_Type &,
				     const Matrix<Second_Type, Table_Class> &);

		template <typename Type_1, typename Type_2>
		static Content_Type dot_product

					(const Matrix<Type_1, Table_Class> &, size_t,
				     const Matrix<Type_2, Table_Class> &, size_t);

		template <typename Type_1, typename Type_2>
		static Content_Type dot_product

					(const Matrix<Type_1, Table_Class> &,
				     const Matrix<Type_2, Table_Class> &);

		template <typename Type_1, typename Type_2>
		static const Matrix cross_product

					(const Matrix<Type_1, Table_Class> &,
                     const Matrix<Type_2, Table_Class> &);

		// Named Constructors

		static const Matrix  matrix (size_t, size_t);
		static const Matrix  matrix (size_t, size_t, const Content_Type &);
		static const Matrix  square     (size_t);
		static const Matrix  square     (size_t, const Content_Type &);
		static const Matrix  single_row (size_t);
		static const Matrix  single_row (size_t, const Content_Type &);
		static const Matrix  single_col (size_t);
		static const Matrix  single_col (size_t, const Content_Type &);
		static const Matrix  identity   (size_t);
};

/*********************
 * --- Functions --- *
 *********************/

// Operator Overloads

template <typename C, template<typename> class T>
std::ostream & operator<<(std::ostream &, const Matrix<C, T> &);

// Named Constructors

const Matrix<int, Table> identity_matrix(size_t);

// Queries

template <typename A, typename B, template<typename> class T>
bool are_congruent    (const Matrix<A, T> &, const Matrix<B, T> &);

template <typename A, typename B, template<typename> class T>
bool are_multipliable (const Matrix<A, T> &, const Matrix<B, T> &);

template <typename A, template<typename> class T>
bool is_square        (const Matrix<A, T> &);

template <typename A, template<typename> class T>
bool is_singular      (const Matrix<A, T> &);


// Matrix Methods --------------------------------------------------------


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

// Default Constructor
template <typename C, template<typename> class T>
Matrix<C, T>::Matrix() {}

// Volume Constructor
template <typename C, template<typename> class T>
Matrix<C, T>::Matrix(size_t colSize, size_t rowSize):
	T<C> (colSize, rowSize) {}

// Uniform Initializing Constructor
template <typename C, template<typename> class T>
Matrix<C, T>::Matrix(size_t colSize, size_t rowSize, const C & input):
	T<C> (colSize, rowSize, input) {}

// Copy Constructor
template <typename C, template<typename> class T>
Matrix<C, T>::Matrix(const Matrix & object): T<C>(object) {}

// Type-Conversion Copy Constructor
template <typename C, template<typename> class T>
template <typename D>
Matrix<C, T>::Matrix(const Matrix<D, T> & object):
	T<C> (object.col_size(), object.row_size())
{
	for(size_t row = 0; row < Matrix::rows(); ++row)

		for(size_t col = 0; col < Matrix::cols(); ++col)

			(*this)[row][col] = C(object[row][col]);
}

// Destructor
template <typename C, template<typename> class T>
Matrix<C, T>::~Matrix() {}


/*********************
 * --- Accessors --- *
 *********************/

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::congruent() const
{
	return Matrix(Matrix::col_size(), Matrix::row_size());
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::complement() const
{
	return Matrix(Matrix::row_size(), Matrix::col_size());
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::transpose() const
{
	size_t colSize = Matrix::row_size();
	size_t rowSize = Matrix::col_size();

	Matrix transposeMatrix(colSize, rowSize);

	for(size_t row = 0; row < colSize; row++)
	{
		for(size_t col = 0; col < rowSize; col++)
		{
			transposeMatrix[row][col] = (*this)[col][row];
		}
	}

	return transposeMatrix;
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::partial(size_t ROW, size_t COL) const
{
	Matrix partialMatrix(Matrix::col_size() - 1, Matrix::row_size() - 1);

	if(partialMatrix.col_size() > 0 && partialMatrix.row_size() > 0)
	{
		modular_int rowCount(0, partialMatrix.col_size() + 1);
		modular_int colCount(0, partialMatrix.row_size() + 1);

		int partialRowIndex = 0;

		for(rowCount = ROW + 1; rowCount != ROW; rowCount++)
		{
			int partialColIndex = 0;

			for(colCount = COL + 1; colCount != COL; colCount++)
			{
				partialMatrix[partialRowIndex][partialColIndex] =
				Matrix::element_data(rowCount, colCount);

				partialColIndex++;
			}

			partialRowIndex++;
		}
	}

	return partialMatrix;
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::reduction() const
{
	Matrix temp = *this;

	C tempFactor;

	size_t i, j, k, size = temp.size();

	for(i = 0; i < size; ++i)
	{
		for(k = i + 1; k < size; ++k)
		{
			tempFactor = temp[k][i];

			for(j = i; j < size && tempFactor != 0
								&& temp[i][i] != 0
								&& temp[i][j] != 0; ++j)
			{
				temp[k][j] -= temp[i][j] *
							  tempFactor /
							  temp[i][i];
			}
		}
	}

	return temp;
}

template <typename C, template<typename> class T>
C Matrix<C, T>::recursive_determinant() const
{
	C determ = 0;

	try
	{
		if(is_square(*this))
		{
			size_t rowSize = Matrix::row_size();

			if(rowSize > 6)
			{
				throw "The size of this matrix is impractical "
				      "for determinant calculation.";
			}
			else if(rowSize > 2)
			{
				int coefficient = 1;

				for(size_t col = 0; col < rowSize; col++)
				{
					determ +=  coefficient * (*this)[0][col] *
					          (this->partial(0, col)).determinant();

					if(rowSize % 2 == 0)
					{
						coefficient *= -1;
					}
				}
			}
			else if(rowSize == 1)
			{
				determ = (*this)[0][0];
			}
			else
			{
				determ = (*this)[0][0] * (*this)[1][1]
				       - (*this)[1][0] * (*this)[0][1];
			}
		}
		else
		{
			throw "Not a square matrix.";
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::determinant() const: [!] "
				  <<  message   << std::endl;
	}

	return determ;
}

template <typename C, template<typename> class T>
Rational<long> Matrix<C, T>::determinant() const
{
	try
	{
		if(is_square(*this))
		{
			Rational<long> determ = 1;

			Matrix<Rational<long>, T> temp = *this;

			temp = temp.reduction();

			for(size_t i = 0; i < temp.size(); ++i) determ *= temp[i][i];

			return determ;
		}
		else
		{
			throw "Not a square matrix.";
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::determinant() const: [!] "
				  <<  message   << std::endl;

		return 0;
	}
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::cofactor() const
{
	Matrix cofactorMatrix;

	try
	{
		if(Matrix::size() == 0)
		{
			throw "The object matrix must have data.";
		}
		else if(!is_square(*this))
		{
			throw "The object matrix must be square.";
		}
		else
		{
			int    rowCoeff = 1;
			int    colCoeff = 1;
			size_t size     = Matrix::size();
			cofactorMatrix  = Matrix::square(size);

			for(size_t row = 0; row < size; row++)
			{
				for(size_t col = 0; col < size; col++)
				{
					cofactorMatrix[row][col] = rowCoeff * colCoeff *
					partial(row, col).determinant();

					if(size % 2 == 0)
					{
						colCoeff *= -1;
					}
				}

				if(size % 2 == 0)
				{
					rowCoeff *= -1;
				}
			}
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::cofactor() const: [!] "
				  <<  message   << std::endl;
	}

	return cofactorMatrix;
}

template <typename C, template<typename> class T>
Matrix<C, T> Matrix<C, T>::adjoint() const
{
	Matrix adjointMatrix;
	Matrix cofactorMatrix;

	cofactorMatrix = cofactor();

	if(cofactorMatrix.size() != 0)
	{
		adjointMatrix = cofactorMatrix.transpose();
	}

	return adjointMatrix;
}

template <typename C, template<typename> class T>
Matrix<float, T> Matrix<C, T>::inverse() const
{
	Matrix<float, T> inverseMatrix;

	try
	{
		int determ = determinant();

		if(determ != 0)
		{
			inverseMatrix =
			Matrix<float, T>::scalar_product(1.0/float(determ), adjoint());
		}
		else
		{
			throw "Not an invertible matrix. "
			      "The object matrix must be square and singular.";
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::inverse() const: [!] "
				  <<  message   << std::endl;
	}

	return inverseMatrix;
}

template <typename C, template<typename> class T>
Matrix<double, T> Matrix<C, T>::precise_inverse() const
{
	Matrix<double, T> inverseMatrix;

	try
	{
		int determ = determinant();

		if(determ != 0)
		{
			inverseMatrix =
			Matrix<double, T>::scalar_product

					( 1.0/double(determ), adjoint() );
		}
		else
		{
			throw "Not an invertible matrix. "
			      "The object matrix must be square and singular.";
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::precise_inverse() const: [!] "
				  <<  message   << std::endl;
	}

	return inverseMatrix;
}

template <typename C, template<typename> class T>
Matrix<long double, T> Matrix<C, T>::very_precise_inverse() const
{
	Matrix<long double, T> inverseMatrix;

	try
	{
		int determ = determinant();

		if(determ != 0)
		{
			inverseMatrix =
			Matrix<long double, T>::scalar_product

					(1.0/(long double)(determ), adjoint());
		}
		else
		{
			throw "Not an invertible matrix. "
			      "The object matrix must be square and singular.";
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::precise_inverse() const: [!] "
				  <<  message   << std::endl;
	}

	return inverseMatrix;
}


/******************************
 * --- Operator Overloads --- *
 ******************************/

// Assignment Operator
template <typename C, template<typename> class T>
template <typename D>
Matrix<C, T> & Matrix<C, T>::operator= (const Matrix<D, T> & object)
{
	*this = Matrix(object);

	return *this;
}

// Output Stream Operator - Method
template <typename C, template<typename> class T>
std::ostream & Matrix<C, T>::operator<<(std::ostream & out) const
{
	out << *this;

	return out;
}


/**************************
 * --- Static Methods --- *
 **************************/

// Calculations

template <typename C, template<typename> class T>
template <typename Type_1, typename Type_2>
const Matrix<C, T> Matrix<C, T>::sum
            (const Matrix<Type_1, T>  & summand1,
             const Matrix<Type_2, T>  & summand2)
{
	Matrix sumMatrix;

	try
	{
		if(are_congruent(summand1, summand2))
		{
			size_t colSize = summand1.col_size();
			size_t rowSize = summand1.row_size();

			sumMatrix = matrix(colSize, rowSize);

			for(size_t row = 0; row < colSize; row++)
			{
				for(size_t col = 0; col < rowSize; col++)
				{
					sumMatrix[row][col] =
				    Data(summand2[row][col] + summand2[row][col]);
				}
			}
		}
		else
		{
			throw "The matrices are not congruent.";
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::sum(const Matrix<> &, const Matrix<> &): "
				  << "[!] " << message << std::endl;
	}

	return sumMatrix;
}

template <typename C, template<typename> class T>
template <typename D>
const Matrix<C, T> Matrix<C, T>::scalar_product
            (const C & scalar, const Matrix<D, T>  & factor)
{
	size_t colSize = factor.col_size();
	size_t rowSize = factor.row_size();

	Matrix productMatrix(colSize, rowSize);

	for(size_t row = 0; row < colSize; row++)
	{
		for(size_t col = 0; col < rowSize; col++)
		{
			productMatrix[row][col] = scalar * factor[row][col];
		}
	}

	return productMatrix;
}

template <typename C, template<typename> class T>
template <typename A, typename B>
C Matrix<C, T>::dot_product
                (const Matrix<A, T> & factor1,   size_t  ROW,
                 const Matrix<B, T> & factor2,   size_t  COL)
{
	C       returnData;
	double  product  = 0;
	size_t  colSize  = factor2.col_size();
	size_t  rowSize  = factor1.row_size();
	bool    validRow = factor1.valid_row_index(ROW);
	bool    validCol = factor2.valid_row_index(COL);

	try
	{
		if(colSize != rowSize)
		{
			throw "Both arguments must have the same length. "
			      "The row's size must be equal to the column's size.";
		}
		else if(!validRow && validCol)
		{
			throw "The row index is out of bounds.";
		}
		else if(validRow && !validCol)
		{
			throw "The column index is out of bounds.";
		}
		else if(!validRow && !validCol)
		{
			throw "The row and column indices are out of bounds.";
		}
		else
		{
			for(size_t count = 0; count < rowSize; count++)
			{
				product += factor1[ROW][count] * factor2[count][COL];
			}
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::dot_product(Matrix<>, const int, "
				  <<                       "Matrix<>, const int): [!] "
				  <<  message   << std::endl;
	}

	returnData = C(product);

	return returnData;
}

template <typename C, template<typename> class T>
template <typename A, typename B>
C Matrix<C, T>::dot_product(const Matrix<A, T> & factor1,
		                    const Matrix<B, T> & factor2)
{
	C     returnData;
	int   product           = 0;
	bool  firstFactorIsRow  = false;
	bool  secondFactorIsCol = false;

	if(is_a_single_col(factor1))
	{
		factor1 = factor1.transpose();
		firstFactorIsRow = true;
	}

	if(is_a_single_row(factor2))
	{
		factor2 = factor2.transpose();
		secondFactorIsCol = true;
	}

	try
	{
		if(!firstFactorIsRow && secondFactorIsCol)
		{
			throw "The first argument is invalid. "
				  "It must be a single row or column.";
		}
		else if(firstFactorIsRow && !secondFactorIsCol)
		{
			throw "The second argument is invalid. "
				  "It must be a single row or column.";
		}
		else if(!firstFactorIsRow && !secondFactorIsCol)
		{
			throw "Both arguments are invalid. "
			      "They must be single rows or columns.";
		}
		else if(factor1.row_size() != factor2.col_size())
		{
			throw "Both arguments must have the same length. "
			      "The row's size must be equal to the column's size.";
		}
		else
		{
			size_t rowSize = factor1.row_size();

			for(size_t count = 0; count < rowSize; count++)
			{
				product += factor1[0][count] * factor2[count][0];
			}
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::dot_product(Matrix<>, Matrix<>): [!] "
				  <<  message   << std::endl;
	}

	returnData = C(product);

	return returnData;
}

template <typename C, template<typename> class T>
template <typename A, typename B>
const Matrix<C, T> Matrix<C, T>::cross_product
            (const Matrix<A, T> & factor1,
		     const Matrix<B, T> & factor2)
{
	Matrix productMatrix;

	try
	{
		if(are_multipliable(factor1, factor2))
		{
			size_t colSize = factor1.col_size();
			size_t rowSize = factor2.row_size();
			productMatrix  = Matrix::matrix(colSize, rowSize);

			for(size_t row = 0; row < colSize; row++)
			{
				for(size_t col = 0; col < rowSize; col++)
				{
					productMatrix[row][col] =
					round(Matrix<double, T>::dot_product(factor1, row,
							                             factor2, col));
				}
			}
		}
		else if(are_multipliable(factor1, factor2))
		{
			productMatrix = cross_product(factor2, factor1);
		}
		else
		{
			throw "The factors cannot be multiplied."
				  "The first factor's row size must be equal "
			      "to the second factor's column size.";
		}
	}
	catch(const char* message)
	{
		std::cerr <<  std::endl << std::endl
				  << "Matrix<>::cross_product(Matrix<>, Matrix<>): [!] "
				  <<  message   << std::endl;
	}

	return productMatrix;
}

// Named Constructors

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::matrix(size_t colSize, size_t rowSize)
{
	return Matrix(colSize, rowSize);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::matrix(size_t     colSize,
		                                size_t     rowSize,
		                                const C &  content)
{
	return Matrix(colSize, rowSize, content);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::square(size_t size)
{
	return Matrix(size, size);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::square(size_t size, const C & content)
{
	return Matrix(size, size, content);
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::single_row(size_t rowSize)
{
	Matrix singleRow(1, rowSize);

	return singleRow;
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::single_row(size_t     rowSize,
		                                    const C &  content)
{
	Matrix singleRow(1, rowSize, content);

	return singleRow;
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::single_col(size_t colSize)
{
	Matrix singleCol(colSize, 1);

	return singleCol;
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::single_col(size_t     colSize,
                                            const C &  content)
{
	Matrix singleCol(colSize, 1, content);

	return singleCol;
}

template <typename C, template<typename> class T>
const Matrix<C, T> Matrix<C, T>::identity(size_t size)
{
	Matrix id = Matrix::square(size, 0);

	for(size_t count = 0; count < size; count++)
	{
		id[count][count] = 1;
	}

	return id;
}


/*********************
 * --- Functions --- *
 *********************/

// Output Stream Operator - Friend Function

template <typename C, template<typename> class T>
std::ostream & operator<<(std::ostream & out, const Matrix<C, T> & object)
{
	size_t fieldWidth;
	size_t colSize;
	size_t rowSize;

	fieldWidth = out.width();

	if(fieldWidth == 0)
	{
		fieldWidth = Matrix<C, T>::DEFAULT_WIDTH;
	}

	colSize = object.col_size();
	rowSize = object.row_size();

	for(size_t row = 0; row < colSize; row++)
	{
		for(size_t col = 0; col < rowSize; col++)
		{
			out << std::setw(fieldWidth) << object[row][col];
		}

		out << std::endl;
	}

	return out;
}

// Named Constructors

const Matrix<int, Table> identity_matrix(size_t size)
{
	return Matrix<int, Table>::identity(size);
}

// Queries

template <typename A, typename B, template<typename> class T>
bool are_congruent(const Matrix<A, T> & factor1,
                   const Matrix<B, T> & factor2)
{
	return factor1.col_size() == factor2.col_size() &&
		   factor1.row_size() == factor2.row_size();
}

template <typename A, typename B, template<typename> class T>
bool are_multipliable(const Matrix<A, T> & factor1,
				      const Matrix<B, T> & factor2)
{
	return factor1.row_size() == factor2.col_size();
}

template <typename A, template<typename> class T>
bool is_square(const Matrix<A, T> & object)
{
	return object.col_size() == object.row_size();
}

template <typename A, template<typename> class T>
bool is_singular(const Matrix<A, T> & object)
{
	return (is_square(object) && object.determinant() == 0);
}

template <typename A, template<typename> class T>
bool is_unimodular(const Matrix<A, T> & object)
{
    return (is_square(object) && (object.determinant() ==  1 ||
    		                      object.determinant() == -1));
}

#endif /* MATRIX_H_ */
