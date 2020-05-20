#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

# include "Utility.hpp"
# include "Vector.hpp"
# include <sstream>

namespace ft
{
	template <typename E, typename Compare, bool AllowDuplicate>
	class AVLTree;

	template <typename E, typename Compare, bool AllowDuplicate>
	class AVLTreeIterator
	{
		private:
			typedef AVLTree<E, Compare, AllowDuplicate> tree;
			typedef typename tree::node node;

			tree& _tree;
			node* _node;

			AVLTreeIterator(tree& t, node* n):
				_tree(t), _node(n)
			{
			}

		public:
			typedef std::ptrdiff_t difference_type;
			typedef E value_type;
			typedef E* pointer;
			typedef E& reference;
			typedef BidirectionalIteratorTag iterator_category;

			AVLTreeIterator() : AVLTreeIterator<E, Compare, AllowDuplicate>(NULL, NULL){}

			AVLTreeIterator(tree* tree, node* node) : _tree(*tree), _node(node) {}
			AVLTreeIterator(const AVLTreeIterator<E, Compare, AllowDuplicate>& other):
				_tree(other._tree), _node(other._node)
			{
			}

			~AVLTreeIterator()
			{
			}

			AVLTreeIterator<E, Compare, AllowDuplicate>& operator=(const AVLTreeIterator<E, Compare, AllowDuplicate>& other)
			{
				_node = other._node;
				return *this;
			}

			AVLTreeIterator<E, Compare, AllowDuplicate>& operator++()
			{
				if (_node->right)
				{
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
				}
				else
				{
					node* tmp;
					do
					{
						tmp = _node;
						_node = _node->parent;
					}
					while (_node && tmp == _node->right);
				}
				return *this;
			}

			AVLTreeIterator<E, Compare, AllowDuplicate> operator++(int)
			{
				AVLTreeIterator<E, Compare, AllowDuplicate> cpy = *this;
				operator++();
				return cpy;
			}

			AVLTreeIterator<E, Compare, AllowDuplicate>& operator--()
			{
				if (!_node)
				{
					_node = _tree._root;
					while (_node && _node->right)
						_node = _node->right;
				}
				else if (_node->left)
				{
					_node = _node->left;
					while (_node && _node->right)
						_node = _node->right;
				}
				else
				{
					node* tmp;
					do
					{
						tmp = _node;
						_node = _node->parent;
					}
					while (_node && tmp == _node->left);
				}
				return *this;
			}

			AVLTreeIterator<E, Compare, AllowDuplicate> operator--(int)
			{
				AVLTreeIterator<E, Compare, AllowDuplicate> cpy = *this;
				operator--();
				return cpy;
			}

			reference operator*() const
			{
				return _node->el;
			}

			pointer operator->() const
			{
				return &_node->el;
			}

			template <typename U, typename Cmp, bool ADup>
			friend bool operator==(const AVLTreeIterator<U, Cmp, ADup>& lhs, const AVLTreeIterator<U, Cmp, ADup>& rhs);
			template <typename U, typename Cmp, bool ADup>
			friend class AVLTree;
	};

	template <typename E, typename Compare, bool AllowDuplicate>
	bool operator==(const AVLTreeIterator<E, Compare, AllowDuplicate>& lhs, const AVLTreeIterator<E, Compare, AllowDuplicate>& rhs)
	{
		return lhs._node == rhs._node;
	}

