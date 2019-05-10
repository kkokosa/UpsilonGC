#include "stdafx.h"
#include "inc\UpsilonGCHeap.h"
#include <stdio.h>

const int GrowthSize = 1 * 1024 * 1024;

int segmentsCount = 0;
uint8_t* segments[1024];


class ObjHeader
{
private:
#ifdef _WIN64
    DWORD    m_alignpad;
#endif // _WIN64
    DWORD m_SyncBlockValue;
};

class Object
{
	MethodTable* m_pMethTab;

public:
	ObjHeader* GetHeader()
	{
		return ((ObjHeader*)this) - 1;
	}

	MethodTable* RawGetMethodTable() const
	{
		return m_pMethTab;
	}

	void RawSetMethodTable(MethodTable* pMT)
	{
		m_pMethTab = pMT;
	}
};

bool UpsilonGCHeap::gcInProgress = false;

bool UpsilonGCHeap::IsValidSegmentSize(size_t size)
{
    return false;
}

bool UpsilonGCHeap::IsValidGen0MaxSize(size_t size)
{
    return false;
}

size_t UpsilonGCHeap::GetValidSegmentSize(bool large_seg)
{
    return size_t();
}

void UpsilonGCHeap::SetReservedVMLimit(size_t vmlimit)
{
}

void UpsilonGCHeap::WaitUntilConcurrentGCComplete()
{
}

bool UpsilonGCHeap::IsConcurrentGCInProgress()
{
    return false;
}

void UpsilonGCHeap::TemporaryEnableConcurrentGC()
{
}

void UpsilonGCHeap::TemporaryDisableConcurrentGC()
{
}

bool UpsilonGCHeap::IsConcurrentGCEnabled()
{
    return false;
}

HRESULT UpsilonGCHeap::WaitUntilConcurrentGCCompleteAsync(int millisecondsTimeout)
{
    return E_NOTIMPL;
}

bool UpsilonGCHeap::FinalizeAppDomain(void * pDomain, bool fRunFinalizers)
{
    return false;
}

void UpsilonGCHeap::SetFinalizeQueueForShutdown(bool fHasLock)
{
}

size_t UpsilonGCHeap::GetNumberOfFinalizable()
{
    return size_t();
}

bool UpsilonGCHeap::ShouldRestartFinalizerWatchDog()
{
    return false;
}

Object * UpsilonGCHeap::GetNextFinalizable()
{
    return nullptr;
}

void UpsilonGCHeap::SetFinalizeRunOnShutdown(bool value)
{
}

int UpsilonGCHeap::GetGcLatencyMode()
{
    return 0;
}

int UpsilonGCHeap::SetGcLatencyMode(int newLatencyMode)
{
    return 0;
}

int UpsilonGCHeap::GetLOHCompactionMode()
{
    return 0;
}

void UpsilonGCHeap::SetLOHCompactionMode(int newLOHCompactionMode)
{
}

bool UpsilonGCHeap::RegisterForFullGCNotification(uint32_t gen2Percentage, uint32_t lohPercentage)
{
    return false;
}

bool UpsilonGCHeap::CancelFullGCNotification()
{
    return false;
}

int UpsilonGCHeap::WaitForFullGCApproach(int millisecondsTimeout)
{
    return 0;
}

int UpsilonGCHeap::WaitForFullGCComplete(int millisecondsTimeout)
{
    return 0;
}

unsigned UpsilonGCHeap::WhichGeneration(Object * obj)
{
    return 0;
}

int UpsilonGCHeap::CollectionCount(int generation, int get_bgc_fgc_coutn)
{
    return 0;
}

int UpsilonGCHeap::StartNoGCRegion(uint64_t totalSize, bool lohSizeKnown, uint64_t lohSize, bool disallowFullBlockingGC)
{
    return 0;
}

int UpsilonGCHeap::EndNoGCRegion()
{
    return 0;
}

size_t UpsilonGCHeap::GetTotalBytesInUse()
{
    return size_t();
}

