#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>
# include "Utility.hpp"

namespace   ft
{
	template <typename T>
	struct ListNode
	{
		ListNode(ListNode<T> *prv_, ListNode<T> *nxt_, const T &node_):prv(prv_),nxt(nxt_), node(node_)
		{
		}
		ListNode<T> *prv;
		ListNode<T> *nxt;
		T			node;
	};

	template <typename T>
	class ListIterator
	{
		private:
			ListNode<T>* _prv;
			ListNode<T>* _nxt;

		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef BidirectionalIteratorTag iterator_category;

		ListIterator(ListNode<T>* prv, ListNode<T>* nxt):
		_prv(prv), _nxt(nxt)
		{
		}

		ListIterator(const ListIterator<T>& other):
		_prv(other._prv), _nxt(other._nxt)
		{
		}

		~ListIterator()
		{
		}

		ListIterator<T>& operator=(const ListIterator<T> &other)
		{
			_prv = other._prv;
			_nxt = other._nxt;
			return *this;
		}

		ListIterator<T>& operator++()
		{
			_prv = _nxt;
			_nxt = _nxt->nxt;
			return *this;
		}

		ListIterator<T> operator++(int)
		{
			ListIterator<T> cpy = *this;
				_prv = _nxt;
				_nxt = _nxt->nxt;
				return cpy;
		}

		ListIterator<T>& operator--()
		{
			_nxt = _prv;
			_prv = _prv->prv;
			return *this;
		}

		ListIterator<T> operator--(int)
		{
			ListIterator<T> cpy = *this;
			_nxt = _prv;
			_prv = _prv->prv;
			return cpy;
		}

		T& operator*()
		{
			return _nxt->node;
		}

		T* operator->()
		{
			return &_nxt->node;
		}

		template <typename E>
		friend class List;
		template <typename E>
		friend bool operator==(const ListIterator<E>& lhs, const ListIterator<E>& rhs);
		template <typename E>
		friend bool operator!=(const ListIterator<E>& lhs, const ListIterator<E>& rhs);
	};

	template <typename T>
	bool operator==(const ListIterator<T>& lhs, const ListIterator<T>& rhs)
	{
		return lhs._prv == rhs._prv && lhs._nxt == rhs._nxt;
	}

	template <typename T>
	bool operator!=(const ListIterator<T>& lhs, const ListIterator<T>& rhs)
	{
		return lhs._prv != rhs._prv || lhs._nxt != rhs._nxt;
	}
	

	template <class T>
	class   List
	{
		private:
			ListNode<T>*	_head;
			ListNode<T>*	_tail;
			size_t			_len;
		
		public:
			typedef T value_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef T* pointer;
			typedef const T* const_pointer;
			typedef ListIterator<T> iterator;
			typedef ListIterator<const T> const_iterator;
			typedef ReverseIterator<iterator> reverse_iterator;
			typedef ReverseIterator<const iterator> const_reverse_iterator;
			typedef std::ptrdiff_t difference_type;
			typedef size_t size_type;

			explicit List():
			_head(NULL), _tail(NULL), _len(0)
			{
			}

			explicit List(size_type n, const value_type& val = value_type()):
				_head(NULL), _tail(NULL), _len(0)
			{
				insert(begin(), n, val);
			}

			template <typename InputIt>
			explicit List(InputIt first, InputIt last):
				_head(NULL), _tail(NULL), _len(0)
			{
				insert(begin(), first, last);
			}

			List(const List& other):
				_head(NULL), _tail(NULL), _len(0)
			{
				insert(begin(), other.begin(), other.end());
			}

			void clear()
			{
				erase(begin(), end());
			}

			List &operator=(const List<T>& other)
			{
				clear();
				insert(begin(), other.begin(), other.end());
				return *this;
			}

			~List()
			{
				erase(begin(), end());
			}

			//ITERATORS
			iterator begin()
			{
				return iterator(NULL, _head);
			}

			const_iterator begin() const
			{
				return const_iterator(NULL, (ListNode<const T>*)_head);
			}

