cmake_minimum_required(VERSION 3.10.0)
project(LatexGenCpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(src
    src/latexgen.cpp
)

# Bibliothèque principale
add_library(LatexGenCpp SHARED
    ${src}
)

# Adding a version to the library
set_target_properties(LatexGenCpp PROPERTIES VERSION 0.1.0 SOVERSION 0)

target_include_directories(LatexGenCpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)


# Add compiler flags for optimization and warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -O3
        -Wall
        # -Wextra
        # -Wpedantic
        # -Wno-unused-parameter
    )
elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /O2
        /W4
    )
endif()


# Création de l'exemple multilingue
add_executable(multilingual_example
    example/multilingual_example.cpp
)

target_link_libraries(multilingual_example
    PRIVATE
        LatexGenCpp
)


# Création de l'exemple d'article
add_executable(article_example
    example/article_example.cpp
)

target_link_libraries(article_example
    PRIVATE
        LatexGenCpp
)

# Création de l'exemple de livre
add_executable(book_example
    example/book_example.cpp
)

target_link_libraries(book_example
    PRIVATE
        LatexGenCpp
)

# Création de l'exemple d'index
add_executable(index_example
    example/index_example.cpp
)

target_link_libraries(index_example
    PRIVATE
        LatexGenCpp
)

# Création de l'exemple de présentation
add_executable(presentation_example
    example/presentation_example.cpp
)

target_link_libraries(presentation_example
    PRIVATE
        LatexGenCpp
)

# Création de l'exemple de rapport
add_executable(report_example
    example/report_example.cpp
)

target_link_libraries(report_example
    PRIVATE
        LatexGenCpp
)

# Configuration de l'installation
install(TARGETS LatexGenCpp
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Sofiane KHELLADI") #required
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.4)")
set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A C++ library for generating LaTeX documents.") #added description
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://codes.khelladi.page") #added homepage
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional") #added priority

include(CPack)