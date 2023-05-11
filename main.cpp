/*
 * main.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: adaniels4
 */

#include <iomanip>

#include "AVLTree.h"
#include "BinaryTree.h"
#include "SplayTree.h"
#include "Algorithm/TreeTraversal/Print.h"
#include "ForwardList.h"
#include "List.h"
#include "Matrix.h"
#include "TableBuilder.h"

#include "Tridirectional/Instances/Height.h"
#include "Tridirectional/Connect.h"

typedef char current_type;


#define ITERATOR_FUNCTION(classType, name) \
\
void (*name)(classType::iterator &)


#define TYPE_ALIAS(type, name) typedef type name

#define FUNCTR_ALIAS(type) typedef type



// -----------------------------------------------------------------------


int not_main()
{
//	/*
//	 * FORWARDLIST
//	 */
//
//	ForwardList<int> f;
//
//	f.push_front(1);
//	f.push_front(2);
//	f.push_front(3);
//	f.push_back(4);
//	f.push_back(5);
//	f.push_back(6);
//	f.print();
//	std::cin.get();
//	std::cout << f.pop_front();
//	std::cin.get();
//	std::cout << f.pop_front();
//	std::cin.get();
//	std::cout << f.pop_back();
//	std::cin.get();
//	std::cout << f.pop_back();
//	std::cin.get();
//	f.print();
//
//	ForwardList<int>::iterator itforward = f.begin();
//
//	std::cin.get();
//	itforward.insert_after(40);
//	itforward.insert_after(51);
//	itforward.insert_after(70);
//	f.print();
//	std::cin.get();
//	std::cout << f.size();
//	std::cin.get();
//	itforward.remove_after();
//	f.print();
//	std::cin.get();
//	std::cout << f.size();
//	std::cin.get();
//
//	/*
//	 * LIST
//	 */
//
//	List<int> l;
//
//	l.push_front(1);
//	l.push_front(2);
//	l.push_front(3);
//	l.push_back(4);
//	l.push_back(5);
//	l.push_back(6);
//	l.print();
//	std::cin.get();
//	std::cout << l.pop_front();
//	std::cin.get();
//	std::cout << l.pop_front();
//	std::cin.get();
//	std::cout << l.pop_back();
//	std::cin.get();
//	std::cout << l.pop_back();
//	std::cin.get();
//	l.print();
//	std::cin.get();
//
//	List<int>::iterator itlist = l.begin();
//
//	itlist.insert(40);
//	std::cout << l.front();
//	std::cin.get();
//	itlist.insert(51);
//	itlist.insert(70);
//	l.print();
//	std::cin.get();
//	std::cout << l.size();
//	std::cin.get();
//	itlist.remove();
//	l.print();
//	std::cin.get();
//	std::cout << l.size();
//	std::cin.get();
//	l.print_reversed();
//	std::cin.get();
//
//	/*
//	 * BINARYTREE
//	 */
//
//	FUNCTR_ALIAS(ITERATOR_FUNCTION(BinaryTree<current_type>, itFunction));
//
//	BinaryTree<current_type> b;
//
//	b.sprout('A');
//
//	BinaryTree<current_type>::iterator itl = b.root_ptr();
//
//	BinaryTree<char>::iterator itr = itl;
//
//	itl.push_left('B');
//	itl.go_left();
//	itl.push_left('C');
//	itl.push_right('D');
//
//	itr.push_right('E');
//	itr.go_right();
//	itr.push_left('F');
//	itr.push_right('G');
//
//	PreOrderPrint< BinaryTree<current_type> >(b.root_ptr());
//	std::cin.get();
//	TraverseInOrder(b.root_ptr(), itFunction(&PrintNode< BinaryTree<current_type> >));
//	std::cin.get();
//	TraversePostOrder(b.root_ptr(), itFunction(&PrintNode< BinaryTree<current_type> >));
//	std::cin.get();
//
//	itl.root(b);
//	itl.destroy_left();
//
//	TraversePreOrder(b.root_ptr(), itFunction(&PrintNode< BinaryTree<current_type> >));
//	std::cin.get();
//	TraverseInOrder(b.root_ptr(), itFunction(&PrintNode< BinaryTree<current_type> >));
//	std::cin.get();
//	TraversePostOrder(b.root_ptr(), itFunction(&PrintNode< BinaryTree<current_type> >));
//	std::cin.get();
//
//	size_t size = 0;
//
//	ternarynode::GetSize(b.root_ptr(), size/*, ternarynode::ReturnNormally<BinaryTree<current_type>::iterator>*/);
//
//	std::cout << "Size: " << size;
//	std::cin.get();
//
//	std::cout << "Size: " << ternarynode::Size(b.root_ptr());
//	std::cin.get();
//
//	std::cout << "Size: " << b.size();
//	std::cin.get();
//
//	std::cout << "Root: " << b.root();
//	std::cin.get();
//
//	std::cout << "Height: " << (unsigned short)ternarynode::Height(b.root_ptr());
//	std::cin.get();
//
//	/*
//	 * AVLTREE
//	 */
//
//	scoped_ptr< AVLNode<char> > node;
//
//	ternarynode::ConnectLeft< scoped_ptr< AVLNode<char> >,
//	                          AVLNode<char> >(node, node);
//
//	AVLTree<char, inOrder> a;
//
//	a.push('L');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('A');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('B');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('D');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('F');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('G');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('E');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('H');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('C');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('I');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	a.push('J');
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	// -------------------------------------------------------------------
//
//	std::cout << "\nTest I: " << a.remove('I');
//	std::cin.get();
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	std::cout << "\nTest C: " << a.remove('C');
//	std::cin.get();
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	std::cout << "\nTest H: " << a.remove('H');
//	std::cin.get();
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	std::cout << "\nTest E: " << a.remove('E');
//	std::cin.get();
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	std::cout << "\nTest G: " << a.remove('G');
//	std::cin.get();
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	std::cout << "\nTest G: " << a.remove('G');
//	std::cin.get();
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	std::cout << "\nTest F: " << a.remove('F');
//	std::cin.get();
//
//	std::cout << "Root: " << a.root();
//	std::cin.get();
//
//	std::cout << std::endl << std::endl << std::endl;
//
//	/*
//	 * SPLAYTREE
//	 */
//
//	SplayTree<char> s;
//
//	s.push('L');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('A');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('B');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('D');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('F');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('G');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('E');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('H');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('C');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('I');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	s.push('J');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	std::cout << std::endl;
//
//	// -------------------------------------------------------------------
//
//	std::cout << "Removing: C\t";
//	s.remove('C');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	std::cout << "Removing: I\t";
//	s.remove('I');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	std::cout << "Removing: H\t";
//	s.remove('H');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	std::cout << "Removing: E\t";
//	s.remove('E');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	std::cout << "Removing: G\t";
//	s.remove('G');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	std::cout << "Removing: G\t";
//	s.remove('G');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();
//
//	std::cout << "Removing: F\t";
//	s.remove('F');
//
//	std::cout << "Root: " << s.root() << "\t\t";
//	InOrderPrint< SplayTree<char> >(s.root_ptr());
//	std::cin.get();

	/*
	 * MATRIX
	 */

	Matrix<int> m = Matrix<int>::square(8);

	size_t i, j, count = 0;

	for(i = 0; i < m.rows(); ++i)
		for(j = 0; j < m.cols(); ++j)
			m[i][j] = ++count;

	std::cout << std::setw(5) << m;
	std::cout << std::endl << std::endl << m.determinant();

	return 0;
}


