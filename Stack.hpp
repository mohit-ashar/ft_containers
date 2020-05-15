#ifndef STACK_HPP
# define STACK_HPP
#include "List.hpp"

namespace ft
{
	template <typename T>
	class Stack: protected List<T>
	{
		public:
			typedef T value_type;
			typedef list<T> container_type;
			typedef typename list<T>::size_type size_type;
	}
}

#endif