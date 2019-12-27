#ifndef LATTICE_MERGE_H
#define LATTICE_MERGE_H

// Inspired by:
// https://gieseanw.wordpress.com/2019/10/20/we-dont-need-no-stinking-expression-templates/
// https://wandbox.org/permlink/0byiMsdCFgNw7Bq1

// Has not been tuned for memory or performance efficiency

#include <iostream>
#include <type_traits>
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>


// Max merge operator for lattices whose domain has operator>= defined
typedef struct MaxStruct
{
   template<typename T, typename F, template<typename, typename> class L>
   auto operator()(const L<T,F>& left, const L<T,F>& right) const
   {
      return (left.reveal() >= right.reveal()) ? left : right;
   }
   friend std::ostream& operator<<(std::ostream& os, const struct MaxStruct m) {
      os << "Max";
      return (os);
   }
} Max;

// Union merge operator for lattices whose domain has std::set_union, std::begin and std::end defined
typedef struct UnionStruct
{
   template<typename T, typename F, template<typename, typename> class L>
   auto operator()(const L<T,F>& left, const L<T,F>& right) const
   {
      T l = left.reveal();
      T r = right.reveal();
      l.merge(r);
      return(L<T,F>(l));
   }
   friend std::ostream& operator<<(std::ostream& os, const struct UnionStruct m) {
      os << "Union";
      return (os);
   }
} Union;

// MapUnion merge operator for lattice whose domain is of type <Map, Lattice<T>>
typedef struct MapUnionStruct
{
   template<typename T, typename F, template<typename, typename> class L>
   auto operator()(const L<T,F>& left, const L<T,F>& right) const
   {
      auto l = left.reveal();
      auto r = right.reveal();
      auto merged = new std::remove_reference_t<T>(l);

      for (auto &i : r)
      {
         // insert makes a copy; emplace would not.
         auto iterflag = merged->insert(i);
         auto iter = iterflag.first;
         auto flag = iterflag.second;
         if (!flag) {
            auto newval = (iter->second + i.second);
            merged->erase(iter);
            merged->insert(std::pair<decltype(i.first), decltype(i.second)>(i.first, newval));
         }
      }

      T retval = T(*merged);
      delete merged;
      return (retval);
   }
   friend std::ostream& operator<<(std::ostream& os, const struct MapUnionStruct m) {
      os << "MapUnion";
      return (os);
   }
} MapUnion;

#endif // LATTICE_MERGE_H