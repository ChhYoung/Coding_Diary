#ifndef _DSA_INCLUDE_SRC_COMPARATOR_H__
#define _DSA_INCLUDE_SRC_COMPARATOR_H__
namespace DSA {

	// less than 
	template<typename T>
	static bool lt(T* a, T* b) {
		return lt(*a, *b);
	}
	// less than 
	template<typename T>
	static bool lt(T& a, T& b) {
		return a < b;
	}

	// equql
	template<typename T>
	static bool eq(T* a, T* b) {
		return eq(*a, *b);
	}

	// equql
	template<typename T>
	static bool eq(T& a, T& b) {
		return a == b;
	}

}
#endif // _DSA_INCLUDE_SRC_COMPARATOR_H__