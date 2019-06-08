#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>

void insertion_sort(std::vector<int> & v){
    for(int k=1; k<v.size(); ++k) {
        int current = v[k];
        int j = k;
        while(j > 0) {
            if(current < v[j-1]) {
                v[j] = v[j-1];
            } else {
                break;
            }
            --j;
        }
        v[j] = current;
    }
}

double sort_time_a(int n) {
    std::vector<int> array;
    // guenstigster Fall: Array bereits sortiert
    for (int i = 0; i < n; i++) {
        array.push_back(i);
    }
    // Fall a)
    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(array);
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

double sort_time_b(int n) {
    std::vector<int> array;
    // schlechtester Fall: Array falsch herum (absteigend) sortiert
    for (int i = n; i > 0; i--) {
        array.push_back(i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(array);
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

double sort_time_c(int n) {
    std::vector<int> array;
    for (int i = 0; i < n; i++) {
        array.push_back(i);
    }
    // typischer Fall: Arrayelemente zufaellig angeordnet
    std::random_shuffle(array.begin(), array.end());

    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(array);
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

double sort_time_std(int n) {
    std::vector<int> array;
    for (int i = 0; i < n; i++) {
        array.push_back(i);
    }
    std::random_shuffle(array.begin(), array.end());

    auto start = std::chrono::high_resolution_clock::now();
    std::sort(array.begin(), array.end());
    auto stop = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    std::vector<double>lengths {5e3, 1e4, 5e4};

    std::vector<double>times_a;
    std::vector<double>times_b;
    std::vector<double>times_c;
    std::vector<double>times_std;

    for (auto n: lengths) {
        double sum_a = 0;
        double sum_b = 0;
        double sum_c = 0;
        double sum_std = 0;
        for (int i = 0; i < 3; i++) {
            sum_a += sort_time_a(n)/n;
            sum_b += sort_time_b(n)/(n*n);
            sum_c += sort_time_c(n)/(n*n);
            sum_std += sort_time_std(n)/(n*std::log(n));
        }
        times_a.push_back(sum_a/3.0);
        times_b.push_back(sum_b/3.0);
        times_c.push_back(sum_c/3.0);
        times_std.push_back(sum_std/3.0);
    }


    for (int i = 0; i < 3; i++)
    {
        std::cout << "Size: " << lengths.at(i) << ":" << std::endl;
        std::cout << "Best Case: " << times_a.at(i) << std::endl;
        std::cout << "Worst Case: " << times_b.at(i) << std::endl;
        std::cout << "Average Case: " << times_c.at(i) << std::endl;
        std::cout << "std::sort: " << times_std.at(i) << std::endl;
    }
}
