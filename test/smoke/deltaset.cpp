#include "../catch.hpp"
#include "lattice_core.hpp"
#include "merges/setop_mrg.hpp"
#include "TypeZoo/DeltaSet.hpp"

TEST_CASE("delta set with lattice union_delta") {
	std::set<int> l({ 1, 20, 30 });
	std::set<int> r({ 1, 2, 3 });

	DeltaSet<int> lefts(std::move(l));
	DeltaSet<int> rights(std::move(r));

	Lattice ls(lefts, Union{});
	Lattice rs(rights, Union{});

	Lattice<DeltaSet<int>, Union> expr = ls + rs;

	REQUIRE(expr.reveal().size() == 5);
	REQUIRE(expr.get_delta().size() == 2);
	//verify delta does get emptied, and base is merged
	REQUIRE(expr.get_delta().size() == 0);
	REQUIRE(expr.reveal().size() == 5);
}