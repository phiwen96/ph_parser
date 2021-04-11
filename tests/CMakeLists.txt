# Testing library
ph_fetch (catch2)
file(GLOB_RECURSE HEADER_LIST "include/*.hpp")
file(GLOB SOURCE_LIST *.cpp)
add_executable (testlib ${SOURCE_LIST} ${HEADER_LIST})
target_link_libraries (testlib PRIVATE ph::macros ph::coroutines ph::type_list ${PROJECT_NAME} Catch2::Catch2)
target_include_directories (testlib PRIVATE include)
ph_precompile (TARGET testlib PRIVATE PCH ${std_pch})
add_test (NAME testlibtest COMMAND testlib) 
 






