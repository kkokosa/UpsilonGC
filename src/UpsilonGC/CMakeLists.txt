include_directories(
    ${CORECLR_FOR_CUSTOMGC}/src/pal/inc
    ${CORECLR_FOR_CUSTOMGC}/src/inc
    ${CORECLR_FOR_CUSTOMGC}/src/pal/inc/rt
    ${CORECLR_FOR_CUSTOMGC}/src/gc/env
    ${CORECLR_FOR_CUSTOMGC}/src/gc
)

add_library(UpsilonGC SHARED
    UpsilonGC.cpp
    UpsilonGCHeap.cpp
    UpsilonGCHandleManager.cpp
    UpsilonGCHandleStore.cpp
)
