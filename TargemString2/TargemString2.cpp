// TargemString2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include <algorithm>
#include <vector>

void outputString(const String &str)
{
  std::cout << str << std::endl;
}

bool greater(const String &str1, const String &str2)
{
  return str1.caseInsensitiveGreater(str2);
}

std::vector<String> descendingStringSort(char * arr[], int arrLength)
{
  std::vector<String> strVector(arr, arr + arrLength);

  std::cout << "initial order: " << std::endl;
  std::for_each(strVector.begin(), strVector.end(), outputString);

  std::sort(strVector.begin(), strVector.end(), greater);
  std::cout << std::endl << "after sorting: " << std::endl;
  std::for_each(strVector.begin(), strVector.end(), outputString);

  return strVector;
}

int main(int argc, char * argv[])
{
  descendingStringSort(argv + 1, argc - 1);
  system("pause");

	return 0;
}

