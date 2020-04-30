#ifndef DELTAMAP_H
#define DELTAMAP_H

#include "DeltaSet.hpp"
#include <map>
#include "lattice_core.hpp"
#include "merges/map_mrg.hpp"

template <typename k_type, class T, class Func>
class DeltaMap {
public:

	//type alias
	using iterator = typename std::map<k_type, Lattice<T, Func>>::iterator;
	using key_type = k_type;
	using mapped_type = Lattice<T, Func>;
	using value_type = std::pair<k_type, Lattice<T, Func>>;
	using size_type = std::size_t;
	using delta_type = Lattice<DeltaMap<k_type, T, Func>, MapUnion>;

	DeltaMap() : _base(std::map<k_type, Lattice<T, Func>>{}) {};

	//copy constructor
	DeltaMap(const std::map<k_type, Lattice<T, Func>>& base) : _base(base) {};

	
	iterator begin() {
		return _base.begin();
	}

	iterator end() {
		return _base.end();
	}

	mapped_type& at(const key_type& key) {
		return _base.at(key);
	}

	const mapped_type& at(const key_type& key) const {
		return _base.at(key);
	}

	size_type size() const {
		return _base.size();
	}

	size_type count(const key_type& key) const {
		return _base.count(key);
	}

	std::pair<iterator, bool> insert(const value_type& value) {
		return _base.insert(value);
	}

	std::pair<iterator, bool> insert(const value_type&& value) {
		return _base.insert(value);
	}

	iterator erase(iterator pos) {
		return _base.erase(pos);
	}

	template<class... Args>
	std::pair<iterator, bool> emplace(Args&&... args) {
		return _base.emplace(args...);
	}

	bool operator==(const DeltaMap<k_type, T, Func>& right) const {
		return _base == right._base;
	}

	template <class Q=T>
	typename std::enable_if_t<has_delta<Q>::value, delta_type>
	get_delta() {
		DeltaMap<k_type, Q, Func> delta;
		
		for (auto& [key, value] : _base) {
			delta.insert(std::make_pair(key, value.get_delta()));
		}

		return Lattice(delta, MapUnion{});
	}

private:
	std::map<k_type, Lattice<T, Func>> _base;
};

#endif // DELTAMAP_H
