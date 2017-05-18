/*
 * Vector2D.cpp
 *
 *  Created on: 12/05/2017
 *      Author: dante
 */
#include <fstream>

#include "2D/Vector2D.h"

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
  os << " " << rhs.x << " " << rhs.y;

  return os;
}

std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs)
{
  is >> lhs.x >> lhs.y;

  return is;
}


