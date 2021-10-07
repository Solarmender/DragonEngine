set(CMAKE_CXX_STANDARD 20)

add_executable(DragonEngine WIN32
        main.cpp
        core/Windows/MinWindows.h core/Windows/Window.cpp core/Windows/Window.h core/DragonEngine.cpp core/DragonEngine.h)