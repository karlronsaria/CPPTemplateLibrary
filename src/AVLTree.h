/*
 * AVLTree.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "AVLNode.h"
#include "InOrder.h"
#include "Tridirectional/Rotate.h"
#include "Tridirectional/AVL/Insert.h"
#include "Tridirectional/AVL/Remove.h"

/*************************************************************************
 * AVLTree                                                               *
 * _____________________________________________________________________ *
 *                                                                       *
 * A binary search tree that implements                                  *
 * the self-balancing AVL Tree data strucure.                            *
 * Parameterizes node container content and the total order relation.    *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type,
          bool (*Order_Relation)(const Content_Type &,
        		                 const Content_Type &)
        		                 = InOrder<Content_Type> >
class AVLTree
{
	public:

		typedef scoped_ptr< AVLNode<Content_Type> > node_ptr;
		typedef typename node_ptr::locator          node_loc;

		typedef node_ptr & (AVLNode<Content_Type>::*ptr_link)();
		typedef node_loc & (AVLNode<Content_Type>::*loc_link)();

	protected:

		node_ptr _root;

	public:

		AVLTree     () {}
	   ~AVLTree     () {}

		bool empty  () const { return _root.is_null(); }
		void clear  ()       { _root.deallocate();     }

			  Content_Type & root ()       { return _root->content(); }
		const Content_Type & root () const { return _root->content(); }

		void push   (const Content_Type &);
		bool remove (const Content_Type &);
};


// AVLTree Methods -------------------------------------------------------


/*************************************************************************
 * push - Performs an AVL Insertion.                                     *
 *        It searches for the argument key's proper position in          *
 *        the tree and inserts a node with the key in that position.     *
 *        The tree is restructured to maintain balance.                  *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
void AVLTree<C, R>::push(const C & content)
{
	node_ptr node;
	node.reallocate();
	node->content(content);

	avl::Insert< C, node_ptr, AVLNode<C>, R >

		   (_root, node,

			&avl::HeightOf<node_ptr>,
			&ternarynode::RotateAndChangeHeight

				< node_ptr, AVLNode<C>,
				  avl::QualifiedUpdateHeightOf<node_ptr> >,

			&avl::BalanceAndChangeHeight< node_ptr, AVLNode<C> >);

	node.avert();
}

/*************************************************************************
 * remove - Performs an AVL Removal.                                     *
 *          It searches for the argument key in the tree. If found, the  *
 *          node containing the key is removed using a binary search     *
 *          tree removal. Whether the removal succeeded is returned.     *
 *          The tree is restructured to maintain balance.                *
 *************************************************************************/

template <typename C, bool (*R)(const C &, const C &)>
bool AVLTree<C, R>::remove(const C & content)
{
	return avl::Remove< C, node_ptr, AVLNode<C>, R >

		   (_root, content,

			&avl::HeightOf<node_ptr>,
			&ternarynode::RotateAndChangeHeight

				< node_ptr,AVLNode<C>,
				  avl::QualifiedUpdateHeightOf<node_ptr> >,

			&avl::BalanceAndChangeHeight< node_ptr, AVLNode<C> >);
}

#endif /* AVLTREE_H_ */
