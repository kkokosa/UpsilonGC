#include "stdafx.h"
#include "inc\UpsilonGCHandleStore.h"

int handlesCount = 0;
OBJECTHANDLE handles[65535];

void UpsilonGCHandleStore::Uproot()
{
}

bool UpsilonGCHandleStore::ContainsHandle(OBJECTHANDLE handle)
{
    return false;
}

OBJECTHANDLE UpsilonGCHandleStore::CreateHandleOfType(Object * object, HandleType type)
{
    handles[handlesCount] = (OBJECTHANDLE__*)object;
    return (OBJECTHANDLE)&handles[handlesCount++];
}

OBJECTHANDLE UpsilonGCHandleStore::CreateHandleOfType(Object * object, HandleType type, int heapToAffinitizeTo)
{
    return OBJECTHANDLE();
}

OBJECTHANDLE UpsilonGCHandleStore::CreateHandleWithExtraInfo(Object * object, HandleType type, void * pExtraInfo)
{
    return OBJECTHANDLE();
}

OBJECTHANDLE UpsilonGCHandleStore::CreateDependentHandle(Object * primary, Object * secondary)
{
	handles[handlesCount] = (OBJECTHANDLE__*)primary;
	return (OBJECTHANDLE)&handles[handlesCount++];
}

void UpsilonGCHandleStore::RelocateAsyncPinnedHandles(IGCHandleStore* pTarget, void(*clearIfComplete)(Object*), void(*setHandle)(Object*, OBJECTHANDLE))
{
}

bool UpsilonGCHandleStore::EnumerateAsyncPinnedHandles(async_pin_enum_fn callback, void * context)
{
    return false;
}
