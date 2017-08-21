#pragma once

#define PTR_NULL NULL

#define DAC_EMPTY()
#define DAC_EMPTY_ERR()
#define DAC_EMPTY_RET(retVal)
#define DAC_UNEXPECTED() 

#define DPTR(type) type*

typedef DPTR(class Object)              PTR_Object;
typedef DPTR(PTR_Object)                PTR_PTR_Object;

typedef DPTR(PTR_Object) PTR_UNCHECKED_OBJECTREF;

typedef UINT64 TASKID;