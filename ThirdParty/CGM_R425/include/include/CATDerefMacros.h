#ifndef CATDerefMacros_H
#define CATDerefMacros_H

#define DEFINE_ADVOP_CLASS_NAME(ClassName) virtual const char* GetClassName() { return ClassName; }

#define DEFINE_ADVOP_CLASS(ClassName) \
  DEFINE_ADVOP_CLASS_NAME(#ClassName) \
  inline ClassName &Deref() { return *this; }


#endif // !CATDerefMacros_H
