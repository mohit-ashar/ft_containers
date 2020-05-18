#include "Test.hpp"
#include <stack>

static void test_push_pop()
{
	ft::Stack<ConstrCounter> stack;
	std::stack<ConstrCounter> st;


	assert(stack.size() == 0);
	assert(stack.empty());
	//std
	assert(st.size() == 0);
	assert(st.empty());
	

	stack.push(ConstrCounter(0));
	assert(stack.size() == 1);
	assert(!stack.empty());
	assert(stack.top() == 0);
	//std
	st.push(ConstrCounter(0));
	assert(st.size() == 1);
	assert(!st.empty());
	assert(st.top() == 0);


	stack.push(ConstrCounter(1));
	assert(stack.size() == 2);
	assert(!stack.empty());
	assert(stack.top() == 1);
	//std
	st.push(ConstrCounter(1));
	assert(st.size() == 2);
	assert(!st.empty());
	assert(st.top() == 1);


	stack.push(ConstrCounter(2));
	assert(stack.size() == 3);
	assert(!stack.empty());
	assert(stack.top() == 2);
	//std
	st.push(ConstrCounter(2));
	assert(st.size() == 3);
	assert(!st.empty());
	assert(st.top() == 2);


	stack.push(ConstrCounter(3));
	assert(stack.size() == 4);
	assert(!stack.empty());
	assert(stack.top() == 3);
	//std
	st.push(ConstrCounter(3));
	assert(st.size() == 4);
	assert(!st.empty());
	assert(st.top() == 3);


	stack.push(ConstrCounter(4));
	assert(stack.size() == 5);
	assert(!stack.empty());
	assert(stack.top() == 4);
	//std
	st.push(ConstrCounter(4));
	assert(st.size() == 5);
	assert(!st.empty());
	assert(st.top() == 4);

	stack.pop();
	assert(stack.size() == 4);
	assert(!stack.empty());
	assert(stack.top() == 3);
	//std
	st.pop();
	assert(st.size() == 4);
	assert(!st.empty());
	assert(st.top() == 3);

	stack.pop();
	assert(stack.size() == 3);
	assert(!stack.empty());
	assert(stack.top() == 2);
	//std
	st.pop();
	assert(st.size() == 3);
	assert(!st.empty());
	assert(st.top() == 2);

	stack.pop();
	assert(stack.size() == 2);
	assert(!stack.empty());
	assert(stack.top() == 1);
	//std
	st.pop();
	assert(st.size() == 2);
	assert(!st.empty());
	assert(st.top() == 1);

	stack.pop();
	assert(stack.size() == 1);
	assert(!stack.empty());
	assert(stack.top() == 0);
	//std
	st.pop();
	assert(st.size() == 1);
	assert(!st.empty());
	assert(st.top() == 0);

	stack.pop();
	assert(stack.size() == 0);
	assert(stack.empty());
	//std
	st.pop();
	assert(st.size() == 0);
	assert(st.empty());
}

