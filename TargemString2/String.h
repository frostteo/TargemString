#pragma once

#include "RCObject.h"
#include "RCPtr.h"
#include <string>
#include <iostream>

class String
{
  friend std::ostream &operator<<(std::ostream& output, const String& string);
  friend std::istream &operator>>(std::istream& input, String& string);
  friend const String operator+(const String& str1, const String& str2);

  friend class CharProxy;
public:
  class CharProxy
  {
  public:
    CharProxy(String& str, int index);
    CharProxy& operator=(const CharProxy& rhs);
    CharProxy& operator=(char c);
    operator char() const;
    char* operator&();
    const char* operator&() const;

  private:
    String& m_string;
    int m_charIndex;
  };
 
public:
  String(const char* value = "");
  const CharProxy operator[](int index) const;
  CharProxy operator[](int index);

  bool operator==(const String &) const;
  bool operator!=(const String &) const;
  bool operator<(const String &) const;
  bool operator<=(const String &) const;
  bool operator>(const String &) const;
  bool operator>=(const String &) const;

  int size() const;
private:
  struct StringValue : public RCObject
  {
    int m_length;
    char* m_data;
    StringValue(const char* initValue);
    StringValue(const StringValue& rhs);
    void init(const char* initValue);
    ~StringValue();
  };

private:
  RCPtr<StringValue> m_value;
};