unsigned UpsilonGCHeap::GetMaxGeneration()
{
    return 1;
}

void UpsilonGCHeap::SetFinalizationRun(Object * obj)
{
}

bool UpsilonGCHeap::RegisterForFinalization(int gen, Object * obj)
{
    return false;
}

HRESULT UpsilonGCHeap::Initialize()
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

bool UpsilonGCHeap::IsPromoted(Object * object)
{
    return false;
}

bool UpsilonGCHeap::IsHeapPointer(void * object, bool small_heap_only)
{
	if (segmentsCount == 0)
		return false;
	for (int i = 0; i < segmentsCount; ++i)
	{
		uint8_t* address = (uint8_t*)object;
		if (address >= segments[i] &&
			address < segments[i] + GrowthSize)
			return true;
	}
    return false;
}

unsigned UpsilonGCHeap::GetCondemnedGeneration()
{
    return 0;
}

bool UpsilonGCHeap::IsGCInProgressHelper(bool bConsiderGCStart)
{
    return gcInProgress;
}

unsigned UpsilonGCHeap::GetGcCount()
{
    return 0;
}

bool UpsilonGCHeap::IsThreadUsingAllocationContextHeap(gc_alloc_context * acontext, int thread_number)
{
    return acontext->alloc_limit != nullptr;
}

bool UpsilonGCHeap::IsEphemeral(Object * object)
{
    return false;
}

uint32_t UpsilonGCHeap::WaitUntilGCComplete(bool bConsiderGCStart)
{
    return uint32_t();
}

void UpsilonGCHeap::FixAllocContext(gc_alloc_context* acontext, void* arg, void* heap)
{
}

size_t UpsilonGCHeap::GetCurrentObjSize()
{
    return size_t();
}

void UpsilonGCHeap::SetGCInProgress(bool fInProgress)
{
	gcInProgress = fInProgress;
}

bool UpsilonGCHeap::RuntimeStructuresValid()
{
    return true;
}

size_t UpsilonGCHeap::GetLastGCStartTime(int generation)
{
    return size_t();
}

size_t UpsilonGCHeap::GetLastGCDuration(int generation)
{
    return size_t();
}

size_t UpsilonGCHeap::GetNow()
{
    return size_t();
}

HRESULT UpsilonGCHeap::GarbageCollect(int generation, bool low_memory_p, int mode)
{
    return NOERROR;
}

