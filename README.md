# Edge Impulse Project

## Deskripsi
Project ini adalah implementasi model machine learning dari Edge Impulse menggunakan C++ dan TensorFlow Lite. Project ini menggunakan **CMake** sebagai sistem build.

## Prasyarat
Pastikan Anda sudah menginstal dependensi berikut:
- **CMake**: Sistem build.
- **Compiler C++**: GCC, Clang, atau compiler lainnya yang mendukung C++.
- **Edge Impulse SDK** (sudah termasuk dalam project).

## Langkah-Langkah Build dan Run

### 1. mengganti data pada baris

```cpp
std::string folder_path = "../training"; //dia mengeksekusi semua file yang ada dalam folder ini 
```
jalankan
```bash
cmake ..
make
```
### 2. Menjalankan Project
Setelah proses build selesai, jalankan file binary app.exe yang dihasilkan:
```bash
cd build
./app.exe
```
