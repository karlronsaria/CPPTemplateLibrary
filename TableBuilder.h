/*
 * TableBuilder.h
 *
 *  Created on: Apr 30, 2015
 *      Author: adaniels4
 */

#ifndef TABLEBUILDER_H_
#define TABLEBUILDER_H_

#include "RowList.h"
#include "List.h"
#include "Table.h"

template <typename Content_Type>
class Subtable: public RowList<Content_Type, List>
{
	template <typename C>
	friend class TableBuilder;
};

template <typename Content_Type>
class TableBuilder: public Subtable< Subtable<Content_Type> >
{
	protected:

	   /*****************************
	    * --- Protected Methods --- *
	    *****************************/

	   typename TableBuilder::row_it find_row(size_t) const;

	   const Content_Type & element_data(size_t, size_t) const;

	public:

	   /*************************************
	    * --- Constructors & Destructor --- *
	    *************************************/

	    TableBuilder          ();
	    TableBuilder          (size_t, size_t);
	    TableBuilder          (size_t, size_t, const Content_Type &);
	    TableBuilder          (const TableBuilder &);
	   ~TableBuilder          ();

	   /*********************
	    * --- Accessors --- *
	    *********************/

	   size_t col_size        () const;
	   size_t row_size        () const;

	   const TableBuilder row (size_t) const;
	   const TableBuilder col (size_t) const;

	   // Verifiers

	   bool valid_row_index   (size_t) const;
	   bool valid_col_index   (size_t) const;

	   // Conversion

	   Table<Content_Type> to_table() const;

	   /********************
	    * --- Mutators --- *
	    ********************/

	   void unit_table        ();
	   void unit_table        (const Content_Type &);

	   void push_back_row     ();
	   void push_back_col     ();
	   void push_front_row    ();
	   void push_front_col    ();

	   void push_back_row     (const Content_Type &);
	   void push_back_col     (const Content_Type &);
	   void push_front_row    (const Content_Type &);
	   void push_front_col    (const Content_Type &);

	   void pop_back_row      ();
	   void pop_back_col      ();
	   void pop_front_row     ();
	   void pop_front_col     ();

	   void set_row           (size_t, const Content_Type &);
	   void set_col           (size_t, const Content_Type &);

	   void set_row           (size_t, const TableBuilder &);
	   void set_col           (size_t, const TableBuilder &);

	   /******************************
	    * --- Operator Overloads --- *
	    ******************************/

	          std::ostream & operator<< (std::ostream &) const;

	   template <typename Type>
	   friend std::ostream & operator<< (std::ostream &,
	   		                          const TableBuilder<Type> &);

	   /**************************
	    * --- Static Methods --- *
	    **************************/

	   static const TableBuilder single_row (size_t);
	   static const TableBuilder single_row (size_t, const Content_Type &);
	   static const TableBuilder single_col (size_t);
	   static const TableBuilder single_col (size_t, const Content_Type &);

	   /**********************************
	    * --- Other Friend Functions --- *
	    **********************************/

	   // Queries

	   template<typename Type>
	   friend bool is_a_single_row(const TableBuilder<Type> &);

	   template<typename Type>
	   friend bool is_a_single_col(const TableBuilder<Type> &);
};


// TableBuilder Methods --------------------------------------------------


/*****************************
 * --- Protected Methods --- *
 *****************************/

template <typename C>
typename TableBuilder<C>::row_it
TableBuilder<C>::find_row(size_t index) const
{
	typename TableBuilder::row_it rowIt;

	rowIt = TableBuilder::begin();

	for(size_t row = 0; row < index; ++row) ++rowIt;

	return rowIt;
}

template <typename C>
const C &
TableBuilder<C>::element_data(size_t rowIndex, size_t colIndex) const
{
	typename TableBuilder::row_it

	elementIt = TableBuilder::find_row(rowIndex)->begin();

	for(size_t col = 0; col < colIndex; ++col) ++elementIt;

	return *elementIt;
}

/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

// Default
template <typename C>
TableBuilder<C>::TableBuilder() {}

// Volume Constructor
template <typename C>
TableBuilder<C>::TableBuilder(size_t colSize, size_t rowSize)
{
	TableBuilder newRow;

	newRow.unit();

	newRow[0].build(rowSize);

	for(size_t count = 0; count < colSize; ++count)
	{
		TableBuilder::push_front(newRow[0]);
	}
}

// Uniform Initializing Constructor
template <typename C>
TableBuilder<C>::TableBuilder(size_t    colSize,
		                      size_t    rowSize,
		                      const C & content)
{
	TableBuilder newRow;

	newRow.unit();

	newRow[0].build(rowSize, content);

	for(size_t count = 0; count < colSize; ++count)
	{
		TableBuilder::push_front(newRow[0]);
	}
}

// Destructor
template <typename C>
TableBuilder<C>::~TableBuilder() {}


/*********************
 * --- Accessors --- *
 *********************/

