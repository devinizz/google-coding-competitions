#ifndef PRIME_SIEVE_HPP_
#define PRIME_SIEVE_HPP_

#include <vector>

class PrimeSieve {
 private:
  std::vector<bool> is_prime_;
  std::vector<int> primes_;
 public:
  bool check(int n) const { return is_prime_.at(n); }
  std::vector<int>::const_iterator begin() const { return primes_.begin(); }
  std::vector<int>::const_iterator end() const { return primes_.end(); }

  PrimeSieve(int n = 0) {
    if (n <= 2)
      return;
    is_prime_.resize(n, true);
    is_prime_[0] = is_prime_[1] = false;
    for (int i = 2; i < n; i++) {
      if (is_prime_[i])
        primes_.push_back(i);
      for (int p : primes_) {
        if (i * p >= n)
          break;
        is_prime_[i * p] = false;
        if (i % p == 0)
          break;
      }
    }
  }
};

#endif // PRIME_SIEVE_HPP_
