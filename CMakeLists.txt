cmake_minimum_required(VERSION 3.28)
project(Fellmare LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(fellmare "src/main.cpp"  "src/base/entity_list.cpp"  "src/entities/player.cpp" "src/base/entity2d.cpp")
target_compile_features(fellmare PRIVATE cxx_std_23)
target_link_libraries(fellmare PRIVATE SFML::Graphics SFML::Audio SFML::Main)
