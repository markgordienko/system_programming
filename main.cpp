#include <iostream>
#include <bitset>
typedef int16_t WORD;

using namespace std;

int main() {
    WORD ar [] = {110, 1021, 2112, 312, 4323, 5501, 2316, 5317, 2318, 9123};

    for (int i = 0; i < 10; ++i) {
        if ((i + 1) % 2 == 0) {
            cout << i + 1 << " element:\n" << bitset<16> (ar[i]) << endl;
            ar[i] ^= 255;
            cout << bitset<16> (ar[i]) << endl;
            cout << (ar[i]) << "\n________________________________________________________________\n\n";
        }
    }

    return 0;
}
