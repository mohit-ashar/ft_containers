
#include "Test.hpp"

template <typename T>
static ft::ListIterator<T> get_n_fwd(ft::List<T>& lst, size_t index)
{
	size_t i = 0;
	for (ft::ListIterator<T> ite = lst.begin();
			ite != lst.end(); ++ite)
		if (i++ == index)
			return ite;
	std::stringstream ss;
	ss << "Index " << index << " is out of bound!";
	throw std::out_of_range(ss.str());
}

template <typename T>
static typename ft::List<T>::reverse_iterator get_n_bwd(
	ft::List<T>& lst, size_t index)
{
	size_t i = lst.size() - 1;
	for (typename ft::List<T>::reverse_iterator ite = lst.rbegin();
			ite != lst.rend(); ++ite)
		if (i-- == index)
			return ite;
	std::stringstream ss;
	ss << "Index " << index << " is out of bound!";
	throw std::out_of_range(ss.str());
}

static void test_pushfront()
{
	ft::List<ConstrCounter> lst;
	assert(lst.size() == 0);

	lst.push_front(ConstrCounter(0));
	assert(lst.size() == 1);
	assert(lst.front().val == 0);

	lst.push_front(ConstrCounter(1));
	assert(lst.size() == 2);
	assert(lst.front().val == 1);

	lst.push_front(ConstrCounter(8000));
	assert(lst.size() == 3);
	assert(lst.front().val == 8000);

	lst.push_front(ConstrCounter(33));
	assert(lst.size() == 4);
	assert(lst.front().val == 33);
}

static void test_pushback()
{
	ft::List<ConstrCounter> lst;
	assert(lst.size() == 0);

	lst.push_back(ConstrCounter(0));
	assert(lst.size() == 1);
	assert(lst.back().val == 0);

	lst.push_back(ConstrCounter(1));
	assert(lst.size() == 2);
	assert(lst.back().val == 1);

	lst.push_back(ConstrCounter(8000));
	assert(lst.size() == 3);
	assert(lst.back().val == 8000);

	lst.push_back(ConstrCounter(33));
	assert(lst.size() == 4);
	assert(lst.back().val == 33);
}

static void test_assign()
{
	ft::List<ConstrCounter> lst;
	assert(lst.size() == 0);

	lst.assign(0, ConstrCounter(66));
	assert(lst.size() == 0);

	lst.assign(10, ConstrCounter(5));
	assert(lst.size() == 10);
	assert(get_n_fwd(lst, 2)->val == 5);
	assert(get_n_bwd(lst, 9)->val == 5);

	lst.assign(15, ConstrCounter(120));
	assert(lst.size() == 15);
	assert(get_n_fwd(lst, 0)->val == 120);
	assert(get_n_bwd(lst, 6)->val == 120);

	lst.assign(5, ConstrCounter(6));
	assert(lst.size() == 5);
	assert(get_n_fwd(lst, 2)->val == 6);
	assert(get_n_bwd(lst, 3)->val == 6);

	lst.assign(50, ConstrCounter(9000));
	assert(lst.size() == 50);
	assert(get_n_fwd(lst, 26)->val == 9000);
	assert(get_n_bwd(lst, 49)->val == 9000);
}

static void test_assign_iter()
{
	ft::List<ConstrCounter> lst;
	assert(lst.size() == 0);

	{
		ConstrCounter array[0] = {};

		lst.assign(array, array);
		assert(lst.size() == 0);
	}
	{
		ConstrCounter array[5] = { 0, 1, 2, 3, 4 };

		lst.assign(array, array + 5);
		assert(lst.size() == 5);
		assert(get_n_fwd(lst, 0)->val == 0);
		assert(get_n_bwd(lst, 1)->val == 1);
		assert(get_n_fwd(lst, 2)->val == 2);
		assert(get_n_bwd(lst, 3)->val == 3);
		assert(get_n_fwd(lst, 4)->val == 4);
	}
	{
		ConstrCounter array[2] = { 42, 43 };

		lst.assign(array, array + 2);
		assert(lst.size() == 2);
		assert(get_n_fwd(lst, 0)->val == 42);
		assert(get_n_fwd(lst, 1)->val == 43);
	}
}

