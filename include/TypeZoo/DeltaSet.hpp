//
// Created by alclol on 4/19/20.
//

#include <set>
#include <utility>
#include <iterator>
#include "utils/delta_iterator.hpp"

template<class _KeyType>
class DeltaSet {
public:

    DeltaSet() : _base(std::set<_KeyType>{}), _delta(std::set<_KeyType>{}), _end(_delta.end()) {};

    // move constructor
    DeltaSet(const std::set<_KeyType>&& base) : _base(std::move(base)), _delta(std::set<_KeyType>{}), _end(_delta.end()) {};

    // return type of get_delta
    using delta_type = DeltaSet<_KeyType>;

    // type returned by dereferencing the iterator type
    using value_type = _KeyType;

    void merge(DeltaSet<_KeyType>& __src) {
       // make a copy of all the keys here, need a way to avoid this
       for (const auto& key : __src._base) {
           insert(key);
       }
    }

    void insert(const _KeyType& key) {
        if (!_base.count(key)) {
            _delta.insert(key);
       }
    }

    delta_type get_delta() {
        DeltaSet<_KeyType> delta(std::move(_delta));
        rebase();
        return delta;
    }

    int size() const {
        return _base.size() + _delta.size();
    }

    int count(const _KeyType& key) const {
        return _base.count(key) + _delta.count(key);
    }

    DeltaIterator<std::set<_KeyType>> begin() {
        _end = _delta.end();
        DeltaIterator<std::set<_KeyType>> result(_base.begin(), _base.end(), _delta.begin(), _end);
        return result;
    }

    DeltaIterator<std::set<_KeyType>> end() {
        DeltaIterator<std::set<_KeyType>> result(_end);
        return result;
    }

    void rebase() {
        _base.merge(_delta);
        _delta.clear();
    }

private:
    std::set<_KeyType> _base;
    std::set<_KeyType> _delta;
    typename std::set<_KeyType>::iterator _end;
};
