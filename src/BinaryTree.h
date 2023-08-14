/*
 * BinaryTree.h
 *
 *  Created on: Apr 14, 2015
 *      Author: adaniels4
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include "Collection.h"
#include "TernaryNode.h"
#include "Node/Connect.h"
#include "Node/Link.h"
#include "Tridirectional/Destroy.h"
#include "Tridirectional/Instances/Size.h"

/*************************************************************************
 * BinaryTree                                                            *
 * _____________________________________________________________________ *
 *                                                                       *
 * A general-purpose binary tree.                                        *
 * Parameterizes node container content.                                 *
 *                                                                       *
 *************************************************************************/

template <typename Content_Type>
class BinaryTree: public Collection
{
	public:

		typedef scoped_ptr< TernaryNode<Content_Type> > node_ptr;
		typedef typename node_ptr::locator              node_loc;

		typedef node_ptr & (TernaryNode<Content_Type>::*ptr_link)();
		typedef node_loc & (TernaryNode<Content_Type>::*loc_link)();

	private:

		node_ptr _root;

	public:

		BinaryTree() {}
	   ~BinaryTree() {}

		bool   any    () const { return _root.any(); }
		size_t size   () const { return ternarynode::Size(_root); }
		void   clear  ()       { _root.release();     }
		void   sprout ()       { _root.reallocate();     }

		void sprout (const Content_Type & content)
		{
			_root.reallocate();
			_root->content(content);
		}

		      Content_Type & root ()       { return _root->content(); }
		const Content_Type & root () const { return _root->content(); }

		class iterator
		{
			private:

				node_loc _pointer;

			protected:

				void push_left(node_ptr & node)
				{
					node::PushOntoLink(_pointer, node,
							ptr_link(&TernaryNode<Content_Type>::left),
							loc_link(&TernaryNode<Content_Type>::parent));
				}

				void push_right(node_ptr & node)
				{
					node::PushOntoLink(_pointer, node,
							ptr_link(&TernaryNode<Content_Type>::right),
							loc_link(&TernaryNode<Content_Type>::parent));
				}

			public:

				iterator() {}
				iterator(const node_ptr   & node): _pointer(node)        {}
				iterator(const node_loc   & node): _pointer(node)        {}
				iterator(const iterator   & it)  : _pointer(it._pointer) {}
				iterator(const BinaryTree & tree): _pointer(tree._root)  {}
			   ~iterator() {}

			    bool any() const { return _pointer.any(); }

			    short is_leaf() const
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

				Content_Type & operator*()
				{
					return _pointer->content();
				}

				const Content_Type & operator*() const
				{
					return _pointer->content();
				}

				Content_Type * operator->()
				{
					return &_pointer->content();
				}

				const Content_Type * operator->() const
				{
					return &_pointer->content();
				}

				iterator left() const
				{
					return

						node::Link< iterator,
							        node_loc,
							        node_ptr,
							        TernaryNode<Content_Type> >

						    (_pointer,

							 ptr_link(&TernaryNode<Content_Type>::left));

//					if(!_pointer->left().any()) return *this;
//					else return iterator(_pointer->left());
				}

				iterator right() const
				{
					return

						node::Link< iterator,
							        node_loc,
							        node_ptr,
							        TernaryNode<Content_Type> >

						    (_pointer,

							 ptr_link(&TernaryNode<Content_Type>::right));

//					if(!_pointer->left().any()) return *this;
//					else return iterator(_pointer->right());
				}

				iterator parent() const
				{
					return

						node::Link< iterator,
							        node_loc,
							        node_loc,
							        TernaryNode<Content_Type> >

						    (_pointer,

							 ptr_link(&TernaryNode<Content_Type>::parent));

//					if(!_pointer->left().any()) return *this;
//					else return iterator(_pointer->parent());
				}

				void root(const BinaryTree & tree)
				{
					_pointer = tree._root;
				}

				void go_left()
				{
					node::GoToLink(_pointer,
							ptr_link(&TernaryNode<Content_Type>::left));
				}

				void go_right()
				{
					node::GoToLink(_pointer,
							ptr_link(&TernaryNode<Content_Type>::right));
				}

				void go_up()
				{
					node::GoToLink(_pointer,
							loc_link(&TernaryNode<Content_Type>::parent));
				}

				void push_left()
				{
					node_ptr node;
					node.reallocate();
					push_left(node);
				}

				void push_left(const Content_Type & content)
				{
					node_ptr node;
					node.reallocate();
					node->content(content);
					push_left(node);
				}

				void push_right()
				{
					node_ptr node;
					node.reallocate();
					push_right(node);
				}

				void push_right(const Content_Type & content)
				{
					node_ptr node;
					node.reallocate();
					node->content(content);
					push_right(node);
				}

				void destroy_left()
				{
					ternarynode::Destroy< node_loc,
										  node_ptr,
										  TernaryNode<Content_Type> >

						(_pointer, &TernaryNode<Content_Type>::left);
				}

				void destroy_right()
				{
					ternarynode::Destroy< node_loc,
										  node_ptr,
										  TernaryNode<Content_Type> >

						(_pointer, &TernaryNode<Content_Type>::right);
				}

				friend class BinaryTree;
		};

	public:

		iterator root_ptr() const
		{
			iterator temp;
			temp._pointer = _root;
			return temp;
		}
};

#endif /* BINARYTREE_H_ */
