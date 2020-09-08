include_directories(
    ${CORECLR_SOURCE_PATH}/src/pal/inc
    ${CORECLR_SOURCE_PATH}/src/inc
    ${CORECLR_SOURCE_PATH}/src/pal/inc/rt
    ${CORECLR_SOURCE_PATH}/src/gc/env
    ${CORECLR_SOURCE_PATH}/src/gc
)

add_library(UpsilonGC
    UpsilonGC.cpp
)

target_link_libraries(UpsilonGC
)
