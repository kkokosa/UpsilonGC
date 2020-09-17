// CustomGC.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "inc/UpsilonGC.h"
#include "inc/UpsilonGCHeap.h"
#include "inc/UpsilonGCHandleManager.h"


#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#ifndef DLLEXPORT
#define DLLEXPORT __attribute__ ((visibility ("default")))
#endif // DLLEXPORT
#endif // _MSC_VER

extern "C" DLLEXPORT HRESULT
GC_Initialize(
    /* In */  IGCToCLR* clrToGC,
    /* Out */ IGCHeap** gcHeap,
    /* Out */ IGCHandleManager** gcHandleManager,
    /* Out */ GcDacVars* gcDacVars
)
{
	auto handleManager = new UpsilonGCHandleManager();
	auto heap = new UpsilonGCHeap(clrToGC, handleManager);
	*gcHeap = heap;
    *gcHandleManager = handleManager;
    return S_OK;
}

extern "C" DLLEXPORT void
GC_VersionInfo(
    /* Out */ VersionInfo* result
)
{
	result->MajorVersion = GC_INTERFACE_MAJOR_VERSION;
	result->MinorVersion = GC_INTERFACE_MINOR_VERSION;
    result->BuildVersion = 0;
    result->Name = "Upsilon GC";
}
