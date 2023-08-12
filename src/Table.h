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

            for (auto& item : *this)
                item = temp;
		}

		Table(
			size_t rows,
			size_t cols,
			std::initializer_list<std::initializer_list<Content_Type>>
				list
		):
			Table(rows, cols)
		{
			auto rowIt = list.begin();

			for (int row = 0; row < (int)this->rows(); ++row)
			{
				auto colIt = rowIt->begin();

				for (int col = 0; col < (int)this->cols(); ++col)
				{
					(*this)[row][col] = *colIt;
					++colIt;
				}

				++rowIt;
			}
		}

		Table(
			std::initializer_list<std::initializer_list<Content_Type>>
				list
		) {
			size_t rows = list.size();
			auto it = list.begin();
			size_t cols = it->size();

			while (++it != list.end())
				if (it->size() < cols)
					cols = it->size();

			*this = Table(rows, cols, list);
		}

		Table(
			size_t rows,
			size_t cols,
			const Content_Type & content
		):
			Array<Array<Content_Type>>(rows),
			_rows(rows),
			_cols(cols)
		{
			Array<Content_Type> temp(cols, content);

            for (auto& item : *this)
                item = temp;
		}

		Table(const Table &) = default;
		Table & operator=(const Table &) = default;
		virtual ~Table() = default;

		size_t rows() const { return _rows; }
		size_t cols() const { return _cols; }

		bool operator==(const Table & other) const {
			if (rows() != other.rows() || cols() != other.cols())
				return false;

			for (int row = 0; row < rows(); ++row)
				for (int col = 0; col < cols(); ++col)
					if ((*this)[row][col] != other[row][col])
						return false;

			return true;
		}

		static Table square(size_t length)
		{
			return Table(length, length);
		}
};

#endif /* TABLE_H_ */