	template <typename E, typename Compare, bool AllowDuplicate>
	bool operator!=(const AVLTreeIterator<E, Compare, AllowDuplicate>& lhs, const AVLTreeIterator<E, Compare, AllowDuplicate>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename E, typename Compare, bool AllowDuplicate>
	class AVLTree
	{

		public:
			typedef AVLTreeNode<E> node;
		
		private:

			Compare _cmp;
			node* _root;
			size_t _len;

			static int balance_factor(node* n)
			{
				if (!n)
					return 0;
				return (n->left ? n->left->height : -1) -
					(n->right ? n->right->height : -1);
			}

			static void rotate_left(node** target)
			{
				node* y = (*target)->right;
				node* parent = (*target)->parent;
				(*target)->parent = y;
				y->parent = parent;
				(*target)->right = y->left;
				y->left = *target;
				(*target)->height = max(
					(*target)->left ? (*target)->left->height : -1,
					(*target)->right ? (*target)->right->height : -1
				) + 1;
				*target = y;
				y->height = max(
					y->left ? y->left->height : -1,
					y->right ? y->right->height : -1
				) + 1;
			}

			static void rotate_right(node** target)
			{
				node* y = (*target)->left;
				node* parent = (*target)->parent;
				(*target)->parent = y;
				y->parent = parent;
				(*target)->left = y->right;
				y->right = *target;
				(*target)->height = max(
					(*target)->left ? (*target)->left->height : -1,
					(*target)->right ? (*target)->right->height : -1
				) + 1;
				*target = y;
				y->height = max(
					y->left ? y->left->height : -1,
					y->right ? y->right->height : -1
				) + 1;
			}

			static void deep_free(node*& n)
			{
				if (!n)
					return;
				deep_free(n->left);
				deep_free(n->right);
				delete n;
				n = NULL;
			}

			static int max(int a, int b)
			{
				return a > b ? a : b;
			}

			static node* deep_cpy(node *parent, node* n)
			{
				if (!n)
					return NULL;
				node* cpy = new node(n->el, parent, NULL, NULL, n->height);
				cpy->left = deep_cpy(cpy, n->left);
				cpy->right = deep_cpy(cpy, n->right);
				return cpy;
			}

			void erase_rebalance(node *parent)
			{
				for (node* p = parent; p; p = p->parent)
				{
					p->height = max(
						p->left ? p->left->height : -1,
						p->right ? p->right->height : -1
					) + 1;
					if (balance_factor(p) <= -2 || balance_factor(p) >= 2)
					{
						node* x = p;
						node* y = x->left->height > x->right->height ?
							x->left : x->right;
						node* z;
						if (y->left->height == y->right->height)
							z = y == x->left ? y->left : y->right;
						else
							z = y->left->height > y->right->height ? y->left : y->right;

						if (y == x->left)
						{
							if (z == x->left->right)
								rotate_left(&y);
							rotate_right(&x);
						}
						else if (y == x->right)
						{
							if (z == x->right->left)
								rotate_left(&y);
							rotate_right(&x);
						}
					}
				}
			}

			void insert_rebalance(node *inserted)
			{
				// go back to the root and update heights
				for (node* n = inserted; n; n = n->parent)
				{
					n->height = max(
						n->left ? n->left->height : -1,
						n->right ? n->right->height : -1
					) + 1;
					node** x;
					if (!n->parent)
						x = &_root;
					else
						x = n == n->parent->left ? &n->parent->left : &n->parent->right;

					if (balance_factor(n) < -1)
					{
						if (balance_factor(n->right) > 0)
							rotate_right(&(*x)->right);
						rotate_left(x);
						break;
					}
					else if (balance_factor(n) > 1)
					{
						if (balance_factor(n->left) < 0)
							rotate_left(&(*x)->left);
						rotate_right(x);
						break;
					}
				}
			}

		public:
			typedef E value_type;
			typedef Compare compare;
			typedef AVLTreeIterator<E, compare, AllowDuplicate> iterator;
			typedef AVLTreeIterator<const E, compare, AllowDuplicate> const_iterator;
			typedef ReverseIterator<iterator> reverse_iterator;
			typedef ReverseIterator<const_iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit AVLTree(const compare& cmp = compare()):
				_cmp(cmp), _root(NULL), _len(0)
			{
			}

			template <typename InputIt>
			AVLTree(InputIt first, InputIt last, const compare& cmp = compare()):
				_cmp(cmp), _root(NULL), _len(0)
			{
				insert(first, last);
			}

			AVLTree(const AVLTree<E, Compare, AllowDuplicate>& o):
				_cmp(o._cmp), _root(deep_cpy(NULL, o._root)), _len(o._len)
			{
			}

			~AVLTree()
			{
				deep_free(_root);
			}

			AVLTree<E, Compare, AllowDuplicate> &operator=(const AVLTree<E, Compare, AllowDuplicate>& o)
			{
				deep_free(_root);
				_root = deep_cpy(NULL, o._root);
				_cmp = o._cmp;
				_len = o._len;
				return *this;
			}

			iterator begin()
			{
				node* n = _root;
				while (n && n->left)
					n = n->left;
				return iterator(*this, n);
			}

			const_iterator begin() const
			{
				node* n = _root;
				while (n && n->left)
					n = n->left;
				return const_iterator(*this, n);
			}

			iterator end()
			{
				return iterator(*this, NULL);
			}

			const_iterator end() const
			{
				return const_iterator(*this, NULL);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			bool empty() const
			{
				return _len == 0;
			}

			size_type size() const
			{
				return _len;
			}

			size_type max_size() const
			{
				return static_cast<size_type>(-1 / sizeof(node));
			}

			Pair<iterator, bool> insert(const value_type& val)
			{
				return insert(iterator(*this, _root), val);
			}

			Pair<iterator, bool> insert(iterator hint, const value_type& val)
			{
				node* part = hint._node;
				node* newNode;

				if (!_root)
				{
					_root = new node(val, NULL, NULL, NULL, 0);
					_len++;
					return make_pair(iterator(*this, _root), true);
				}

				while (true)
				{
					if (!AllowDuplicate && part->el == val)
						return make_pair(iterator(*this, part), false);
					if (_cmp(val, part->el))
					{
						if (part->left)
							part = part->left;
						else
						{
							newNode = new node(val, part, NULL, NULL, 0);
							part->left = newNode;
							break;
						}
					}
					else
					{
						if (part->right)
							part = part->right;
						else
						{
							newNode = new node(val, part, NULL, NULL, 0);
							part->right = newNode;
							break;
						}
					}
				}

				insert_rebalance(newNode);

				_len++;
				return make_pair(iterator(*this, newNode), true);
			}

			template <typename InputIt>
			void insert(InputIt first, InputIt last)
			{
				for (; first != last; ++first)
				{
					insert(*first);
				}
			}

			void transplant(node* u, node *v)
			{
				if (u->parent == NULL) //u is root
					_root = v;
				else if (u == u->parent->left) // u is left child
					u->parent->left = v;
				else //u is right child
					u->parent->right = v;

				if (v != NULL)
					v->parent = u->parent;
			}

			void avl_delete_fixup(node *n)
			{
				node *p = n;
				while (p != NULL)
				{
					p->height = 1 + max((p->left?p->left->height:-1), (p->right?p->right->height:-1));

					if (balance_factor(p) <= -2 || balance_factor(p) >= 2) //grandparent is unbalanced
					{
						node *x, *y, *z;
						x = p;

						//taller child of x will be y
						if ((x->left?x->left->height:-1) > (x->right?x->right->height:-1))
							y = x->left;
						else
							y = x->right;

						//taller child of y will be z
						if ((y->left?y->left->height:-1) > (y->right?y->right->height:-1))
							z = y->left;
						else if((y->left?y->left->height:-1) < (y->right?y->right->height:-1))
							z = y->right;
						else //same height, go for single rotation
						{
							if (y == x->left)
								z = y->left;
							else
								z = y->right;
						}

						if(y == x->left)
						{
							if (z == (x->left?x->left->left:x->left)) // case 1
								rotate_right(&x);
							else if (z == (x->left?x->left->right:x->left)) // case 3
							{
								rotate_left(&y);
								rotate_right(&x);
							}
						}
						else if (y == x->right)
						{
							if (z == (x->right?x->right->right:x->right)) // case 2
								rotate_left(&x);
							else if (z == (x->right?x->right->left:x->right)) // case 4
							{
								rotate_right(&y);
								rotate_left(&x);
							}
						}
					}
					p = p->parent;
				}
			}

			node* minimum(node* x)
			{
				while(x->left != NULL)
					x = x->left;
				return x;
			}

			bool erase(const value_type& val)
			{
				node *del = NULL;
				node *delp = NULL;
				node *cdd = NULL;
				node *cddp = NULL;
				node *tmp = NULL;

				if(_root == NULL)
					return false;
				tmp = _root;
				while (tmp)
				{
					if (val.first == tmp->el.first)
					{
						del = tmp;
						break;
					}
					if (_cmp(val, tmp->el))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (!del)
					return false;
				delp =del->parent;
				if (!del->right) // case1. no right node of del
					cdd = del->left;
				else if (!del->right->left) // case2. right node of del has no left child
				{
					cdd = del->right;
					cdd->left = del->left;
					del->left->parent = cdd;
				}
				else // case3
				{
					cddp = del;
					cdd = del->right;
					while (cdd->left)
					{
						cddp = cdd;
						cdd = cdd->left;
					}
					cddp->left = cdd->right;
					if (cdd->right)
						cdd->right->parent = cddp;

					cdd->left = del->left;
					if (del->left)
						del->left->parent = cdd;

					cdd->right = del->right;
					del->right->parent = cdd;
				}
				// make cdd as child of delp
				if (delp)
				{
					node **delpLR = (delp->left == del) ? &delp->left : &delp->right;
					*delpLR = cdd;
				}
				else
				{
					_root = cdd;
				}
				if (cdd) // if del is not leaf node
					cdd->parent = delp;
				delete del;
				_len--;
				return true;
			}

			void erase(iterator position)
			{
				node* z = position._node;
				if (z->left == NULL)
				{
					transplant(z, z->right);
					if (z->right != NULL)
						avl_delete_fixup(z->right);
					delete z;
					_len--;
				}
				else if (z->right == NULL)
				{
					transplant(z, z->left);
					if (z->left != NULL)
						avl_delete_fixup(z->left);
					delete z;
					_len--;
				}
				else
				{
					node* y = minimum(z->right);
					if (y->parent != z)
					{
						transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					if (y != NULL)
						avl_delete_fixup(y);
					delete z;
					_len--;
				}
				
			}


			node* getRoot() const
			{
				return this->_root;
			}

			void swap(AVLTree<E, Compare, AllowDuplicate>& x)
			{
				std::swap(x._root, _root);
				std::swap(x._cmp, _cmp);
				std::swap(x._len, _len);
			}

			void clear()
			{
				deep_free(_root);
				_len = 0;
			}

			template <typename EqualPredicate>
			iterator find(EqualPredicate pred, const value_type &v)
			{
				node* n = _root;
				while (n)
				{
					if (pred(n->el, v))
						return iterator(*this, n);
					if (_cmp(v, n->el))
						n = n->left;
					else
						n = n->right;
				}
				return end();
			}

			template <typename EqualPredicate>
			const_iterator find(EqualPredicate pred, const value_type& v) const
			{
				node* n = _root;
				while (n)
				{
					if (pred(n->el, v))
						return const_iterator(*this, n);
					if (_cmp(v, n->el))
						n = n->left;
					else
						n = n->right;
				}
				return end();
			}

			template <typename U, typename Cmp, bool ADup>
			friend class AVLTreeIterator;
	};
}

#endif