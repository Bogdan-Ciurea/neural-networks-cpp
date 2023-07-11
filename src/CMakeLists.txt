set(GLOB HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/*.h")

SET(SOURCES 
    math.cpp
)

add_library(neural-library ${SOURCES} ${HEADER_LIST})

target_include_directories(neural-library PUBLIC ../include)

# Parallelization
OPTION (USE_OpenMP "Use OpenMP to enamble <omp.h>" ON)

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    message(FATAL_ERROR "Your compiler version is too old. Please use a compiler that supports C++14.")
endif()

# If the gcc version his higher than 13.0, we can't use OpenMP
# Check the default C++ compiler version
execute_process(
  COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
  OUTPUT_VARIABLE GCC_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Check if the GCC version is higher than 13
if (GCC_VERSION GREATER 13)
  message(WARNING "Using GCC version ${GCC_VERSION}, which is higher than 13. Switching to GCC version 12.")
  if (APPLE)
    # check if the path to GCC 12 is correct
    if (NOT EXISTS "/opt/homebrew/Cellar/gcc@12/12.3.0/bin/gcc-12")
      message(FATAL_ERROR "The path to GCC 12 is incorrect. Please install GCC 12 with Homebrew.")
      set(USE_OpenMP OFF)
    endif()
    set(CMAKE_C_COMPILER "/opt/homebrew/Cellar/gcc@12/12.3.0/bin/gcc-12")
    set(CMAKE_CXX_COMPILER "/opt/homebrew/Cellar/gcc@12/12.3.0/bin/gcc-12")
  else()
    set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")  # Replace with the path to your GCC 13 executable
  endif()
endif()

# Find OpenMP
if(APPLE AND USE_OpenMP)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
    set(OpenMP_CXX_FLAGS "-fopenmp")
    set(OpenMP_CXX_LIB_NAMES "libomp")
    set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
  endif()
endif()

# Find OpenMP
if (USE_OpenMP)
  find_package(OpenMP REQUIRED)
endif()

if (OPENMP_FOUND)
  # Print that we are using OpenMP
  message(STATUS "Using OpenMP for parallelization")
  set(HAVE_OPENMP 1)
  
  # Enable OpenMP support for the target
  # target_link_libraries(neural-library PUBLIC OpenMP::OpenMP_CXX)
  
  # Set OpenMP flags
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

  set(OpenMP_CXX_INCLUDE_DIRS "/opt/homebrew/Cellar/libomp/16.0.6/include")
  target_include_directories(neural-library PUBLIC ${OpenMP_CXX_INCLUDE_DIRS})
endif()


target_compile_features(neural-library PUBLIC cxx_std_14)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

