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

bool ZeroGCHeap::IsValidSegmentSize(size_t size)
{
    return false;
}

bool ZeroGCHeap::IsValidGen0MaxSize(size_t size)
{
    return false;
}

size_t ZeroGCHeap::GetValidSegmentSize(bool large_seg)
{
    return size_t();
}

void ZeroGCHeap::SetReservedVMLimit(size_t vmlimit)
{
}

void ZeroGCHeap::WaitUntilConcurrentGCComplete()
{
}

bool ZeroGCHeap::IsConcurrentGCInProgress()
{
    return false;
}

void ZeroGCHeap::TemporaryEnableConcurrentGC()
{
}

void ZeroGCHeap::TemporaryDisableConcurrentGC()
{
}

bool ZeroGCHeap::IsConcurrentGCEnabled()
{
    return false;
}

HRESULT ZeroGCHeap::WaitUntilConcurrentGCCompleteAsync(int millisecondsTimeout)
{
    return E_NOTIMPL;
}

bool ZeroGCHeap::FinalizeAppDomain(void * pDomain, bool fRunFinalizers)
{
    return false;
}

void ZeroGCHeap::SetFinalizeQueueForShutdown(bool fHasLock)
{
}

size_t ZeroGCHeap::GetNumberOfFinalizable()
{
    return size_t();
}

bool ZeroGCHeap::ShouldRestartFinalizerWatchDog()
{
    return false;
}

Object * ZeroGCHeap::GetNextFinalizable()
{
    return nullptr;
}

void ZeroGCHeap::SetFinalizeRunOnShutdown(bool value)
{
}

int ZeroGCHeap::GetGcLatencyMode()
{
    return 0;
}

int ZeroGCHeap::SetGcLatencyMode(int newLatencyMode)
{
    return 0;
}

int ZeroGCHeap::GetLOHCompactionMode()
{
    return 0;
}

void ZeroGCHeap::SetLOHCompactionMode(int newLOHCompactionMode)
{
}

bool ZeroGCHeap::RegisterForFullGCNotification(uint32_t gen2Percentage, uint32_t lohPercentage)
{
    return false;
}

bool ZeroGCHeap::CancelFullGCNotification()
{
    return false;
}

int ZeroGCHeap::WaitForFullGCApproach(int millisecondsTimeout)
{
    return 0;
}

int ZeroGCHeap::WaitForFullGCComplete(int millisecondsTimeout)
{
    return 0;
}

unsigned ZeroGCHeap::WhichGeneration(Object * obj)
{
    return 0;
}

int ZeroGCHeap::CollectionCount(int generation, int get_bgc_fgc_coutn)
{
    return 0;
}

int ZeroGCHeap::StartNoGCRegion(uint64_t totalSize, bool lohSizeKnown, uint64_t lohSize, bool disallowFullBlockingGC)
{
    return 0;
}

int ZeroGCHeap::EndNoGCRegion()
{
    return 0;
}

size_t ZeroGCHeap::GetTotalBytesInUse()
{
    return size_t();
}

unsigned ZeroGCHeap::GetMaxGeneration()
{
    return 1;
}

void ZeroGCHeap::SetFinalizationRun(Object * obj)
{
}

bool ZeroGCHeap::RegisterForFinalization(int gen, Object * obj)
{
    return false;
}

HRESULT ZeroGCHeap::Initialize()
{
    // Not used currently
    MethodTable* freeObjectMethodTable = gcToCLR->GetFreeObjectMethodTable();

    WriteBarrierParameters args = {};
    args.operation = WriteBarrierOp::Initialize;
    args.is_runtime_suspended = true;
    args.requires_upper_bounds_check = false;
    args.card_table = new uint32_t[1];
    args.lowest_address = reinterpret_cast<uint8_t*>(~0);;
    args.highest_address = reinterpret_cast<uint8_t*>(1);
    args.ephemeral_low = reinterpret_cast<uint8_t*>(~0);
    args.ephemeral_high = reinterpret_cast<uint8_t*>(1);
    gcToCLR->StompWriteBarrier(&args);

    return NOERROR;
}

bool ZeroGCHeap::IsPromoted(Object * object)
{
    return false;
}

bool ZeroGCHeap::IsHeapPointer(void * object, bool small_heap_only)
{
    return object != 0;
}

unsigned ZeroGCHeap::GetCondemnedGeneration()
{
    return 0;
}

bool ZeroGCHeap::IsGCInProgressHelper(bool bConsiderGCStart)
{
    return false;
}

unsigned ZeroGCHeap::GetGcCount()
{
    return 0;
}

bool ZeroGCHeap::IsThreadUsingAllocationContextHeap(gc_alloc_context * acontext, int thread_number)
{
    return false;
}

bool ZeroGCHeap::IsEphemeral(Object * object)
{
    return false;
}

uint32_t ZeroGCHeap::WaitUntilGCComplete(bool bConsiderGCStart)
{
    return uint32_t();
}

void ZeroGCHeap::FixAllocContext(gc_alloc_context* acontext, void* arg, void* heap)
{
}

size_t ZeroGCHeap::GetCurrentObjSize()
{
    return size_t();
}

