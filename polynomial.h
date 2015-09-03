#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include <stddef.h>

#include <algorithm>
#include <vector>

namespace FF {

using std::max;
using std::vector;

template <typename F>
class Polynomial {
public:
  Polynomial() {
  };

  Polynomial(const F& scalar) {
    coef.push_back(scalar);
  }

  Polynomial(vector<F> && elements)
    : coef(elements) {
  }

  virtual ~Polynomial() {
  }

  template<typename>
  friend Polynomial operator +(const Polynomial<F>&, const Polynomial<F>&);

  F get_coef(size_t i) {
    if (i < coef.size()) {
      return coef[i];
    } else {
      return 0;
    }
  }

  bool is_zero() {
    for (auto c : coef) {
      if (c != 0)
        return false;
    }
    return true;
  }

  int degree() {
    return ((int) coef.size()) - 1;
  }


private:
  vector<F> coef;

  void trim() {
    while (!coef.empty() && coef[coef.size() - 1] == 0) {
      coef.resize(coef.size() - 1);
    }
  }
};

template<typename F>
Polynomial<F> operator + (const Polynomial<F>& a, const Polynomial<F>& b) {
  Polynomial<F> result;
  result.coef.resize(max(a.coef.size(), b.coef.size()));
  for (size_t i = 0; i < a.size(); ++i) {
    result.coef[i] = a.get_coef(i) + b.get_coef(i);
  }
  result.trim();
  return result;
}

template<typename F>
Polynomial<F> operator * (const Polynomial<F>& a, const Polynomial<F>& b) {
  if (a.is_zero() || b.is_zero()) {
    return Polynomial<F>();
  }
  Polynomial<F> result;
  result.resize(a.degree() * b.degree() + 1);
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < b.size(); ++j) {
      result.coef[i + j] += a[i] * b[j];
    }
  }
  result.trim();
  return result;
}

template<typename F>
Polynomial<F> operator - (const Polynomial<F>& a, const Polynomial<F>& b) {

}


};


#endif // POLYNOMIAL_H_INCLUDED
