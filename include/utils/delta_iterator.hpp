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

	// the iterator type the specified container
	using iter_type = typename T::iterator;

	DeltaIterator(iter_type base_begin, iter_type base_end,
				  iter_type delta_begin, iter_type delta_end) :
			      _base_begin(base_begin), _base_end(base_end), 
				  _delta_begin(delta_begin), _delta_end(delta_end) {
		base_done = (_base_begin == _base_end);
	};

	// construct a special end iterator
	DeltaIterator(iter_type end) :
				  _base_begin(end), _base_end(end),
				  _delta_begin(end), _delta_end(end) {
		base_done = true;
	};

	//incrementing operation
	DeltaIterator& operator++ () {
		if (!base_done) {
			if (++_base_begin == _base_end) {
				base_done = true;
			}
		}
		else {
			if (_delta_begin != _delta_end) {
				++_delta_begin;
			}
		}
		return *this;
	}

	reference operator *() const{
		if (base_done) {
			return *_delta_begin;
		}
		return *_base_begin;
	}

	bool operator== (const DeltaIterator& rhs) const {
		if (base_done && _delta_begin == _delta_end) {
			return rhs.base_done && (rhs._delta_begin == rhs._delta_end);
		}
		else if (rhs.base_done && (rhs._delta_begin == rhs._delta_end)) {
			return false;
		}
		return *(*this) == *rhs;
	}

	bool operator!= (const DeltaIterator& rhs) const {
		if (base_done && _delta_begin == _delta_end) {
			return !rhs.base_done || (rhs._delta_begin != rhs._delta_end);
		}
		else if (rhs.base_done && (rhs._delta_begin == rhs._delta_end)) {
			return true;
		}
		return *(*this) != *rhs;
	}

private:
	iter_type _base_begin;
	iter_type _base_end;
	iter_type _delta_begin;
	iter_type _delta_end;
	bool base_done;
};

#endif // DELTA_ITERATOR_H
