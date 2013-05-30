// Copyright (c) 2008-2010 Kent State University
// Copyright (c) 2011-2012 Texas A&M University
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

namespace origin
{
  namespace adjacency_list_impl
  {
    template<typename T> class pool_node;
    template<typename T> class pool_iterator;

    // ---------------------------------------------------------------------- //
    //                                 Pool
    //
    // The node pool is the basis for the vertex and edge sets in the adjacency
    // list data structure. The data structure is a cross between a vector and
    // an object pool in that removing elements from the pool do not cause any
    // additional data movements. Insertions into the pool always reuse a free
    // (previously erased) index in the pool.
    //
    // The pool provides one other useful feature: iteration. The elements of
    // the pool can be traversed in time proportional to the number of elements.
    // Traversal skips deleted elements by jumping over the "dead" locations in
    // the pool. This is done by creating a linked list rather than using a
    // filtering technique.
    //
    // The data structure functions like normal vector until an object is
    // erased. When erased, the object is cleared, and its index is added to the
    // free index list, which is actually a min-queue. When a new object is
    // inserted, the least index is taken from the queue and used as the
    // location for the new object. The new object is woven into the linked
    // list of live nodes in constant time. Re-linking list to incorporate the
    // new node is done in constant time.
    //
    // Because the free index list is a min-queue, we always return the first
    // unoccuped index. Unless that index is 0, we are guaranteed that the
    // next lower index is occupied, and we can thus re-link the list based on
    // its pointers. If the returned index is 0, we rely simply use the head
    // pointer to find the first non-empty index and re-link the list with the
    // new element at the head.
    //
    // Performance properties:
    //    - Insertion: O(log2 d)
    //    - Erasure: O(log2 d)
    // Where d is the number of deleted nodes in the pool.
    //
    // This data structure has some similarity to conventional object pools
    // except that it doesn't really allocate memory, and it has additional
    // requirements. In particular, it must maintain the correspondence between
    // indices and the objects that they are mapped to. We also have to
    // provide efficient iteration over elements in the pool.
    template<typename T>
      class pool
      {
        friend class pool_iterator<T>;
        friend class pool_iterator<const T>;
      public:
        using value_type = T;
        using node_type = pool_node<T>;

        using iterator       = pool_iterator<T>;
        using const_iterator = pool_iterator<const T>;

        using list_type = std::vector<node_type>;
        using queue_type = std::priority_queue<std::size_t, 
                                               std::vector<std::size_t>, 
                                               std::greater<size_t>>;

        static constexpr std::size_t npos = node_type::npos;

        // Observers
        bool empty() const;
        std::size_t size() const;

        // Debugging and Testing
        // These are not part of the general interface. They are provided
        // solely for the purposes of debugging and testing.
        const list_type& data() const;
        const queue_type& free() const;
        
        // Capacity
        std::size_t capacity() const;
        void reserve(std::size_t n);

        // Element access
        T&       operator[](std::size_t n);
        const T& operator[](std::size_t n) const;

        // Insert
        std::size_t insert(T&& x);
        std::size_t insert(const T& x);
        template<typename... Args> std::size_t emplace(Args&&... args);

        // Erase
        void erase(std::size_t x);
        void clear();

        // Iterators
        iterator begin() { return iterator(this, head_); }
        iterator end()   { return iterator(this, npos); }
        
        const_iterator begin() const { return const_iterator(this, head_); }
        const_iterator end() const   { return const_iterator(this, npos); }

      private:
        // Node access and properties
        node_type&       node(std::size_t n)       { return nodes_[n]; }
        const node_type& node(std::size_t n) const { return nodes_[n]; }
        
        node_type&       head()       { return node(head_); }
        const node_type& head() const { return node(head_); }
        
        node_type&       tail()       { return node(tail_); }
        const node_type& tail() const { return node(tail_); }
        
        node_type&       next(node_type& p)             { return node(p.next); }
        const node_type& next(const node_type& p) const { return node(p.next); }

