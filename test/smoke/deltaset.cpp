#include "../catch.hpp"
#include "lattice_core.hpp"
#include "TypeZoo/DeltaSet.hpp"

TEST_CASE("union_delta") {
	std::set<int> l({ 1, 20, 30 });
	std::set<int> r({ 1, 2, 3 });

	DeltaSet<int> lefts(std::move(l));
	DeltaSet<int> rights(std::move(r));
}