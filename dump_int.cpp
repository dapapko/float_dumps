#include <iostream>
#include <vector>
using namespace std;


void dumper(vector<int>* dump, unsigned short int value) {
    unsigned short int mask = 1;
    int base_shift = 1;
    int correction_shift = 0;
    int upperbound = 16;
    for(int i = 0; i < upperbound; i++) {
        int digit = (value & mask) >> correction_shift;
        mask <<= base_shift;
        correction_shift += base_shift;
        dump->insert(dump->begin(), digit);
    }
}


template <typename T>
vector<int> fdumper(T value) {
    vector<int> dump = vector<int>();
    int iterations;
    sizeof(T) == 4 ? iterations = 2 : iterations = 4;
    T* pValue = &value;
    auto* p = reinterpret_cast<unsigned short int*>(pValue);
    for(int i=0; i < iterations;i++)
        dumper(&dump, p[i]);
    return dump;
}


void get_inner_representation(vector<int> dump) {
    int lenexp;
    dump.size() == 64 ? lenexp = 11 : lenexp = 8 ;
    auto exp_end = next(dump.begin() + 1, lenexp);
    auto curpos = dump.begin() + 1;
    cout << dump.front() << ' ';
    for(curpos; curpos < exp_end ; curpos++)
        cout << *curpos;
    cout << ' ';
    for(curpos; curpos < dump.end() ; curpos++)
        cout << *curpos;
}


template<typename T>
T bin_to_number(vector<int> dump) {
    if(sizeof(T)*8 != dump.size())
        throw std::out_of_range("Invalid size of dump");
    unsigned long long int val = 0;
    int correction_shift = dump.size() - 1;
    for(unsigned long long int digit: dump) {
        val |= (digit << correction_shift);
        correction_shift--;
    }
    T rvalue = *reinterpret_cast<T*>(&val);
    return rvalue;
}


int main() {
    double f = -567.78;
    std::vector<int> dump = fdumper(f);
    get_inner_representation(dump);
    double a = bin_to_number<double>(dump);
    cout << endl << a;
}