        node_type&       prev(node_type& p)             { return node(p.prev); }
        const node_type& prev(const node_type& p) const { return node(p.prev); }
        
        // Return the index of the given node.
        std::size_t index(const node_type& p) const { return &p - &node(0); }

        // Returns true if the node n is alive.
        bool alive(std::size_t n) const { return node(n).valid(); }

        // Insertion functions
        // These functions have their arguments forwarded as parameter packs
        // so I don't have to implement different versions of the same logic
        // for copy insertion, move insertion, and emplacement. It's a pain,
        // and it's gross, but it should be fast.
        template<typename... Args> std::size_t append(Args&&... x);
        template<typename... Args> void append_empty(Args&&... x);
        template<typename... Args> void append_nonempty(std::size_t n, Args&&... x);

        template<typename... Args> std::size_t reuse(Args&&... x);
        template<typename... Args> void reuse_front(Args&&... x);
        template<typename... Args> void reuse_middle(std::size_t n, Args&&... x);
        template<typename... Args> void reuse_end(std::size_t n, Args&&... x);

        std::size_t take();

        // Erase functions
        void reset(std::size_t n);
        void reset_head(std::size_t n);
        void reset_tail(std::size_t n);
        void reset_middle(std::size_t n);
        void recycle(std::size_t n);

      private:

        list_type  nodes_; // The actual node vector
        queue_type free_;  // The free index list
        std::size_t head_; // Head of the live node list
        std::size_t tail_; // Tail of the live node list
      };

    // Returns true if the pool contains no nodes.
    template<typename T>
      inline bool
      pool<T>::empty() const { return size() == 0; }

    // Returns the number of nodes contained in the pool.
    template<typename T>
      inline std::size_t
      pool<T>::size() const { return nodes_.size() - free_.size(); }

    // Returns the objects in the data pool.
    template<typename T>
      inline auto
      pool<T>::data() const -> const list_type& { return nodes_; }

    // Returns the free index list.
    template<typename T>
      inline auto
      pool<T>::free() const -> const queue_type& { return free_; }

    // Returns the capacity allocated to the pool.
    template<typename T>
      inline std::size_t
      pool<T>::capacity() const { return nodes_.capacity(); }

    // Reserve at least n objects of capacity.
    template<typename T>
      inline void
      pool<T>::reserve(std::size_t n) { nodes_.reserve(n); }

    // Returns a reference to the element in the nth position. This function
    // results in undefined behavior if the element at the nth position has been
    // previously erased.
    template<typename T>
      inline T&
      pool<T>::operator[](std::size_t n)
      {
        assert(alive(n));
        return nodes_[n].get();
      }

    template<typename T>
      inline const T&
      pool<T>::operator[](std::size_t n) const
      {
        assert(alive(n));
        return nodes_[n].get();
      }

    // Move inser the value x into the pool.
    template<typename T>
      inline std::size_t
      pool<T>::insert(T&& x)
      {
        if (free_.empty())
          return append(std::move(x));
        else
          return reuse(std::move(x));
      }

    // Copy the value x into the vector. If there are dead indices, reuse
    // one. Otherwise, append the vertex.
    template<typename T>
      inline std::size_t
      pool<T>::insert(const T& x)
      {
        if (free_.empty())
          return append(x);
        else 
          return reuse(x);
      }

    template<typename T>
      template<typename... Args>
      inline std::size_t
      pool<T>::emplace(Args&&... args)
      {
        if (free_.empty())
          return append(std::forward<Args>(args)...);
        else
          return reuse(std::forward<Args>(args)...);
      }



    // Insert the value x at the end of the node list, returning the index
    // at which the object was stored.
    template<typename T>
      template<typename... Args>
        inline std::size_t
        pool<T>::append(Args&&... args)
        {
          std::size_t n = nodes_.size();
          if (nodes_.empty())
            append_empty(std::forward<Args>(args)...);
          else
            append_nonempty(n, std::forward<Args>(args)...);
          return n;
        }