static void test_assign_copy()
{
	ft::Stack<ConstrCounter> stack;
	std::stack<ConstrCounter> st;

	stack.push(ConstrCounter(0));
	stack.push(ConstrCounter(1));
	stack.push(ConstrCounter(2));
	//std
	st.push(ConstrCounter(0));
	st.push(ConstrCounter(1));
	st.push(ConstrCounter(2));


	ft::Stack<ConstrCounter> stack2(stack);
	assert(stack2.size() == 3);
	assert(stack2.top() == 2);
	stack2.pop();
	assert(stack2.size() == 2);
	assert(stack2.top() == 1);
	stack2.pop();
	assert(stack2.size() == 1);
	assert(stack2.top() == 0);
	stack2.pop();
	assert(stack2.size() == 0);
	//std
	std::stack<ConstrCounter> st2(st);
	assert(st2.size() == 3);
	assert(st2.top() == 2);
	st2.pop();
	assert(st2.size() == 2);
	assert(st2.top() == 1);
	st2.pop();
	assert(st2.size() == 1);
	assert(st2.top() == 0);
	st2.pop();
	assert(st2.size() == 0);


	stack2.push(ConstrCounter(0));
	assert(stack2.size() == 1);
	stack2.push(ConstrCounter(1));
	assert(stack2.size() == 2);
	stack2.push(ConstrCounter(2));
	assert(stack2.size() == 3);
	//std
	st2.push(ConstrCounter(0));
	assert(st2.size() == 1);
	st2.push(ConstrCounter(1));
	assert(st2.size() == 2);
	st2.push(ConstrCounter(2));
	assert(st2.size() == 3);


	stack2.push(ConstrCounter(3));
	assert(stack.size() == 3);
	assert(stack2.size() == 4);
	//std
	st2.push(ConstrCounter(3));
	assert(st.size() == 3);
	assert(st2.size() == 4);


	ft::Stack<ConstrCounter> stack3;
	assert(stack3.size() == 0);
	//std
	std::stack<ConstrCounter> st3;
	assert(st3.size() == 0);


	stack3 = stack2;
	assert(stack.size() == 3);
	assert(stack2.size() == 4);
	assert(stack3.size() == 4);
	//std
	st3 = st2;
	assert(st.size() == 3);
	assert(st2.size() == 4);
	assert(st3.size() == 4);


	stack = stack3;
	assert(stack.size() == 4);
	assert(stack2.size() == 4);
	assert(stack3.size() == 4);
	//std
	st = st3;
	assert(st.size() == 4);
	assert(st2.size() == 4);
	assert(st3.size() == 4);


	assert(stack.size() == 4);
	assert(stack.top() == 3);
	stack.pop();
	assert(stack.size() == 3);
	assert(stack.top() == 2);
	stack.pop();
	assert(stack.size() == 2);
	assert(stack.top() == 1);
	stack.pop();
	assert(stack.size() == 1);
	assert(stack.top() == 0);
	stack.pop();
	assert(stack.size() == 0);
	//std
	assert(st.size() == 4);
	assert(st.top() == 3);
	st.pop();
	assert(st.size() == 3);
	assert(st.top() == 2);
	st.pop();
	assert(st.size() == 2);
	assert(st.top() == 1);
	st.pop();
	assert(st.size() == 1);
	assert(st.top() == 0);
	st.pop();
	assert(st.size() == 0);


	assert(stack2.size() == 4);
	assert(stack2.top() == 3);
	stack2.pop();
	assert(stack2.size() == 3);
	assert(stack2.top() == 2);
	stack2.pop();
	assert(stack2.size() == 2);
	assert(stack2.top() == 1);
	stack2.pop();
	assert(stack2.size() == 1);
	assert(stack2.top() == 0);
	stack2.pop();
	assert(stack2.size() == 0);
	//std
	assert(st2.size() == 4);
	assert(st2.top() == 3);
	st2.pop();
	assert(st2.size() == 3);
	assert(st2.top() == 2);
	st2.pop();
	assert(st2.size() == 2);
	assert(st2.top() == 1);
	st2.pop();
	assert(st2.size() == 1);
	assert(st2.top() == 0);
	st2.pop();
	assert(st2.size() == 0);

	assert(stack3.size() == 4);
	assert(stack3.top() == 3);
	stack3.pop();
	assert(stack3.size() == 3);
	assert(stack3.top() == 2);
	stack3.pop();
	assert(stack3.size() == 2);
	assert(stack3.top() == 1);
	stack3.pop();
	assert(stack3.size() == 1);
	assert(stack3.top() == 0);
	stack3.pop();
	assert(stack3.size() == 0);
	//std
	assert(st3.size() == 4);
	assert(st3.top() == 3);
	st3.pop();
	assert(st3.size() == 3);
	assert(st3.top() == 2);
	st3.pop();
	assert(st3.size() == 2);
	assert(st3.top() == 1);
	st3.pop();
	assert(st3.size() == 1);
	assert(st3.top() == 0);
	st3.pop();
	assert(st3.size() == 0);


}

static void test_swap()
{
	ft::Stack<ConstrCounter> stack;
    stack.push(5);
    stack.push(2);
    stack.push(3);
    stack.push(1);
    stack.push(4);
	//std
	std::stack<ConstrCounter> st;
    st.push(5);
    st.push(2);
    st.push(3);
    st.push(1);
    st.push(4);

	ft::Stack<ConstrCounter> stack2;
    stack2.push(3);
    stack2.push(2);
    stack2.push(1);
	//std
	std::stack<ConstrCounter> st2;
    st2.push(3);
    st2.push(2);
    st2.push(1);


	ft::swap(stack, stack2);
	assert(stack.size() == 3);
	assert(stack2.size() == 5);
	assert(stack.top() == 1);
	assert(stack2.top() == 4);
	//std
	std::swap(st, st2);
	assert(st.size() == 3);
	assert(st2.size() == 5);
	assert(st.top() == 1);
	assert(st2.top() == 4);


	ft::swap(stack2, stack);
	assert(stack.size() == 5);
	assert(stack2.size() == 3);
	assert(stack.top() == 4);
	assert(stack2.top() == 1);
	//std
	std::swap(st2, st);
	assert(st.size() == 5);
	assert(st2.size() == 3);
	assert(st.top() == 4);
	assert(st2.top() == 1);
}

static void test_cmp_eq()
{
	ft::Stack<ConstrCounter> stack;
    stack.push(5);
    stack.push(2);
    stack.push(3);
    stack.push(1);
    stack.push(4);
	//std
	std::stack<ConstrCounter> st;
    st.push(5);
    st.push(2);
    st.push(3);
    st.push(1);
    st.push(4);


    ft::Stack<ConstrCounter> stack2(stack);
	assert(stack == stack2);
	assert(stack >= stack2);
	assert(stack <= stack2);
	//std
	std::stack<ConstrCounter> st2(st);
	assert(st == st2);
	assert(st >= st2);
	assert(st <= st2);

	stack2.push(50);
	assert(stack != stack2);
	assert(stack < stack2);
	assert(stack <= stack2);
	assert(stack2 > stack);
	assert(stack2 >= stack);
	//std
	st2.push(50);
	assert(st != st2);
	assert(st < st2);
	assert(st <= st2);
	assert(st2 > st);
	assert(st2 >= st);

	stack.push(200);
	assert(stack != stack2);
	assert(stack > stack2);
	assert(stack >= stack2);
	assert(stack2 < stack);
	assert(stack2 <= stack);
	//std
	st.push(200);
	assert(st != st2);
	assert(st > st2);
	assert(st >= st2);
	assert(st2 < st);
	assert(st2 <= st);
}

void test_stack()
{
	test_one("push_pop", test_push_pop);
	test_one("assign_copy", test_assign_copy);
	test_one("swap", test_swap);
	test_one("cmp_eq", test_cmp_eq);
}