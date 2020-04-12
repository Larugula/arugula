//
// Created by alclol on 4/12/20.
//
#include "lattice_core.hpp"
#include "merges/boolean_mrg.hpp"

#ifndef MANGO_GREATER_THAN_H
#define MANGO_GREATER_THAN_H

// potentially multi-thread unsafe!
template <class T>
struct CompareTransformer {
private:
    std::reference_wrapper<const Lattice<T, Max> > _target;
    std::reference_wrapper<const T> _val;

public:
    CompareTransformer(std::reference_wrapper<const Lattice<T, Max>> threshold,
                       std::reference_wrapper<const Lattice<T, Max>> target)
                       : _val(std::cref(threshold.get().reveal())), _target(target) { };

    CompareTransformer(std::reference_wrapper<const T> threshold_val,
                       std::reference_wrapper<const Lattice<T, Max>> target)
                       : _val(threshold_val), _target(target) { };

    Lattice<bool, Or> greater_than() const {
       return Lattice(_target.get().reveal() > _val, Or{});
    }

    Lattice<bool, Or> greater_than_or_eq() const {
       auto gt = _target.get().reveal();
       return Lattice(gt>_val || gt==_val, Or{});
    }

    Lattice<bool, Or> less_than() const {
       return Lattice(_target.get().reveal()<_val, Or{});
    }

    Lattice<bool, Or> less_than_or_eq() const {
       auto lt = _target.get().reveal();
       return Lattice(lt<this->_val || lt==this->_val, Or{});
    }
};

template <bool X, bool Y>
struct TempOr { static constexpr bool val {X || Y}; };

template <class Func, class T>
typename std::enable_if_t< std::is_same<Func, Max>::value, Lattice<bool, T> >
greater_than(Lattice<T, Func> obj, T n) {
   return Lattice(obj.reveal()>n, Or{});
}

template <class T, class Func>
typename std::enable_if_t< TempOr<std::is_same<Func, Max>::value, std::is_same<Func, Min>::value>::val, Lattice<T, Func> >
add_delta (const Lattice<T, Func>& target, const T& delta) {
  T data = target.reveal() + delta;
  return Lattice(data, Func{});
}

template <class T, class Func>
typename std::enable_if_t< TempOr<std::is_same<Func, Max>::value, std::is_same<Func, Min>::value>::val, Lattice<T, Func> >
deduct_delta (const Lattice<T, Func>& target, const T& delta) {
   T data = target.reveal() - delta;
   return Lattice(data, Func{});
}

#endif //MANGO_GREATER_THAN_H
