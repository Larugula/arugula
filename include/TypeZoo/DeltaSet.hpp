//
// Created by alclol on 4/19/20.
//

#include <set>

template<class _Key>
class DeltaSet {
public:

    void merge(std::set<V>& __src) {
       _delta.merge(__src);
    }

    void rebase() {
       _base.merge(_delta);
       _delta.clear();
    }

private:
    std::set<_Key> _base;
    std::set<_Key> _delta;
};
