cmake_minimum_required(VERSION 3.31)

project(Nanbou)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG f6864924f76e1a0b4abaefc76ae2ed22b1a8916e
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SDL3)

add_executable(nanbou WIN32
    "src/main.cpp"
    "src/game.cpp"
    "src/player.cpp"
)
target_link_libraries(nanbou SDL3::SDL3)

add_custom_command(TARGET nanbou POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:nanbou>/res"
)

if (WIN32)
    add_custom_command(TARGET nanbou POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:nanbou>
        $<TARGET_FILE_DIR:nanbou>
    )
endif()
