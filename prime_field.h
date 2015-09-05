#ifndef PRIME_FIELD_H_INCLUDED
#define PRIME_FIELD_H_INCLUDED

#include "finite_fields_precompiled.h"


template<class INT, int P>
class PrimeField {
public:

  PrimeField(INT initial_value) : value(normalize(initial_value)) {
  }

  PrimeField<INT, P> operator +(PrimeField other) const {
    return PrimeField(normalize(value + other.value));
  }

  INT get_value() { return value; }

private:
  const INT value;



  static INT normalize(INT value);

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



#endif // PRIME_FIELD_H_INCLUDED

