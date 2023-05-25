#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>

double add(int count);
double sub(int count);
double mul(int count);
double div(int count);

void saveToFile(double a, double b, double c, double d, int count);

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    int counts[] = {2048, 4096, 8192};

    for (int i = 0; i < 3; ++i) {
        double timeA = add(counts[i]);
        double timeS = sub(counts[i]);
        double timeM = mul(counts[i]);
        double timeD = div(counts[i]);

        saveToFile(timeA, timeS, timeM, timeD, counts[i]);
    }

    return 0;
}

double add(int count) {
    double totalTime = 0;
    double avgTime = 0;
    float arr[4] = {0, 0, 0, 0};

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < count; ++j) {
            float array[4];
            for (int k = 0; k < 4; ++k) {
                array[k] = rand();
                std::chrono::high_resolution_clock::time_point x = std::chrono::high_resolution_clock::now();
                arr[k] += array[k];
                double y = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - x).count();
                totalTime += y;
            }
        }
    }

    avgTime = totalTime / (10 * count);
    return avgTime;
}

double sub(int count) {
    double totalTime = 0;
    double avgTime = 0;
    float arr[4] = {0, 0, 0, 0};

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < count; ++j) {
            float array[4];
            for (int k = 0; k < 4; ++k) {
                array[k] = rand();
                std::chrono::high_resolution_clock::time_point x = std::chrono::high_resolution_clock::now();
                arr[k] -= array[k];
                double y = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - x).count();
                totalTime += y;
            }
        }
    }

    avgTime = totalTime / (10 * count);
    return avgTime;
}

double mul(int count) {
    double totalTime = 0;
    double avgTime = 0;
    float arr[4] = {0, 0, 0, 0};

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < count; ++j) {
            float array[4];
            for (int k = 0; k < 4; ++k) {
                array[k] = rand();
                std::chrono::high_resolution_clock::time_point x = std::chrono::high_resolution_clock::now();
                arr[k] *= array[k];
                double y = std::chrono::duration_cast<std::chrono

::microseconds>(std::chrono::high_resolution_clock::now() - x).count();
                totalTime += y;
            }
        }
    }

    avgTime = totalTime / (10 * count);
    return avgTime;
}

double div(int count) {
    double totalTime = 0;
    double avgTime = 0;
    float arr[4] = {1, 1, 1, 1};

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < count; ++j) {
            float array[4];
            for (int k = 0; k < 4; ++k) {
                array[k] = rand();
                std::chrono::high_resolution_clock::time_point x = std::chrono::high_resolution_clock::now();
                arr[k] /= array[k];
                double y = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - x).count();
                totalTime += y;
            }
        }
    }

    avgTime = totalTime / (10 * count);
    return avgTime;
}

void saveToFile(double a, double b, double c, double d, int count) {
    std::string filename = std::to_string(count) + ".txt";

    std::ofstream file(filename);

    file << "Typ obliczen: SISD\n";
    file << "Liczba liczb: " << count << "\n";
    file << "Sredni czas [us]: \n";
    file << "+ " << a << "\n";
    file << "- " << b << "\n";
    file << "* " << c << "\n";
    file << "/ " << d << "\n";

    file.close();
}