static void test_constr()
{
	{
		ft::List<ConstrCounter> lst(0, ConstrCounter(5));
		assert(lst.size() == 0);
	}
	{
		ft::List<ConstrCounter> lst(10, ConstrCounter(5));
		assert(lst.size() == 10);
		assert(get_n_fwd(lst, 5)->val == 5);
		assert(get_n_bwd(lst, 9)->val == 5);
	}
	{
		ft::List<ConstrCounter> lst(15, ConstrCounter(120));
		assert(lst.size() == 15);
		assert(get_n_fwd(lst, 0)->val == 120);
		assert(get_n_bwd(lst, 6)->val == 120);
	}
	{
		ft::List<ConstrCounter> lst(5, ConstrCounter(6));
		assert(lst.size() == 5);
		assert(get_n_fwd(lst, 2)->val == 6);
		assert(get_n_bwd(lst, 3)->val == 6);
	}
	{
		ft::List<ConstrCounter> lst(50, ConstrCounter(9000));
		assert(lst.size() == 50);
		assert(get_n_fwd(lst, 26)->val == 9000);
		assert(get_n_bwd(lst, 43)->val == 9000);
	}
}

static void test_constr_iter()
{
	{
		ConstrCounter array[0] = {};

		ft::List<ConstrCounter> lst(array, array);
		assert(lst.size() == 0);
	}
	{
		ConstrCounter array[5] = { 0, 1, 2, 3, 4 };

		ft::List<ConstrCounter> lst(array, array + 5);
		assert(lst.size() == 5);
		assert(get_n_fwd(lst, 0)->val == 0);
		assert(get_n_bwd(lst, 1)->val == 1);
		assert(get_n_fwd(lst, 2)->val == 2);
		assert(get_n_bwd(lst, 3)->val == 3);
		assert(get_n_fwd(lst, 4)->val == 4);
	}
	{
		ConstrCounter array[2] = { 42, 43 };

		ft::List<ConstrCounter> lst(array, array + 2);
		assert(lst.size() == 2);
		assert(get_n_fwd(lst, 0)->val == 42);
		assert(get_n_fwd(lst, 1)->val == 43);
	}
}

static void test_assign_copy()
{
	ft::List<ConstrCounter> lst;
	lst.push_back(ConstrCounter(0));
	lst.push_back(ConstrCounter(1));
	lst.push_back(ConstrCounter(2));

	ft::List<ConstrCounter> lst2(lst);
	assert(lst2.size() == 3);
	assert(get_n_fwd(lst2, 0)->val == 0);
	assert(get_n_bwd(lst2, 1)->val == 1);
	assert(get_n_fwd(lst2, 2)->val == 2);

	lst2.push_back(ConstrCounter(3));
	assert(lst.size() == 3);
	assert(lst2.size() == 4);

	ft::List<ConstrCounter> lst3;
	assert(lst3.size() == 0);

	lst3 = lst2;
	assert(lst.size() == 3);
	assert(lst2.size() == 4);
	assert(lst3.size() == 4);

	lst = lst3;
	assert(lst.size() == 4);
	assert(lst2.size() == 4);
	assert(lst3.size() == 4);

	assert(get_n_fwd(lst, 0)->val == 0);
	assert(get_n_bwd(lst, 1)->val == 1);
	assert(get_n_fwd(lst, 2)->val == 2);
	assert(get_n_bwd(lst, 3)->val == 3);
	assert(get_n_fwd(lst2, 0)->val == 0);
	assert(get_n_bwd(lst2, 1)->val == 1);
	assert(get_n_fwd(lst2, 2)->val == 2);
	assert(get_n_bwd(lst2, 3)->val == 3);
	assert(get_n_fwd(lst3, 0)->val == 0);
	assert(get_n_bwd(lst3, 1)->val == 1);
	assert(get_n_fwd(lst3, 2)->val == 2);
	assert(get_n_bwd(lst3, 3)->val == 3);
}