    // Insert the value x into the front of the node list. This happens only
    // when the pool is completely empty.
    template<typename T>
      template<typename... Args>
        inline void
        pool<T>::append_empty(Args&&... args)
        {
          nodes_.emplace_back(0, 0, std::forward<Args>(args)...);
          head_ = 0;
          tail_ = 0;
        }

    // Insert the value x into the list. This corresponds to thje following
    // layout.
    //
    //    h ... t x
    //
    // Here, h is followed by 0 or more live nodes, and we are inserting into
    // x. There are no free indexes in the pool. Note that n == nodes_.size(),
    // whichn is the index of x.
    template<typename T>
      template<typename... Args>
        inline void
        pool<T>::append_nonempty(std::size_t n, Args&&... args)
        {
          nodes_.emplace_back(tail_, n, std::forward<Args>(args)...);
          tail().next = n;
          tail_ = n;
        }


    // Reuse a free index to store the object x.
    template<typename T>
      template<typename... Args>
        inline std::size_t
        pool<T>::reuse(Args&&... args)
        {
          std::size_t n = take();
          if (n == 0)
            reuse_front(std::forward<Args>(args)...);
          else if (n < tail_)
            reuse_middle(n, std::forward<Args>(args)...);
          else
            reuse_end(n, std::forward<Args>(args)...);
          return n;
        }

    // Reuse the free index at the front of the pool. This corresponds to the
    // following layout.
    //
    //  p ... h ... t
    //
    // Here, the first free index (the node p) is succeeded by some number of
    // live or dead nodes, which is in turn succeeded by h.
    //
    // There is a special case when there are no live nodes. Here, we simply
    // overwrite the initial element. Here, we make p the both the head and
    // the tail.
    template<typename T>
      template<typename... Args>
        inline void
        pool<T>::reuse_front(Args&&... args)
        {
          node_type& p = node(0);
          if (head_ != npos) {
            p.assign(0, head_, std::forward<Args>(args)...);
            head().prev = 0;
            head_ = 0;
          } else {
            p.assign(0, 0, std::forward<Args>(args)...);
            head_ = 0;
            tail_ = 0;
          }
        }



    // Reuse a free index in the middle of the pool. This corresponds to the
    // pool layout:
    //
    //    h ... q p ... r
    //
    // The first free index, p, succeeds the head and preceeds the tail by some
    // number of live objects. Note that the node at n - 1 is always a live
    // object, q. Otherwise, n would not be the least free index. The next
    // live object, r, is directly accessible from q.
    template<typename T>
      template<typename... Args>
        inline void
        pool<T>::reuse_middle(std::size_t n, Args&&... args)
        {
          node_type& p = node(n);
          node_type& q = node(n - 1);
          node_type& r = next(q);
          p.assign(n - 1, q.next, std::forward<Args>(args)...);
          q.next = n;
          r.prev = n;
        }

    // Reuse the free index at the end of the pool. This corresponds to the
    // pool layout:
    //
    //   h ... t x
    //
    // We are reusing the first - and T is the tail. There are two things to
    // observe here. First, t is preceeded by zero or more live objects. In
    // other words, there are no free indexes before t. The case where h == t is
    // also possible. Second, it is always the case that n == t + 1 (I'm not
    // sure what that knowledge buys me though).
    template<typename T>
      template<typename... Args>
        inline void
        pool<T>::reuse_end(std::size_t n, Args&&... args)
        {
          node_type& p = node(n);
          p.assign(tail_, n, std::forward<Args>(args)...);
          tail().next = n;
          tail_ = n;
        }

    // Take the next free index from the free list.
    template<typename T>
      inline std::size_t
      pool<T>::take()
      {
        std::size_t n = free_.top();
        free_.pop();
        return n;
      }

    // Erase the element at the nth position in the pool, returning the index
    // n to the free list. If that element is not alive, do nothing.
    template<typename T>
      inline void
      pool<T>::erase(std::size_t n)
      {
        assert(n < nodes_.size());
        if (alive(n)) {
          reset(n);
        }
      }

