add_executable(DragonEngine WIN32
        main.cpp
        core/DragonEngine.cpp
        core/DragonEngine.h
        core/windows/MinWindows.h
        core/windows/Window.cpp
        core/windows/Window.h
        core/logger/Logger.cpp
        core/logger/Logger.h
        core/logger/FileSink.cpp
        core/logger/FileSink.h
        core/input/InputSystem.cpp
        core/input/InputSystem.h)

set_property(TARGET DragonEngine PROPERTY CXX_STANDARD 20)
set_property(TARGET DragonEngine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET DragonEngine PROPERTY CXX_EXTENSIONS OFF)