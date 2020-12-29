cmake_minimum_required(VERSION 3.17)
project(proton-chess LANGUAGES C VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)

# Sources
set(LIBRARY_MAIN_SOURCES
        src/library/chess.c src/library/stringutils.c)
set(LIBRARY_MAIN_TEST_SOURCES
        test/chess.test.c)

set(FEN_EXT_SOURCES
        src/extensions/fen.c)
set(FEN_EXT_TEST_SOURCES
        test/fen.test.c)

set(IE_EXT_SOURCES
        src/extensions/import_export.c)

set(POC_SOURCES
        src/applications/poc.c)

# Include directories
set(LIBRARY_INCLUDE_DIRECTORIES
        ${CMAKE_BINARY_DIR}/include)
set(TEST_INCLUDE_DIRECTORIES
        lib/scpunitc/src/include)

# Options
option(FEN_EXTENSIONS "Enable proton-chess FEN extensions." ON)
option(IMPORT_EXPORT_EXTENSIONS "Enable proton-chess Import/Export extensions." ON)

# Configure extensions header
configure_file(src/include/extensions.h.in ${CMAKE_BINARY_DIR}/include/extensions.h)
configure_file(src/include/chess.h.in ${CMAKE_BINARY_DIR}/include/chess.h)

## Targets

# Main library
add_library(protonchess ${LIBRARY_MAIN_SOURCES})

if(FEN_EXTENSIONS)
    target_sources(protonchess PUBLIC ${FEN_EXT_SOURCES})
endif()

if(IMPORT_EXPORT_EXTENSIONS)
    target_sources(protonchess PUBLIC ${IE_EXT_SOURCES})
endif()

target_include_directories(protonchess PUBLIC ${LIBRARY_INCLUDE_DIRECTORIES})

## Tests

# Tests target
add_custom_target(proton-chess-tests-all)

# Add in unit testing library
add_subdirectory(lib/scpunitc)

# Main Library
add_executable(libprotonchess-tests ${LIBRARY_MAIN_TEST_SOURCES})
target_link_libraries(libprotonchess-tests protonchess)
target_include_directories(libprotonchess-tests PUBLIC ${LIBRARY_INCLUDE_DIRECTORIES} SYSTEM ${TEST_INCLUDE_DIRECTORIES})
add_dependencies(proton-chess-tests-all libprotonchess-tests)

# FEN Extensions
if(FEN_EXTENSIONS)
    add_executable(fen-extensions-tests ${FEN_EXT_TEST_SOURCES})
    target_link_libraries(fen-extensions-tests protonchess)
    target_include_directories(fen-extensions-tests PUBLIC ${LIBRARY_INCLUDE_DIRECTORIES} SYSTEM ${TEST_INCLUDE_DIRECTORIES})
    add_dependencies(proton-chess-tests-all fen-extensions-tests)
endif()

# Import Export Extensions
if(IE_EXT_SOURCES)
    add_executable(ie-extensions-tests ${IE_EXT_TEST_SOURCES})
    target_link_libraries(ie-extensions-tests protonchess)
    target_include_directories(ie-extensions-tests PUBLIC ${LIBRARY_INCLUDE_DIRECTORIES} SYSTEM ${TEST_INCLUDE_DIRECTORIES})
    add_dependencies(proton-chess-tests-all ie-extensions-tests)
endif()

## Applications

# proton-chess proof of concept
add_executable(proton-chess-poc ${POC_SOURCES})
target_link_libraries(proton-chess-poc protonchess)
target_include_directories(proton-chess-poc PUBLIC ${LIBRARY_INCLUDE_DIRECTORIES})

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