template <typename C>
size_t TableBuilder<C>::col_size() const
{
	return TableBuilder::size();
}

template <typename C>
size_t TableBuilder<C>::row_size() const
{
	if(col_size() == 0)
	{
		return 0;
	}
	else
	{
		return TableBuilder::front().size();
	}
}

template <typename C>
const TableBuilder<C> TableBuilder<C>::row(const size_t ROW) const
{
	size_t rowSize = row_size();

	TableBuilder newTableBuilder(1, rowSize);

	for(size_t col = 0; col < rowSize; ++col)
	{
		newTableBuilder[0][col] = element_data(ROW, col);
	}

	return newTableBuilder;
}

template <typename C>
const TableBuilder<C> TableBuilder<C>::col(const size_t COL) const
{
	size_t colSize = col_size();

	TableBuilder newTableBuilder(colSize, 1);

	for(size_t row = 0; row < colSize; ++row)
	{
		newTableBuilder[row][0] = element_data(row, COL);
	}

	return newTableBuilder;
}

// Verifiers

template <typename C>
bool TableBuilder<C>::valid_row_index(size_t row) const
{
	return row < col_size();
}

template <typename C>
bool TableBuilder<C>::valid_col_index(size_t col) const
{
	return col < row_size();
}

// Conversion

template <typename C>
Table<C> TableBuilder<C>::to_table() const
{
	Table<C> toTable(col_size(), col_size());
	size_t   row, col;

	for(row = 0; row < col_size(); ++row)
		for(col = 0; col < col_size(); ++col)
			toTable[row][col] = (*this)[row][col];

	return toTable;
}


/********************
 * --- Mutators --- *
 ********************/

template <typename C>
void TableBuilder<C>::unit_table()
{
	TableBuilder::unit();
	(*this)[0].unit();
}

template <typename C>
void TableBuilder<C>::unit_table(const C & content)
{
	TableBuilder::unit();
	(*this)[0].unit(content);
}

template <typename C>
void TableBuilder<C>::push_back_row()
{
	if(TableBuilder::empty())
	{
		unit_table();
	}
	else
	{
		TableBuilder::push_back();
		TableBuilder::back().build(row_size());

//		TableBuilder newRow;
//
//		newRow.unit();
//		newRow[0].array(row_size());
//
//		TableBuilder::append_back(newRow);
	}
}

template <typename C>
void TableBuilder<C>::push_back_col()
{
	if(TableBuilder::empty())
	{
		unit_table();
	}
	else
	{
		size_t colSize = col_size();

		for(size_t count = 0; count < colSize; ++count)
		{
			(*this)[count].push_back();
		}

//		TableBuilder  newRow;;
//
//		newRow.unit();
//		newRow[0].unit();
//		colSize = col_size();
//
//		for(size_t count = 0; count < colSize; count++)
//		{
//			(*this)[count].append_back(newRow[0]);
//		}
	}
}

template <typename C>
void TableBuilder<C>::push_front_row()
{
	if(TableBuilder::empty())
	{
		unit_table();
	}
	else
	{
		TableBuilder::push_front();
		TableBuilder::front().build(row_size());

//		TableBuilder newRow;
//
//		newRow.unit();
//		newRow[0].array(row_size());
//
//		TableBuilder::append_front(newRow);
	}
}

template <typename C>
void TableBuilder<C>::push_front_col()
{
	if(TableBuilder::empty())
	{
		unit_table();
	}
	else
	{
		size_t colSize = col_size();

		for(size_t count = 0; count < colSize; ++count)
		{
			(*this)[count].push_front();
		}

//		TableBuilder  newRow;
//		size_t colSize;
//
//		newRow.unit();
//		newRow[0].unit();
//		colSize = col_size();
//
//		for(size_t count = 0; count < colSize; count++)
//		{
//			(*this)[count].append_front(newRow[0]);
//		}
	}
}


template <typename C>
void TableBuilder<C>::push_back_row(const C & content)
{
	if(TableBuilder::empty())
	{
		unit_table(content);
	}
	else
	{
		TableBuilder::push_back();
		TableBuilder::back().build(row_size(), content);

//		TableBuilder newRow;
//
//		newRow.unit();
//		newRow[0].array(row_size(), INPUT);
//
//		TableBuilder::append_back(newRow);
	}
}

template <typename C>
void TableBuilder<C>::push_back_col(const C & content)
{
	if(TableBuilder::empty())
	{
		unit_table(content);
	}
	else
	{
		size_t colSize = col_size();

		for(size_t count = 0; count < colSize; ++count)
		{
			(*this)[count].push_back();
		}

//		TableBuilder  newRow;
//		size_t colSize;
//
//		newRow.unit();
//		newRow[0].unit(INPUT);
//		colSize = col_size();
//
//		for(size_t count = 0; count < colSize; count++)
//		{
//			(*this)[count].append_back(newRow[0]);
//		}
	}
}

