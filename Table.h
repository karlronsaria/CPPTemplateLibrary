
#ifndef TABLE_H_
#define TABLE_H_

#include "Array.h"

template <typename Content_Type>
class Table: public Array< Array<Content_Type> >
{
	private:

		size_t _rows;
		size_t _cols;

	public:

        /*
        [x] issue 2023_05_06_233151
        - actual: Matrix<> has default constructor, but base class Table<> does not
        - expected: original values copied
        */
		Table():
			  Array< Array<Content_Type> >(0),
			  _rows(0), _cols(0) {}

		Table(size_t colSize, size_t rowSize):
			  Array< Array<Content_Type> >(colSize),
			  _rows(colSize), _cols(rowSize)
		{
			Array<Content_Type> temp(rowSize);
			size_t              index;

			foreach(*this, index) (*this)[index] = temp;
		}

		Table(size_t colSize,
			  size_t rowSize,
			  const Content_Type & content):

			  Array< Array<Content_Type> >(colSize, content),
			 _rows(colSize),
			 _cols(rowSize)
		{
			Array<Content_Type> temp(rowSize);
			size_t              index;

			foreach(*this, index) (*this)[index] = temp;
		}

		Table(const Table & object):

			  Array< Array<Content_Type> >(object),
			 _rows(object._rows),
			 _cols(object._cols) {}

		size_t rows() const { return _rows; }
		size_t cols() const { return _cols; }

		size_t row_size() const { return _cols; }
		size_t col_size() const { return _rows; }

	   ~Table() {}

		static Table square(size_t length)
		{
			return Table(length, length);
		}
};

#endif /* TABLE_H_ */
