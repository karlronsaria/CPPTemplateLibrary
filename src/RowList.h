/*
 * RowList.h
 *
 *  Created on: Apr 30, 2015
 *      Author: adaniels4
 */

#ifndef ROWLIST_H_
#define ROWLIST_H_

template <typename Content_Type, template<typename> class Super_Class>

class RowList: protected Super_Class<Content_Type>
{
	public:

		RowList ();
	   ~RowList ();

	    void   unit  ();
	    void   unit  (const Content_Type &);
	    void   build (size_t);
	    void   build (size_t, const Content_Type &);

		const  Content_Type & operator[] (size_t pos) const;
			   Content_Type & operator[] (size_t pos);

			   std::ostream & operator<< (std::ostream &);

		template <typename C, template<typename> class S>
		friend std::ostream & operator<< (std::ostream        &,
										  const RowList<C, S> &);

		typedef typename Super_Class<Content_Type>::iterator row_it;
};


// RowList Methods -------------------------------------------------------


/*************************************
 * --- Constructors & Destructor --- *
 *************************************/

// Default Constructor
template <typename C, template<typename> class S>
RowList<C, S>::RowList(): S<C>() {}

// Destructor
template <typename C, template<typename> class S>
RowList<C, S>::~RowList() {}


/*************************
 * --- List-Builders --- *
 *************************/

template <typename C, template<typename> class S>
void RowList<C, S>::unit()
{
	RowList::clear();
	RowList::push_back();
}

template <typename C, template<typename> class S>
void RowList<C, S>::unit(const C & content)
{
	RowList::clear();
	RowList::push_back(content);
}

template <typename C, template<typename> class S>
void RowList<C, S>::build(size_t size)
{
	RowList::clear();
	for(size_t count = 1; count <= size; ++count) RowList::push_back();
}

template <typename C, template<typename> class S>
void RowList<C, S>::build(size_t size, const C & content)
{
	RowList::clear();
	for(size_t count = 1; count <= size; ++count)
		RowList::push_back(content);
}


/******************************
 * --- Operator Overloads --- *
 ******************************/

// Subscript Operator - Accessor, returns value.
template <typename C, template<typename> class S>
const C & RowList<C, S>::operator[](size_t index) const
{
	typename S<C>::iterator cursor = RowList::begin();

	size_t count = 0;

	while(count <= index && !cursor.is_null())
	{
		++cursor;
		++count;
	}

	return *cursor;
}

// Subscript Operator - Mutator, returns reference.
template <typename C, template<typename> class S>
C & RowList<C, S>::operator[](size_t index)
{
	typename S<C>::iterator cursor = RowList::begin();

	size_t count = 0;

	while(count <= index && !cursor.is_null())
	{
		++cursor;
		++count;
	}

	return *cursor;
}

// Output Stream Operator - Member Function
template <typename C, template<typename> class S>
std::ostream & RowList<C, S>::operator<<(std::ostream & out)
{
	out << *this;

	return out;
}

// Output Stream Operator - Friend Function
template <typename C, template<typename> class S>
std::ostream & operator<<(std::ostream         & out,
		                  const RowList<C, S>  & object)
{
	typename S<C>::iterator cursor = object.begin();

	while(!cursor.is_null())
	{
		out << *cursor << " ";

		++cursor;
	}

	return out;
}

#endif /* ROWLIST_H_ */
