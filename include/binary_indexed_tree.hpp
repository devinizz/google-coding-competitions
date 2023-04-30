#ifndef BINARY_INDEXED_TREE_HPP_
#define BINARY_INDEXED_TREE_HPP_

#include <vector>

template <class T>
class BinaryIndexedTree {
 private:
  using size_type = typename std::vector<T>::size_type;
  static size_type LSB(size_type i) { return i & -i; }
  static size_type HSB(size_type i) {
    if (i == 0)
      return 0;
    size_type res = 1;
    while (i >>= 1)
      res <<= 1;
    return res;
  }
  std::vector<T> bit_;
 public:
  operator std::vector<T>() const {
    if (bit_.empty())
      return bit_;
    std::vector<T> ret(bit_);
    for (size_type i = ret.size() - 1; i != 0; i--) {
      size_type j = i + LSB(i);
      if (j < ret.size())
        ret[j] -= ret[i];
    }
    return ret;
  }

  BinaryIndexedTree(size_type n = 0) : bit_(n) {}
  template <class... Args>
  BinaryIndexedTree(Args&&... args) : bit_(std::forward<Args>(args)...) {
    for (size_type i = 1; i < bit_.size(); i++) {
      size_type j = i + LSB(i);
      if (j < bit_.size())
        bit_[j] += bit_[i];
    }
  }

  void add(size_type i, const T& delta) {
    bit_.at(i); // check index range
    if (i == 0) {
      bit_[0] += delta;
      return;
    }
    for (; i < bit_.size(); i += LSB(i))
      bit_[i] += delta;
  }

  T prefix_sum(size_type i) const {
    bit_.at(i); // check index range
    T sum = bit_[0];
    for (; i != 0; i -= LSB(i))
      sum += bit_[i];
    return sum;
  }

  T prefix_sum(size_type i, size_type j) const {
    T sum = T();
    if (i >= j)
      return sum;
    bit_.at(j); // check index range
    for (; j > i; j -= LSB(j))
      sum += bit_[j];
    for (; i > j; i -= LSB(i))
      sum -= bit_[i];
    return sum;
  }

  size_type lower_bound_index(const T& value) const {
    if (bit_.empty())
      return 0;
    size_type i = 0;
    T diff = value - bit_[0];
    for (size_type j = HSB(bit_.size() - 1); j != 0; j >>= 1) {
      if (i + j < bit_.size() && bit_[i + j] <= diff) {
        diff -= bit_[i + j];
        i += j;
      }
    }
    return i + (diff > T());
  }
};

#endif // BINARY_INDEXED_TREE_HPP_