static void test_capacity()
{
	ft::List<ConstrCounter> lst;
	assert(lst.empty());
	assert(lst.size() == 0);

	lst.push_back(ConstrCounter(0));
	assert(lst.front().val == 0);
	assert(lst.back().val == 0);
	assert(!lst.empty());
	assert(lst.size() == 1);

	lst.push_back(ConstrCounter(1));
	assert(lst.front().val == 0);
	assert(lst.back().val == 1);
	assert(!lst.empty());
	assert(lst.size() == 2);

	lst.push_back(ConstrCounter(2));
	assert(lst.front().val == 0);
	assert(lst.back().val == 2);
	assert(!lst.empty());
	assert(lst.size() == 3);

	lst.clear();
	assert(lst.size() == 0);
	assert(lst.empty());
}

static void test_iterator()
{
	ft::List<ConstrCounter> lst;
	assert(lst.size() == 0);
	assert(lst.begin() == lst.end());

	lst.push_back(ConstrCounter(0));
	assert(lst.size() == 1);
	{
		ft::ListIterator<ConstrCounter> ite = lst.begin();
		++ite;
		assert(ite == lst.end());
	}

	lst.push_back(ConstrCounter(1));
	assert(lst.size() == 2);
	{
		ft::ListIterator<ConstrCounter> ite = lst.begin();
		++ite; ++ite;
		assert(ite == lst.end());
	}

	lst.push_back(ConstrCounter(2));
	assert(lst.size() == 3);
	{
		ft::ListIterator<ConstrCounter> ite = lst.begin();
		++ite; ++ite; ++ite;
		assert(ite == lst.end());
	}
	{
		ft::ListIterator<ConstrCounter> ite = lst.end();
		--ite; --ite; --ite;
		assert(ite == lst.begin());
	}

	ft::ListIterator<ConstrCounter> ite = lst.begin();
	assert((*ite).val == 0);
	assert(ite->val == 0);
	assert(ite++ == lst.begin());
	assert((*ite).val == 1);
	assert(ite->val == 1);
	{
		ft::ListIterator<ConstrCounter> ite2 = lst.begin();
		++ite2; ++ite2;
		assert(++ite == ite2);
	}
	assert((*ite).val == 2);
	assert(ite->val == 2);
	assert(++ite == lst.end());
	assert(ite-- == lst.end());
	assert(ite++ != lst.end());
	assert(ite == lst.end());
	{
		ft::ListIterator<ConstrCounter> ite2 = lst.end();
		--ite2;
		assert(--ite == ite2);
	}
	assert(++ite == lst.end());
	assert((--ite)->val == 2);
	--ite;
	assert(ite->val == 1);
	assert(--ite == lst.begin());
	assert(ite->val == 0);
}

static void test_reverse_iterator()
{
	ft::List<ConstrCounter> lst;
	lst.push_back(ConstrCounter(0));
	lst.push_back(ConstrCounter(1));
	lst.push_back(ConstrCounter(2));
	
	ft::List<ConstrCounter>::reverse_iterator ite =
		lst.rbegin();
	assert(ite->val == 2);
	++ite;
	assert(ite->val == 1);
	++ite;
	assert(ite->val == 0);
	++ite;
	assert(ite == lst.rend());
}

static void test_insert_one()
{
	ft::List<ConstrCounter> lst;

	assert(lst.insert(lst.begin(), ConstrCounter(5))
		== lst.begin());
	assert(lst.size() == 1);
	assert(get_n_bwd(lst, 0)->val == 5);

	{
		ft::ListIterator<ConstrCounter> ite = lst.begin();
		++ite;
		ft::ListIterator<ConstrCounter> ret =
			lst.insert(ite, ConstrCounter(5));
		ft::ListIterator<ConstrCounter> exp = lst.begin();
		++exp;
		assert(ret == exp);
		assert(lst.size() == 2);
		assert(get_n_fwd(lst, 1)->val == 5);
	}
}

static void test_insert()
{
	ft::List<ConstrCounter> lst;
	assert(lst.size() == 0);

	lst.insert(lst.begin(), 0, ConstrCounter(66));
	assert(lst.size() == 0);

	lst.insert(lst.begin(), 10, ConstrCounter(120));
	assert(lst.size() == 10);
	assert(get_n_bwd(lst, 2)->val == 120);
	assert(get_n_fwd(lst, 9)->val == 120);

	ft::ListIterator<ConstrCounter> ite = lst.begin();
	++ite; ++ite; ++ite;
	lst.insert(ite, 2, ConstrCounter(33));
	assert(lst.size() == 12);
	assert(get_n_bwd(lst, 3)->val == 33);
	assert(get_n_fwd(lst, 6)->val == 120);
}

