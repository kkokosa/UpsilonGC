#include "stdafx.h"
#include "inc\ZeroGCHandleStore.h"

int handlesCount = 0;
OBJECTHANDLE handles[10000];

void CustomGCHandleStore::Uproot()
{
}

bool CustomGCHandleStore::ContainsHandle(OBJECTHANDLE handle)
{
    return false;
}

OBJECTHANDLE CustomGCHandleStore::CreateHandleOfType(Object * object, HandleType type)
{
    handles[handlesCount] = (OBJECTHANDLE__*)object;
    return (OBJECTHANDLE)&handles[handlesCount++];
}

OBJECTHANDLE CustomGCHandleStore::CreateHandleOfType(Object * object, HandleType type, int heapToAffinitizeTo)
{
    return OBJECTHANDLE();
}

OBJECTHANDLE CustomGCHandleStore::CreateHandleWithExtraInfo(Object * object, HandleType type, void * pExtraInfo)
{
    return OBJECTHANDLE();
}

OBJECTHANDLE CustomGCHandleStore::CreateDependentHandle(Object * primary, Object * secondary)
{
    return OBJECTHANDLE();
}

void CustomGCHandleStore::RelocateAsyncPinnedHandles(IGCHandleStore * pTarget)
{
}

bool CustomGCHandleStore::EnumerateAsyncPinnedHandles(async_pin_enum_fn callback, void * context)
{
    return false;
}
