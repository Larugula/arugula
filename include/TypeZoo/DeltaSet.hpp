#ifndef DELTASET_H
#define DELTASET_H

#include <set>
#include <utility>
#include <iterator>
#include "utils/delta_iterator.hpp"

template<class _KeyType>
class DeltaSet {
public:

    DeltaSet() : _base(std::set<_KeyType>{}), _delta(std::set<_KeyType>{}) {};

    // move constructor
    DeltaSet(const std::set<_KeyType>&& base) : _base(std::move(base)), _delta(std::set<_KeyType>{}) {};

    //type alias
    // return type of get_delta
    using delta_type = DeltaSet<_KeyType>;
    // type returned by dereferencing the iterator type
    using value_type = _KeyType;
    using iterator = DeltaIterator<std::set<_KeyType>>;
    using size_type = std::size_t;


    void merge(DeltaSet<_KeyType>& __src) {
       // make a copy of all the keys here, need a way to avoid this
       for (const auto& key : __src._base) {
           insert(key);
       }
    }

    std::pair<iterator, bool> insert(const value_type& key) {
        if (!_base.count(key)) {
            return _delta.insert(key);
       }
        return _base.insert(key);
    }

    delta_type get_delta() {
        DeltaSet<_KeyType> delta(std::move(_delta));
        rebase();
        return delta;
    }

    size_type size() const {
        return _base.size() + _delta.size();
    }

    size_type count(const _KeyType& key) const {
        return _base.count(key) + _delta.count(key);
    }

    iterator begin() {
        iterator result(_base.begin(), _base.end(), _delta.begin(), _delta.end());
        return result;
    }

    iterator end() {
        iterator result(_delta.end());
        return result;
    }

    //current definition require both base and delta to be exactly
    //the same. Maybe we should relax this is to only require the
    //union of _base and _delta to be the same?
    bool operator==(const DeltaSet<_KeyType>& right) const {
        return (_base == right._base) && (_delta == right._delta);
    }

    void rebase() {
        _base.merge(_delta);
        _delta.clear();
    }

private:
    std::set<_KeyType> _base;
    std::set<_KeyType> _delta;
};

#endif // DELTASET_H