static void test_insert_iter()
{
	ft::List<ConstrCounter> lst;
	assert(lst.size() == 0);

	{
		ConstrCounter array[5] = { 0, 1, 2, 3, 4 };

		lst.insert(lst.begin(), array, array + 5);
		assert(lst.size() == 5);
		assert(get_n_fwd(lst, 0)->val == 0);
		assert(get_n_bwd(lst, 1)->val == 1);
		assert(get_n_fwd(lst, 2)->val == 2);
		assert(get_n_bwd(lst, 3)->val == 3);
		assert(get_n_fwd(lst, 4)->val == 4);
	}
	{
		ConstrCounter array[0] = {};
		ft::ListIterator<ConstrCounter> ite = lst.begin();
		++ite; ++ite;

		lst.insert(ite, array, array);
		assert(lst.size() == 5);
	}
	{
		ConstrCounter array[2] = { 42, 43 };
		ft::ListIterator<ConstrCounter> ite = lst.begin();
		++ite; ++ite;

		lst.insert(ite, array, array + 2);
		assert(lst.size() == 7);
		assert(get_n_fwd(lst, 0)->val == 0);
		assert(get_n_bwd(lst, 1)->val == 1);
		assert(get_n_fwd(lst, 2)->val == 42);
		assert(get_n_bwd(lst, 3)->val == 43);
		assert(get_n_fwd(lst, 4)->val == 2);
		assert(get_n_bwd(lst, 5)->val == 3);
		assert(get_n_fwd(lst, 6)->val == 4);
	}
}

static void test_erase()
{
	ft::List<ConstrCounter> lst;
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	lst.insert(lst.begin(), array, array + 5);

	assert(lst.erase(lst.begin()) == lst.begin());
	assert(lst.size() == 4);
	assert(get_n_fwd(lst, 0)->val == 1);

	ft::ListIterator<ConstrCounter> ite = lst.begin();
	++ite; ++ite;
	ft::ListIterator<ConstrCounter> ret = lst.erase(ite);
	ft::ListIterator<ConstrCounter> exp = lst.begin();
	++exp; ++exp;
	assert(ret == exp);
	assert(lst.size() == 3);
	assert(get_n_fwd(lst, 2)->val == 4);
}

static void test_erase_range()
{
	ft::List<ConstrCounter> lst;
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	lst.insert(lst.begin(), array, array + 5);

	ft::ListIterator<ConstrCounter> ite1 = lst.begin();
	++ite1;
	ft::ListIterator<ConstrCounter> ite2 = lst.end();
	--ite2;
	lst.erase(ite1, ite2);
	assert(lst.size() == 2);
	assert(get_n_bwd(lst, 0)->val == 0);
	assert(get_n_fwd(lst, 1)->val == 4);

	lst.erase(lst.begin(), lst.begin());
	assert(lst.size() == 2);
	assert(get_n_bwd(lst, 0)->val == 0);
	assert(get_n_fwd(lst, 1)->val == 4);
}

static void test_pop_back()
{
	ft::List<ConstrCounter> lst;
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	lst.insert(lst.begin(), array, array + 5);

	assert(lst.back() == 4);
	assert(lst.size() == 5);
	lst.pop_back();
	assert(lst.back() == 3);
	assert(lst.size() == 4);
	lst.pop_back();
	assert(lst.back() == 2);
	assert(lst.size() == 3);
	lst.pop_back();
	assert(lst.back() == 1);
	assert(lst.size() == 2);
	lst.pop_back();
	assert(lst.back() == 0);
	assert(lst.size() == 1);
	lst.pop_back();
	assert(lst.size() == 0);
}

static void test_pop_front()
{
	ft::List<ConstrCounter> lst;
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	lst.insert(lst.begin(), array, array + 5);

	assert(lst.front() == 0);
	assert(lst.size() == 5);
	lst.pop_front();
	assert(lst.front() == 1);
	assert(lst.size() == 4);
	lst.pop_front();
	assert(lst.front() == 2);
	assert(lst.size() == 3);
	lst.pop_front();
	assert(lst.front() == 3);
	assert(lst.size() == 2);
	lst.pop_front();
	assert(lst.front() == 4);
	assert(lst.size() == 1);
	lst.pop_front();
	assert(lst.size() == 0);
}

