//
// Created by LI YANZHE on 2019-03-19.
//

#ifndef LYZTOYS_BITINDEX_VECTOR_H
#define LYZTOYS_BITINDEX_VECTOR_H

#include <memory>

namespace lyz {

template<class _Tp, class _Allocator = std::allocator<_Tp> >
class bitindex_vector {
 public:
  typedef _Allocator allocator_type;
  typedef typename _Allocator::value_type value_type;
  typedef typename _Allocator::reference reference;
  typedef typename _Allocator::const_reference const_reference;
  typedef typename _Allocator::difference_type difference_type;
  typedef typename _Allocator::size_type size_type;

  class iterator {
   public:
    typedef typename _Allocator::difference_type difference_type;
    typedef typename _Allocator::value_type value_type;
    typedef typename _Allocator::reference reference;
    typedef typename _Allocator::pointer pointer;
    typedef std::random_access_iterator_tag iterator_category; //or another tag

    iterator();
    iterator(const iterator &);
    ~iterator();

    iterator &operator=(const iterator &);
    bool operator==(const iterator &) const;
    bool operator!=(const iterator &) const;
//    bool operator<(const iterator &) const; //optional
//    bool operator>(const iterator &) const; //optional
//    bool operator<=(const iterator &) const; //optional
//    bool operator>=(const iterator &) const; //optional

    iterator &operator++();
//    iterator operator++(int); //optional
//    iterator &operator--(); //optional
//    iterator operator--(int); //optional
//    iterator &operator+=(size_type); //optional
//    iterator operator+(size_type) const; //optional
//    friend iterator operator+(size_type, const iterator &); //optional
//    iterator &operator-=(size_type); //optional
//    iterator operator-(size_type) const; //optional
//    difference_type operator-(iterator) const; //optional

    reference operator*() const;
    pointer operator->() const;
//    reference operator[](size_type) const; //optional
  };
  class const_iterator {
   public:
    typedef typename _Allocator::difference_type difference_type;
    typedef typename _Allocator::value_type value_type;
    typedef typename _Allocator::reference const_reference;
    typedef typename _Allocator::pointer const_pointer;
    typedef std::random_access_iterator_tag iterator_category; //or another tag

    const_iterator();
    const_iterator(const const_iterator &);
    explicit const_iterator(const iterator &);
    ~const_iterator();

    const_iterator &operator=(const const_iterator &);
    bool operator==(const const_iterator &) const;
    bool operator!=(const const_iterator &) const;
//    bool operator<(const const_iterator &) const; //optional
//    bool operator>(const const_iterator &) const; //optional
//    bool operator<=(const const_iterator &) const; //optional
//    bool operator>=(const const_iterator &) const; //optional

    const_iterator &operator++();
//    const_iterator operator++(int); //optional
//    const_iterator &operator--(); //optional
//    const_iterator operator--(int); //optional
//    const_iterator &operator+=(size_type); //optional
//    const_iterator operator+(size_type) const; //optional
//    friend const_iterator operator+(size_type, const const_iterator &); //optional
//    const_iterator &operator-=(size_type); //optional
//    const_iterator operator-(size_type) const; //optional
//    difference_type operator-(const_iterator) const; //optional

    const_reference operator*() const;
    const_pointer operator->() const;
//    const_reference operator[](size_type) const; //optional
  };

//  typedef std::reverse_iterator<iterator> reverse_iterator; //optional
//  typedef std::reverse_iterator<const_iterator> const_reverse_iterator; //optional

  bitindex_vector();
  bitindex_vector(const bitindex_vector &);
  ~bitindex_vector();

  bitindex_vector &operator=(const bitindex_vector &);
  bool operator==(const bitindex_vector &) const;
  bool operator!=(const bitindex_vector &) const;
//  bool operator<(const bitindex_vector &) const; //optional
//  bool operator>(const bitindex_vector &) const; //optional
//  bool operator<=(const bitindex_vector &) const; //optional
//  bool operator>=(const bitindex_vector &) const; //optional

  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;
//  reverse_iterator rbegin(); //optional
//  const_reverse_iterator rbegin() const; //optional
//  const_reverse_iterator crbegin() const; //optional
//  reverse_iterator rend(); //optional
//  const_reverse_iterator rend() const; //optional
//  const_reverse_iterator crend() const; //optional

//  reference front(); //optional
//  const_reference front() const; //optional
//  reference back(); //optional
//  const_reference back() const; //optional
//  template<class ...Args>
//  void emplace_front(Args...); //optional
//  template<class ...Args>
//  void emplace_back(Args...); //optional
//  void push_front(const _Tp &); //optional
//  void push_front(_Tp &&); //optional
//  void push_back(const _Tp &); //optional
//  void push_back(_Tp &&); //optional
//  void pop_front(); //optional
//  void pop_back(); //optional
//  reference operator[](size_type); //optional
//  const_reference operator[](size_type) const; //optional
//  reference at(size_type); //optional
//  const_reference at(size_type) const; //optional

//  template<class ...Args>
//  iterator emplace(const_iterator, Args...); //optional
//  iterator insert(const_iterator, const _Tp &); //optional
//  iterator insert(const_iterator, _Tp &&); //optional
//  iterator insert(const_iterator, size_type, _Tp &); //optional
//  template<class iter>
//  iterator insert(const_iterator, iter, iter); //optional
//  iterator insert(const_iterator, std::initializer_list<_Tp>); //optional
//  iterator erase(const_iterator); //optional
//  iterator erase(const_iterator, const_iterator); //optional
//  void clear(); //optional
//  template<class iter>
//  void assign(iter, iter); //optional
//  void assign(std::initializer_list<_Tp>); //optional
//  void assign(size_type, const _Tp &); //optional

  void swap(bitindex_vector &);
  size_type size();
  size_type max_size();
  bool empty();

//  _Allocator get_allocator(); //optional
};
//template<class _Tp, class _Allocator = std::allocator<_Tp> >
//void swap(bitindex_vector<_Tp, _Allocator> &, bitindex_vector<_Tp, _Allocator> &); //optional

}

#endif //LYZTOYS_BITINDEX_VECTOR_H
