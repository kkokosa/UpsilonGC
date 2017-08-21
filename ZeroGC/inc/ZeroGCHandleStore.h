#pragma once
#include "inc\common.h"
#include "inc\threads.h"
#include "inc\appdomain.h"
#include "inc\methodtable.h"
#include "inc\gcinterface.h"
#include "inc\gcinterface.ee.h"

class ZeroGCHandleStore : public IGCHandleStore
{
public:
    // Inherited via IGCHandleStore
    virtual void Uproot() override;
    virtual bool ContainsHandle(OBJECTHANDLE handle) override;
    virtual OBJECTHANDLE CreateHandleOfType(Object * object, HandleType type) override;
    virtual OBJECTHANDLE CreateHandleOfType(Object * object, HandleType type, int heapToAffinitizeTo) override;
    virtual OBJECTHANDLE CreateHandleWithExtraInfo(Object * object, HandleType type, void * pExtraInfo) override;
    virtual OBJECTHANDLE CreateDependentHandle(Object * primary, Object * secondary) override;
    virtual void RelocateAsyncPinnedHandles(IGCHandleStore * pTarget) override;
    virtual bool EnumerateAsyncPinnedHandles(async_pin_enum_fn callback, void * context) override;
};