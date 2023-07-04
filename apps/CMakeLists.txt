# TODO: Create an executable for every .cpp file in this directory
add_executable(neural-networks 
    neural-networks.cpp
)
target_compile_features(neural-networks PRIVATE cxx_std_14)

target_link_libraries(neural-networks PRIVATE neural-library)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")