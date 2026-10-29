cmake_minimum_required(VERSION 3.10.0)
project(flakesdk VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#- Flake SDK engine library paths

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(ENGINE_DIR "${SRC_DIR}/flake_engine")
set(ENGINE_DEPENDENCIES_DIR "${CMAKE_SOURCE_DIR}/dependencies")
set(INCLUDE_DIR "${ENGINE_DEPENDENCIES_DIR}/include")
set(LIB_DIR "${ENGINE_DEPENDENCIES_DIR}/lib")

#- Flake SDK tools paths

set(SDK_TOOLS_DIR "${CMAKE_SOURCE_DIR}/src/flakesdk_tools")
set(SDK_TOOLS_EDITOR "${SDK_TOOLS_DIR}/flakeditor")
set(SDK_TOOLS_MAPPER "${SDK_TOOLS_DIR}/hinge_mapper")

#- GLF}

if(WIN32)
    add_library(glfw STATIC IMPORTED)

    set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION
            "${LIB_DIR}/GLFW/glfw3.lib"

        INTERFACE_INCLUDE_DIRECTORIES
            "${INCLUDE_DIR}/GLFW"
    )

    set(GLFW_TARGET glfw)
else()
    find_package(glfw3 REQUIRED)

    if(TARGET glfw)
        set(GLFW_TARGET glfw)
    elseif(TARGET glfw3::glfw)
        set(GLFW_TARGET glfw3::glfw)
    else()
        message(FATAL_ERROR
            "GLFW was found, but no usable GLFW target exists."
        )
    endif()
endif()

#- GLAD

set(GLAD_SOURCE "${INCLUDE_DIR}/glad.c")

if(NOT EXISTS "${GLAD_SOURCE}")
    message(FATAL_ERROR
        "Could not find glad.c at:\n"
        "  ${GLAD_SOURCE}"
    )
endif()

add_library(glad STATIC
    "${GLAD_SOURCE}"
)

target_include_directories(glad
    PUBLIC
        "${INCLUDE_DIR}"
)

#- ImGUI

set(IMGUI_DIR "${INCLUDE_DIR}/imgui")

add_library(imgui STATIC
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"

    "${IMGUI_DIR}/imgui_impl_glfw.cpp"
    "${IMGUI_DIR}/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui
    PUBLIC
        "${IMGUI_DIR}"
)

target_compile_definitions(imgui
    PRIVATE
        IMGUI_IMPL_OPENGL_LOADER_GLAD
)

target_link_libraries(imgui
    PUBLIC
        ${GLFW_TARGET}
        glad
)

#- GLM

set(GLM_DIR "${INCLUDE_DIR}/glm")

if(NOT EXISTS "${GLM_DIR}")
    message(WARNING
        "GLM was not found at:\n"
        "  ${GLM_DIR}\n"
        "Make sure GLM is installed in the dependencies/include directory."
    )
endif()

#-Flake SDK Engine (library)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    "${ENGINE_DIR}/*.cpp"
)

add_library(flakesdk STATIC
    ${ENGINE_SOURCES}
)

target_include_directories(flakesdk
    PUBLIC
        "${SRC_DIR}"
        "${ENGINE_DEPENDENCIES_DIR}"
)

if(EXISTS "${GLM_DIR}")
    target_include_directories(flakesdk
        PUBLIC
            "${INCLUDE_DIR}"
    )
endif()

target_link_libraries(flakesdk
    PUBLIC
        imgui
        glad
        ${GLFW_TARGET}
)

#- Flake SDK Editor (tool)

file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS
    "${SDK_TOOLS_EDITOR}/*.cpp"
)

add_executable(flakeditor
    ${EDITOR_SOURCES}
)

target_include_directories(flakeditor
    PRIVATE
        "${SRC_DIR}"
)

target_link_libraries(flakeditor
    PRIVATE
        flakesdk
)

#- Flake SDK Hinge Mapper (tool)

file(GLOB_RECURSE MAPPER_SOURCES CONFIGURE_DEPENDS
    "${SDK_TOOLS_MAPPER}/*.cpp"
)

add_executable(hinge_mapper
    ${MAPPER_SOURCES}
)

target_include_directories(hinge_mapper
    PRIVATE
        "${SRC_DIR}"
)

target_link_libraries(hinge_mapper
    PRIVATE
        flakesdk
)

#- Specific Compiler settings

if(MSVC)
    target_compile_options(flakesdk PRIVATE /W4)
    target_compile_options(flakeditor PRIVATE /W4)
    target_compile_options(hinge_mapper PRIVATE /W4)
    #target_compile_options(sandbox PRIVATE /W4)
else()
    target_compile_options(flakesdk PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(flakeditor PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(hinge_mapper PRIVATE -Wall -Wextra -Wpedantic)
    #target_compile_options(sandbox PRIVATE -Wall -Wextra -Wpedantic)
endif()