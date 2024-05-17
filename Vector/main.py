#include <iostream>

#include "vector.h"

using namespace std;

int josephus(int n, int k) {
    if (n == 1)
        return 1;
    else
        return (josephus(n - 1, k) + k - 1) % n + 1;
}

int main(){
    int n = 100;
    int k = 2;
    Vector v1(n);
    for (int i = 1; i <= n; i++){
        v1.push_back(i);
    }

    int idx = 0;
    while (v1.getSize() > 1) {
        idx = (idx + k - 1) % v1.getSize();
        v1.remove(v1[0]* + idx);
    }

    cout << v1 << endl;

    return 0;
}
