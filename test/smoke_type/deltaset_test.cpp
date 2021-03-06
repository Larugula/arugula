#include "../catch.hpp"
#include "TypeZoo/DeltaSet.hpp"
#include <iostream>

TEST_CASE("Test constructors") {


}

TEST_CASE("basics int set") {
	std::set<int> l({ 1, 20, 30 });
	std::set<int> r({ 1, 2, 3 });

	DeltaSet<int> lefts(std::move(l));
	DeltaSet<int> rights(std::move(r));

	REQUIRE(lefts.size() == 3);
	REQUIRE(lefts.count(20) == 1);

	lefts.merge(rights);

	REQUIRE(lefts.size() == 5);
	REQUIRE(lefts.count(3) == 1);

	REQUIRE(lefts.get_delta().size() == 2);
	REQUIRE(lefts.size() == 5);
	REQUIRE(lefts.get_delta().size() == 0);
}

TEST_CASE("iterator test") {
	std::set<int> l({ 1, 20, 30 });
	std::set<int> r({ 1, 2, 3 });

	DeltaSet<int> lefts(std::move(l));
	DeltaSet<int> rights(std::move(r));

	lefts.merge(rights);

	std::set<int> result;
	
	for (auto& e : lefts) {
		result.insert(e);
	}

	REQUIRE(result == std::set<int> {1, 2, 3, 20, 30});
}
