#include "stdafx.h"
#include "inc\UpsilonGCHeap.h"
#include <stdio.h>
#include <cassert>
#include "gcdesc.h"
#include <cstddef>

const int GrowthSize = 1 * 1024 * 1024;

int segmentsCount = 0;
uint8_t* segments[1024];

#define GC_MARKED       (size_t)0x1

class ObjHeader
{
private:
#ifdef _WIN64
    DWORD m_alignpad;
#endif // _WIN64
    DWORD m_SyncBlockValue;
};

class Object
{
	MethodTable* m_pMethTab;
	uint32_t m_dwLength;

public:
	ObjHeader* GetHeader()
	{
		return ((ObjHeader*)this) - 1;
	}

	MethodTable* GetMethodTable() const
	{
		return ((MethodTable*)(((size_t)RawGetMethodTable()) & (~(GC_MARKED))));
	}

	MethodTable* RawGetMethodTable() const
	{
		return m_pMethTab;
	}

	void RawSetMethodTable(MethodTable* pMT)
	{
		m_pMethTab = pMT;
	}

	bool IsMarked()
	{
		return !!(((size_t)RawGetMethodTable()) & GC_MARKED);
	}

	void SetMarked()
	{
		RawSetMethodTable((MethodTable*)(((size_t)RawGetMethodTable()) | GC_MARKED));
	}

	void ClearMarked()
	{
		RawSetMethodTable(GetMethodTable());
	}

	uint32_t GetNumComponents()
	{
		//assert(GetMethodTable()->HasComponentSize())
		return m_dwLength;
	}
};

#define MTFlag_ContainsPointers     0x0100
#define MTFlag_HasCriticalFinalizer 0x0800
#define MTFlag_HasFinalizer         0x0010
#define MTFlag_IsArray              0x0008
#define MTFlag_Collectible          0x1000
#define MTFlag_HasComponentSize     0x8000

/*
 * The whole MethodTable is a part of EE-GC contract, we cannot change the layout or
 * masks used here.
 */
class MethodTable
{
private:
	uint16_t    m_componentSize;
	uint16_t    m_flags;
	uint32_t    m_baseSize;
	MethodTable* m_pRelatedType; // parent

	//const uint16_t MTFlag_ContainsPointers = 0x0100;
	//const uint16_t MTFlag_HasCriticalFinalizer = 0x0800;
	//const uint16_t MTFlag_HasFinalizer = 0x0010;
	//const uint16_t MTFlag_IsArray = 0x0008;
	//const uint16_t MTFlag_Collectible = 0x1000;
	//const uint16_t MTFlag_HasComponentSize = 0x8000;

public:
	uint32_t GetBaseSize()
	{
		return m_baseSize;
	}

	uint16_t GetComponentSize()
	{
		return m_componentSize;
	}

	static uint32_t GetTotalSize(Object* obj)
	{
		MethodTable* mT = obj->GetMethodTable();
		return (mT->GetBaseSize() + 
	 	        (mT->HasComponentSize() ? (obj->GetNumComponents() * mT->GetComponentSize()) : 0));
	}

	bool ContainsPointers()
	{
		return (m_flags & MTFlag_ContainsPointers) != 0;
	}

	bool IsCollectible()
	{
		return (m_flags & MTFlag_Collectible) != 0;
	}

	bool HasComponentSize()
	{
		return (m_flags & MTFlag_HasComponentSize) != 0;
	}
};

bool UpsilonGCHeap::gcInProgress = false;
IGCToCLR* UpsilonGCHeap::gcToCLR = nullptr;

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
		printf("GCLOG: Scan stack roots\n");
		gcToCLR->GcScanRoots(UpsilonGCHeap::MarkReachableRoot, 0, 0, &sc);
		printf("GCLOG: Scan handles roots\n");
		handleManager->ScanHandles(UpsilonGCHeap::MarkReachableRoot, &sc);
		gcToCLR->RestartEE(true);
	}
	int beginGap = 24;
	uint8_t* newPages = (uint8_t*)VirtualAlloc(NULL, GrowthSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	uint8_t* allocationStart = newPages + beginGap;
	acontext->alloc_ptr = allocationStart + size;
	acontext->alloc_limit = newPages + GrowthSize;
	acontext->alloc_bytes += GrowthSize;
	registerSegment(newPages);
	printf("GCLOG: Segment crated %p-%p\n", acontext->alloc_ptr, acontext->alloc_limit);
	//gcToCLR->EventSink()->FireGCCreateSegment_V1(newPages, growthSize, 0);
	return (Object*)(allocationStart);
}

void UpsilonGCHeap::MarkReachableRoot(Object** ppObject, ScanContext* sc, uint32_t flags)
{
	Object* obj = *ppObject;
	if (obj == nullptr)
		return;
	MethodTable* pMT = (*ppObject)->GetMethodTable();	
	printf("GCLOG: Reachable root at %p MT %p (flags: %d)\n", obj, pMT, flags);
	//MarkObjectTransitively(obj, sc, flags);
}

void UpsilonGCHeap::MarkObjectTransitively(Object* obj, ScanContext* sc, uint32_t flags)
{
	if (obj->IsMarked())
	{
		printf("GCLOG:    Mark - already marked\n");
		return;
	}
	obj->SetMarked();
	MethodTable* pMT = obj->RawGetMethodTable();
	if (pMT->IsCollectible())
	{
		printf("GCLOG:    Mark - collectible type\n");
		// TODO
		uint8_t* class_obj = gcToCLR->GetLoaderAllocatorObjectForGC(obj);                             
		uint8_t** poo = &class_obj;
		uint8_t* oo = *poo;
		// exp
	}
	if (pMT->ContainsPointers())
	{
		printf("GCLOG:    Mark - containing pointers type at %p MT %p\n", obj, pMT);
		int start_useful = 0;
		uint8_t* start = (uint8_t*)obj;
		uint32_t size = MethodTable::GetTotalSize(obj);
		CGCDesc* map = CGCDesc::GetCGCDescFromMT(pMT);
		CGCDescSeries* cur = map->GetHighestSeries();
		ptrdiff_t cnt = (ptrdiff_t)map->GetNumSeries();
		if (cnt >= 0)
		{
			CGCDescSeries* last = map->GetLowestSeries();
			uint8_t** parm = 0;
			do
			{
				assert(parm <= (uint8_t**)((obj)+cur->GetSeriesOffset()));
				parm = (uint8_t * *)((obj)+cur->GetSeriesOffset());
				uint8_t** ppstop = (uint8_t * *)((uint8_t*)parm + cur->GetSeriesSize() + (size));
				if (!start_useful || (uint8_t*)ppstop > (start))
				{
					if (start_useful && (uint8_t*)parm < (start)) parm = (uint8_t * *)(start);
					while (parm < ppstop)                                       
					{
						//exp
						parm++;
					}
				}
				cur--;
			} while (cur >= last);
		}
		else
		{
			/* Handle the repeating case - array of valuetypes */
		}
	}
}

bool UpsilonGCHeap::IsInFrozenSegment(Object* object)
{
	return false;
}

// This variation is used in the rare circumstance when you want to allocate an object on the
// large object heap but the object is not big enough to naturally go there.
Object * UpsilonGCHeap::AllocLHeap(size_t size, uint32_t flags)
{
    int sizeWithHeader = size + sizeof(ObjHeader);
    ObjHeader* address = (ObjHeader*)calloc(sizeWithHeader, sizeof(char*));
	printf("GCLOG: Special obj at %p size %llu (flags: %d)\n", address, size, flags);
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
