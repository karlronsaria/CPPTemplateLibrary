/*
 * Height.h
 *
 *  Created on: Apr 16, 2015
 *      Author: adaniels4
 */

#ifndef AVL_HEIGHT_H_
#define AVL_HEIGHT_H_

#ifndef height_t
typedef unsigned char height_t;
#endif

namespace avl
{
	void UpdateHeight(const height_t & leftHeight,
					  const height_t & rightHeight,
						    height_t & nodeHeight)
	{
		nodeHeight = (leftHeight > rightHeight ? leftHeight
											   : rightHeight) + 1;

	}


	// -------------------------------------------------------------------


	template <class Node_Type>
	height_t HeightOf(const Node_Type & node)
	{
		return node.is_null() ? 0 : node->height();
	}


	// -------------------------------------------------------------------


	template <class Node_Type>
	void SetHeightOf(Node_Type & node, const height_t & newHeight)
	{
		node->height(newHeight);
	}


	// -------------------------------------------------------------------


	template <class Node_Type>
	void UpdateHeightOf

		(Node_Type & node,
		 height_t (*GetHeight)(const Node_Type &),
		 void     (*SetHeight)(      Node_Type &, const height_t &))
	{
		height_t tempHeight;

		UpdateHeight(GetHeight(node->left()),
				     GetHeight(node->right()), tempHeight);

		SetHeight(node, tempHeight);
	}


	// -------------------------------------------------------------------


	template <class Node_Type>
	void QualifiedUpdateHeightOf(Node_Type & node)
	{
		UpdateHeightOf(node, &HeightOf, &SetHeightOf);
	}
}

#endif /* AVL_HEIGHT_H_ */
