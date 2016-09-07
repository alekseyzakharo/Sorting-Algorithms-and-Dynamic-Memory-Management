// File:        stockitem.cpp
// Author:      Aleksey Zakharov
// Date:        2016-03-15
// Description: Implemintation of RedBlackTree functions

#ifdef _REDBLACKTREE_H_

// Function helps create a deep copy of another tree
// PARAM: sourcenode = Node<T>* object which we are trying to make a copy of
// PARAM: sourcenode = Node<T>* object which we link back to from created node
template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode)
{
	if (sourcenode == NULL)
	{
		return NULL;
	}
	Node<T>* tmp = new Node<T>(sourcenode->data);
	tmp->p = parentnode;
	tmp->is_black = sourcenode->is_black;
	tmp->data = sourcenode->data;
	size++;
	if (sourcenode != NULL)
	{	
		tmp->left = CopyTree(sourcenode->left, tmp);
		tmp->right = CopyTree(sourcenode->right, tmp);
	}
	return tmp;
}

// Function recursively deletes all nodes and deallocates all memory used
// PARAM: node = Node<T>* object which we are deleting
template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	if(node == NULL)
		return;
	RemoveAll(node->left);
	RemoveAll(node->right);
	delete node;
}

// Function recursivly calculates height of tree, branches into all paths to find height
// PARAM: node = Node<T>* object used to calculate height of tree
template <class T>
int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
	if(node == NULL)
		return -1;
	//calculate the height of the left node
	int lHeight = CalculateHeight(node->left);
    //calculate height of the right node
	int rHeight = CalculateHeight(node->right);
    //choose the one with highest height
	if(lHeight > rHeight)
        return lHeight + 1;
    else
        return rHeight +1;
}

// Default constructor
template <class T>
RedBlackTree<T>::RedBlackTree()
{
	root = NULL;
	size = 0;
}

// Copy constructor, creates deep copy of passed tree
// PARAM: rbtree = RedBlackTree<T>* reference from which all nodes are copied
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
	root = new Node<T>(rbtree.root->data);
	Node<T>* tmp = rbtree.root;
	CopyTree(tmp->right,tmp);
	CopyTree(tmp->left,tmp);
}

// Destructor
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll(root);
}

// Assignment operator
// PARAM: rbtree = RedBlackTree<T>* reference from which all nodes are copied
template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
{
	if (this != &rbtree)
	{
		RemoveAll();
		RedBlackTree(rbtree);
	}
	return *this;
}

// Function inserts an item into RedBlackTree, fixes redblacktree properties
// PARAM: item = T object which we are inserting into RedBlackTree
template <class T>
bool RedBlackTree<T>::Insert(T item)
{
	if(Search(item))
		return false;

	Node<T>* x = BSTInsert(item);
	Node<T>* y;
	x->is_black = false;
	while(x != root && x->p->is_black == false) //x is not root and x parent is red
	{
		if(x->p == x->p->p->left) //if x parent is left child
		{
			y = x->p->p->right; // uncle of x
			if(y != NULL && y->is_black == false) // if uncle and x both red
			{
				x->p->is_black = true; //x parent color = black
				y->is_black = true; // uncle color = black
				x->p->p->is_black = false;
				x = x->p->p;
			}
			else //uncle color == black
			{
				if(x == x->p->right)
				{
					x = x->p;
					LeftRotate(x);
				}
				x->p->is_black = true;
				x->p->p->is_black = false;
				RightRotate(x->p->p);
			}
		}
		else //if x parent is right child
		{
			y = x->p->p->left;
			if(y != NULL && y->is_black == false)
			{
				x->p->is_black = true;
				y->is_black = true;
				x->p->p->is_black = false;
				x = x->p->p;
			}

			else
			{
				if(x == x->p->left)
				{
					x = x->p;
					RightRotate(x);
				}

				x->p->is_black = true;
				x->p->p->is_black = false;
				LeftRotate(x->p->p);
			}
		}
	}
	root->is_black = true;
	size++;
	return true;
}

