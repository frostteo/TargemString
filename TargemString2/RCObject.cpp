#include "stdafx.h"
#include "RCObject.h"


RCObject::RCObject() 
  : m_refCount(0), 
  m_shareable(true)
{
}

RCObject::RCObject(const RCObject& rhs)
  : m_refCount(0),
  m_shareable(true)
{
}

RCObject& RCObject::operator= (const RCObject& rhs)
{
  return *this;
}

RCObject::~RCObject()
{
}

void RCObject::addReference()
{
  ++m_refCount;
}

void RCObject::removeReference()
{
  if (--m_refCount == 0)
  {
    delete this;
  }
}

void RCObject::markUnshareable()
{
  m_shareable = false;
}

bool RCObject::isShareable() const
{
  return m_shareable;
}

bool RCObject::isShared() const
{
  return m_refCount > 1;
}
