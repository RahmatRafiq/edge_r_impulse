// // 

// #include <iostream>
// #include <fstream>
// #include <vector>
// #include "json.hpp"  // Pastikan Anda memasukkan pustaka JSON yang telah diunduh
// #include "edge-impulse-sdk/classifier/ei_run_classifier.h"

// std::vector<float> load_json_data(const std::string& file_path) {
//     std::ifstream file(file_path);
//     if (!file.is_open()) {
//         throw std::runtime_error("Could not open file " + file_path);
//     }

//     nlohmann::json json_data;
//     try {
//         file >> json_data;
//     } catch (nlohmann::json::parse_error& e) {
//         std::cerr << "Error parsing JSON file: " << e.what() << std::endl;
//         throw;
//     }

//     // Mengambil nilai dari payload.values
//     std::vector<float> features;
//     for (const auto& value_array : json_data["payload"]["values"]) {
//         for (const auto& value : value_array) {
//             features.push_back(value.get<float>());
//         }
//     }

//     return features;
// }

// int main() {
//     std::cout << "Starting Edge Impulse inferencing..." << std::endl;

//     try {
//         // Ganti path dengan path yang benar
//         std::string file_path = "../testing/sp3_2024-03-31 (5).s1.json.52ld8v2c.ingestion-5547b88db7-gdv5c.json";
//         std::vector<float> features = load_json_data(file_path);
//         size_t features_size = features.size();

//         ei::signal_t signal;
//         signal.total_length = features_size;
//         signal.get_data = [&features](size_t offset, size_t length, float *out_ptr) -> int {
//             memcpy(out_ptr, features.data() + offset, length * sizeof(float));
//             return 0;
//         };

//         ei_impulse_result_t result = { 0 };
//         EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

//         if (res != EI_IMPULSE_OK) {
//             std::cerr << "Failed to run classifier: " << res << std::endl;
//             return 1;
//         }

//         std::cout << "Predictions:" << std::endl;
//         for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
//             std::cout << result.classification[ix].label << ": " << result.classification[ix].value << std::endl;
//         }

//     } catch (const std::exception& e) {
//         std::cerr << "Exception occurred: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }



// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <string>
// #include <cstdio>  // Untuk fungsi popen
// #include <cstring> // Untuk fungsi strcmp
// #include "json.hpp"  // Pastikan Anda memasukkan pustaka JSON yang telah diunduh
// #include "edge-impulse-sdk/classifier/ei_run_classifier.h"

// // Fungsi untuk memuat data JSON
// std::vector<float> load_json_data(const std::string& file_path) {
//     std::ifstream file(file_path);
//     if (!file.is_open()) {
//         throw std::runtime_error("Could not open file " + file_path);
//     }

//     nlohmann::json json_data;
//     try {
//         file >> json_data;
//     } catch (nlohmann::json::parse_error& e) {
//         std::cerr << "Error parsing JSON file: " << e.what() << std::endl;
//         throw;
//     }

//     // Mengambil nilai dari payload.values
//     std::vector<float> features;
//     for (const auto& value_array : json_data["payload"]["values"]) {
//         for (const auto& value : value_array) {
//             features.push_back(value.get<float>());
//         }
//     }

//     return features;
// }

// // Fungsi untuk menjalankan perintah shell dan menangkap outputnya
// std::vector<std::string> get_files_in_directory(const std::string& directory) {
//     std::vector<std::string> files;
//     std::string command = "dir /b " + directory + "/*.json"; // Perintah untuk mendapatkan file .json saja

//     FILE* pipe = _popen(command.c_str(), "r");
//     if (!pipe) {
//         throw std::runtime_error("popen() failed!");
//     }

//     char buffer[128];
//     while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
//         std::string file = buffer;
//         file.erase(file.find_last_not_of(" \n\r\t") + 1); // Menghapus karakter newline
//         files.push_back(directory + "/" + file);
//     }

//     _pclose(pipe);
//     return files;
// }

// int main() {
//     std::cout << "Starting Edge Impulse inferencing..." << std::endl;

