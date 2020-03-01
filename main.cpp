//Task 1: from  binary string to float or double
// Task 2: from float or double to octal/hex/bin string

#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

using namespace std;

void dumper(vector<char>* dump, unsigned short int value, int base) {
    short int mask = 0b1111;
    int base_shift = log2(base);
    int correction_shift = 0;
    int upperbound = 16 / base_shift;
    if(base == 3) mask <<=1;
    else if (base == 1) mask <<=3;
    for(int i =0; i < upperbound; i++) {
        int digit = (value & mask) >> correction_shift;
        mask <<= base_shift;
        correction_shift += base_shift;
        char dig = (digit > 9 ? char(digit + 87) : char(digit + 48));
        dump->insert(dump->begin(), dig);
    }
}

template <typename T>
vector<char> fdumper(T value, int base) {
    vector<char> dump = vector<char>();
    int iterations;
    sizeof(T) == 4 ? iterations = 2 : iterations = 4;
    T* pValue = &value;
    auto* p = reinterpret_cast<unsigned short int*>(pValue);
    for(int i=0; i < iterations;i++)
        dumper(&dump, p[i], base);
    return dump;
}

template <typename T>
void get_inner_representation(T value) {
    int firstbound, secondbound, int sign_index;
    T* pValue = &value;
    auto* p = reinterpret_cast<long long int*>(pValue);
    bitset<64> dump = bitset<64>(*p);
    if(sizeof(T) == 8) {
        firstbound = 51;
        secondbound = 62;
        sign_index = 63;
    } else if (sizeof(T) == 4) {
        firstbound = 22;
        secondbound = 30;
        sign_index = 31;
    }
    cout << "Sign: " << dump[sign_index] << endl;
    cout  << "Exponent: ";
    for(int i = secondbound; i >firstbound ; i--)
        cout << dump[i];
    cout << endl << "Mantis: ";
    for(int i = firstbound; i > 0; i--)
        cout << dump[i];
}


int main() {
    float a = 1.5;
    get_inner_representation(a);
}