#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r, std::vector<T>(c, T())) {}
  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.rows) {}
  ~Matrix() { rows.clear(); }

  Matrix<T> & operator=(const Matrix<T> & rhs);

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert((0 <= index) && (index < numRows));
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert((0 <= index) && (index < numRows));
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const;

  Matrix<T> operator+(const Matrix<T> & rhs) const;

  template<typename Y>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<Y> & rhs);
};

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  return (numRows == rhs.numRows) && (numColumns == rhs.numColumns) && (rows == rhs.rows);
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  Matrix<T> ans(numRows, numColumns);
  typename std::vector<std::vector<T> >::iterator it1 = ans.rows.begin();
  typename std::vector<std::vector<T> >::const_iterator it2 = rows.begin();
  typename std::vector<std::vector<T> >::const_iterator it3 = rhs.rows.begin();
  while (it1 != ans.rows.end()) {
    typename std::vector<T>::iterator it11 = it1->begin();
    typename std::vector<T>::const_iterator it22 = it2->begin();
    typename std::vector<T>::const_iterator it33 = it3->begin();
    while (it11 != it1->end()) {
      *it11 = *it22 + *it33;
      ++it11;
      ++it22;
      ++it33;
    }
    ++it1;
    ++it2;
    ++it3;
  }
  return ans;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[";
  if (rhs.numColumns == 0) {
  }
  else {
    typename std::vector<std::vector<T> >::const_iterator it0 = rhs.rows.begin();
    while (it0 != rhs.rows.end()) {
      if (it0 != rhs.rows.begin()) {
        s << ",\n{";
      }
      else {
        s << "{";
      }
      typename std::vector<T>::const_iterator it00 = it0->begin();
      while (it00 != it0->end()) {
        if (it00 != it0->begin()) {
          s << ", ";
        }
        s << *it00;
        ++it00;
      }
      s << "}";
      ++it0;
    }
  }
  s << " ]";
  return s;
}

#endif
