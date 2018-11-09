// CustomGC.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "inc\ZeroGC.h"
#include "inc\ZeroGCHeap.h"
#include "inc\ZeroGCHandleManager.h"


#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __attribute__ ((visibility ("default")))
#endif // _MSC_VER

extern "C" DLLEXPORT HRESULT
GC_Initialize(
    /* In */  IGCToCLR* clrToGC,
    /* Out */ IGCHeap** gcHeap,
    /* Out */ IGCHandleManager** gcHandleManager,
    /* Out */ GcDacVars* gcDacVars
)
{
    IGCHeap* heap = new ZeroGCHeap(clrToGC);
    IGCHandleManager* handleManager = new ZeroGCHandleManager();
    *gcHeap = heap;
    *gcHandleManager = handleManager;
    return S_OK;
}

extern "C" DLLEXPORT void
GC_VersionInfo(
    /* Out */ VersionInfo* result
)
{
	result->MajorVersion = 1; // GC_INTERFACE_MAJOR_VERSION;
	result->MinorVersion = 1; // GC_INTERFACE_MINOR_VERSION;
    result->BuildVersion = 0;
    result->Name = "Zero GC";
}
