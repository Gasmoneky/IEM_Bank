cmake_minimum_required(VERSION 3.10)
project(IEM_Database_App)

# 1. Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Find System Threads (Fixes the -lthreads error)
find_package(Threads REQUIRED)

# 3. Configure Bundled GLFW
# We disable extras to speed up your build time
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/glfw)

# 4. Configure Bundled SQLite
add_library(sqlite3 STATIC third_party/sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC third_party/sqlite)

# 5. Define ImGui Source Files
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# 6. Gather Your App Source Code
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")

# 7. Create the Executable
add_executable(${PROJECT_NAME} ${APP_SOURCES} ${IMGUI_SOURCES})

# 8. Include Directories (Where the .h files live)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite
)

# 9. Link Everything Together
# We use 'Threads::Threads' to fix the Fedora linking issue
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    sqlite3
    GL 
    ${CMAKE_DL_LIBS}
    Threads::Threads
)