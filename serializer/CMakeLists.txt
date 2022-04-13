cmake_minimum_required(VERSION 3.21)

project("json_serializer" VERSION 1.0.0
        DESCRIPTION "A lightweight JSON serializer in C."
        HOMEPAGE_URL "https://github.com/BobAaldering/"
        )

add_library(json_serializer)

target_sources(json_serializer
        PRIVATE

        ./src/json_serializer.c
        )

target_compile_features(json_serializer PUBLIC c_std_99) # Default C++ version is CPP17.

target_include_directories(json_serializer PUBLIC ./inc) # Include these extra libraries. Used for a better overview of this library.

set_target_properties(json_serializer PROPERTIES C_EXTENSIONS OFF) # Disable all language specific extensions.

# Set options for GNU-like compilers.
target_compile_options(json_serializer PUBLIC
        # Set warnings for all build types.
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer>
        # O3 optimisation in 'Release'.
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
        # Optimisation in 'Debug'.
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g>
        )

# Set options for MSVC compiler.
target_compile_options(json_serializer PUBLIC
        # Set warnings for all build types.
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        # O2 optimisation in 'Release'.
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
        # Optimisation in 'Debug'.
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/RTC1 /Od /Zi>
        )
