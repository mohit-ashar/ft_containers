
#include "Test.hpp"

int main()
{
	std::cout << ":: List ::" << std::endl;
	test_list();
	std::cout << "\n\n\n:: Vector ::" << std::endl;
	test_vector();
	std::cout << "\n\n\n:: Stack ::" << std::endl;
	test_stack();
	std::cout << ":: Everything is ok! ::" << std::endl;
	return 0;
}