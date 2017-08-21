#include "stdafx.h"
#include "inc\ZeroGCHandleManager.h"
#include "inc\ZeroGCHandleStore.h"

CustomGCHandleStore* g_gcGlobalHandleStore;

bool CustomGCHandleManager::Initialize()
{
    g_gcGlobalHandleStore = new CustomGCHandleStore();
    return true;
}

void CustomGCHandleManager::Shutdown()
{
}

void * CustomGCHandleManager::GetHandleContext(OBJECTHANDLE handle)
{
    return (void*)1;
}

IGCHandleStore * CustomGCHandleManager::GetGlobalHandleStore()
{
    return g_gcGlobalHandleStore;
}

IGCHandleStore * CustomGCHandleManager::CreateHandleStore(void * context)
{
    return nullptr;
}

void CustomGCHandleManager::DestroyHandleStore(IGCHandleStore * store)
{
}

OBJECTHANDLE CustomGCHandleManager::CreateGlobalHandleOfType(Object * object, HandleType type)
{
    return g_gcGlobalHandleStore->CreateHandleOfType(object, type);
}

OBJECTHANDLE CustomGCHandleManager::CreateDuplicateHandle(OBJECTHANDLE handle)
{
    return OBJECTHANDLE();
}

void CustomGCHandleManager::DestroyHandleOfType(OBJECTHANDLE handle, HandleType type)
{
}

void CustomGCHandleManager::DestroyHandleOfUnknownType(OBJECTHANDLE handle)
{
}

void CustomGCHandleManager::SetExtraInfoForHandle(OBJECTHANDLE handle, HandleType type, void * pExtraInfo)
{
}

void * CustomGCHandleManager::GetExtraInfoFromHandle(OBJECTHANDLE handle)
{
    return nullptr;
}

void CustomGCHandleManager::StoreObjectInHandle(OBJECTHANDLE handle, Object * object)
{
    Object** handleObj = (Object**)handle;
    *handleObj = object;
}

bool CustomGCHandleManager::StoreObjectInHandleIfNull(OBJECTHANDLE handle, Object * object)
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

void CustomGCHandleManager::SetDependentHandleSecondary(OBJECTHANDLE handle, Object * object)
{
}

Object * CustomGCHandleManager::GetDependentHandleSecondary(OBJECTHANDLE handle)
{
    return nullptr;
}

Object * CustomGCHandleManager::InterlockedCompareExchangeObjectInHandle(OBJECTHANDLE handle, Object * objectRef, Object * oldObjectRef)
{
    // unwrap the objectref we were given
    Object* object = OBJECTREF_TO_UNCHECKED_OBJECTREF(objectRef);
    Object* oldObject = OBJECTREF_TO_UNCHECKED_OBJECTREF(oldObjectRef);

    // store the pointer
    //void* ret = Interlocked::CompareExchangePointer(reinterpret_cast<Object volatile*>(handle), object, oldObject);
    //if (handle == oldObject) handle = objectRef

    // TODO: This is not thread-safe
    Object** handleObject = (Object**)handle;
    if (*handleObject == oldObject)
    {
        *handleObject = object;
    }
    return *handleObject;
}

HandleType CustomGCHandleManager::HandleFetchType(OBJECTHANDLE handle)
{
    return HandleType();
}

void CustomGCHandleManager::TraceRefCountedHandles(HANDLESCANPROC callback, uintptr_t param1, uintptr_t param2)
{
}
