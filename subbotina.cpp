#include <iostream>
#include <vector>
using namespace std;


void bin_dumper(vector<char>* dump, short int value) {
    short int mask = 040000;
    int bs = 1;
    int cs = 14;
    int upperbound = 15;
    value < 0 ? dump->push_back('1') : dump->push_back('0');
    for(int i = 0; i < upperbound; i++) {
        int digit = (value & mask) >> cs;
        mask >>= bs;
        cs -= bs;
        char d = (digit == 0  ? '0' : '1');
        dump->push_back(d);
    }
}


template <typename T>
vector<char> dumper(T value) {
    vector<char> bindump = vector<char>();
    int loop_counter;
    if (sizeof(T) == 4) loop_counter = 1;
    else loop_counter = 3;
    T* pValue = &value;
    auto* p = reinterpret_cast<short int*>(pValue);
    for(int i=loop_counter; i >= 0;i--)
        bin_dumper(&bindump, p[i]);
    return bindump;
}


void print_fields(vector<char> dump) {
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
    int cs = dump.size() - 1;
    for(char c: dump) {
        c == '0' ? digit = 0 : digit = 1;
        val = val | (digit << cs);
        cs--;
    }
    return *reinterpret_cast<T*>(&val);
}


int main() {
    float f = 12.34;
    std::vector<char> dump = dumper(f);
    cout << endl;
    print_fields(dump);
    float a = bin_to_number<float>(dump);
    cout << endl << a;
}