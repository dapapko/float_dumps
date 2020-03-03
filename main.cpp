#include <iostream>
#include <vector>
using namespace std;


void dumper(vector<char>* dump, unsigned short int value) {
    short int mask = 1;
    int base_shift = 1;
    int correction_shift = 0;
    int upperbound = 16;
    for(int i = 0; i < upperbound; i++) {
        int digit = (value & mask) >> correction_shift;
        mask <<= base_shift;
        correction_shift += base_shift;
        char dig = (digit == 0  ? '0' : '1');
        dump->insert(dump->begin(), dig);
    }
}


template <typename T>
vector<char> fdumper(T value) {
    vector<char> dump = vector<char>();
    int iterations;
    sizeof(T) == 4 ? iterations = 2 : iterations = 4;
    T* pValue = &value;
    auto* p = reinterpret_cast<unsigned short int*>(pValue);
    for(int i=0; i < iterations;i++)
        dumper(&dump, p[i]);
    return dump;
}


void get_inner_representation(vector<char> dump) {
    int lenexp;
    dump.size() == 64 ? lenexp = 11 : lenexp = 8 ;
    auto it1 = next(dump.begin() + 1, lenexp);
    auto begin = dump.begin() + 1;
    cout << dump.back() << ' ';
    for(begin; begin < it1 ; begin++)
        cout << *begin;
    cout << ' ';
    for(auto a = begin; a <= dump.end() ; a++)
        cout << *a;
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
    double f = 12.34;
    std::vector<char> dump = fdumper(f);
    cout << endl;
    get_inner_representation(dump);
    double a = bin_to_number<double>(dump);
    cout << endl << a;
}
