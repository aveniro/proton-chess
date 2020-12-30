cmake_minimum_required(VERSION 3.17)
project(proton-chess LANGUAGES C VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)

# Options
option(FEN_EXTENSIONS "Enable proton-chess FEN extensions." ON)
option(IMPORT_EXPORT_EXTENSIONS "Enable proton-chess Import/Export extensions." ON)
option(ENABLE_TESTING "Enable testing." ON)

# Configure headers
configure_file(include/extensions.h.in ${CMAKE_BINARY_DIR}/include/extensions.h)
configure_file(include/chess.h.in ${CMAKE_BINARY_DIR}/include/chess.h)

# Include directories
set(INCLUDE_DIRECTORIES
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/lib/pcmath/include
        ${CMAKE_SOURCE_DIR}/lib/pcmem/include
        ${CMAKE_SOURCE_DIR}/lib/pcstrings/include
        ${CMAKE_SOURCE_DIR}/lib/scpunitc/include
        ${CMAKE_CURRENT_BINARY_DIR}/include)

## Targets

# Helper libraries
add_subdirectory(lib/pcmath)
add_subdirectory(lib/pcmem)
add_subdirectory(lib/pcstrings)

if(ENABLE_TESTING)
    add_subdirectory(lib/scpunitc)
endif()

# Extensions
add_library(pcfen src/extensions/fen.c)
target_include_directories(pcfen PUBLIC ${INCLUDE_DIRECTORIES})

add_library(pcie src/extensions/import_export.c)
target_include_directories(pcie PUBLIC ${INCLUDE_DIRECTORIES})

# Main library
add_library(protonchess src/chess.c)
target_include_directories(protonchess PUBLIC ${INCLUDE_DIRECTORIES})
target_link_libraries(protonchess pcmath pcmem pcstrings)

if(FEN_EXTENSIONS)
    target_link_libraries(protonchess pcfen)
endif()

if(IMPORT_EXPORT_EXTENSIONS)
    target_link_libraries(protonchess pcie)
endif()

## Testing

if(ENABLE_TESTING)
    add_library(protonchess-test test/chess.test.c)
    target_link_libraries(protonchess-test protonchess)
    target_include_directories(protonchess-test PUBLIC ${INCLUDE_DIRECTORIES})

    add_executable(tests test/test.c)
    target_include_directories(tests PUBLIC ${INCLUDE_DIRECTORIES})
    target_link_libraries(tests protonchess-test pcstrings-test)

    if(FEN_EXTENSIONS)
        add_library(fen-ext-test test/extensions/fen.test.c)
        target_link_libraries(fen-ext-test protonchess pcstrings pcfen)
        target_include_directories(fen-ext-test PUBLIC ${INCLUDE_DIRECTORIES})

        target_link_libraries(tests fen-ext-test)
    endif()

    if(IMPORT_EXPORT_EXTENSIONS)
        add_library(ie-ext-test test/extensions/ie.test.c)
        target_link_libraries(fen-ext-test protonchess pcie)
        target_include_directories(ie-ext-test PUBLIC ${INCLUDE_DIRECTORIES})

        target_link_libraries(tests ie-ext-test)
    endif()
endif()

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_FILE_PATTERNS *.c *.h *.h.in)
    set(DOXYGEN_FULL_PATH_NAMES NO)
    set(DOXYGEN_GENERATE_MAN YES)
    doxygen_add_docs(documentation ./src ./lib ./test ${CMAKE_CURRENT_BINARY_DIR}/include)
else()
    message("WARNING: Doxygen could not be found! Documentation target could not be generated.")
endif()
