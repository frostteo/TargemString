#include "stdafx.h"
#include "String.h"
#include <iomanip>

std::ostream &operator<<(std::ostream& output, const String& string)
{
  output << string.m_value->m_data;
  return output;
}

std::istream &operator>>(std::istream& input, String& string)
{
  static const int MAX_LENGTH = 100;

  char *temp = new char[MAX_LENGTH];
  input >> std::setw(MAX_LENGTH) >> temp;
  string = temp;
  return input;
}

String const operator+(const String& str1, const String& str2)
{
  int length = str1.size() + str2.size();
  char *sPtr = new char[length + 1] {0};

  strcpy_s(sPtr, length, str1.m_value->m_data);
  strcpy_s(sPtr + str1.size(), length, str2.m_value->m_data);
  sPtr[length] = '\0';
  return sPtr;
}

String::CharProxy::CharProxy(String& str, int index)
  : m_string(str),
  m_charIndex(index)
{

}

String::CharProxy& String::CharProxy::operator=(const CharProxy& rhs)
{
  if (m_string.m_value->isShared()) {
    m_string.m_value = new StringValue(m_string.m_value->m_data);
  }

  m_string.m_value->m_data[m_charIndex] = rhs.m_string.m_value->m_data[m_charIndex];
  return *this;
}

String::CharProxy& String::CharProxy::operator=(char c)
{
  if (m_string.m_value->isShared()) {
    m_string.m_value = new StringValue(m_string.m_value->m_data);
  }

  m_string.m_value->m_data[m_charIndex] = c;
  return *this;
}

String::CharProxy::operator char() const
{
  return m_string.m_value->m_data[m_charIndex];
}

char* String::CharProxy::operator&()
{
  if (m_string.m_value->isShared()) {
    m_string.m_value = new StringValue(m_string.m_value->m_data);
  }

  m_string.m_value->markUnshareable();
  return &(m_string.m_value->m_data[m_charIndex]);
}

const char* String::CharProxy::operator&() const
{
  return &(m_string.m_value->m_data[m_charIndex]);
}

void String::StringValue::init(const char* initValue)
{
  m_length = strlen(initValue);
  m_data = new char[m_length + 1];
  strcpy_s(m_data, m_length + 1, initValue);
  m_data[m_length] = '\0';
}

String::StringValue::StringValue(const char* value)
{
  init(value);
}

String::StringValue::StringValue(const StringValue& rhs)
{
  init(rhs.m_data);
}

String::StringValue::~StringValue()
{
  delete[] m_data;
}

String::String(const char* initValue) 
  : m_value(new StringValue(initValue))
{
  
}

const String::CharProxy String::operator[] (int index) const
{
  return CharProxy(const_cast<String&>(*this), index);
}

String::CharProxy String::operator[] (int index)
{
  return CharProxy(*this, index);
}

int String::size() const
{
  return m_value->m_length;
}

bool String::operator<(const String &right) const
{
  return strcmp(m_value->m_data, right.m_value->m_data) < 0;
}

bool String::operator<=(const String &right) const
{
  return strcmp(m_value->m_data, right.m_value->m_data) <= 0;
}

bool String::operator>(const String &right) const
{
  return strcmp(m_value->m_data, right.m_value->m_data) > 0;
}

bool String::operator>=(const String &right) const
{
  return strcmp(m_value->m_data, right.m_value->m_data) >= 0;
}

bool String::operator==(const String &right) const
{
  return strcmp(m_value->m_data, right.m_value->m_data) == 0;
}

bool String::operator!=(const String &right) const
{
  return strcmp(m_value->m_data, right.m_value->m_data) != 0;
}

const String& String::operator = (const String& rhs)
{
  if (this == &rhs)
    return *this;

  m_value = rhs.m_value;
  return *this;
}

bool String::caseInsensitiveLessOrEqual(const String& rhs) const
{
  return strcmpciportable(m_value->m_data, rhs.m_value->m_data) <= 0;
}