// Normally both SOH and LOH allocations go through there
Object * UpsilonGCHeap::Alloc(gc_alloc_context * acontext, size_t size, uint32_t flags)
{
	uint8_t* result = acontext->alloc_ptr;
	uint8_t* advance = result + size;
	if (advance <= acontext->alloc_limit)
	{
		acontext->alloc_ptr = advance;
		return (Object* )result;
	}
	if (acontext->alloc_limit != nullptr)
	{
		// Some allocation context filled, start GC
		gcInProgress = true;
		ScanContext sc;
		gcToCLR->SuspendEE(SUSPEND_FOR_GC);
		//gcToCLR->DisablePreemptiveGC();
		gcToCLR->GcScanRoots(UpsilonGCHeap::MarkStackRoots, 0, 0, &sc);
		//gcInProgress = false;
		gcToCLR->RestartEE(true);
	}
	int beginGap = 24;
	uint8_t* newPages = (uint8_t*)VirtualAlloc(NULL, GrowthSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	uint8_t* allocationStart = newPages + beginGap;
	acontext->alloc_ptr = allocationStart + size;
	acontext->alloc_limit = newPages + GrowthSize;
	registerSegment(newPages);
	printf("GCLOG: Segment crated %p-%p\r\n", acontext->alloc_ptr, acontext->alloc_limit);
	//gcToCLR->EventSink()->FireGCCreateSegment_V1(newPages, growthSize, 0);
	return (Object*)(allocationStart);
}

void UpsilonGCHeap::MarkStackRoots(Object** ppObject, ScanContext* sc, uint32_t flags)
{
	uint8_t* o = (uint8_t*)* ppObject;
	if (o == 0)
		return;
	MethodTable* pMT = (*ppObject)->RawGetMethodTable();
	printf("GCLOG: Reachable at %p MT %p\r\n", o, pMT);
}

// This variation is used in the rare circumstance when you want to allocate an object on the
// large object heap but the object is not big enough to naturally go there.
Object * UpsilonGCHeap::AllocLHeap(size_t size, uint32_t flags)
{
    int sizeWithHeader = size + sizeof(ObjHeader);
    ObjHeader* address = (ObjHeader*)calloc(sizeWithHeader, sizeof(char*));
    return (Object*)(address + 1);
}

Object * UpsilonGCHeap::AllocAlign8(gc_alloc_context * acontext, size_t size, uint32_t flags)
{
    int sizeWithHeader = size + sizeof(ObjHeader);
    ObjHeader* address = (ObjHeader*)calloc(sizeWithHeader, sizeof(char*));
    return (Object*)(address + 1);
}

void UpsilonGCHeap::PublishObject(uint8_t * obj)
{
}

void UpsilonGCHeap::SetWaitForGCEvent()
{
}

void UpsilonGCHeap::ResetWaitForGCEvent()
{
}

bool UpsilonGCHeap::IsObjectInFixedHeap(Object * pObj)
{
    return false;
}

void UpsilonGCHeap::ValidateObjectMember(Object * obj)
{
}

Object * UpsilonGCHeap::NextObj(Object * object)
{
    return nullptr;
}

Object * UpsilonGCHeap::GetContainingObject(void * pInteriorPtr, bool fCollectedGenOnly)
{
    return nullptr;
}

void UpsilonGCHeap::DiagWalkObject(Object * obj, walk_fn fn, void * context)
{
}

void UpsilonGCHeap::DiagWalkHeap(walk_fn fn, void * context, int gen_number, bool walk_large_object_heap_p)
{
}

void UpsilonGCHeap::DiagWalkSurvivorsWithType(void * gc_context, record_surv_fn fn, void * diag_context, walk_surv_type type)
{
}

void UpsilonGCHeap::DiagWalkFinalizeQueue(void * gc_context, fq_walk_fn fn)
{
}

void UpsilonGCHeap::DiagScanFinalizeQueue(fq_scan_fn fn, ScanContext * context)
{
}

void UpsilonGCHeap::DiagScanHandles(handle_scan_fn fn, int gen_number, ScanContext * context)
{
}

void UpsilonGCHeap::DiagScanDependentHandles(handle_scan_fn fn, int gen_number, ScanContext * context)
{
}

void UpsilonGCHeap::DiagDescrGenerations(gen_walk_fn fn, void * context)
{
}

void UpsilonGCHeap::DiagTraceGCSegments()
{
}

bool UpsilonGCHeap::StressHeap(gc_alloc_context * acontext)
{
    return false;
}

segment_handle UpsilonGCHeap::RegisterFrozenSegment(segment_info * pseginfo)
{
    return segment_handle();
}

void UpsilonGCHeap::UnregisterFrozenSegment(segment_handle seg)
{
}

void UpsilonGCHeap::ControlEvents(GCEventKeyword keyword, GCEventLevel level)
{
}

void UpsilonGCHeap::ControlPrivateEvents(GCEventKeyword keyword, GCEventLevel level)
{
}

void UpsilonGCHeap::GetMemoryInfo(uint32_t * highMemLoadThreshold, uint64_t * totalPhysicalMem, uint32_t * lastRecordedMemLoad, size_t * lastRecordedHeapSize, size_t * lastRecordedFragmentation)
{
}

void UpsilonGCHeap::SetSuspensionPending(bool fSuspensionPending)
{
}

void UpsilonGCHeap::SetYieldProcessorScalingFactor(float yieldProcessorScalingFactor)
{
}

void UpsilonGCHeap::registerSegment(uint8_t* new_pages)
{
	segments[segmentsCount++] = new_pages;
}
