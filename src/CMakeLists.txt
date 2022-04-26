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
        core/input/InputSystem.h
        core/graphics/GraphicsSystem.cpp
        core/graphics/GraphicsSystem.h
        core/entities/Entity.cpp
        core/entities/Entity.h
        core/entities/Scene.cpp
        core/entities/Scene.h
        core/graphics/Cube.cpp
        core/graphics/Cube.h
        core/graphics/VertexShader.cpp
        core/graphics/VertexShader.h
        core/graphics/PixelShader.cpp
        core/graphics/PixelShader.h
        core/graphics/InputLayout.cpp
        core/graphics/InputLayout.h
        core/graphics/VertexBuffer.cpp
        core/graphics/VertexBuffer.h
        core/graphics/IndexBuffer.cpp
        core/graphics/IndexBuffer.h
        core/entities/Camera.cpp
        core/entities/Camera.h
        core/graphics/ConstantBuffer.cpp
        core/graphics/ConstantBuffer.h
        core/graphics/Topology.cpp
        core/graphics/Topology.h)

set_property(TARGET DragonEngine PROPERTY CXX_STANDARD 20)
set_property(TARGET DragonEngine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET DragonEngine PROPERTY CXX_EXTENSIONS OFF)

target_link_libraries(DragonEngine PRIVATE d3d11 d3dcompiler)