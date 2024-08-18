cmake_minimum_required(VERSION 3.13.1)

# Tambahkan project() untuk mendefinisikan proyek
project(RahmadaniProject)

# Tambahkan target executable sebelum include SDK
add_executable(app main.cpp)

# Sertakan utilitas dari SDK Edge Impulse
include(edge-impulse-sdk/cmake/utils.cmake)

# Tambahkan subdirektori yang berisi kode dari SDK
add_subdirectory(edge-impulse-sdk/cmake/zephyr)

# Temukan semua file sumber dalam folder "tflite-model" yang berakhiran ".cpp"
RECURSIVE_FIND_FILE_APPEND(MODEL_SOURCE "tflite-model" "*.cpp")

# Tambahkan direktori include untuk target app
target_include_directories(app PRIVATE .)

# Tambahkan semua file sumber yang ditemukan ke target app
target_sources(app PRIVATE ${MODEL_SOURCE})

# Menambahkan direktori include tempat json.hpp disimpan
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)
