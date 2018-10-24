#include "stdafx.h"
#include "inc\ZeroGCHandleStore.h"

int handlesCount = 0;
OBJECTHANDLE handles[65535];

void ZeroGCHandleStore::Uproot()
{
}

bool ZeroGCHandleStore::ContainsHandle(OBJECTHANDLE handle)
{
    return false;
}

OBJECTHANDLE ZeroGCHandleStore::CreateHandleOfType(Object * object, HandleType type)
{
    handles[handlesCount] = (OBJECTHANDLE__*)object;
    return (OBJECTHANDLE)&handles[handlesCount++];
}

OBJECTHANDLE ZeroGCHandleStore::CreateHandleOfType(Object * object, HandleType type, int heapToAffinitizeTo)
{
    return OBJECTHANDLE();
}

OBJECTHANDLE ZeroGCHandleStore::CreateHandleWithExtraInfo(Object * object, HandleType type, void * pExtraInfo)
{
    return OBJECTHANDLE();
}

OBJECTHANDLE ZeroGCHandleStore::CreateDependentHandle(Object * primary, Object * secondary)
{
    return OBJECTHANDLE();
}

void ZeroGCHandleStore::RelocateAsyncPinnedHandles(IGCHandleStore* pTarget, void(*clearIfComplete)(Object*), void(*setHandle)(Object*, OBJECTHANDLE))
{
}

bool ZeroGCHandleStore::EnumerateAsyncPinnedHandles(async_pin_enum_fn callback, void * context)
{
    return false;
}