void ZeroGCHeap::SetGCInProgress(bool fInProgress)
{
}

bool ZeroGCHeap::RuntimeStructuresValid()
{
    return true;
}

size_t ZeroGCHeap::GetLastGCStartTime(int generation)
{
    return size_t();
}

size_t ZeroGCHeap::GetLastGCDuration(int generation)
{
    return size_t();
}

size_t ZeroGCHeap::GetNow()
{
    return size_t();
}

HRESULT ZeroGCHeap::GarbageCollect(int generation, bool low_memory_p, int mode)
{
    return NOERROR;
}

// Normally both SOH and LOH allocations go through there
Object * ZeroGCHeap::Alloc(gc_alloc_context * acontext, size_t size, uint32_t flags)
{
	uint8_t* result = acontext->alloc_ptr;
	uint8_t* advance = result + size;
	if (advance <= acontext->alloc_limit)
	{
		acontext->alloc_ptr = advance;
		return (Object* )result;
	}
	int beginGap = 24;
	int growthSize = 16 * 1024 * 1024;
	uint8_t* newPages = (uint8_t*)VirtualAlloc(NULL, growthSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	uint8_t* allocationStart = newPages + beginGap;
	acontext->alloc_ptr = allocationStart + size;
	acontext->alloc_limit = newPages + growthSize;

	//gcToCLR->EventSink()->FireGCCreateSegment_V1(newPages, growthSize, 0);

	return (Object*)(allocationStart);
}

// This variation is used in the rare circumstance when you want to allocate an object on the
// large object heap but the object is not big enough to naturally go there.
Object * ZeroGCHeap::AllocLHeap(size_t size, uint32_t flags)
{
    int sizeWithHeader = size + sizeof(ObjHeader);
    ObjHeader* address = (ObjHeader*)calloc(sizeWithHeader, sizeof(char*));
    return (Object*)(address + 1);
}

Object * ZeroGCHeap::AllocAlign8(gc_alloc_context * acontext, size_t size, uint32_t flags)
{
    int sizeWithHeader = size + sizeof(ObjHeader);
    ObjHeader* address = (ObjHeader*)calloc(sizeWithHeader, sizeof(char*));
    return (Object*)(address + 1);
}

void ZeroGCHeap::PublishObject(uint8_t * obj)
{
}

void ZeroGCHeap::SetWaitForGCEvent()
{
}

void ZeroGCHeap::ResetWaitForGCEvent()
{
}

bool ZeroGCHeap::IsObjectInFixedHeap(Object * pObj)
{
    return false;
}

void ZeroGCHeap::ValidateObjectMember(Object * obj)
{
}

Object * ZeroGCHeap::NextObj(Object * object)
{
    return nullptr;
}

Object * ZeroGCHeap::GetContainingObject(void * pInteriorPtr, bool fCollectedGenOnly)
{
    return nullptr;
}

void ZeroGCHeap::DiagWalkObject(Object * obj, walk_fn fn, void * context)
{
}

void ZeroGCHeap::DiagWalkHeap(walk_fn fn, void * context, int gen_number, bool walk_large_object_heap_p)
{
}

void ZeroGCHeap::DiagWalkSurvivorsWithType(void * gc_context, record_surv_fn fn, void * diag_context, walk_surv_type type)
{
}

void ZeroGCHeap::DiagWalkFinalizeQueue(void * gc_context, fq_walk_fn fn)
{
}

void ZeroGCHeap::DiagScanFinalizeQueue(fq_scan_fn fn, ScanContext * context)
{
}

void ZeroGCHeap::DiagScanHandles(handle_scan_fn fn, int gen_number, ScanContext * context)
{
}

void ZeroGCHeap::DiagScanDependentHandles(handle_scan_fn fn, int gen_number, ScanContext * context)
{
}

void ZeroGCHeap::DiagDescrGenerations(gen_walk_fn fn, void * context)
{
}

void ZeroGCHeap::DiagTraceGCSegments()
{
}

bool ZeroGCHeap::StressHeap(gc_alloc_context * acontext)
{
    return false;
}

segment_handle ZeroGCHeap::RegisterFrozenSegment(segment_info * pseginfo)
{
    return segment_handle();
}

void ZeroGCHeap::UnregisterFrozenSegment(segment_handle seg)
{
}

void ZeroGCHeap::ControlEvents(GCEventKeyword keyword, GCEventLevel level)
{
}

void ZeroGCHeap::ControlPrivateEvents(GCEventKeyword keyword, GCEventLevel level)
{
}

void ZeroGCHeap::GetMemoryInfo(uint32_t * highMemLoadThreshold, uint64_t * totalPhysicalMem, uint32_t * lastRecordedMemLoad, size_t * lastRecordedHeapSize, size_t * lastRecordedFragmentation)
{
}

void ZeroGCHeap::SetSuspensionPending(bool fSuspensionPending)
{
}

void ZeroGCHeap::SetYieldProcessorScalingFactor(float yieldProcessorScalingFactor)
{
}

bool ZeroGCHeap::IsInFrozenSegment(Object* object)
{
	return false;
}