static void test_resize()
{
	ft::List<ConstrCounter> lst;

	lst.resize(3, ConstrCounter(0));
	assert(lst.size() == 3);
	assert(get_n_bwd(lst, 0)->val == 0);
	assert(get_n_fwd(lst, 1)->val == 0);
	assert(get_n_bwd(lst, 2)->val == 0);

	lst.resize(2, ConstrCounter(5));
	assert(lst.size() == 2);
	assert(get_n_bwd(lst, 0)->val == 0);
	assert(get_n_fwd(lst, 1)->val == 0);

	lst.resize(5, ConstrCounter(99));
	assert(lst.size() == 5);
	assert(get_n_bwd(lst, 0)->val == 0);
	assert(get_n_fwd(lst, 1)->val == 0);
	assert(get_n_bwd(lst, 2)->val == 99);
	assert(get_n_fwd(lst, 3)->val == 99);
	assert(get_n_bwd(lst, 4)->val == 99);
}

static void test_swap()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ft::List<ConstrCounter> lst(array, array + 5);

	ConstrCounter array2[3] = { 2, 3, 1 };
	ft::List<ConstrCounter> lst2(array2, array2 + 3);

	lst.swap(lst2);
	assert(lst.size() == 3);
	assert(lst2.size() == 5);
	assert(get_n_fwd(lst, 0)->val == 2);
	assert(get_n_bwd(lst2, 0)->val == 0);

	ft::swap(lst2, lst);
	assert(lst.size() == 5);
	assert(lst2.size() == 3);
	assert(get_n_fwd(lst, 0)->val == 0);
	assert(get_n_bwd(lst2, 0)->val == 2);
}

static void test_cmp_eq()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ft::List<ConstrCounter> lst(array, array + 5);
	ft::List<ConstrCounter> lst2(lst);

	assert(lst == lst2);
	assert(lst >= lst2);
	assert(lst <= lst2);

	lst2.push_back(50);
	assert(lst != lst2);
	assert(lst < lst2);
	assert(lst <= lst2);
	assert(lst2 > lst);
	assert(lst2 >= lst);

	lst.push_back(200);
	assert(lst != lst2);
	assert(lst > lst2);
	assert(lst >= lst2);
	assert(lst2 < lst);
	assert(lst2 <= lst);
}

static void test_splice()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ConstrCounter array2[5] = { 10, 11, 12, 13, 14 };

	ft::List<ConstrCounter> lst(array, array + 5);
	ft::List<ConstrCounter> lst2(array2, array2 + 5);

	ft::ListIterator<ConstrCounter> ite1 = lst.begin();
	++ite1;
	lst.splice(ite1, lst2);

	assert(lst.size() == 10);
	assert(lst2.size() == 0);
	assert(lst2.empty());

	assert(get_n_bwd(lst, 0)->val == 0);
	assert(get_n_fwd(lst, 1)->val == 10);
	assert(get_n_bwd(lst, 2)->val == 11);
	assert(get_n_fwd(lst, 3)->val == 12);
	assert(get_n_bwd(lst, 4)->val == 13);
	assert(get_n_bwd(lst, 5)->val == 14);
	assert(get_n_bwd(lst, 6)->val == 1);
	assert(get_n_bwd(lst, 7)->val == 2);
	assert(get_n_bwd(lst, 8)->val == 3);
	assert(get_n_bwd(lst, 9)->val == 4);
}

static void test_splice_iter()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ft::List<ConstrCounter> lst(array, array + 5);
	ft::List<ConstrCounter> lst2(0, ConstrCounter(5));
	
	
	
	ft::ListIterator<ConstrCounter> ite1 = lst.begin();
	++ite1; ++ite1;
	
	lst2.splice (lst2.begin(),lst, ite1);
	assert(lst2.size() == 1);
	assert(get_n_bwd(lst2, 0)->val == 2);
	assert(lst.size() == 4);
}