template <typename C>
void TableBuilder<C>::push_front_row(const C & content)
{
	if(TableBuilder::empty())
	{
		unit_table(content);
	}
	else
	{
		TableBuilder::push_front();
		TableBuilder::front().build(row_size(), content);

//		TableBuilder newRow;
//
//		newRow.unit();
//		newRow[0].array(TableBuilder::rowSize(), INPUT);
//
//		TableBuilder::append_front(newRow);
	}
}

template <typename C>
void TableBuilder<C>::push_front_col(const C & content)
{
	if(TableBuilder::empty())
	{
		unit_table(content);
	}
	else
	{
		size_t colSize = col_size();

		for(size_t count = 0; count < colSize; ++count)
		{
			(*this)[count].push_front();
		}

//		TableBuilder  newRow;
//		size_t colSize;
//
//		newRow.unit();
//		newRow[0].unit(INPUT);
//		colSize = col_size();
//
//		for(size_t count = 0; count < colSize; count++)
//		{
//			(*this)[count].append_front(newRow[0]);
//		}
	}
}


template <typename C>
void TableBuilder<C>::pop_back_row()
{
	TableBuilder::pop_back();
}

template <typename C>
void TableBuilder<C>::pop_back_col()
{
	size_t colSize;

	colSize = col_size();

	for(size_t count = 0; count < colSize; ++count)
	{
		(*this)[count].pop_back();
	}
}

template <typename C>
void TableBuilder<C>::pop_front_row()
{
	TableBuilder::pop_front();
}

template <typename C>
void TableBuilder<C>::pop_front_col()
{
	size_t colSize;

	colSize = col_size();

	for(size_t count = 0; count < colSize; ++count)
	{
		(*this)[count].pop_front();
	}
}


template <typename C>
void TableBuilder<C>::set_row(size_t row, const C & content)
{
	size_t rowSize;

	rowSize = row_size();

	for(size_t col = 0; col < rowSize; ++col)
	{
		(*this)[row][col] = content;
	}
}

template <typename C>
void TableBuilder<C>::set_col(size_t col, const C & content)
{
	size_t colSize;

	colSize = col_size();

	for(size_t row = 0; row < colSize; ++row)
	{
		(*this)[row][col] = content;
	}
}

template <typename C>
void TableBuilder<C>::set_row(size_t row, const TableBuilder & singleRow)
{
	size_t rowSize;
	size_t singleRowSize;

	rowSize       = row_size();
	singleRowSize = singleRow.row_size();

	for(size_t col = 0; col < rowSize && col < singleRowSize; ++col)
	{
		(*this)[row][col] = singleRow[row][col];
	}
}

template <typename C>
void TableBuilder<C>::set_col(size_t col, const TableBuilder & singleCol)
{
	size_t colSize;
	size_t singleColSize;

	colSize       = col_size();
	singleColSize = singleCol.col_size();

	for(size_t row = 0; row < colSize && col < singleColSize; ++row)
	{
		(*this)[row][col] = singleCol[row][col];
	}
}


/******************************
 * --- Operator Overloads --- *
 ******************************/

// Output Stream Operator - Method
template <typename C>
std::ostream & TableBuilder<C>::operator<<(std::ostream & out) const
{
	out << *this;

	return out;
}

// Output Stream Operator - Friend Function
template<typename Type>
std::ostream & operator<<(std::ostream             & out,
		                  const TableBuilder<Type> & object)
{
	size_t tableLength;

	tableLength = object.col_size();

	for(size_t index = 0; index < tableLength; ++index)
	{
		out << object[index] << "\n";
	}

	return out;
}


/**************************
 * --- Static Methods --- *
 **************************/

template <typename C>
const TableBuilder<C> TableBuilder<C>::single_row(size_t rowSize)
{
	TableBuilder singleRow(rowSize, 1);

	return singleRow;
}

template <typename C>
const TableBuilder<C> TableBuilder<C>::single_row(size_t    rowSize,
		                                          const C & content)
{
	TableBuilder singleRow(rowSize, 1, content);

	return singleRow;
}

template <typename C>
const TableBuilder<C> TableBuilder<C>::single_col(size_t colSize)
{
	TableBuilder singleCol(1, colSize);

	return singleCol;
}

template <typename C>
const TableBuilder<C> TableBuilder<C>::single_col(size_t    colSize,
		                                          const C & content)
{
	TableBuilder singleCol(1, colSize, content);

	return singleCol;
}


/**********************************
 * --- Other Friend Functions --- *
 **********************************/

// Verifiers

template<typename Type>
bool is_a_single_row(const TableBuilder<Type> & object)
{
	return object.row_size()  > 1 &&
		   object.col_size() == 1;
}

template<typename Type>
bool is_a_single_col(const TableBuilder<Type> & object)
{
	return object.row_size() == 1 &&
		   object.col_size()  > 1;
}

#endif /* TABLEBUILDER_H_ */
