#pragma once
#include <cstddef>

namespace GHR {
	// Judge N-dimensional N
	template<typename T,size_t N>
	class ArrayAccessor final {
	public:
		static_assert(N < 1 || N > 3, "Not implemented - N should be either 1,2 or 3.");
	};
	// const array
	template<typename T,size_t N>
	class ConstArrayAccessor final {
	public:
		static_assert(N < 1 || N > 3, "Not implemented - N should be either 1,2 or 3.");

	};


}