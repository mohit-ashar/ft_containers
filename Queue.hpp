#ifndef QUEUE_HPP
# define QUEUE_HPP
#include "List.hpp"

namespace ft
{
	template <typename T, typename Container = List<T> >
	class Queue: protected List<T>
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

			explicit Queue(const container_type &ctnr = container_type()): _c(ctnr)
			{
			}

			Queue(const Queue<T, Container> &other): _c(other._c)
			{
			}
			Queue &operator=(const Queue<T, Container> &other)
			{
				_c = other._c;
				return *this;
			}
			
			~Queue()
			{

			}

			bool empty() const
			{
				return _c.empty();
			}

			size_type size() const
			{
				return _c.size();
			}

			value_type &back()
			{
				return _c.back();
			}

			const value_type &back() const
			{
				return _c.back();
			}

            value_type &front()
			{
				return _c.front();
			}

			const value_type &front() const
			{
				return _c.front();
			}

			void push(const value_type &val)
			{
				_c.push_back(val);
			}

			void pop()
			{
				_c.pop_front();
			}
			
			template <typename T2, typename Container2>
			friend void swap(Queue<T2, Container2>& lhs, Queue<T2, Container2>& rhs);
			template <typename T2, typename Container2>
			friend bool operator==(const Queue<T2, Container2>& lhs, const Queue<T2, Container2>& rhs);
			template <typename T2, typename Container2>
			friend bool operator<(const Queue<T2, Container2>& lhs, const Queue<T2, Container2>& rhs);
		private:
			container_type _c;
	};
	template <typename T, typename Container>
	void swap(Queue<T, Container>& lhs, Queue<T, Container>& rhs)
	{
		ft::swap(lhs._c, rhs._c);
	}

	template <typename T, typename Container>
	bool operator==(const Queue<T, Container>& lhs, const Queue<T, Container>& rhs)
	{
		return lhs._c == rhs._c;
	}

	template <typename T, typename Container>
	bool operator!=(const Queue<T, Container>& lhs, const Queue<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<(const Queue<T, Container>& lhs, const Queue<T, Container>& rhs)
	{
		return lhs._c < rhs._c;
	}

	template <typename T, typename Container>
	bool operator<=(const Queue<T, Container>& lhs, const Queue<T, Container>& rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Container>
	bool operator>(const Queue<T, Container>& lhs, const Queue<T, Container>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator>=(const Queue<T, Container>& lhs, const Queue<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif