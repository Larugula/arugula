#include "../catch.hpp"
#include "lattice_core.hpp"
#include "TypeZoo/DeltaSet.hpp"
#include "TypeZoo/DeltaSetMap.hpp"
#include "merges/setop_mrg.hpp"
#include <iostream>

TEST_CASE("deltasetmap with lattice mapunion test") {
	DeltaSet<int> t1(std::set<int>{1, 2, 3});
	DeltaSet<int> t3(std::set<int>{1, 20, 30});
	DeltaSet<int> t2(std::set<int>{5, 6, 7});
	DeltaSet<int> t4(std::set<int>{5, 60, 70});

	std::map<std::string, Lattice<DeltaSet<int>, Union>> left = { {"xx", Lattice(t1, Union{})},
																  {"yy", Lattice(t2, Union{})} };
	std::map<std::string, Lattice<DeltaSet<int>, Union>> right = { {"xx", Lattice(t3, Union{})},
																  {"yy", Lattice(t4, Union{})} };

	std::map<std::string, Lattice<DeltaSet<int>, Union>> expected = { {"xx", Lattice(DeltaSet<int>(std::set<int>{20,30}), Union{})},
																	{"yy", Lattice(DeltaSet<int>(std::set<int>{60,70}), Union{})} };
	DeltaSetMap leftmap(left);
	DeltaSetMap rightmap(right);
	Lattice leftLattice(leftmap, MapUnion{});
	Lattice rightLattice(rightmap, MapUnion{});
	DeltaSetMap expectedmap(expected);
	Lattice expectedLattice(expectedmap, MapUnion{});

	leftLattice.merge(rightLattice);
	DeltaSetMap<std::string, int, Union>::delta_type resultLattice = leftLattice.get_delta();

	REQUIRE(resultLattice == expectedLattice);
	//verify the content of leftLattice after get delta
	REQUIRE(leftLattice.reveal().size() == 2);
	REQUIRE(leftLattice.reveal().at("xx") == Lattice(DeltaSet<int>(std::set<int>{1, 2, 3, 20, 30}), Union{}));
	REQUIRE(leftLattice.reveal().at("yy") == Lattice(DeltaSet<int>(std::set<int>{5, 6, 7, 60, 70}), Union{}));
}