/*
 * SplayTree.h
 *
 *  Created on: Apr 20, 2015
 *      Author: adaniels4
 */

#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include "TernaryNode.h"
#include "InOrder.h"
#include "Tridirectional/Height.h"
#include "Tridirectional/Rotate.h"
#include "Tridirectional/Splay.h"

/*************************************************************************
 * SplayTree                                                             *
 * _____________________________________________________________________ *
 *                                                                       *
 * A binary search tree that implements                                  *
 * the self-rotating Splay Tree data structure.                          *
 * Parameterizes node container content and the total order relation.    *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type,
          bool (*Order_Relation)(const Content_Type &,
        		                 const Content_Type &)
        		                 = InOrder<Content_Type> >
class SplayTree
{
	public:

		typedef scoped_ptr< TernaryNode<Content_Type> > node_ptr;
		typedef typename node_ptr::locator              node_loc;

		typedef node_ptr & (TernaryNode<Content_Type>::*ptr_link)();
		typedef node_loc & (TernaryNode<Content_Type>::*loc_link)();

	private:

		node_ptr _root;

	public:

		SplayTree   () {}
	   ~SplayTree   () {}

	    bool any    () const { return _root.any(); }
	    void clear  () const { _root.release();     }

			  Content_Type & root ()       { return _root->content(); }
		const Content_Type & root () const { return _root->content(); }

		void search (const Content_Type &);
		void push   (const Content_Type &);
		void remove (const Content_Type &);

		class iterator
		{
			private:

				node_loc _pointer;

			protected:

				void push_left  (node_ptr &);
				void push_right (node_ptr &);

			public:

				iterator ();
				iterator (const node_ptr  &);
				iterator (const node_loc  &);
				iterator (const iterator  &);
				iterator (const SplayTree &);
			   ~iterator ();

			    bool     any     () const;
			    short    is_leaf () const;

				iterator left    () const;
				iterator right   () const;
				iterator parent  () const;

				      Content_Type & operator*();
				const Content_Type & operator*() const;
				      Content_Type * operator->();
				const Content_Type * operator->() const;

				void root     (const SplayTree &);
				void go_left  ();
				void go_right ();
				void go_up    ();

				friend class SplayTree;
		};

	public:

		iterator root_ptr() const;
};


// SplayTree Methods -----------------------------------------------------


// Mutators

/*************************************************************************
 * search - Performs a Splay Search.                                     *
 *          It searches for the argument key in the tree and the splays  *
 *          it to the root of the tree.                                  *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::search(const C & key)
{
	splay::Splay< C, node_ptr, TernaryNode<C>, R >

		(_root, key, splay::Search);
}

/*************************************************************************
 * push - Performs a Splay Insertion.                                    *
 *        It searches for the argument key's proper position in the tree *
 *        and inserts a node with the key in that position. The node is  *
 *        then splayed to the root of the tree.                          *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::push(const C & key)
{
	splay::Splay< C, node_ptr, TernaryNode<C>, R >

		(_root, key, splay::Insert);
}

/*************************************************************************
 * remove - Performs a Splay Removal.                                    *
 *          It searches for the argument key in the tree. If found, the  *
 *          node containing the key is removed using a binary search     *
 *          tree removal. The nearest in value to that key is then       *
 *          splayed to the root of the tree.                             *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::remove(const C & key)
{
	splay::Splay< C, node_ptr, TernaryNode<C>, R >

		(_root, key, splay::Remove< C, node_ptr, TernaryNode<C> >);
}

/*************************************************************************
 * root_ptr - Returns an iterator to the root of the tree.               *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
typename SplayTree<C, R>::iterator SplayTree<C, R>::root_ptr() const
{
	iterator temp;
	temp._pointer = _root;
	return temp;
}


// Splay Tree iterator Methods -------------------------------------------


/*****************************
 * --- Protected Methods --- *
 *****************************/

/*************************************************************************
 * push_left - Pushes onto the left of the iterator in the tree.         *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::iterator::push_left(node_ptr & node)
{
	node::PushOntoLink(_pointer, node,
			ptr_link(&TernaryNode<C>::left),
			loc_link(&TernaryNode<C>::parent));
}

/*************************************************************************
 * push_right - Pushes onto the right of the iterator in the tree.       *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::iterator::push_right(node_ptr & node)
{
	node::PushOntoLink(_pointer, node,
			ptr_link(&TernaryNode<C>::right),
			loc_link(&TernaryNode<C>::parent));
}


/**************************
 * --- Public Methods --- *
 **************************/

