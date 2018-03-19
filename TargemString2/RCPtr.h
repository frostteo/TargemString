#ifndef __RC_PTR_
#define __RC_PTR_

template<class T>
class RCPtr
{
public:
  RCPtr(T* realPtr = 0);
  RCPtr(const RCPtr& rhs);
  ~RCPtr();
  RCPtr& operator=(const RCPtr& rhs);
  T* operator->() const;
  T& operator*() const;
private:
  T* m_pointee;
  void init();
};

#endif // __RC_PTR_

template<class T>
void RCPtr<T>::init()
{
  if (m_pointee == nullptr) 
    return;

  if (m_pointee->isShareable() == false) {
    m_pointee = new T(*m_pointee);
  }

  m_pointee->addReference();
}

template<class T>
RCPtr<T>::RCPtr(T* realPtr) : m_pointee(realPtr)
{
  init();
}

template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs) : m_pointee(rhs.m_pointee)
{
  init();
}

template<class T>
RCPtr<T>::~RCPtr()
{
  if (m_pointee)
    m_pointee->removeReference();
}

template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
  if (m_pointee != rhs.m_pointee)
  {
    T* oldPointee = m_pointee;
    m_pointee = rhs.m_pointee;
    init();

    if (oldPointee)
      oldPointee->removeReference();
  }

  return *this;
}

template<class T>
T* RCPtr<T>::operator->() const
{
  return m_pointee;
}

template<class T>
T& RCPtr<T>::operator*() const
{
  return *m_pointee;
}