#ifndef DELTASETMAP_H
#define DELTASETMAP_H

#include "DeltaSet.hpp"
#include <map>
#include "lattice_core.hpp"
#include "merges/map_mrg.hpp"

template <typename k_type, typename set_v_type, class Func>
class DeltaSetMap {
public:

	//type alias
	using iterator = typename std::map<k_type, Lattice<DeltaSet<set_v_type>, Func>>::iterator;
	using key_type = k_type;
	using mapped_type = Lattice<DeltaSet<set_v_type>, Func>;
	using value_type = std::pair<k_type, Lattice<DeltaSet<set_v_type>, Func>>;
	using size_type = std::size_t;
	using delta_type = Lattice<DeltaSetMap<k_type, set_v_type, Func>, MapUnion>;

	DeltaSetMap() : _base(std::map<k_type, Lattice<DeltaSet<set_v_type>, Func>>{}) {};

	//copy constructor
	DeltaSetMap(const std::map<k_type, Lattice<DeltaSet<set_v_type>, Func>>& base) : _base(base) {};

	
	iterator begin() {
		return _base.begin();
	}

	iterator end() {
		return _base.end();
	}

	mapped_type& at(const key_type& key) {
		return _base.at(key);
	}

	size_type size() {
		return _base.size();
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

	bool operator==(const DeltaSetMap<k_type, set_v_type, Func>& right) const {
		return _base == right._base;
	}

	delta_type get_delta() {
		DeltaSetMap<k_type, set_v_type, Func> delta;
		
		for (auto& [key, value] : _base) {
			delta.insert(std::make_pair(key, value.get_delta()));
		}

		return Lattice(delta, MapUnion{});
	}

private:
	std::map<k_type, Lattice<DeltaSet<set_v_type>, Func>> _base;
};

#endif // DELTASETMAP_H
