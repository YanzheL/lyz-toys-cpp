//
// Created by LI YANZHE on 2019-03-19.
//

#include "bitindex_vector.h"

using namespace lyz;
using namespace std;

template<class _Tp, class _BitSet, class _Allocator, class _Set>
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
reference::
reference(const size_type pos, const int pack_size, const _Set &atoms, _BitSet &parent) :
    parent(parent),
    real_pos(pos*pack_size),
    pack_size(pack_size),
    atoms(atoms) {
  size_type idx = pos*pack_size;
  for (int p = 0; p < pack_size; ++p) {
    size_type bit = (parent[idx + p]) << p;
    atom_idx |= bit;
  }
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
reference::
operator _Tp() const {
  auto it = atoms.begin();
  std::advance(it, atom_idx);
  return *it;
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
typename bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::reference &
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
reference::
operator=(_Tp x) {
  __do_assign(x);
  return *this;
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
typename bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::reference &
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
reference::
operator=(const reference &rhs) {
  const _Tp item = rhs;
  __do_assign(item);
  return *this;
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
void
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
reference::
__do_assign(_Tp item) {
  size_type new_atom_idx = std::distance(atoms.begin(), atoms.find(item));
  if (new_atom_idx!=atoms.size()) {
    atom_idx = new_atom_idx;
    for (int p = 0; p < pack_size; ++p) {
      bool bit = (bool) (atom_idx & (1L << p));
//                    std::cout << "i = " << idx << " bit = " << bit << " p = " << p << std::endl;
      parent[real_pos + p] = bit;
    }
  }
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
bitindex_vector(const _Set &atoms) : __atoms_(atoms) {
  size_type atom_size = atoms.size();
  while (1 << __pack_size_ < atom_size)
    ++__pack_size_;
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
bitindex_vector(const size_type n, const _Set &atoms): bitindex_vector(
    atoms) {
  __bits_.reserve(n*__pack_size_);
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
template<class _InputIterator>
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
bitindex_vector(_InputIterator __first, _InputIterator __last, const _Set &atoms):
    bitindex_vector(std::distance(__first, __last), atoms) {
  for (auto it = __first; it!=__last; ++it)
    push_back(*it);
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
void
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
push_back(const _Tp &item) {
  size_type atom_idx = std::distance(__atoms_.begin(), __atoms_.find(item));
  __push_back(atom_idx);
}

template<class _Tp, class _BitSet, class _Allocator, class _Set>
typename bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::reference
bitindex_vector<_Tp, _BitSet, _Allocator, _Set>::
operator[](size_type i) {
  return reference(i, __pack_size_, __atoms_, __bits_);
}