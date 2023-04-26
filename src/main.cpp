#include <iostream>
#include "jet/array.h"
#include "jet/array1.h"
#include "jet/array2.h"
int main() {
	jet::Array2<int> arr(2,5,5);

	arr.print();
	return 0;
}