static void test_splice_iter_first_last()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ConstrCounter array2[5] = { 100, 200, 300, 400, 500 };

	ft::List<ConstrCounter> lst(array, array + 5);
	ft::List<ConstrCounter> lst2(array2, array2 + 5);

	ft::ListIterator<ConstrCounter> ite1 = lst.begin();
	++ite1;
	lst2.splice(lst2.begin(), lst, ite1, lst.end());
	assert(lst2.size() == 9);
	assert(get_n_bwd(lst2, 0)->val == 1);
	assert(get_n_fwd(lst2, 1)->val == 2);
	assert(get_n_bwd(lst2, 2)->val == 3);
	assert(get_n_fwd(lst2, 3)->val == 4);
	assert(get_n_bwd(lst2, 4)->val == 100);
	assert(get_n_bwd(lst2, 5)->val == 200);
	assert(get_n_bwd(lst2, 6)->val == 300);
	assert(get_n_bwd(lst2, 7)->val == 400);
	assert(get_n_bwd(lst2, 8)->val == 500);
}

static void test_remove()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ft::List<ConstrCounter> lst(array, array + 5);
	lst.remove(2);

	assert(lst.size() == 4);
	assert(get_n_bwd(lst, 0)->val == 0);
	assert(get_n_fwd(lst, 1)->val == 1);
	assert(get_n_bwd(lst, 2)->val == 3);
	assert(get_n_fwd(lst, 3)->val == 4);
	lst.remove(0);
	assert(lst.size() == 3);
	assert(get_n_bwd(lst, 0)->val == 1);
	assert(get_n_fwd(lst, 1)->val == 3);
	assert(get_n_bwd(lst, 2)->val == 4);
	
}

static bool	is_positive(int x)
{
	return (x >= 0);
}

static void test_remove_if()
{
	int array[5] = { 0, -1, -2, 3, 4 };
	ft::List<int> lst(array, array + 5);
	lst.remove_if(is_positive);

	assert(lst.size() == 2);
	assert(*get_n_bwd(lst, 0) == -1);
	assert(*get_n_fwd(lst, 1) == -2);
}

static void test_unique()
{
	ConstrCounter array[5] = { 1, 1, 1, 3, 4 };
	ft::List<ConstrCounter> lst(array, array + 5);

	lst.unique();
	assert(lst.size() == 3);

	assert(*get_n_bwd(lst, 0) == 1);
	assert(*get_n_bwd(lst, 1) == 3);
	assert(*get_n_bwd(lst, 2) == 4);
}

//a binary predicate implemented as a function:
bool same_integral_part (ConstrCounter first, ConstrCounter second)
{
	return (first.val == second.val); 
}

// a binary predicate implemented as a class:
struct is_near
{
  bool operator() (double first, double second)
	{
		return (fabs(first-second)<5.0);
	}
};

static void test_unique_binary_predicate()
{
	ConstrCounter array[5] = { 42, 42, 43, 43, 45 };
	ft::List<ConstrCounter> lst(array, array + 5);

	lst.unique(same_integral_part);
	assert(lst.size() == 3);
	assert(get_n_bwd(lst, 0)->val == 42);
	assert(get_n_fwd(lst, 1)->val == 43);
	assert(get_n_bwd(lst, 2)->val == 45);

	double mydoubles[]={ 2.72,  3.14, 12.15, 15.3,  72.25, 73.0 };
	ft::List<double> lst1(mydoubles, mydoubles + 6);
	lst1.unique(is_near());
	assert(lst1.size() == 3);
	ft::ListIterator<double> ite1 = lst1.begin();
	assert(*ite1++ == 2.72);
	assert(*ite1++ == 12.15);
	assert(*ite1 == 72.25);

}

static void test_reverse()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ft::List<ConstrCounter> lst(array, array + 5);

	lst.reverse();
	assert(lst.size() == 5);
	assert(get_n_fwd(lst, 0)->val == 4);
	assert(get_n_fwd(lst, 1)->val == 3);
	assert(get_n_fwd(lst, 2)->val == 2);
	assert(get_n_fwd(lst, 3)->val == 1);
	assert(get_n_fwd(lst, 4)->val == 0);
}

