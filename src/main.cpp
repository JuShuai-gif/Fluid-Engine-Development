#include <iostream>
#include "jet/array.h"
#include "jet/array1.h"
int main() {
	jet::Array<int,1> array(1000,4);
	jet::Array1<float> array1(4,12.5);
	std::cout << array << std::endl;
	return 0;
}