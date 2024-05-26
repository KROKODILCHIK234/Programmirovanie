#include <iostream>
#include <chrono>

#include "vector.h"

using namespace std;


int josephus(Vector warriors, int step) {
    int remaining_warriors = warriors.getSize();
    int current_index = step - 1;
    while (remaining_warriors > 1) {
        warriors.remove(current_index);
        remaining_warriors--;
        current_index = (current_index + step - 1) % remaining_warriors;
    }
    return warriors[0];
}

int main(){
    setlocale(LC_ALL, "Ru");
    int n = 10000;
    int k = 2;
    Vector v1(n);
    for (int i = 1; i <= n; i++){
        v1.push_back(i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    int last_survivor = josephus(v1, k);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    cout << "last survivor: " << last_survivor << '\t' << duration.count() << endl; // 951425   370.122

    return 0;
}
