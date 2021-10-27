#pragma once

#include <cstddef>

class Vector {
public:
  using value_type = double;
  using size_type = std::size_t;

private:
  // initialize members with meaningful values: IMPORTANT
  size_type _size = 0;
  value_type *_data = nullptr;

public:
  // default constructor
  Vector();
  // constructor to initialize count elements with value
  Vector(size_type, const value_type &);

  // copy constructor
  Vector(const Vector &);
  // move constructor
  Vector(Vector &&);
  // destructor
  ~Vector();

  value_type *data();
  size_type size();
  value_type &operator[](size_type);
};