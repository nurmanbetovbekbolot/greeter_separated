# --- Import tools ----

include(../cmake/CPM.cmake)

# ---- Dependencies ----

CPMAddPackage(
        NAME cxxopts
        GITHUB_REPOSITORY jarro2783/cxxopts
        VERSION 2.2.0
        OPTIONS
        "CXXOPTS_BUILD_EXAMPLES Off"
        "CXXOPTS_BUILD_TESTS Off"
)

# ---- Create standalone executable ----

add_executable(greeter main.cpp)
target_link_libraries(greeter PRIVATE project_options project_warnings fmt::fmt cxxopts spdlog::spdlog)
