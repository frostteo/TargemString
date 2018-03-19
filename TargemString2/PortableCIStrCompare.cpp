#include "stdafx.h"
#include "PortableCIStrCompare.h"
 
int strcmpciportable(const char* lhs, const char* rhs)
{
  if (lhs == nullptr)
    throw std::invalid_argument("lhs must be not null");

  if (rhs == nullptr)
    throw std::invalid_argument("rhs must be not null");

  const int LESSER = -1;
  const int GREATER = 1;
  const int EQUAL = 0;

  int lhsLength = strlen(lhs);
  int rhsLength = strlen(rhs);
  int maxLength = std::max(lhsLength, rhsLength);

  for (int i = 0; i < maxLength; ++i)
  {
    int lowerCharLeft = std::tolower(static_cast<int>(lhs[i]));
    int lowerCharRight = std::tolower(static_cast<int>(rhs[i]));

    if (lowerCharLeft < lowerCharRight)
      return LESSER;

    if (lowerCharLeft > lowerCharRight)
      return GREATER;
  }

  if (lhsLength < rhsLength)
    return LESSER;

  if (lhsLength > rhsLength)
    return GREATER;

  return EQUAL;
}