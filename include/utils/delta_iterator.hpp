#ifndef DELTA_ITERATOR_H
#define DELTA_ITERATOR_H

#include <iterator>

template<class T>
class DeltaIterator {

public:
	// iterator types
	using iterator_category = std::input_iterator_tag;
	using value_type = typename T::value_type;
	using difference_type = std::ptrdiff_t;
	using pointer = const value_type*;
	using reference = const value_type&;

	using iter_type = typename T::iterator;

	DeltaIterator(iter_type base_begin, iter_type base_end,
				  iter_type delta_begin, iter_type delta_end) :
			      _base_begin(base_begin), _base_end(base_end), 
				  _delta_begin(delta_begin), _delta_end(delta_end) {
		_cur = base_begin;
	};

	// construct a special end iterator
	DeltaIterator(iter_type end) :
				  _base_begin(end), _base_end(end),
				  _delta_begin(end), _delta_end(end) {
		_cur = end;
	};

	//incrementing operation
	DeltaIterator& operator++ () {
		if (_cur != _delta_end) {
			if (_cur == _base_end) {
				_cur = _delta_begin;
			}
			else {
				++_cur;
			}
			return *this;
		}
	}

	reference operator *() {
		return *_cur;
	}

	bool operator== (const DeltaIterator& rhs) const {
		return (*_cur) == (*rhs._cur);
	}

	bool operator!= (const DeltaIterator& rhs) const {
		return (*_cur) != (*rhs._cur);
	}

private:
	iter_type _base_begin;
	iter_type _base_end;
	iter_type _delta_begin;
	iter_type _delta_end;
	iter_type _cur;

};

#endif // DELTA_ITERATOR_H