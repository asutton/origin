// Copyright (c) 2008-2013 Andrew Sutton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

int main() { }

#if 0

#include <cassert>
#include <iostream>

#include <origin/graph/adjacency_list.hpp>

using namespace std;
using namespace origin;
using namespace origin::adjacency_list_impl;


template<typename Q>
  struct hack_queue : Q
  {
    using Q::c;
    using Q::comp;
  };

template<typename Q>
  const hack_queue<Q>& 
  hack(const Q& q)
  {
    return reinterpret_cast<const hack_queue<Q>&>(q);
  }

template<typename P>
  void 
  print_queue(const P& p)
  {
    using Hack = hack_queue<typename P::queue_type>;
    const Hack& q = hack(p.free());

    cout << "free: ";
    for (const auto& x : q.c)
      cout << x << ' ';
    cout << '\n';
  }

template<typename P>
  void
  print_pool(const P& p)
  {
    using Vec = typename P::list_type;
    const Vec& v = p.data();

    cout << "pool: ";
    for (const auto& x : v) {
      if (x)
        cout << x.get() << ' ';
      else
        cout << 'X' << ' ';
    }
    cout << '\n';
  }

template<typename P>
  void
  print_live(P&& p)
  {
    cout << "live: ";
    for (const auto& x : p)
      cout << x << ' ';
    cout << '\n';
  }

template<typename P>
  void debug_pool(P&& p)
  {
    print_pool(p);
    print_queue(p);
    print_live(p);
    // print_live((const P&)p);
    cout << "-----\n";
  }


void check_node()
{
  pool_node<int> a;
  assert(!a);

  pool_node<int> b(0, 0, 3);
  assert(b);
  assert(b.get() == 3);
}

void
check_pool_insert_1()
{
  pool<int> p;
  assert(p.empty());

  size_t n = p.insert(10);
  assert(p.size() == 1);
  assert(p[n] == 10);
}

void
check_pool_insert_n()
{
  pool<int> p;
  vector<size_t> ns;
  for (int i = 0; i < 10; ++i)
    ns.push_back(p.insert(i));
  assert(p.size() == 10);
  for (int i = 0; i < 10; ++i)
    assert(p[ns[i]] == i);
}

void
check_pool_erase()
{
  pool<int> p;
  for (int i = 0; i < 10; ++i)
    p.insert(i);
  debug_pool(p);

  p.erase(9);
  assert(p.size() == 9);
  debug_pool(p);

  p.erase(3);
  assert(p.size() == 8);
  debug_pool(p);

  p.erase(1);
  assert(p.size() == 7);
  debug_pool(p);

  p.erase(7);
  assert(p.size() == 6);
  debug_pool(p);
}

void
check_pool_reuse()
{
  // Create a pool with 10 values and then erase every other.
  pool<int> p;
  for (int i = 0; i < 10; ++i)
    p.insert(i);
  for (int i = 0; i < 5; ++i)
    p.erase(2 * i);
  debug_pool(p);

  // Re-use the dead lists
  for (int i = 0; i < 5; ++i)
    p.insert(2 * i);
  debug_pool(p);

  // Add more stuff.
  for (int i = 0; i < 10; ++i)
    p.insert(10 + i);
  debug_pool(p);
}

// Erase elements left-to-right, and then re-build the list.
void 
check_pool_yoyo_lr()
{
  std::cout << "*** yoyo (lr) ***\n";
  pool<int> p;
  for (int i = 0; i < 10; ++i)
    p.insert(i);
  for (int i = 0; i < 10; ++i)
    p.erase(i);
  debug_pool(p);
  for (int i = 0; i < 10; ++i)
    p.insert(i);
  debug_pool(p);
}

void 
check_pool_yoyo_rl()
{
  std::cout << "*** yoyo (rl) ***\n";
  pool<int> p;
  for (int i = 0; i < 10; ++i)
    p.insert(i);
  for (int i = 0; i < 10; ++i)
    p.erase(10 - i - 1);
  debug_pool(p);
  for (int i = 0; i < 10; ++i)
    p.insert(i);
  debug_pool(p);
}


int main()
{
  check_node();
  check_pool_insert_1();
  check_pool_insert_n();
  check_pool_erase();
  check_pool_reuse();
  check_pool_yoyo_lr();
  check_pool_yoyo_rl();
}

#endif