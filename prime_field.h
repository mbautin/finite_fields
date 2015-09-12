#ifndef PRIME_FIELD_H_INCLUDED
#define PRIME_FIELD_H_INCLUDED

#include "finite_fields_precompiled.h"


template<class INT, int P>
class PrimeField {
public:

  PrimeField(INT initial_value) : value(normalize(initial_value)) {
  }

  PrimeField<INT, P> operator +(INT other) const {
    return PrimeField(normalize(value + other));
  }

  PrimeField<INT, P> operator +(PrimeField<INT, P> other) const {
    return *this + other.value;
  }

  PrimeField<INT, P> operator -(INT other) const {
    return PrimeField(normalize(value - other));
  }

  PrimeField<INT, P> operator -(PrimeField<INT, P> other) const {
    return *this - other.value;
  }

  PrimeField<INT, P> operator *(PrimeField<INT, P> other) const {
    return *this * other.value;
  }

  PrimeField<INT, P> operator *(INT other) const {
    return PrimeField(normalize(normalize(value) * normalize(other)));
  }

  PrimeField<INT, P> operator /(INT other) const {
    INT denominator = normalize(other);
    if (denominator == 0) {
      // This behavior is really undefined.
      return PrimeField<INT, P>(0);
    }

    // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Modular_integers
    INT t = 0;
    INT newt = 1;
    INT r = P;
    INT newr = other;
    while (newr != 0) {
      INT quotient = r / newr;

      INT t_next = newt;
      newt = t - quotient * newt;
      t = t_next;

      INT r_next = newr;
      newr = r - quotient * newr;
      r = r_next;
    }
    if (r > 1) {
      // undefined
      return PrimeField<INT, P>(0);
    }

    if (t < 0) t += P;
    return *this * t;
  }

  PrimeField<INT, P> operator /(PrimeField<INT, P> other) const {
    return *this / other.value;
  }

  bool operator ==(PrimeField other) const {
    return normalize(value) == normalize(other.value);
  }

  bool operator !=(PrimeField other) const {
    return normalize(value) != normalize(other.value);
  }

  INT get_value() { return value; }

private:
  const INT value;

  static INT normalize(INT value);
//
//  template<class INT_, int P_>
//  friend bool operator == (PrimeField<INT_, P_>, PrimeField<INT_, P_>);
//
//  template<class INT_, int P_>
//  friend bool operator != (PrimeField<INT_, P_>, PrimeField<INT_, P_>);
};


template<class INT, int P>
INT PrimeField<INT, P>::normalize(INT value) {
  if (value < 0) {
    INT mod = value % P;
    if (mod == 0) {
      return 0;
    } else {
      return P + mod;
    }
  } else {
    return value % P;
  }
}

//template<class INT, int P>
//bool operator == (PrimeField<INT, P> a, PrimeField<INT, P> b) {
//  return PrimeField<INT, P>::normalize(a.value) == PrimeField<INT, P>::normalize(b.value);
//}
//
//template<class INT, int P>
//bool operator != (PrimeField<INT, P> a, PrimeField<INT, P> b) {
//  return PrimeField<INT, P>::normalize(a.value) != PrimeField<INT, P>::normalize(b.value);
//}

#endif // PRIME_FIELD_H_INCLUDED

