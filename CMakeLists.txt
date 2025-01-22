cmake_minimum_required (VERSION 3.8)

project ("sycamore")

# Output a static library
add_library (sycamore STATIC "include/Core.h"  "include/Graphics/Geometry.h" "include/Graphics/Material.h" "include/Graphics/MeshComponent.h" "include/Graphics/Renderer.h" "include/Graphics/Shader.h" "include/Graphics/Texture.h" "include/Graphics/Vertex.h" "src/Graphics/Geometry.cpp" "src/Graphics/Material.cpp" "src/Graphics/MeshComponent.cpp" "src/Graphics/Renderer.cpp" "src/Graphics/Shader.cpp" "src/Graphics/Texture.cpp" "src/Graphics/Vertex.cpp" "include/Engine/GameComponent.h" "include/Engine/GameObject.h" "include/Engine/Input.h" "include/Engine/Transform.h" "include/Engine/World.h" "src/Engine/GameComponent.cpp" "src/Engine/GameObject.cpp" "src/Engine/Input.cpp" "src/Engine/Transform.cpp" "src/Engine/World.cpp" "src/Engine/Camera.cpp" "include/Engine/Camera.h" "include/ThirdParty/GLFW/glfw3.h" "include/ThirdParty/GLFW/glfw3native.h" "include/ThirdParty/GL/eglew.h" "include/ThirdParty/GL/glew.h" "include/ThirdParty/GL/glxew.h" "include/ThirdParty/GL/wglew.h" "include/Engine/Application.h" "src/Engine/Application.cpp" "include/Sycamore.h" "include/Engine/Event.h" "include/Engine/Stopwatch.h" "src/Engine/Stopwatch.cpp" "include/Engine/Notify.h" "src/Engine/Notify.cpp")

# Use C++20
set_property(TARGET sycamore PROPERTY CXX_STANDARD 20)
set_property(TARGET sycamore PROPERTY CXX_STANDARD_REQUIRED ON)

# Setup include & library directories
target_include_directories(sycamore PUBLIC "./include/")
target_link_directories(sycamore PUBLIC "./lib/")

if (WIN32)
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		# x64 Windows
		target_link_directories(sycamore PUBLIC "./lib/win64")
	else ()
		# x86 Windows
		target_link_directories(sycamore PUBLIC "./lib/win32")
	endif ()
endif ()

# Add third party include directories
target_include_directories(sycamore PUBLIC "./include/ThirdParty/")
target_include_directories(sycamore PUBLIC "./include/ThirdParty/glm/")

# Link against static libraries
target_link_libraries(sycamore PUBLIC glew32s glfw3 opengl32 assimp-vc143-mtd)
add_compile_definitions(GLEW_STATIC)

# Optionally build example executables
option(BUILD_EXAMPLES "Whether or not the example executables should be built" true)

if (BUILD_EXAMPLES)
	project ("sycamore_examples")

	add_executable (sycamore_examples "examples/HelloCube/Main.cpp")
	target_link_libraries(sycamore_examples sycamore)

	# Transfer runtime dependencies (DLLs and the like) to binary output directory
	add_custom_command(TARGET sycamore_examples POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		"${CMAKE_CURRENT_SOURCE_DIR}/assimp-vc143-mtd.dll"              
		$<TARGET_FILE_DIR:sycamore_examples>)
endif ()