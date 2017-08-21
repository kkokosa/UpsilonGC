
#include "stdafx.h"
#include "inc\ZeroGCHeap.h"

class ObjHeader
{
private:
#ifdef _WIN64
    DWORD    m_alignpad;
#endif // _WIN64
    DWORD m_SyncBlockValue;
};

bool CustomGCHeap::IsValidSegmentSize(size_t size)
{
    return false;
}

bool CustomGCHeap::IsValidGen0MaxSize(size_t size)
{
    return false;
}

size_t CustomGCHeap::GetValidSegmentSize(bool large_seg)
{
    return size_t();
}

void CustomGCHeap::SetReservedVMLimit(size_t vmlimit)
{
}

void CustomGCHeap::WaitUntilConcurrentGCComplete()
{
}

bool CustomGCHeap::IsConcurrentGCInProgress()
{
    return false;
}

void CustomGCHeap::TemporaryEnableConcurrentGC()
{
}

void CustomGCHeap::TemporaryDisableConcurrentGC()
{
}

bool CustomGCHeap::IsConcurrentGCEnabled()
{
    return false;
}

HRESULT CustomGCHeap::WaitUntilConcurrentGCCompleteAsync(int millisecondsTimeout)
{
    return E_NOTIMPL;
}

bool CustomGCHeap::FinalizeAppDomain(AppDomain * pDomain, bool fRunFinalizers)
{
    return false;
}

void CustomGCHeap::SetFinalizeQueueForShutdown(bool fHasLock)
{
}

size_t CustomGCHeap::GetNumberOfFinalizable()
{
    return size_t();
}

bool CustomGCHeap::ShouldRestartFinalizerWatchDog()
{
    return false;
}

Object * CustomGCHeap::GetNextFinalizable()
{
    return nullptr;
}

void CustomGCHeap::SetFinalizeRunOnShutdown(bool value)
{
}

int CustomGCHeap::GetGcLatencyMode()
{
    return 0;
}

int CustomGCHeap::SetGcLatencyMode(int newLatencyMode)
{
    return 0;
}

int CustomGCHeap::GetLOHCompactionMode()
{
    return 0;
}

void CustomGCHeap::SetLOHCompactionMode(int newLOHCompactionMode)
{
}

bool CustomGCHeap::RegisterForFullGCNotification(uint32_t gen2Percentage, uint32_t lohPercentage)
{
    return false;
}

bool CustomGCHeap::CancelFullGCNotification()
{
    return false;
}

int CustomGCHeap::WaitForFullGCApproach(int millisecondsTimeout)
{
    return 0;
}

int CustomGCHeap::WaitForFullGCComplete(int millisecondsTimeout)
{
    return 0;
}

unsigned CustomGCHeap::WhichGeneration(Object * obj)
{
    return 0;
}

int CustomGCHeap::CollectionCount(int generation, int get_bgc_fgc_coutn)
{
    return 0;
}

int CustomGCHeap::StartNoGCRegion(uint64_t totalSize, bool lohSizeKnown, uint64_t lohSize, bool disallowFullBlockingGC)
{
    return 0;
}

int CustomGCHeap::EndNoGCRegion()
{
    return 0;
}

size_t CustomGCHeap::GetTotalBytesInUse()
{
    return size_t();
}

HRESULT CustomGCHeap::GarbageCollect(int generation, bool low_memory_p, int mode)
{
    return NOERROR;
}

unsigned CustomGCHeap::GetMaxGeneration()
{
    return 0;
}

void CustomGCHeap::SetFinalizationRun(Object * obj)
{
}

bool CustomGCHeap::RegisterForFinalization(int gen, Object * obj)
{
    return false;
}

HRESULT CustomGCHeap::Initialize()
{
    MethodTable* freeObjectMethodTable = gcToCLR->GetFreeObjectMethodTable();

    WriteBarrierParameters args = {};
    args.operation = WriteBarrierOp::Initialize;
    args.is_runtime_suspended = true;
    args.requires_upper_bounds_check = false;
    args.card_table = new uint32_t[1];
#ifdef FEATURE_MANUALLY_MANAGED_CARD_BUNDLES
    args.card_bundle_table = g_gc_card_bundle_table;
#endif
    args.lowest_address = reinterpret_cast<uint8_t*>(~0);;
    args.highest_address = reinterpret_cast<uint8_t*>(1);
    args.ephemeral_low = reinterpret_cast<uint8_t*>(~0);
    args.ephemeral_high = reinterpret_cast<uint8_t*>(1);
    gcToCLR->StompWriteBarrier(&args);

    return NOERROR;
}

