#include "vector.hpp"
#include<cstring>
#include<iostream>

// default constructor
Vector::Vector() {}
// Constructor
Vector::Vector(size_type size, const value_type &value): _size(size), _data(new Vector::value_type[size]) 
{
  for (std::size_t i = 0; i < _size; ++i) 
  {
    _data[i] = value;
  }
}
// access to raw pointer to the data
Vector::value_type *Vector::data() { return _data; }
// get the number of elements stored in the vector
Vector::size_type Vector::size() { return _size; }
// access an element of the vector
Vector::value_type &Vector::operator[](size_type pos) { return _data[pos]; }

// -------------------- YOUR IMPLEMENTATION STARTS HERE ---------------------
// copy constructor
Vector::Vector(const Vector &other): _size(other._size), _data(new Vector::value_type[other._size])
{
  // because of the _size has been copied already _size(other._size)
  // so we only need to copy the _data memeber
  std::copy(other._data, other._data + _size, _data);
}

//move constructor
Vector::Vector(Vector &&other): _size(0), _data(nullptr)
{
  // move data to new object

  // or use the following or directly use the _size(other._size) before constructor execute
  _size = other._size;

  _data = other._data;

  // release old object
  other._data = nullptr;
  other._size = 0;

}

// destructor
Vector::~Vector()
{
  // only the member _data needed be released because it's a pointer while the member _size is not;
  if(_data != nullptr)
  {
    delete[] _data;
  }
}
