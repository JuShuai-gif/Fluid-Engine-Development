#include <iostream>
#include "jet/array.h"
#include "jet/array1.h"
int main() {
	jet::Array<int,1> array(1000,4);
	jet::Array1<float> array1(4,12.5);
	jet::Array<int,1> array2({12,15,45,13});
	std::cout << array << std::endl;
	jet::Array<int, 1> array3(1000, 4);
    array.parallelForEach([](int& elem) {
         elem *= 2;
    });
	array2.parallelForEach([](int& elem){
		std::cout << elem ;
	});
	return 0;
}