			iterator end()
			{
				return iterator(_tail, NULL);
			}

			const_iterator end() const
			{
				return const_iterator((ListNode<const T>*)_tail, NULL);
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

			//CAPACITY
			bool empty() const
			{
				return _len == 0;
			}

			size_type size() const
			{
				return _len;
			}
		
			size_t max_size() const;

			//ELEMENT ACCESS
			reference front()
			{
				return _head->node;
			}

			const_reference front() const
			{
				return _head->node;
			}

			reference back()
			{
				return _tail->node;
			}

			const_reference back() const
			{
				return _tail->node;
			}

			//MODIFIERS
			template <typename InputIt>
			void assign(InputIt first, InputIt last)
			{
				clear();
				insert(begin(), first, last);
			}

			void assign(size_type n, const value_type& val)
			{
				clear();
				insert(begin(), n, val);
			}

			void push_front(const value_type& val)
			{
				insert(begin(), val);
			}

			void pop_front()
			{
				erase(begin());
			}

			void push_back(const value_type& val)
			{
				insert(end(), val);
			}

			void pop_back()
			{
				iterator ite = end();
				--ite;
				erase(ite);
			}

			iterator	insert(iterator position, const value_type& val)
			{
				insert(position, 1, val);
				
				ListNode<T>* nodeLeft = position._prv;
				ListNode<T>* nodeRight = nodeLeft ? nodeLeft->nxt : _head;
				return iterator(nodeLeft, nodeRight);
			}

			void		insert(iterator position, size_type n, const value_type& val)
			{
				ListNode<T>* nodeLeft = position._prv;
				ListNode<T>* nodeRight = position._nxt;

				ListNode<T>* nn = nodeLeft;
				for (size_t i = 0; i < n; i++)
				{
					ListNode<T>* tmp = new ListNode<T>(nn, NULL, val);
					if (nn)
						nn->nxt = tmp;
					else
						_head = tmp;
					_len++;
					nn = tmp;
				}
				if (nodeRight)
				{
					nodeRight->prv = nn;
					nn->nxt = nodeRight;
				}
				else
					_tail = nn;
			}

			template <typename InputIt>
			void insert(iterator position, InputIt first, InputIt last)
			{
				ListNode<T>* nodeLeft = position._prv;
				ListNode<T>* nodeRight = position._nxt;

				ListNode<T>* nn = nodeLeft;
				for (InputIt ite = first; ite != last; ++ite)
				{
					ListNode<T>* tmp = new ListNode<T>(nn, NULL, *ite);
					if (nn)
						nn->nxt = tmp;
					else
						_head = tmp;
					_len++;
					nn = tmp;
				}

				if (nodeRight)
				{
					nodeRight->prv = nn;
					nn->nxt = nodeRight;
				}
				else
					_tail = nn;
			}

			iterator erase(iterator first, iterator last)
			{
				ListNode<T>* nodeLeft = first._prv;
				ListNode<T>* nodeRight = last._nxt;

				iterator ite = first;
				while(ite != last)
				{
					iterator tmp(ite);
					_len--;
					ite = ++ite;
					delete tmp._nxt;
				}

				if (nodeLeft)
					nodeLeft->nxt = nodeRight;
				else
					_head = nodeRight;
				if (nodeRight)
					nodeRight->prv = nodeLeft;
				else
					_tail = nodeLeft;

				last._prv = first._prv;
				return last;
			}

			iterator erase(iterator position)
			{
				iterator nxt = iterator(position);
				nxt++;
				return erase(position, nxt);
			}

			void swap(List &x)
			{
				std::swap(_head, x._head);
				std::swap(_tail, x._tail);
				std::swap(_len, x._len);
			}

			void resize(size_t n, value_type val = value_type())
			{
				if (n >= _len)
					insert(end(), n - _len, val);
				else
				{
					iterator ite = begin();
					for (size_t i = 0; i < n; i++)
						++ite;
					erase(ite, end());
				}
			}

			//OPERATIONS
			void splice(iterator position, List& x)
			{
				insert(position, x.begin(), x.end());
				x.clear();
			}

			void splice(iterator position, List& x, iterator i)
			{
				insert(position, *i);
				x.erase(i);
			}

			void splice(iterator position, List& x, iterator first, iterator last)
			{
				insert(position, first, last);
				x.erase(first, last);
			}

			void remove(const value_type& val)
			{
				for(iterator it = begin(); it != end();)
				{
					if(*it == val)
						it = erase(it);
					else 
						it++;
				}
			}

			template <typename Predicate>
			void remove_if(Predicate pred)
			{
				for(iterator it = begin(); it != end();)
				{
					if(pred(*it))
						it = erase(it);
					else 
						it++;
				}
			}

			void unique()
			{
				iterator start = begin();
				start++;
				for (iterator it = start; it != end();)
				{
					iterator tmp = it;
					tmp--;
					if (*tmp == *it)
						it = erase(it);
					else
						it++;
				}
			}

			template <typename BinaryPredicate>
			void unique(BinaryPredicate binary_pred)
			{
				iterator start = begin();
				start++;
				for (iterator it = start; it != end();)
				{
					iterator tmp = it;
					--tmp;
					if (binary_pred(*tmp, *it))
						it = erase(it);
					else
						++it;
				}
			}

			void merge(List& x)
			{
				iterator beg = x.begin();
				iterator end = x.end();
				ft::List<T> newList;
				while (beg != end)
				{
					push_back(*beg);
					beg++;
				}
				this->sort();
			}

			template <typename Compare>
			void merge(List& x, Compare comp)
			{
				iterator beg = x.begin();
				iterator end = x.end();
				ft::List<T> newList;
				while (beg != end)
				{
					push_back(*beg);
					beg++;
				}
				this->sort(comp);
			}
			void sort()
			{
				iterator it = begin();
				iterator tmp(it);
				while (it != end())
				{
					tmp = it;
					it++;
					if (it == end())
						break;
					if (*tmp > *it)
					{
						std::swap(*tmp, *it);
						it = begin();
					}
				}
			}
			template <typename Compare>
			void sort(Compare comp)
			{
				iterator it = begin();
				iterator tmp(it);
				while (it != end())
				{
					tmp = it;
					it++;
					if (it == end())
						break;
					if (comp(*it, *tmp))
					{
						std::swap(*tmp, *it);
						it = begin();
					}
				}
			}
			
			void reverse()
			{
				iterator beg = this->begin();
				iterator end = this->end();
				end--; 

				for (unsigned int i = 0; i < this->size() / 2; i++)
				{
					std::swap(*beg, *end);
					beg++;
					end--;
				}
			}

			template <typename E>
			friend class ListIterator;

	};

	template <typename T>
	bool operator==(const List<T>& lhs, const List<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		ListIterator<const T> ite1 = lhs.begin();
		ListIterator<const T> ite2 = rhs.begin();
		while (ite1 != lhs.end() && ite2 != rhs.end())
		{
			if (*ite1 != *ite2)
				return false;

			++ite1;
			++ite2;
		}
		return true;
	}

	template <typename T>
	bool operator!=(const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const List<T>& lhs, const List<T>& rhs)
	{
		ListIterator<const T> ite1 = lhs.begin();
		ListIterator<const T> ite2 = rhs.begin();
		while (ite1 != lhs.end() && ite2 != rhs.end())
		{
			if (*ite1 != *ite2)
				return *ite1 < *ite2;

			++ite1;
			++ite2;
		}
		
		if (lhs.size() == rhs.size())
            return false; // lhs == rhs at that point

        return lhs.size() < rhs.size(); // lhs < rhs if lhs is prefix of rhs

	}

	template <typename T>
	bool operator<=(const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T>
	bool operator>(const List<T>& lhs, const List<T>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator>=(const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	void swap(List<T>& x, List<T>& y)
	{
		x.swap(y);
	}
}

#endif
