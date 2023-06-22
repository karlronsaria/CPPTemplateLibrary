/*
 * Tree.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef TREE_H_
#define TREE_H_

#include "scoped_ptr.h"

template <typename Content_Type,
          template<typename> class Node_Type>
class Tree
{
	public:

		typedef scoped_ptr< Node_Type<Content_Type> > node_ptr;
		typedef typename node_ptr::locator            node_loc;

		typedef node_ptr & (Node_Type<Content_Type>::*ptr_link)();
		typedef node_loc & (Node_Type<Content_Type>::*loc_link)();

	protected:

		node_ptr _root;

	public:

		Tree() {}
	   ~Tree() {}

		bool empty  () const { return _root.is_null(); }
		void clear  ()       { _root.deallocate();     }
		void sprout ()       { _root.reallocate();     }

		void sprout (const Content_Type & content)
		{
			_root.reallocate();
			_root->content(content);
		}

			  Content_Type & root ()       { return _root->content(); }
		const Content_Type & root () const { return _root->content(); }
};

#endif /* TREE_H_ */