// Constructors & Destructor

/*************************************************************************
 * Default Constructor                                                   *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
SplayTree<C, R>::iterator::iterator() {}

/*************************************************************************
 * Non-Default Constructor - Starts the iterator at a certain node       *
 *                           through a dynamic pointer.                  *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
SplayTree<C, R>::iterator::iterator(const node_ptr & node):
	_pointer(node) {}

/*************************************************************************
 * Non-Default Constructor - Starts the iterator at a certain node       *
 *                           through a passive pointer.                  *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
SplayTree<C, R>::iterator::iterator(const node_loc & node):
	_pointer(node) {}

/*************************************************************************
 * Copy Constructor                                                      *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
SplayTree<C, R>::iterator::iterator(const iterator & it):
	_pointer(it._pointer) {}

/*************************************************************************
 * Non-Default Constructor - Starts the iterator at the top of a tree.   *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
SplayTree<C, R>::iterator::iterator(const SplayTree & tree):
	_pointer(tree._root)  {}

/*************************************************************************
 * Destructor                                                            *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
SplayTree<C, R>::iterator::~iterator() {}

// Accessors

// - Queries

/*************************************************************************
 * any     - Returns whether the iterator is not pointing to null.       *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
bool SplayTree<C, R>::iterator::any() const
{
	return _pointer.any();
}

/*************************************************************************
 * is_leaf - Returns whether the node the iterator points to             *
 *           has no children.                                            *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
short SplayTree<C, R>::iterator::is_leaf() const
{
	try
	{
		if(!_pointer.any()) throw NoData(__FUNCTION__);
		else return (!_pointer->left().any() &&
					 !_pointer->right().any()) ? 1 : 0;
	}
	catch(Exception & e)
	{
		puts(e.message());
		return -1;
	}
}

// - Object Returns

/*************************************************************************
 * right - Returns an iterator to the node in the tree that is           *
 *         to the right of the iterator.                                 *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
typename SplayTree<C, R>::iterator SplayTree<C, R>::iterator::left() const
{
	return node::Link< iterator, node_loc, node_ptr, TernaryNode<C> >

			(_pointer, ptr_link(&TernaryNode<C>::left));
}

/*************************************************************************
 * left - Returns an iterator to the node in the tree that is            *
 *        to the left of the iterator.                                   *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
typename SplayTree<C, R>::iterator SplayTree<C, R>::iterator::right() const
{
	return node::Link< iterator, node_loc, node_ptr, TernaryNode<C> >

			(_pointer, ptr_link(&TernaryNode<C>::right));
}

/*************************************************************************
 * parent - Returns an iterator to the parent of the node in the tree    *
 *          that the iterator is pointing to.                            *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
typename
SplayTree<C, R>::iterator SplayTree<C, R>::iterator::parent() const
{
	return node::Link< iterator, node_loc, node_ptr, TernaryNode<C> >

			(_pointer, ptr_link(&TernaryNode<C>::parent));
}

// Operators

/*************************************************************************
 * Qualify                                                               *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
C & SplayTree<C, R>::iterator::operator*()
{
	return _pointer->content();
}

/*************************************************************************
 * Constant Qualify                                                      *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
const C & SplayTree<C, R>::iterator::operator*() const
{
	return _pointer->content();
}

/*************************************************************************
 * Dereference Qualify                                                   *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
C * SplayTree<C, R>::iterator::operator->()
{
	return &_pointer->content();
}

/*************************************************************************
 * Constant Dereferece Qualify                                           *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
const C * SplayTree<C, R>::iterator::operator->() const
{
	return &_pointer->content();
}

// Mutators

// - Traversal

/*************************************************************************
 * root - Moves the iterator to the root of the argumental tree.         *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::iterator::root(const SplayTree & tree)
{
	_pointer = tree._root;
}

/*************************************************************************
 * go_left - Moves the iterator left down the tree.                      *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::iterator::go_left()
{
	node::GoToLink(_pointer,
			ptr_link(&TernaryNode<C>::left));
}

/*************************************************************************
 * go_right - Moves the iterator right down the tree.                    *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::iterator::go_right()
{
	node::GoToLink(_pointer,
			ptr_link(&TernaryNode<C>::right));
}

/*************************************************************************
 * go_up - Moves the iterator up the tree.                               *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void SplayTree<C, R>::iterator::go_up()
{
	node::GoToLink(_pointer,
			loc_link(&TernaryNode<C>::parent));
}

#endif /* SPLAYTREE_H_ */
