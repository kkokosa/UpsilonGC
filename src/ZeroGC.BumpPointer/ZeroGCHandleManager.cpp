#include "stdafx.h"
#include "inc\ZeroGCHandleManager.h"
#include "inc\ZeroGCHandleStore.h"

ZeroGCHandleStore* g_gcGlobalHandleStore;

bool ZeroGCHandleManager::Initialize()
{
    g_gcGlobalHandleStore = new ZeroGCHandleStore();
    return true;
}

void ZeroGCHandleManager::Shutdown()
{
}

void * ZeroGCHandleManager::GetHandleContext(OBJECTHANDLE handle)
{
    return (void*)1;
}

IGCHandleStore * ZeroGCHandleManager::GetGlobalHandleStore()
{
    return g_gcGlobalHandleStore;
}

IGCHandleStore * ZeroGCHandleManager::CreateHandleStore(void * context)
{
    return nullptr;
}

void ZeroGCHandleManager::DestroyHandleStore(IGCHandleStore * store)
{
}

OBJECTHANDLE ZeroGCHandleManager::CreateGlobalHandleOfType(Object * object, HandleType type)
{
    return g_gcGlobalHandleStore->CreateHandleOfType(object, type);
}

OBJECTHANDLE ZeroGCHandleManager::CreateDuplicateHandle(OBJECTHANDLE handle)
{
    return OBJECTHANDLE();
}

void ZeroGCHandleManager::DestroyHandleOfType(OBJECTHANDLE handle, HandleType type)
{
}

void ZeroGCHandleManager::DestroyHandleOfUnknownType(OBJECTHANDLE handle)
{
}

void ZeroGCHandleManager::SetExtraInfoForHandle(OBJECTHANDLE handle, HandleType type, void * pExtraInfo)
{
}

void * ZeroGCHandleManager::GetExtraInfoFromHandle(OBJECTHANDLE handle)
{
    return nullptr;
}

void ZeroGCHandleManager::StoreObjectInHandle(OBJECTHANDLE handle, Object * object)
{
    Object** handleObj = (Object**)handle;
    *handleObj = object;
}

bool ZeroGCHandleManager::StoreObjectInHandleIfNull(OBJECTHANDLE handle, Object * object)
{
    // TODO: This is not thread-safe    
    Object** handleObj = (Object**)handle;
    if (*handleObj == NULL)
    {        
        *handleObj = object;
        return true;
    }
    return false;
}

Object* ZeroGCHandleManager::InterlockedCompareExchangeObjectInHandle(OBJECTHANDLE handle, Object * object, Object * oldObject)
{
    // TODO: This is not thread-safe
    Object** handleObject = (Object**)handle;
    if (*handleObject == oldObject)
    {
        *handleObject = object;
    }
    return *handleObject;
}

void ZeroGCHandleManager::SetDependentHandleSecondary(OBJECTHANDLE handle, Object * object)
{
}

Object * ZeroGCHandleManager::GetDependentHandleSecondary(OBJECTHANDLE handle)
{
    return nullptr;
}

HandleType ZeroGCHandleManager::HandleFetchType(OBJECTHANDLE handle)
{
    return HandleType();
}

void ZeroGCHandleManager::TraceRefCountedHandles(HANDLESCANPROC callback, uintptr_t param1, uintptr_t param2)
{
}
