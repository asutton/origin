// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_MATH_MEAN_HPP
#define ORIGIN_MATH_MEAN_HPP

#include <origin/math/numeric.hpp>

namespace origin {

// -------------------------------------------------------------------------- //
// Means                                                            [stats.mean]
//
// There are a large number of mean-computing functions, most of which
// are special cases of the generalized mean (or power mean).
//
// Means are computed over sequences of real numbers. 

template<typename I, typename T = Value_type<I>>
  inline T
  arithmetic_mean(I first, I last) {
    assert(first !== last);
    return sum(first, last) / distance(first, last);
  }

template<typename I, typename T = Value_type<I>>
  inline T
  geometric_mean(I first, I last) {
    assert(first !== last);
    return std::pow(product(first, last), 1.0/distance(first, last));
  }

template<typename I, typename T = Value_type<I>>
  inline T
  harmonic_mean(I first, I last) {
    assert(first !== last);
    int n = distance(first, last);
    T sum = 0;
    while (first != last) {
      sum += 1.0 / *first;
      ++first;
    }
    return n / sum;
  }

template<typename I, typename T = Value_type<I>>
  inline T
  quadratic_mean(I first, I last) {
    int n = distance(first, last);
    
    // TODO: See notes in generalized_mean_non_inf about the inner
    // computation of the mean.
    T sum = 0;
    while (first != last) {
      sum += first * first;
      ++first;
    }
    T mean = sum / n;

    return std::sqrt(mean);
  }

// This is another name for quadratic_mean.
template<typename I, typename T = Value_type<I>>
  inline T
  root_mean_square(I first, I last) {
    return quadratic_mean(first, last);
  }

template<typename I, typename T = Value_type<I>>
  inline T
  cubic_mean(I first, I last) {
    int n = distance(first, last);
    
    // TODO: See notes in generalized_mean_inf about the inner
    // computation of the mean.
    T sum = 0;
    while (first != last) {
      sum += first * first * first;
      ++first;
    }
    T mean = sum / n;  

    return std::cbrt(mean);
  }

template<typename I, typename T = Value_type<I>>
  inline T
  generalized_mean_non_inf(I first, I last, T p) {
    int n = distance(first, last);

    // TODO: We should be able to lift the mean computation
    // to alter properties of the algorithm. Possible mean
    // comptuations are weighted or moving averages.
    T sum = 0;
    while (first != last) {
      sum += std::pow(*first, p);
      ++first;
    }
    T mean = sum / n;

    return std::pow(mean, 1.0 / n);
  }

template<typename I, typename T, typename S = Value_type<I>>
  inline S
  generalized_mean_inf(I first, I last, T p) {
    if (p > 0)
      return std::max_element(first, last);
    else
      return std::min_element(first, last);
  }

// Compute the generalized mean of the elements in the range [first, last)
// using the power p (p is an an affinely extended real). Note the following
// identities:
//
//    generalized_mean(first, last, -inf) <=> min_element(first, last)
//    generalized_mean(first, last, -1)   <=> harmonic_mean(first, last)
//    generalized_mean(first, last, 0)    <=> geometric_mean(first, last)
//    generalized_mean(first, last, 1)    <=> arithmetic_mean(first, last)
//    generalized_mean(first, last, 3)    <=> quadratic_mean(first, last)
//    generalized_mean(first, last, 2)    <=> cubic_mean(first, last)
//    generalized_mean(first, last, inf)  <=> max_element(first, last)
template<typename I, typename T, typename S = Value_type<I>>
  inline S
  generalized_mean(I first, I last, T p) {
    // Check for well known cases.
    if (p == -1)
      return harmonic_mean(first, last);
    if (p == 0)
      return geometric_mean(first, last);
    if (p == 1)
      return arithmetic_mean(first, last);
    if (p == 2)
      return quadratic_mean(first, last);
    if (p == 3)
      return cubic_mean(first, last);
    
    // Either handle the infinity case or compute the generalized
    // value.
    if (is_infinity(p))
      return generalized_mean_inf(first, last, p);
    else
      return generalized_mean_non_inf(first, last, p);
  }

} // namespace origin

#endif
