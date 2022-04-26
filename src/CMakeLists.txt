file (GLOB_RECURSE CPP_FILES *.cpp)
file (GLOB_RECURSE H_FILES *.h)

set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

add_executable(DragonEngine WIN32 ${SOURCE_FILES})

set_property(TARGET DragonEngine PROPERTY CXX_STANDARD 20)
set_property(TARGET DragonEngine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET DragonEngine PROPERTY CXX_EXTENSIONS OFF)

target_link_libraries(DragonEngine PRIVATE d3d11 d3dcompiler)
