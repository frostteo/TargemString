#ifndef __RC_OBJECT_
#define __RC_OBJECT_

class RCObject
{
public:
  void addReference();
  void removeReference();
  void markUnshareable();
  bool isShareable() const;
  bool isShared() const;
protected:
  RCObject();
  RCObject(const RCObject& rhs);
  RCObject& operator=(const RCObject& rhs);
  virtual ~RCObject() = 0;
private:
  int m_refCount;
  bool m_shareable;
};

#endif	// __RC_OBJECT_
