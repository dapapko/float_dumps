//Task 1: from  binary string to float or double
// Task 2: from float or double to octal/hex/bin string

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

void dumper(vector<char>* dump, unsigned short int value, int base) {
    short int mask = 0xf;
    if(base == 2) mask >>=3;
    int base_shift = 4;
    if(base == 2) base_shift = 1;
    int correction_shift = 0;
    int upperbound = 4;
    if(base == 2) upperbound = 16;
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
    int firstbound, secondbound, sign_index;
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
    cout << dump[sign_index] << ' ';
    for(int i = secondbound; i >firstbound ; i--)
        cout << dump[i];
    cout << ' ';
    for(int i = firstbound; i > 0; i--)
        cout << dump[i];
}


template<typename T>
T bin_to_number(vector<char> dump) {
    unsigned long long int digit, val;
    val = 0;
    int correction_shift = dump.size() - 1;
    for(char c: dump) {
        c == '0' ? digit = 0 : digit = 1;
        val |= (digit << correction_shift);
        correction_shift--;
    }
    T rvalue = *reinterpret_cast<T*>(&val);
    return rvalue;
}


int main() {
    float f = 12.34;
    std::vector<char> dump = fdumper(f, 2);
    get_inner_representation(f);
    float a = bin_to_number<float>(dump);
    cout << endl << a;
}