    // Reset the node at the nth position, depending on the value of n.
    template<typename T>
      inline void
      pool<T>::reset(std::size_t n)
      {
        if (n == head_)
          reset_head(n);
        else if (n == tail_)
          reset_tail(n);
        else
          reset_middle(n);
      }

    // Reset the head node. This corresponds to the following layout.
    //
    //    ... x/h ... p
    //
    // Here, x is the node being erased and x == h. x is follwed by zero or
    // or more live live or dead nodes. Note that there can be no live nodes
    // preceeding h, but any number of dead nodes is possible. Here, we
    // advance h to the next live node. h is followed by at least one live
    // node, which becomes the new head.
    //
    //    ... p/h ...
    //
    // There is a special case when h == t, corresponding to the erasure of
    // the last live node. Both h and t are set to npos.
    template<typename T>
      inline void
      pool<T>::reset_head(std::size_t n)
      {
        if (head_ != tail_) {
          node_type& p = next(head());
          p.prev = head().next;
          head_ = head().next;
        } else {
          head_ = tail_ = npos;
        }
        recycle(n);
      }

    // Reset the node at the the tail of the live node list. This corresponds
    // to the following layout:
    //
    //    h * p t
    //
    // Note that there must be a previous element. If there is not, then
    // we must be removing the head, which is handled by reset_head. The 
    // previous live node is made the new tail.
    template<typename T>
      inline void
      pool<T>::reset_tail(std::size_t n)
      {
        node_type& p = prev(tail());
        p.next = tail().prev;
        tail_ = tail().prev;
        recycle(n);
      }

    // Reset a node in the middle of the live node list.
    //
    // Note that both the next and previos nodes must be valid. If not, the
    // node at the nth position would be either the head or the tail.
    template<typename T>
      inline void
      pool<T>::reset_middle(std::size_t n)
      {
        node_type& p = node(n); 
        prev(p).next = p.next;
        next(p).prev = p.prev;
        recycle(n);
      }

    // Finally destroy the node at the nth position and return its index to the
    // free index list.
    template<typename T>
      inline void
      pool<T>::recycle(std::size_t n)
      {
        node(n).reset();
        free_.push(n);
      }

    // Reset the pool to its initial state.
    template<typename T>
      inline void
      pool<T>::clear()
      {
        // std::priority_queue does not have clear() method, so we have to
        // reset it by brute force.
        free_ = std::move(queue_type());
        nodes_.clear();
      }


    // ---------------------------------------------------------------------- //
    //                                Pool Node
    //
    // A pool node is a mix between an optional type and a linked list node.
    // The prev and next fields refer to the corresponding "live" nodes in a
    // pool. The data buffer stores a possibly initialized value.
    //
    // A node is uninitialized when either of prev or next is the same as
    // limit (i.e., size_t(-1)).
    template<typename T>
      class pool_node
      {
      public:
        static constexpr std::size_t npos = -1;

        pool_node();

        // Forwarding constructor
        template<typename... Args>
          pool_node(std::size_t p, std::size_t n, Args&&... args);


        ~pool_node();

        explicit operator bool() const { return valid(); }

        // Returns true if the object is initialized.
        bool valid() const;

        // Returns a pointer to the stored object.
        T*       ptr();
        const T* ptr() const;

        // Returns a reference to the stored object.
        T&       get();
        const T& get() const;

        // Assign and reset
        template<typename... Args>
          void assign(std::size_t p, std::size_t n, Args&&... args);

        void reset();
        void destroy();

        std::size_t prev;
        std::size_t next;
        Aligned_storage<sizeof(T), alignof(T)> data;
      };

    template<typename T>
      pool_node<T>::pool_node() : prev(npos), next(npos) { }

    template<typename T>
      template<typename... Args>
        pool_node<T>::pool_node(std::size_t p, std::size_t n, Args&&... args)
          : prev(p), next(n)
        {
          new (&data) T(std::forward<Args>(args)...);
        }

    template<typename T>
      pool_node<T>::~pool_node() { destroy(); }

    template<typename T>
      inline bool
      pool_node<T>::valid() const { return next != npos; }