// Function removes an item into RedBlackTree
// PARAM: item = T object which we are removing from RedBlackTree
template <class T>
bool RedBlackTree<T>::Remove(T item)
{
	if(!Search(item))
		return false;


	bool leftChild = false;

	Node<T>* findNode = root;
	Node<T>* z;
	Node<T>* y;
	Node<T>* x;

	if(root->data == item)
		z = root;
	else
	{
		while(findNode->data != item)
		{
			if(findNode->data > item)
				findNode=findNode->left;
			else
				findNode=findNode->right;
		}
		z = findNode;
	}
	//at this point z points to the node we are trying to remove

	if(z->left == NULL || z->right == NULL)
		y = z;
	else
		y = Predecessor(z);
	if(y->left != NULL)
	{
		x = y->left;
	}
	else
		x = y->right;
	if(x != NULL)
	{
		x->p = y->p;
		//x->is_black = y->is_black;
	}
	if(y->p == NULL)
	{
		root = x;
	}
	else
	{
		//attach x to y's parents
		if( y == y->p->left) //left child
		{
			y->p->left = x;
			leftChild = true;
		}
		else //right child
		{
			y->p->right = x;
			leftChild = false;
		}
	}
	if(y != z) //i.e y has been moved up
		z->data = y->data;
	if(y->is_black == true)
	{	
		RBDeleteFixUp(x,y->p,leftChild);
	}
	delete y;
	size--;
	return true;
}

// Helper function to 'remove', this function fixes the redblacktree 
// properties after deletion of a node.
// PARAM: x = Node<T>* node that we start up fixing our tree up
// PARAM: xparent = Node<T>* x's parent node
// PARAM: xisleftchild = boolean for wheather x is a left child
template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	

	Node<T>* XXPARENT = xparent;
	Node<T>* y;

	while(x != root && x == NULL || x != root && !x->is_black)
	{
		if(x == root)
			break;
		if(xisleftchild)
		{
			y = XXPARENT->right; // y = right sibling
			if(y == NULL)
				break;
			if(!y->is_black) //is y(sibling red)
			{

				y->is_black = true;
				XXPARENT->is_black = false;
				LeftRotate(XXPARENT);
				y = XXPARENT->right;
			}
			else if(y->left == NULL && y->right == NULL ||y->left == NULL && (y->right != NULL && y->right->is_black) || y->right == NULL && (y->left != NULL && y->left->is_black) )//are both y's children black
			{
				y->is_black = false;
				x = XXPARENT;
				XXPARENT = XXPARENT->p;
				if(x != root && x == x->p->right)
					xisleftchild = false;
				else if(x != root && x == x->p->left)
					xisleftchild = true;
			}
			else
			{
				if(y->right == NULL || y->right->is_black)
				{
					y->left->is_black = true;
					y->is_black = false;
					RightRotate(y);
					y=XXPARENT->right;
				}
				if(y!= NULL)
					y->is_black = XXPARENT->is_black;
				XXPARENT->is_black = true;
				if(y!= NULL)
					y->right->is_black = true;
				LeftRotate(XXPARENT);
				x = root;
			}
		}
		else
		{
			if(x == root)
				break;
			y = XXPARENT->left; //y = right sibling
			if(y == NULL)
				break;
			if(!y->is_black)//is y(sibling red)
			{
				y->is_black = true;
				XXPARENT->is_black = false;
				RightRotate(XXPARENT);
				y = XXPARENT->left;
			}
			else if(y->left == NULL && y->right == NULL || y->left == NULL && (y->right != NULL && y->right->is_black) || y->right == NULL && (y->left != NULL && y->left->is_black) )//are both y's children black
			{

				y->is_black = false;
				x = XXPARENT;
				XXPARENT = XXPARENT->p;
				if(x != root && x == x->p->right)
					xisleftchild = false;
				else if(x != root && x == x->p->left)
					xisleftchild = true;
			}
			else //
			{
				if(y->left == NULL || y->left->is_black)
				{
					y->right->is_black = true;
					y->is_black = false;
					LeftRotate(y);
					y=XXPARENT->left;
				}
				if(y!= NULL)
					y->is_black = XXPARENT->is_black;
				XXPARENT->is_black = true;
				if(y!= NULL)
					y->left->is_black = true;
				RightRotate(XXPARENT);
				x = root;
			}
		}
	}
}

// Function removes all items from RedBlackTree
template <class T>
void RedBlackTree<T>::RemoveAll()
{
	RemoveAll(root->left);
	RemoveAll(root->right);
	delete root;

	size = 0;
	root = NULL;
}

// Function returns size of RedBlackTree
template <class T>
int RedBlackTree<T>::Size() const
{
	return size;
}

// Function returns height of RedBlackTree
template <class T>
int RedBlackTree<T>::Height() const
{
	if(size == 0)
		return 0;
	return CalculateHeight(root);
}

#endif