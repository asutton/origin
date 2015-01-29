// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#ifndef ORIGIN_MATH_STATS_HPP
#define ORIGIN_MATH_STATS_HPP

#include <origin.math/numeric.hpp>

// The stats module provides a suite of algorithms for computing
// statistical measures of sequences of data points. Each element
// in a sequence represents some quantitative observation or
// a value generated from a random variable. In general, these
// values are numeric (often real numbers). Some algorithms
// however, support computation of non-real types such as
// vectors and complex numbers.
//
// TODO: Determine which algorithms are valid for non-real types.

namespace origin {

// -------------------------------------------------------------------------- //
// Means                                                            [stats.mean]
//
// There are a large number of mean-computing functions, most of which
// are special cases of the generalized mean (or power mean).
//
// TODO: Support weighed means and moving means.

template<typename I, typename T = Value_type<I>>
  inline T
  arithmetic_mean(I first, I last) {
    assert(first != last);
    return sum(first, last) / distance(first, last);
  }

template<typename I, typename T = Value_type<I>>
  inline T
  geometric_mean(I first, I last) {
    assert(first != last);
    return std::pow(product(first, last), 1.0/distance(first, last));
  }

template<typename I, typename T = Value_type<I>>
  inline T
  harmonic_mean(I first, I last) {
    assert(first != last);
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

// Note that if the inner mean is negative, this operation
// results in NaN.
template<typename I, typename T = Value_type<I>>
  inline T
  cubic_mean(I first, I last) {
    int n = distance(first, last);
    
    // TODO: See notes in generalized_mean_non_inf about the inner
    // computation of the mean.
    T sum = 0;
    while (first != last) {
      sum += first * first * first;
      ++first;
    }
    T mean = sum / n;  

    return std::pow(mean, 1.0 / 3.0); // FIXME: Use std::cbrt.
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

// A helper function for generalized_mean. Computes either
// the min or max of a sequence when the exponent p is known
// to be infinite.
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


// -------------------------------------------------------------------------- //
// Medians                                                     [stats.median]
//
// Compute the median of a sequence of data points.


// A helper function for median. Note that n == distance(first, last).
template<typename I, typename T = Value_type<I>>
  inline T 
  median_even(I first, I last, int n) {
    std::advance(first, n / 2);
    T a = *first;
    std::advance(first);
    T b = *first;
    return (a + b) / 2;
  }

// A helper function for median. Note that n == distance(first, last).
template<typename I, typename T = Value_type<I>>
  inline T 
  median_odd(I first, I last, int n) {
    std::advance(first, n / 2);
    return *first;
  }


// Compute the median of the elements in [first, last). The range
// [first, last) shall be sorted ascending order.
//
// FIXME: Check corner cases for one- and two-element sequences.
template<typename I, typename T = Value_type<I>>
  inline T 
  median(I first, I last) {
    assert(first != last);
    assert(std::is_sorted(first, last));
    int n = distance(first, last);
    if (even(n))
      return median_even(first, last, n);
    else
      return median_odd(first, last, n);
  }

// A helper function for median_unsorted. Note that 
// n == distance(first, last).
template<typename I, typename T = Value_type<I>>
  inline T 
  median_unsorted_even(I first, I last, int n) {
    I mid = std::next(first, (n + 1) / 2);
    I iter = std::nth_element(first, mid, last);
    T b = *iter;
    std::advance(iter, -1);
    T a = *iter;
    return (a + b) / 2;
  }

// A helper function for median_unsorted. Note that 
// n == distance(first, last).
template<typename I, typename T = Value_type<I>>
  inline T 
  median_unsorted_odd(I first, I last, int n) {
    I mid = std::next(first, n / 2);
    I iter = std::nth_element(first, mid, last);
    return *iter;
  }

// Compute the median of the elements in [first, last). Note that this
// algorithm permutes the input sequence to find the median. The
// iterator type is required to be a Random Access Iterator.
//
// FIXME: Check corner cases for one- and two-element sequences.
template<typename I, typename T = Value_type<I>>
  inline T 
  median_unsorted(I first, I last) {
    assert(first != last);
    int n = distance(first, last);
    if (even(n))
      return median_unsorted_even(first, last, n);
    else
      return median_unsorted_odd(first, last, n);
  }

// -------------------------------------------------------------------------- //
// Mode                                                        [stats.median]
//
// Compute the mode of a sequence of data points.


// Return the number of equivalence classes in the
// sorted range [first, last).
template<typename I, typename O, typename T = Value_type<I>>
  I
  count_equivalent(I first, I last, O out) {
    int n = 0;
    I iter = first;
    while (first != last) {
      first = std::upper_bound(first, last, *iter);
      ++n;
    }
    return n;
  }

// Create a histogram of equivalence classes in the sorted
// range [first, last). Note that I is a vector iterator whose 
// value type is a pair of int * T.
template<typename I, typename O, typename T = Value_type<I>>
  void
  build_histogram(I first, I last, O out) {
    I iter = first;
    while (first != last) {
      first = std::upper_bound(first, last, *iter);
      *out = { *std::prev(first), std::distance(iter, first) };
      iter = first;
      ++out;
    }
  }

// Returns a vector containing the modes of the elements in
// the sorted range [first, last).
template<typename I, typename T = Value_type<I>>
  std::vector<T>
  mode(I first, I last) {
    assert(first != last);
    assert(std::is_sorted(first, last));

    using Count = std::pair<int, T>;

    // Accumulate counts of all equivalent observations. If all
    // elements are unique, there is no mode.
    int n = count_equivalent(first, last);
    if (n == 1)
      return std::vector<T>{};

    std::vector<Count> v(n);
    build_histogram(first, last, v.begin());

    // Sort the accumulation by their counts and find the 
    // position of the first of the greatest counts.
    std::sort(v.begin(), v.end(), [](Count const& a, Count const& b) {
      return a.first < b.first;
    });
    auto bound = std::lower_bound(v.begin(), v.end(), v.back());

    // If all elements have the same count, then this
    // is an amodal distribution.
    if (bound == v.end())
      return std::vector<T>{};
    
    // Otherwise, copy out the elements with the greatest counts.
    std::vector<T> result(std::distance(bound, v.end()));
    auto iter = result.begin();
    while (bound != v.end()) {
      *iter = (*bound).second;
      ++iter;
      ++bound;
    }
    return result;
  }


} // namespace origin

#endif
