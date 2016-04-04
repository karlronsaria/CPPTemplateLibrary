/*
 * ForwardList.h
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#ifndef FORWARDLIST_H_
#define FORWARDLIST_H_

#include "Collection.h"
#include "Unidirectional\Connect.h"
#include "Unidirectional\End.h"
#include "Unidirectional\Pop.h"
#include "Unidirectional\Position.h"
#include "Unidirectional\Push.h"

// Test
#include "Unidirectional\Print.h"
#include <iostream>

/*************************************************************************
 * ForwardList                                                           *
 * _____________________________________________________________________ *
 *                                                                       *
 * A singly-linked list that can be traversed in one direction.          *
 * Parameterizes node container content.                                 *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type/*, template <typename> class Node_Type*/>
class ForwardList: public Collection
{
	public:

		typedef scoped_ptr< UnaryNode<Content_Type> > node_ptr;
		typedef typename node_ptr::locator            node_loc;

		typedef scoped_ptr< size_t > size_ptr;
		typedef size_ptr::locator    size_loc;

	private:

		node_ptr   _head;
		size_ptr   _size;

	protected:

		void push_front (node_ptr &);
		void push_back  (node_ptr &);

	public:

		ForwardList(): _size(new size_t(0)) {}
	   ~ForwardList()                       {}

	          Content_Type & front ()

	          	  { return _head->content(); }

	    const Content_Type & front () const

	    		  { return _head->content(); }

	          Content_Type & back  ()

	          	  { return unarynode::End(_head)->content(); }

	    const Content_Type & back  () const

	    		  { return unarynode::End(_head)->content(); }

		bool   empty () const { return *_size == 0; }
		size_t size  () const { return *_size; }

		void   clear ()       { _head.deallocate(); *_size = 0; }

		void push_front ();
		void push_front (const Content_Type &);
		void push_back  ();
		void push_back  (const Content_Type &);

		Content_Type pop_front ();
		Content_Type pop_back  ();

		// Test
		void print()
		{
			listnode::Print(_head);
		}

		class iterator
		{
			private:

				node_loc _pointer;
				size_loc _list_size;

			protected:

				void insert_after(node_ptr &);

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
				      iterator     & operator+= (size_t);
				const iterator       operator+  (size_t) const;

				void         insert_after ();
				void         insert_after (const Content_Type &);
				Content_Type remove_after ();

				friend class ForwardList;
		};

		iterator begin () const;
		iterator end   () const;
};


// --


/*****************************
 * --- Protected Methods --- *
 *****************************/

template <typename C>
void ForwardList<C>::iterator::insert_after(node_ptr & node)
{
	if(!_pointer.is_null())
	{
		if(unarynode::Connect(node, _pointer->next()) &&
		   unarynode::Connect(_pointer, node))
		{
			node.avert();
			++(*_list_size);
		}
	}
}


/**************************
 * --- Public Methods --- *
 **************************/

// Constructor & Destructor

template <typename C>
ForwardList<C>::iterator::iterator() {}

template <typename C>
ForwardList<C>::iterator::~iterator() {}

// Operators

template <typename C>
typename ForwardList<C>::iterator &
ForwardList<C>::iterator::operator=(const iterator & other)
{
	_pointer   = other._pointer;
	_list_size = other._list_size;

	return *this;
}

template <typename C>
C & ForwardList<C>::iterator::operator*()
{
	assert(_pointer);
	return _pointer->content();
}

template <typename C>
const C & ForwardList<C>::iterator::operator*() const
{
	assert(_pointer);
	return _pointer->content();
}

template <typename C>
C * ForwardList<C>::iterator::operator->()
{
	assert(_pointer);
	return &_pointer->content();
}

template <typename C>
const C * ForwardList<C>::iterator::operator->() const
{
	assert(_pointer);
	return &_pointer->content();
}

template <typename C>
typename ForwardList<C>::iterator
ForwardList<C>::iterator::operator++()
{
	_pointer = _pointer->next();

	return *this;
}

template <typename C>
typename ForwardList<C>::iterator
ForwardList<C>::iterator::operator++(int)
{
	iterator temp;

	temp._pointer = _pointer;

	++(*this);

	return temp;
}

template <typename C>
typename ForwardList<C>::iterator &
ForwardList<C>::iterator::operator+=(size_t distance)
{
	unarynode::GetPosition(_pointer, distance, _pointer);

	return *this;
}

template <typename C>
const typename ForwardList<C>::iterator
ForwardList<C>::iterator::operator+(size_t distance) const
{
	node_loc temp;

	return temp += distance;
}

// List-changing Methods

template <typename C>
void ForwardList<C>::iterator::insert_after()
{
	node_ptr node;

	node.reallocate();

	insert_after(node);
}

template <typename C>
void ForwardList<C>::iterator::insert_after(const C & content)
{
	node_ptr node;

	node.reallocate();

	node->content(content);

	insert_after(node);
}

template <typename C>
C ForwardList<C>::iterator::remove_after()
{
	if(!_pointer.is_null() && !_pointer->next().is_null())
	{
		node_ptr temp;

		temp.assign(_pointer->next());

		unarynode::Connect(_pointer, _pointer->next()->next());

		temp->next().avert();

		--(*_list_size);

		return temp->content();
	}

	return C();
}


// --


/*****************************
 * --- Protected Methods --- *
 *****************************/

template <typename C/*, template <typename> class N*/>
void ForwardList<C>::push_front(typename ForwardList<C>::node_ptr & node)
{
	unarynode::PushFront(_head, node);

    ++(*_size);
}

template <typename C/*, template <typename> class N*/>
void ForwardList<C>::push_back(typename ForwardList<C>::node_ptr & node)
{
	unarynode::PushBack(_head, node);

    ++(*_size);
}


/**************************
 * --- Public Methods --- *
 **************************/

// - Mutators

// - - Push

template <typename C/*, template <typename> class N*/>
void ForwardList<C>::push_front()
{
	node_ptr temp;

	temp.reallocate();

	push_front(temp);
}

template <typename C/*, template <typename> class N*/>
void ForwardList<C>::push_front(const C & content)
{
	node_ptr temp;

	temp.reallocate();

	temp->content(content);

	push_front(temp);
}

template <typename C/*, template <typename> class N*/>
void ForwardList<C>::push_back()
{
	node_ptr temp;

	temp.reallocate();

	push_back(temp);
}

template <typename C/*, template <typename> class N*/>
void ForwardList<C>::push_back(const C & content)
{
	node_ptr temp;

	temp.reallocate();

	temp->content(content);

	push_back(temp);
}

// - - Pop

template <typename C/*, template <typename> class N*/>
C ForwardList<C>::pop_front()
{
    --(*_size);

	return unarynode::PopFront(_head);
}

template <typename C/*, template <typename> class N*/>
C ForwardList<C>::pop_back()
{
    --(*_size);

	return unarynode::PopBack(_head);
}

// - - Returning Iterators

template <typename C>
typename ForwardList<C>::iterator ForwardList<C>::begin() const
{
	iterator temp;

	temp._pointer   = _head;
	temp._list_size = _size;

	return temp;
}

template <typename C>
typename ForwardList<C>::iterator ForwardList<C>::end() const
{
	iterator temp;

	temp._pointer   = End(_head);
	temp._list_size = _size;

	return temp;
}


#endif /* FORWARDLIST_H_ */
