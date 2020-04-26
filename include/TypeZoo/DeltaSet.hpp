//
// Created by alclol on 4/19/20.
//

#include <set>
#include <utility>
#include <iterator>

template<class _KeyType>
class DeltaSet {
public:

    DeltaSet() : _base(std::set<_KeyType>{}), _delta(std::set<_KeyType>{}) {};

    //move constructor
    DeltaSet(const std::set<_KeyType>&& base) : _base(std::move(base)), _delta(std::set<_KeyType>{}) {};

    //define a type alias for delta, mandatory
    using delta_type = DeltaSet<_KeyType>;

    void merge(DeltaSet<_KeyType>& __src) {
       // make a copy of all the keys here, need a way to avoid this
       for (const auto& key : __src._base) {
           insert(key)
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
        return dalta;
    }

    int size() {
        return _base.size();
    }

    int count(const _KeyType& key) {
        return _base.count(key) + _delta.count(key);
    }

    void rebase() {
        _base.merge(_delta);
        _delta.clear();
    }

private:
    std::set<_KeyType> _base;
    std::set<_KeyType> _delta;
};