bool CustomGCHeap::IsPromoted(Object * object)
{
    return false;
}

bool CustomGCHeap::IsHeapPointer(void * object, bool small_heap_only)
{
    return false;
}

unsigned CustomGCHeap::GetCondemnedGeneration()
{
    return 0;
}

bool CustomGCHeap::IsGCInProgressHelper(bool bConsiderGCStart)
{
    return false;
}

unsigned CustomGCHeap::GetGcCount()
{
    return 0;
}

bool CustomGCHeap::IsThreadUsingAllocationContextHeap(gc_alloc_context * acontext, int thread_number)
{
    return false;
}

bool CustomGCHeap::IsEphemeral(Object * object)
{
    return false;
}

uint32_t CustomGCHeap::WaitUntilGCComplete(bool bConsiderGCStart)
{
    return uint32_t();
}

void CustomGCHeap::FixAllocContext(gc_alloc_context * acontext, bool lockp, void * arg, void * heap)
{
}

size_t CustomGCHeap::GetCurrentObjSize()
{
    return size_t();
}

void CustomGCHeap::SetGCInProgress(bool fInProgress)
{
}

bool CustomGCHeap::RuntimeStructuresValid()
{
    return true;
}

size_t CustomGCHeap::GetLastGCStartTime(int generation)
{
    return size_t();
}

size_t CustomGCHeap::GetLastGCDuration(int generation)
{
    return size_t();
}

size_t CustomGCHeap::GetNow()
{
    return size_t();
}

Object * CustomGCHeap::Alloc(gc_alloc_context * acontext, size_t size, uint32_t flags)
{
    int sizeWithHeader = size + sizeof(ObjHeader);
    ObjHeader* address = (ObjHeader*)calloc(sizeWithHeader, sizeof(char*));
    return (Object*)(address + 1);
}

Object * CustomGCHeap::AllocLHeap(size_t size, uint32_t flags)
{
    int sizeWithHeader = size + sizeof(ObjHeader);
    ObjHeader* address = (ObjHeader*)calloc(sizeWithHeader, sizeof(char*));
    return (Object*)(address + 1);
}

Object * CustomGCHeap::AllocAlign8(gc_alloc_context * acontext, size_t size, uint32_t flags)
{
    int sizeWithHeader = size + sizeof(ObjHeader);
    ObjHeader* address = (ObjHeader*)calloc(sizeWithHeader, sizeof(char*));
    return (Object*)(address + 1);
}

void CustomGCHeap::PublishObject(uint8_t * obj)
{
}

void CustomGCHeap::SetWaitForGCEvent()
{
}

void CustomGCHeap::ResetWaitForGCEvent()
{
}

bool CustomGCHeap::IsObjectInFixedHeap(Object * pObj)
{
    return false;
}

void CustomGCHeap::ValidateObjectMember(Object * obj)
{
}

Object * CustomGCHeap::NextObj(Object * object)
{
    return nullptr;
}

Object * CustomGCHeap::GetContainingObject(void * pInteriorPtr, bool fCollectedGenOnly)
{
    return nullptr;
}

void CustomGCHeap::DiagWalkObject(Object * obj, walk_fn fn, void * context)
{
}

void CustomGCHeap::DiagWalkHeap(walk_fn fn, void * context, int gen_number, bool walk_large_object_heap_p)
{
}

void CustomGCHeap::DiagWalkSurvivorsWithType(void * gc_context, record_surv_fn fn, void * diag_context, walk_surv_type type)
{
}

void CustomGCHeap::DiagWalkFinalizeQueue(void * gc_context, fq_walk_fn fn)
{
}

void CustomGCHeap::DiagScanFinalizeQueue(fq_scan_fn fn, ScanContext * context)
{
}

void CustomGCHeap::DiagScanHandles(handle_scan_fn fn, int gen_number, ScanContext * context)
{
}

void CustomGCHeap::DiagScanDependentHandles(handle_scan_fn fn, int gen_number, ScanContext * context)
{
}

void CustomGCHeap::DiagDescrGenerations(gen_walk_fn fn, void * context)
{
}

void CustomGCHeap::DiagTraceGCSegments()
{
}

bool CustomGCHeap::StressHeap(gc_alloc_context * acontext)
{
    return false;
}

segment_handle CustomGCHeap::RegisterFrozenSegment(segment_info * pseginfo)
{
    return segment_handle();
}

void CustomGCHeap::UnregisterFrozenSegment(segment_handle seg)
{
}
