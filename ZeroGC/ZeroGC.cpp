// CustomGC.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "inc\ZeroGC.h"
#include "inc\ZeroGCHeap.h"
#include "inc\ZeroGCHandleManager.h"
#include "inc\common.h"
#include "inc\threads.h"
#include "inc\appdomain.h"
#include "inc\methodtable.h"
#include "inc\gcinterface.h"
#include "inc\gcinterface.ee.h"

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __attribute__ ((visibility ("default")))
#endif // _MSC_VER

extern "C" DLLEXPORT bool
InitializeGarbageCollector(
    /* In */  IGCToCLR* clrToGC,
    /* Out */ IGCHeap** gcHeap,
    /* Out */ IGCHandleManager** gcHandleManager,
    /* Out */ GcDacVars* gcDacVars
)
{
    IGCHeap* heap = new CustomGCHeap(clrToGC);
    IGCHandleManager* handleManager = new CustomGCHandleManager();
    *gcHeap = heap;
    *gcHandleManager = handleManager;
    return true;
}