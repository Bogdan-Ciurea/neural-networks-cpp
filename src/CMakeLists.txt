set(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")

SET(SOURCES 
    math.cpp
)

add_library(neural-library ${SOURCES} ${HEADER_LIST})

target_include_directories(neural-library PUBLIC ../include)

target_compile_features(neural-library PUBLIC cxx_std_14)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

