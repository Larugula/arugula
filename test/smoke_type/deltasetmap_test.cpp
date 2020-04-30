#include "../catch.hpp"
#include "lattice_core.hpp"
#include "TypeZoo/DeltaSet.hpp"
#include "TypeZoo/DeltaSetMap.hpp"
#include "merges/setop_mrg.hpp"
#include <iostream>


TEST_CASE("deltasetmap basic tests") {
	std::map<std::string, Lattice<DeltaSet<int>, Union>> left = { {"xx", Lattice(DeltaSet<int>(std::set<int>{1,2,3}), Union{})},
																  {"yy", Lattice(DeltaSet<int>(std::set<int>{1,20,30}), Union{})} };
	std::map<std::string, Lattice<DeltaSet<int>, Union>> result;
	DeltaSetMap leftmap(left);
	DeltaSetMap resultmap(result);

	//test basic functionalities
	REQUIRE(leftmap.size() == 2);
	REQUIRE(leftmap.count("xx") == 1);
	REQUIRE(leftmap.at("xx") == Lattice(DeltaSet<int>(std::set<int>{1, 2, 3}), Union{}));

	//test the iterator
	for (auto& e : leftmap) {
		resultmap.insert(e);
	}

	REQUIRE(leftmap == resultmap);
}

TEST_CASE("delta test") {
	DeltaSet<int> t1(std::set<int>{1, 2, 3});
	t1.merge(DeltaSet<int>(std::set<int>{1, 20, 30}));
	DeltaSet<int> t2(std::set<int>{5, 6, 7});
	t2.merge(DeltaSet<int>(std::set<int>{5, 60, 70}));

	std::map<std::string, Lattice<DeltaSet<int>, Union>> left = { {"xx", Lattice(t1, Union{})},
																  {"yy", Lattice(t2, Union{})}};
	std::map<std::string, Lattice<DeltaSet<int>, Union>> expected = { {"xx", Lattice(DeltaSet<int>(std::set<int>{20,30}), Union{})},
																    {"yy", Lattice(DeltaSet<int>(std::set<int>{60,70}), Union{})} };
	DeltaSetMap leftmap(left);
	DeltaSetMap expectedmap(expected);
	Lattice expectedLattice(expectedmap, MapUnion{});

	DeltaSetMap<std::string, DeltaSet<int>, Union>::delta_type resultLattice = leftmap.get_delta();

	REQUIRE(resultLattice == expectedLattice);
}
