# Minimum version de CMake requise
cmake_minimum_required(VERSION 3.5)

# Nom du projet
project(Projet)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Configuration de la compilation C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pedantic -O3 -g")
set(CMAKE_EXE_LINKER_FLAGS)

# Déclaration des fichiers source
file(GLOB CPP_FILES src/*.cpp src/UI/*.cpp src/Helpers/*.cpp)
file(GLOB RC_FILES src/*.rc)

# Inclure les en-têtes
include_directories(include)

# Inclure les bibliothèques (remplace 'lib' par le chemin réel)
link_directories(lib)

# Lister les bibliothèques qu'on utilise
set(LIB_FILES SDL2 SDL2main SDL2_ttf SDL2_image)

# Créer une cible pour le programme
add_executable(program ${CPP_FILES} ${RC_FILES})


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# Lier les bibliothèques
target_link_libraries(program ${LIB_FILES})
