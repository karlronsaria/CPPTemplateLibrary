/*
 * List.h
 *
 *  Created on: Apr 10, 2015
 *      Author: adaniels4
 */

#ifndef LIST_H_
#define LIST_H_

#include "Iterator.h"
#include "Collection.h"
#include "BinaryNode.h"
#include "Bidirectional\Connect.h"
#include "Bidirectional\Pop.h"
#include "Bidirectional\Position.h"
#include "Bidirectional\Push.h"

// Test
#include "Bidirectional\Print.h"
#include <iostream>

/*************************************************************************
 * List                                                                  *
 * _____________________________________________________________________ *
 *                                                                       *
 * A doubly-linked list that can be traversed to two directions.         *
 * Parameterizes node container content.                                 *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type>
class List: public Collection
{
	public:

		typedef scoped_ptr< BinaryNode<Content_Type> > node_ptr;
		typedef typename node_ptr::locator             node_loc;

		typedef scoped_ptr< size_t > size_ptr;
		typedef size_ptr::locator    size_loc;

	private:

		struct object
		{
			node_ptr  _head;
			node_loc  _tail;
			size_ptr  _size;

			object(): _size(new size_t(0)) {}
		};

		typedef scoped_ptr<object>            object_ptr;
		typedef typename object_ptr::locator  object_loc;

		object_ptr _attributes;

	protected:

		void push_front (node_ptr &);
		void push_back  (node_ptr &);

	public:

		List(): _attributes(new object) {}
	   ~List()                          {}

	          Content_Type & front ()       { return _attributes->_head->content(); }
	    const Content_Type & front () const { return _attributes->_head->content(); }
	          Content_Type & back  ()       { return _attributes->_tail->content(); }
	    const Content_Type & back  () const { return _attributes->_tail->content(); }

		bool   empty () const { return *_attributes->_size == 0; }
		size_t size  () const { return *_attributes->_size; }

		void   clear () {  _attributes->_head.deallocate();
		                   _attributes->_tail.avert();
		                  *_attributes->_size = 0; }

		void push_front ();
		void push_front (const Content_Type &);
		void push_back  ();
		void push_back  (const Content_Type &);

		Content_Type pop_front ();
		Content_Type pop_back  ();

		// Test
		void print          () const

			{ listnode::Print(_attributes->_head); }

		void print_reversed () const

			{ listnode::PrintReversed< BinaryNode<Content_Type> >

				(_attributes->_tail); }

		class iterator
		{
			private:

				node_loc   _pointer;
				object_loc _list_pointer;

			protected:

				void insert(node_ptr &);

			public:

				      iterator();
			         ~iterator();

				      iterator     & operator=  (const iterator &);
				      Content_Type & operator*  ();
				const Content_Type & operator*  ()       const;
				      Content_Type * operator-> ();
				const Content_Type * operator-> ()       const;
				      iterator       operator++ ();
				      iterator       operator++ (int);
				      iterator       operator-- ();
				      iterator       operator-- (int);
				      iterator     & operator+= (size_t);
				const iterator       operator+  (size_t) const;
				      iterator     & operator-= (size_t);
				const iterator       operator-  (size_t) const;

				void         insert ();
				void         insert (const Content_Type &);
				Content_Type remove ();

				friend class List;
		};

	protected:

		void set (iterator &) const;

	public:

		iterator begin () const;
		iterator end   () const;
};


// iterator Methods ------------------------------------------------------


/*****************************
 * --- Protected Methods --- *
 *****************************/

template <typename C>
void List<C>::iterator::insert(node_ptr & node)
{
	if(!_pointer.is_null())
	{
		if(!node.is_null())
		{
			if(_pointer->prev().is_null())
				_list_pointer->_head.assign(node);
			else
				binarynode::Connect(_pointer->prev(), node);

			binarynode::Connect(node, _pointer);
			node.avert();
			++(*_list_pointer->_size);
		}
	}
}


/**************************
 * --- Public Methods --- *
 **************************/

// - Constructor & Destructor

template <typename C>
List<C>::iterator::iterator() {}

template <typename C>
List<C>::iterator::~iterator() {}

// - Operators

// - - Assignment

template <typename C>
typename List<C>::iterator &
List<C>::iterator::operator=(const iterator & other)
{
	_pointer      = other._pointer;
	_list_pointer = other._list_pointer;

	return *this;
}

// - - Dereference

template <typename C>
C & List<C>::iterator::operator*()
{
	assert(_pointer);
	return _pointer->content();
}

template <typename C>
const C & List<C>::iterator::operator*() const
{
	assert(_pointer);
	return _pointer->content();
}

// - - Dereference Qualifier

