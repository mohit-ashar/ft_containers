#ifndef STACK_HPP
# define STACK_HPP
#include "List.hpp"

namespace ft
{
	template <typename T, typename Container = List<T> >
	class Stack: protected List<T>
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

			explicit Stack(const container_type &ctnr = container_type()): _c(ctnr)
			{
			}

			Stack(const Stack<T, Container> &other): _c(other._c)
			{
			}
			Stack &operator=(const Stack<T, Container> &other)
			{
				_c = other._c;
				return *this;
			}
			
			~Stack()
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

			value_type &top()
			{
				return _c.back();
			}

			const value_type &top() const
			{
				return _c.back();
			}

			void push(const value_type &val)
			{
				_c.push_back(val);
			}

			void pop()
			{
				_c.pop_back();
			}
			
			template <typename T2, typename Container2>
			friend void swap(Stack<T2, Container2>& lhs, Stack<T2, Container2>& rhs);
			template <typename T2, typename Container2>
			friend bool operator==(const Stack<T2, Container2>& lhs, const Stack<T2, Container2>& rhs);
			template <typename T2, typename Container2>
			friend bool operator<(const Stack<T2, Container2>& lhs, const Stack<T2, Container2>& rhs);
		private:
			container_type _c;
	};
	template <typename T, typename Container>
	void swap(Stack<T, Container>& lhs, Stack<T, Container>& rhs)
	{
		ft::swap(lhs._c, rhs._c);
	}

	template <typename T, typename Container>
	bool operator==(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return lhs._c == rhs._c;
	}

	template <typename T, typename Container>
	bool operator!=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator<(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return lhs._c < rhs._c;
	}

	template <typename T, typename Container>
	bool operator<=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T, typename Container>
	bool operator>(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator>=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif