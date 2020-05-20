#ifndef MAP_HPP
# define MAP_HPP

# include "Utility.hpp"
# include "AVLTree.hpp"

namespace ft
{


	struct classcomp {
		bool operator() (const char& lhs, const char& rhs) const
		{return lhs<rhs;}
	};


	template <class Key, class T, class Compare = ft::less<Key>>
	class Map
	{
		public:
				class value_compare;

		private:
				AVLTree<Pair<const Key, T>, value_compare, false> _tree;

				static int keys_eq_predicate(const Pair<const Key, T> &a, const Pair<const Key, T> &b)
				{
					return a.first == b.first;
				}

		public:
				typedef Key key_type;
				typedef T mapped_type;
				typedef Pair<const key_type, mapped_type> value_type;
				typedef Compare key_compare;
				typedef T& reference;
				typedef const T& const_reference;
				typedef T* pointer;
				typedef const T* const_pointer;
				typedef AVLTreeIterator<value_type, value_compare, false> iterator;
				typedef AVLTreeIterator<const value_type, value_compare, false> const_iterator;
				typedef ReverseIterator<iterator> reverse_iterator;
				typedef ReverseIterator<const_iterator>     const_reverse_iterator;
				typedef std::ptrdiff_t difference_type;
				typedef size_t size_type;
				typedef AVLTreeNode<Pair<const Key, T> > node;

		class value_compare
		{
			private:
					Compare _cmp;

					value_compare(Compare c):_cmp(c)
					{
					}

			public:
					typedef bool result_type;
					typedef Pair<const Key,T> first_argument_type;
					typedef Pair<const Key,T> second_argument_type;

					~value_compare()
					{
					}

					value_compare(const value_compare& o):_cmp(o._cmp)
					{
					}

					value_compare& operator=(const value_compare& o)
					{
						_cmp = o._cmp;
						return (*this);
					}

					bool operator()(const Pair<const Key, T>& x, const Pair<const Key, T>& y) const
					{
						return _cmp(x.first, y.first);
					}

					template <typename K, typename U, typename Cmp>
					friend class Map;
		};

		explicit Map(const key_compare& cmp = key_compare()):_tree(value_compare(cmp))
		{
		}
		
		template <typename InputIt>
		Map(InputIt first, InputIt last, const key_compare& cmp = key_compare()): _tree(first, last, value_compare(cmp))
		{
		}

		Map(const Map& o):_tree(o._tree)
		{
		}

		~Map()
		{
		}

		Map<Key, T, Compare> &operator=(const Map<Key, T, Compare>& o)
		{
			_tree = o._tree;
			return *this;
		}

		iterator begin()
		{
			return _tree.begin();
		}

		const_iterator begin() const
		{
			return _tree.begin();
		}
		
		iterator end()
		{
			return _tree.end();
		}

		const_iterator end() const
		{
			return _tree.end();
		}

		reverse_iterator rbegin()
		{
			return _tree.rbegin();
		}


		const_reverse_iterator rbegin() const
		{
			return _tree.rbegin();
		}

		reverse_iterator rend()
		{
			return _tree.rend();
		}

		const_reverse_iterator rend() const
		{
			return _tree.rend();
		}

		bool empty() const
		{
			return _tree.empty();
		}

		size_type size() const
		{
			return _tree.size();
		}

		size_type max_size() const
		{
			return _tree.max_size();
		}

		mapped_type& operator[](const key_type& k)
		{
			iterator it = find(k);
			if (it != end())
				return it->second;
			Pair<iterator, bool> res = insert(make_pair(k, mapped_type()));
			return res.first->second;
		}

		Pair<iterator,bool> insert(const value_type& val)
		{
			return _tree.insert(val);
		}

		iterator insert(iterator hint, const value_type& val)
		{
			return _tree.insert(hint, val).first;
		}

		template <typename InputIt>
		void insert(InputIt first, InputIt last)
		{
			_tree.insert(first, last);
		}

		void erase(iterator position)
		{
			_tree.erase(position);
		}

		size_type erase(const key_type& k)
		{
			_tree.erase(find(k));
			return _tree.size();
		}

	
		void erase(iterator first, iterator last)
		{
			iterator it = first;
			while (it != last)
			{
				iterator successor = ft::fwd(it, 1);
				erase(it);
				it = successor;
			}
		}

		void swap(Map<Key, T, Compare>& x)
		{
			std::swap(_tree, x._tree);
		}

		void clear()
		{
			_tree.clear();
		}

		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		}

		iterator find(const key_type& k)
		{
			return _tree.find(keys_eq_predicate, make_pair(k, mapped_type()));
		}
		
		const_iterator find(const key_type& k) const
		{
			return _tree.find(keys_eq_predicate, make_pair(k, mapped_type()));
		}

		size_type count(const key_type& k) const
		{
			node* tmp = _tree.getRoot();
			key_compare cmp = key_comp();
			while (tmp)
			{
				if (tmp->el.first == k)
					return (1);
				if (cmp(k, tmp->el.first))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return (0);
		}
		iterator lower_bound(const key_type& k)
		{
			node *tmp = _tree.getRoot();
			node *ptmp = NULL;
			key_compare cmp = key_comp();
			if (tmp)
			{
				while(tmp)
				{
					ptmp = tmp;
					if (tmp->el.first == k)
						return iterator(&_tree, tmp);
					if (cmp(k, tmp->el.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				while(ptmp)
				{
					if (!cmp(k, ptmp->el.first)) //k > el.first
						ptmp = ptmp->parent;
					else
						return (iterator(&_tree, ptmp));
				}
			}
			return (end());
		}
		const_iterator lower_bound(const key_type& k) const
		{
			node *tmp = _tree.getRoot();
			node *ptmp = NULL;
			key_compare cmp = key_comp();
			if (tmp)
			{
				while(tmp)
				{
					ptmp = tmp;
					if (tmp->el.first == k)
						return (const_iterator(&_tree, tmp));
					if (cmp(k, tmp->el.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				while(ptmp)
				{
					if (!cmp(k, ptmp->el.first)) //k > el.first
						ptmp = ptmp->parent;
					else
						return (const_iterator(&_tree, ptmp));
				}
			}
			return (end());
		}
		iterator upper_bound(const key_type& k)
		{
			node* tmp = _tree.getRoot();
			node* ptmp = NULL;
			key_compare cmp = key_comp();
			if (tmp)
			{
				while (tmp)
				{
					ptmp = tmp;
					if (cmp(k, tmp->el.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				while (ptmp)
				{
					if (!cmp(k, ptmp->el.first)) // k > el.first
						ptmp = ptmp->parent;
					else
						return iterator(&_tree, ptmp);
				}
			}
			return (end());
		}
		const_iterator upper_bound(const key_type& k) const
		{
			node* tmp = _tree.getRoot();
			node* ptmp = NULL;
			key_compare cmp = key_comp();
			if (tmp)
			{
				while (tmp)
				{
					ptmp = tmp;
					if (cmp(k, tmp->el.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				while (ptmp)
				{
					if (!cmp(k, ptmp->el.first)) // k > el.first
						ptmp = ptmp->parent;
					else
						return const_iterator(&_tree, ptmp);
				}
			}
			return (end());
		}

		Pair<iterator, iterator> equal_range(const key_type& k)
		{
			return make_pair(lower_bound(k), upper_bound(k));
		}
		Pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return make_pair(lower_bound(k), upper_bound(k));
		}
	};
}

#endif