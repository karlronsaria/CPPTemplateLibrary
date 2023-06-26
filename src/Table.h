#ifndef TABLE_H_
#define TABLE_H_

#include "Array.h"

template <typename Content_Type>
class Table: public Array<Array<Content_Type>>
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
			Array<Array<Content_Type>>(0),
			_rows(0),
			_cols(0) {}

		Table(size_t rows, size_t cols):
			Array<Array<Content_Type>>(rows),
			_rows(rows),
			_cols(cols)
		{
			Array<Content_Type> temp(cols);
			size_t index;

			foreach (*this, index)
				(*this)[index] = temp;
		}

		Table(
			size_t rows,
			size_t cols,
			std::initializer_list<std::initializer_list<Content_Type>>
				list
		):
			Array<Array<Content_Type>>(rows, cols),
			_rows(rows),
			_cols(cols)
		{
			auto rowIt = list.begin();

			for (size_t row = 0; row < this->rows(); ++row)
			{
				auto colIt = rowIt->begin();

				for (size_t col = 0; col < this->cols(); ++col)
				{
					(*this)[row][col] = *colIt;
					++colIt;
				}

				++rowIt;
			}
		}

		Table(
			size_t rows,
			size_t cols,
			const Content_Type & content
		):
			Array<Array<Content_Type>>(rows, content),
			_rows(rows),
			_cols(cols)
		{
			Array<Content_Type> temp(cols);
			size_t index;

			foreach (*this, index)
				(*this)[index] = temp;
		}

		Table(const Table & object):
			Array< Array<Content_Type> >(object),
			_rows(object._rows),
			_cols(object._cols) {}

		size_t rows() const { return _rows; }
		size_t cols() const { return _cols; }

	   ~Table() {}

		static Table square(size_t length)
		{
			return Table(length, length);
		}
};

#endif /* TABLE_H_ */
