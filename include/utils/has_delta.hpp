#ifndef HAS_DELTA_H
#define HAS_DELTA_H

#include <type_traits>

template<typename T, typename=void>
struct has_delta : std::false_type {};

template<typename T>
struct has_delta<T, std::void_t<typename T::delta_type,
								decltype(std::declval<T>.get_delta()),
								std::enable_if_t<std::is_same<decltype(std::declval<T>.get_delta()), 
															  typename T::deltatype>::value>>>
	: std::true_type {};

#endif // HAS_DELTA_H
