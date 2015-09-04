#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include <stddef.h>

#include <algorithm>
#include <vector>
#include <sstream>
#include <ostream>

namespace FF {

using std::max;
using std::vector;
using std::string;
using std::ostringstream;

template <typename F>
class Polynomial {
public:
  Polynomial() {
  };

  Polynomial(const F& scalar) {
    coef.push_back(scalar);
  }

  Polynomial(const vector<F> & elements)
    : coef(elements) {
  }


  Polynomial(vector<F> && elements)
    : coef(elements) {
  }

  virtual ~Polynomial() {
  }

  template<typename>
  friend Polynomial operator +(const Polynomial<F>&, const Polynomial<F>&);

  F get_coef(size_t i) const {
    if (i < coef.size()) {
      return coef[i];
    } else {
      return 0;
    }
  }

  bool is_zero() const {
    for (auto c : coef) {
      if (c != 0)
        return false;
    }
    return true;
  }

  int degree() const {
    return ((int) effective_size()) - 1;
  }

  size_t effective_size() const {
    size_t s = coef.size();
    while (s > 0 && coef[s - 1] == 0) {
      s--;
    }
    return s;
  }

  string str(const string& variable_name = "x") const {
    if (is_zero()) {
      return "0";
    }
    ostringstream ss;
    bool output_produced = false;
    for (int i = degree(); i >= 0; --i) {
      auto c = coef[i];
      if (c == 0) continue;

      if (c > 0) {
        if (output_produced) {
          ss << " + ";
        }
      } else {
        if (output_produced) {
          ss << " - ";
        } else {
          ss << "-";
        }
      }
      output_produced = true;

      if (abs(c) != 1 || i == 0) {
        ss << abs(c);
        if (i > 0) {
          ss << "*";
        }
      }

      if (i > 0) {
        ss << variable_name;
        if (i > 1) {
          ss << "^" << i;
        }
      }
    }
    return ss.str();
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

template<typename F>
bool operator == (const Polynomial<F>& a, const Polynomial<F>& b) {
  size_t a_size = a.effective_size();
  size_t b_size = b.effective_size();
  if (a_size != b_size) {
    return false;
  }

  for (size_t i = 0; i < a_size; ++i) {
    if (a.get_coef(i) != b.get_coef(i)) {
      return false;
    }
  }

  return true;
}

};


#endif // POLYNOMIAL_H_INCLUDED
