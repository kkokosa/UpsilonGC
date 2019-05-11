#include "stdafx.h"
#include "inc\UpsilonGCHandleManager.h"
#include "inc\UpsilonGCHandleStore.h"

UpsilonGCHandleStore* g_gcGlobalHandleStore;

bool UpsilonGCHandleManager::Initialize()
{
    g_gcGlobalHandleStore = new UpsilonGCHandleStore();
    return true;
}

void UpsilonGCHandleManager::Shutdown()
{
}

void * UpsilonGCHandleManager::GetHandleContext(OBJECTHANDLE handle)
{
    return (void*)1;
}

IGCHandleStore * UpsilonGCHandleManager::GetGlobalHandleStore()
{
    return g_gcGlobalHandleStore;
}

IGCHandleStore * UpsilonGCHandleManager::CreateHandleStore(void * context)
{
    return nullptr;
}

void UpsilonGCHandleManager::DestroyHandleStore(IGCHandleStore * store)
{
}

OBJECTHANDLE UpsilonGCHandleManager::CreateGlobalHandleOfType(Object * object, HandleType type)
{
    return g_gcGlobalHandleStore->CreateHandleOfType(object, type);
}

OBJECTHANDLE UpsilonGCHandleManager::CreateDuplicateHandle(OBJECTHANDLE handle)
{
    return OBJECTHANDLE();
}

void UpsilonGCHandleManager::DestroyHandleOfType(OBJECTHANDLE handle, HandleType type)
{
	g_gcGlobalHandleStore->DestroyHandleOfType(handle, type);
}

void UpsilonGCHandleManager::DestroyHandleOfUnknownType(OBJECTHANDLE handle)
{
	g_gcGlobalHandleStore->DestroyHandleOfUnknownType(handle);
}

void UpsilonGCHandleManager::SetExtraInfoForHandle(OBJECTHANDLE handle, HandleType type, void * pExtraInfo)
{
}

void * UpsilonGCHandleManager::GetExtraInfoFromHandle(OBJECTHANDLE handle)
{
    return nullptr;
}

void UpsilonGCHandleManager::StoreObjectInHandle(OBJECTHANDLE handle, Object * object)
{
    Object** handleObj = (Object**)handle;
    *handleObj = object;
}

bool UpsilonGCHandleManager::StoreObjectInHandleIfNull(OBJECTHANDLE handle, Object * object)
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

Object* UpsilonGCHandleManager::InterlockedCompareExchangeObjectInHandle(OBJECTHANDLE handle, Object * object, Object * oldObject)
{
    // TODO: This is not thread-safe
    Object** handleObject = (Object**)handle;
    if (*handleObject == oldObject)
    {
        *handleObject = object;
    }
    return *handleObject;
}

void UpsilonGCHandleManager::SetDependentHandleSecondary(OBJECTHANDLE handle, Object * object)
{
}

Object * UpsilonGCHandleManager::GetDependentHandleSecondary(OBJECTHANDLE handle)
{
    return nullptr;
}

HandleType UpsilonGCHandleManager::HandleFetchType(OBJECTHANDLE handle)
{
    return HandleType();
}

void UpsilonGCHandleManager::TraceRefCountedHandles(HANDLESCANPROC callback, uintptr_t param1, uintptr_t param2)
{
}

void UpsilonGCHandleManager::ScanHandles(promote_func* pf, ScanContext* sc)
{
	g_gcGlobalHandleStore->ScanHandles(pf, sc);
}