//     // Path ke folder tempat file JSON berada
//     std::string folder_path = "../testing";

//     // Mendapatkan daftar file JSON dalam folder
//     std::vector<std::string> file_paths = get_files_in_directory(folder_path);

//     for (const auto& file_path : file_paths) {
//         try {
//             std::cout << "Processing file: " << file_path << std::endl;
//             std::vector<float> features = load_json_data(file_path);
//             size_t features_size = features.size();

//             ei::signal_t signal;
//             signal.total_length = features_size;
//             signal.get_data = [&features](size_t offset, size_t length, float *out_ptr) -> int {
//                 memcpy(out_ptr, features.data() + offset, length * sizeof(float));
//                 return 0;
//             };

//             ei_impulse_result_t result = { 0 };
//             EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

//             if (res != EI_IMPULSE_OK) {
//                 std::cerr << "Failed to run classifier: " << res << std::endl;
//                 continue;
//             }

//             std::cout << "Predictions for file " << file_path << ":" << std::endl;
//             for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
//                 std::cout << result.classification[ix].label << ": " << result.classification[ix].value << std::endl;
//             }

//         } catch (const std::exception& e) {
//             std::cerr << "Exception occurred while processing file " << file_path << ": " << e.what() << std::endl;
//             continue;
//         }
//     }

//     return 0;
// }


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>  // Untuk fungsi popen
#include <cstring> // Untuk fungsi strcmp
#include "json.hpp"  // Pastikan Anda memasukkan pustaka JSON yang telah diunduh
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"

// Fungsi untuk memuat data JSON
std::vector<float> load_json_data(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + file_path);
    }

    nlohmann::json json_data;
    try {
        file >> json_data;
    } catch (nlohmann::json::parse_error& e) {
        std::cerr << "Error parsing JSON file: " << e.what() << std::endl;
        throw;
    }

    // Mengambil nilai dari payload.values
    std::vector<float> features;
    for (const auto& value_array : json_data["payload"]["values"]) {
        for (const auto& value : value_array) {
            features.push_back(value.get<float>());
        }
    }

    return features;
}

// Fungsi untuk menjalankan perintah shell dan menangkap outputnya
std::vector<std::string> get_files_in_directory(const std::string& directory) {
    std::vector<std::string> files;
    std::string command = "dir /b \"" + directory + "\\*.json\""; // Tambahkan tanda kutip di sekitar path dan gunakan "\\" untuk Windows path

    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::string file = buffer;
        file.erase(file.find_last_not_of(" \n\r\t") + 1); // Menghapus karakter newline
        files.push_back(directory + "/" + file);
    }

    _pclose(pipe);
    return files;
}

int main() {
    std::cout << "Starting Edge Impulse inferencing..." << std::endl;

    // Path ke folder tempat file JSON berada
    std::string folder_path = "../training"; //dia mengeksekusi semua file yang ada dalam folder ini 

    // Mendapatkan daftar file JSON dalam folder
    std::vector<std::string> file_paths = get_files_in_directory(folder_path);

    for (const auto& file_path : file_paths) {
        try {
            std::cout << "Processing file: " << file_path << std::endl;
            std::vector<float> features = load_json_data(file_path);
            size_t features_size = features.size();

            ei::signal_t signal;
            signal.total_length = features_size;
            signal.get_data = [&features](size_t offset, size_t length, float *out_ptr) -> int {
                memcpy(out_ptr, features.data() + offset, length * sizeof(float));
                return 0;
            };

            ei_impulse_result_t result = { 0 };
            EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);

            if (res != EI_IMPULSE_OK) {
                std::cerr << "Failed to run classifier: " << res << std::endl;
                continue;
            }

            std::cout << "Predictions for file " << file_path << ":" << std::endl;
            for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
                std::cout << result.classification[ix].label << ": " << result.classification[ix].value << std::endl;
            }

        } catch (const std::exception& e) {
            std::cerr << "Exception occurred while processing file " << file_path << ": " << e.what() << std::endl;
            continue;
        }
    }

    return 0;
}