template <typename C>
C * List<C>::iterator::operator->()
{
	assert(_pointer);
	return &_pointer->content();
}

template <typename C>
const C * List<C>::iterator::operator->() const
{
	assert(_pointer);
	return &_pointer->content();
}

// - - Increment

template <typename C>
typename List<C>::iterator
List<C>::iterator::operator++()
{
	_pointer = _pointer->next();

	return *this;
}

template <typename C>
typename List<C>::iterator
List<C>::iterator::operator++(int)
{
	iterator temp;

	temp._pointer = _pointer;

	++(*this);

	return temp;
}

// - - Decrement

template <typename C>
typename List<C>::iterator
List<C>::iterator::operator--()
{
	_pointer = _pointer->prev();

	return *this;
}

template <typename C>
typename List<C>::iterator
List<C>::iterator::operator--(int)
{
	iterator temp;

	temp._pointer = _pointer;

	--(*this);

	return temp;
}

// - - Forward Shift

template <typename C>
typename List<C>::iterator &
List<C>::iterator::operator+=(size_t distance)
{
	binarynode::GetPositionForward(_pointer, distance, _pointer);

	return *this;
}

template <typename C>
const typename List<C>::iterator
List<C>::iterator::operator+(size_t distance) const
{
	node_loc temp;

	return temp += distance;
}

// - - Backward Shift

template <typename C>
typename List<C>::iterator &
List<C>::iterator::operator-=(size_t distance)
{
	binarynode::GetPositionBackward(_pointer, distance, _pointer);

	return *this;
}

template <typename C>
const typename List<C>::iterator
List<C>::iterator::operator-(size_t distance) const
{
	node_loc temp;

	return temp -= distance;
}

// - List-changing Methods

template <typename C>
void List<C>::iterator::insert()
{
	node_ptr node;

	node.reallocate();

	insert(node);
}

template <typename C>
void List<C>::iterator::insert(const C & content)
{
	node_ptr node;

	node.reallocate();

	node->content(content);

	insert(node);
}

template <typename C>
C List<C>::iterator::remove()
{
	if(!_pointer.is_null())
	{
		node_ptr temp;

		temp.assign(_pointer);

		if(temp->prev().is_null())
			_list_pointer->_head.avert();
		else
			temp->prev()->next().assign(temp->next());

		if(temp->next().is_null())
			_list_pointer->_tail.avert();
		else
		{
			temp->next()->prev().assign(temp->prev());
			temp->next().avert();
		}

		--(*_list_pointer->_size);

		return temp->content();
	}

	return C();
}


// List Methods ----------------------------------------------------------


/*****************************
 * --- Protected Methods --- *
 *****************************/

template <typename C>
void List<C>::push_front(typename List<C>::node_ptr & node)
{
	_attributes->_head.is_null();

	binarynode::PushFront(_attributes->_head, _attributes->_tail, node);

    ++(*_attributes->_size);
}

template <typename C>
void List<C>::push_back(typename List<C>::node_ptr & node)
{
	binarynode::PushBack(_attributes->_head, _attributes->_tail, node);

    ++(*_attributes->_size);
}

template <typename C>
void List<C>::set(iterator & it) const
{
	it._list_pointer = _attributes;
}


/**************************
 * --- Public Methods --- *
 **************************/

// - Mutators

// - - Push

template <typename C>
void List<C>::push_front()
{
	node_ptr temp;

	temp.reallocate();

	push_front(temp);
}

template <typename C>
void List<C>::push_front(const C & content)
{
	node_ptr temp;

	temp.reallocate();

	temp->content(content);

	push_front(temp);
}

template <typename C>
void List<C>::push_back()
{
	node_ptr temp;

	temp.reallocate();

	push_back(temp);
}

template <typename C>
void List<C>::push_back(const C & content)
{
	node_ptr temp;

	temp.reallocate();

	temp->content(content);

	push_back(temp);
}

// - - Pop

template <typename C>
C List<C>::pop_front()
{
    --(*_attributes->_size);

	return binarynode::PopFront(_attributes->_head, _attributes->_tail);
}

template <typename C>
C List<C>::pop_back()
{
    --(*_attributes->_size);

	return binarynode::PopBack(_attributes->_head, _attributes->_tail);
}

// - Accessors

// - - Iterators

template <typename C>
typename List<C>::iterator List<C>::begin() const
{
	iterator temp;

	temp._pointer = _attributes->_head;

	set(temp);

	return temp;
}

template <typename C>
typename List<C>::iterator List<C>::end() const
{
	iterator temp;

	temp._pointer = _attributes->_tail;

	set(temp);

	return temp;
}

#endif /* LIST_H_ */