static void test_merge()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ConstrCounter array1[5] = { 5, 10, 7, 9, 8 };


	ft::List<ConstrCounter> lst(array1, array1 + 5);
	ft::List<ConstrCounter> lst1(array, array + 5);
	lst.merge(lst1);
	assert(lst.size() == 10);
	assert(get_n_fwd(lst, 0)->val == 0);
	assert(get_n_fwd(lst, 1)->val == 1);
	assert(get_n_fwd(lst, 2)->val == 2);
	assert(get_n_fwd(lst, 3)->val == 3);
	assert(get_n_fwd(lst, 4)->val == 4);
	assert(get_n_fwd(lst, 5)->val == 5);
	assert(get_n_fwd(lst, 6)->val == 7);
	assert(get_n_fwd(lst, 7)->val == 8);
	assert(get_n_fwd(lst, 8)->val == 9);
	assert(get_n_fwd(lst, 9)->val == 10);
}

static void test_merge_comp()
{
	ConstrCounter array[5] = { 0, 1, 2, 3, 4 };
	ConstrCounter array1[5] = { 5, 10, 7, 9, 8 };


	ft::List<ConstrCounter> lst(array1, array1 + 5);
	ft::List<ConstrCounter> lst1(array, array + 5);
	lst.merge(lst1, std::greater<ConstrCounter>());
	assert(lst.size() == 10);
	assert(get_n_fwd(lst, 0)->val == 10);
	assert(get_n_fwd(lst, 1)->val == 9);
	assert(get_n_fwd(lst, 2)->val == 8);
	assert(get_n_fwd(lst, 3)->val == 7);
	assert(get_n_fwd(lst, 4)->val == 5);
	assert(get_n_fwd(lst, 5)->val == 4);
	assert(get_n_fwd(lst, 6)->val == 3);
	assert(get_n_fwd(lst, 7)->val == 2);
	assert(get_n_fwd(lst, 8)->val == 1);
	assert(get_n_fwd(lst, 9)->val == 0);
}

static void test_sort()
{
	ConstrCounter array[5] = { 5, 3, 1, 2, 4 };
	ft::List<ConstrCounter> lst(array, array + 5);

	lst.sort();
	assert(lst.size() == 5);
	assert(get_n_fwd(lst, 0)->val == 1);
	assert(get_n_fwd(lst, 1)->val == 2);
	assert(get_n_fwd(lst, 2)->val == 3);
	assert(get_n_fwd(lst, 3)->val == 4);
	assert(get_n_fwd(lst, 4)->val == 5);
}

static void test_sort_comp()
{
	ConstrCounter array[5] = { 5, 3, 1, 2, 4 };
	ft::List<ConstrCounter> lst(array, array + 5);

	lst.sort(std::greater<ConstrCounter>());
	assert(lst.size() == 5);
	assert(get_n_fwd(lst, 0)->val == 5);
	assert(get_n_fwd(lst, 1)->val == 4);
	assert(get_n_fwd(lst, 2)->val == 3);
	assert(get_n_fwd(lst, 3)->val == 2);
	assert(get_n_fwd(lst, 4)->val == 1);
}

void test_list()
{
	test_one("push_back", test_pushback);
	test_one("push_front", test_pushfront);
	test_one("assign", test_assign);
	test_one("assign_iter", test_assign_iter);
	test_one("constr", test_constr);
	test_one("constr_iter", test_constr_iter);
	test_one("assign_copy", test_assign_copy);
	test_one("capacity", test_capacity);
	test_one("iterator", test_iterator);
	test_one("reverse_iterator", test_reverse_iterator);
	test_one("insert_one", test_insert_one);
	test_one("insert", test_insert);
	test_one("insert_iter", test_insert_iter);
	test_one("erase", test_erase);
	test_one("erase_range", test_erase_range);
	test_one("pop_back", test_pop_back);
	test_one("pop_front", test_pop_front);
	test_one("resize", test_resize);
	test_one("swap", test_swap);
	test_one("cmp_eq", test_cmp_eq);
	test_one("splice", test_splice);
	test_one("splice_iter", test_splice_iter);
	test_one("splice_iter_first_last", test_splice_iter_first_last);
	test_one("remove", test_remove);
	test_one("remove_if", test_remove_if);
	test_one("unique", test_unique);
	test_one("unique_binary_predicate", test_unique_binary_predicate);
	test_one("reverse", test_reverse);
	test_one("merge", test_merge);
	test_one("sort", test_sort);
	test_one("merge_compartor", test_merge_comp);
	test_one("sort_comparator", test_sort_comp);

}