    template<typename T>
      inline T*
      pool_node<T>::ptr() 
      { 
        assert(valid());
        return reinterpret_cast<T*>(&data); 
      }

    template<typename T>
      inline const T*
      pool_node<T>::ptr() const 
      { 
        assert(valid());
        return reinterpret_cast<const T*>(&data); 
      }

    template<typename T>
      inline T&
      pool_node<T>::get() { return *ptr(); }

    template<typename T>
      inline const T&
      pool_node<T>::get() const { return *ptr(); }

    template<typename T>
      template<typename... Args>
        inline void
        pool_node<T>::assign(std::size_t p, std::size_t n, Args&&... args)
        {
          prev = p;
          next = n;
          destroy();
          new (&data) T(std::forward<Args>(args)...);
        }

    template<typename T>
      inline void
      pool_node<T>::reset()
      {
        assert(valid());
        get().~T();
        prev = next = npos;
      }

    template<typename T>
      inline void
      pool_node<T>::destroy()
      {
        if (valid())
          get().~T();
      }


    // ---------------------------------------------------------------------- //
    //                             Pool Iterator
    //
    // A forward iterator over the elements in a pool.
    //
    // NOTE: This could be a bidirectional iterator, but we'd have to make some
    // changes to the pool to accommodate that modification. In particular, we
    // would have to have an extra object serving explicitly as the "end"
    // so that we can decrement it to reach the last element. Because the
    // current implementation uses a self-looped link to terminate the live
    // node list, we can't effectively define an "end" position.
    template<typename T>
      class pool_iterator
      {
      public:
        using value_type = Remove_const<T>;
        using pool_type = If<Const<T>(), const pool<value_type>, pool<value_type>>;
        using node_type = If<Const<T>(), const pool_node<value_type>, pool_node<value_type>>;

        pool_iterator();
        pool_iterator(pool_type* p, std::size_t i);

        // Const conversion.
        template<typename U>
          pool_iterator(const pool_iterator<U>& x)
            : p_(x.container()), i_(x.index())
          { }

        // Returns the pool being iterated over.
        pool_type* container() const { return p_; }

        // Returns the current index of the iterator.
        std::size_t index() const { return i_; }

        T& operator*() const;
        T* operator->() const;

        bool operator==(const pool_iterator& x) const;
        bool operator!=(const pool_iterator& x) const;

        pool_iterator& operator++();
        pool_iterator  operator++(int);

      private:
        void incr();
      
      public:
        pool_type*  p_; // The pool
        std::size_t i_; // The current index
      };

    template<typename T>
      inline
      pool_iterator<T>::pool_iterator()
        : p_(nullptr), i_(-1)
      { }

    template<typename T>
      inline
      pool_iterator<T>::pool_iterator(pool_type* p, std::size_t i)
        : p_(p), i_(i)
      { }

    template<typename T>
      inline T&
      pool_iterator<T>::operator*() const
      {
        return p_->node(i_).get();
      }

    template<typename T>
      inline T*
      pool_iterator<T>::operator->() const
      {
        return p_->node(i_).get();
      }

    template<typename T>
      inline bool
      pool_iterator<T>::operator==(const pool_iterator& x) const
      {
        assert(p_ == x.p_);
        return i_ == x.i_;
      }

    template<typename T>
      inline bool
      pool_iterator<T>::operator!=(const pool_iterator& x) const
      {
        return !operator==(x);
      }

    template<typename T>
      inline pool_iterator<T>&
      pool_iterator<T>::operator++()
      {
        incr();
        return *this;
      }

    template<typename T>
      inline pool_iterator<T>
      pool_iterator<T>::operator++(int)
      {
        pool_iterator tmp = *this;
        incr();
        return tmp;
      }

    template<typename T>
      inline void
      pool_iterator<T>::incr() 
      {
        const node_type& n = p_->node(i_);
        i_ = (n.next == i_ ? pool_node<T>::npos : n.next);
      }

  } // namespace adjacency_list_impl
} // namespace origin
