#include <iostream>
#include <vector>
using namespace std;


template <typename T>
T to_number(vector<int> a) {
    unsigned long long int val = 0;
    int correction_shift = sizeof(T)*8 -1;
    for(unsigned long long int digit: a) {
        val = val | (digit << correction_shift);
        correction_shift--;
    }
    T f = *reinterpret_cast<T*>(&val);
    return f;
}

template <typename T>
vector<int> dumper(T a) {
    unsigned long long int ifloat = *reinterpret_cast<unsigned long long int*>(&a);
    vector<int> dump = vector<int>();
    unsigned long long int mask = 1;
    int digit;
    int correction_shift = 0;
    for(int i=0;i<sizeof(T)*8;i++) {
        digit = (ifloat & mask) >> correction_shift;
        dump.insert(dump.begin(), digit);
        correction_shift++;
        mask <<= 1;
    }
    return dump;
}

void print_fields(vector<int> dump) {
    int lenexp;
    dump.size() == 64 ? lenexp = 11 : lenexp = 8 ;
    auto exp_end = next(dump.begin() + 1, lenexp);
    auto curpos = dump.begin() + 1;
    cout << dump.front() << ' ';
    for(curpos; curpos < exp_end ; curpos++)
        cout << *curpos;
    cout << ' ';
    for(curpos; curpos <= dump.end() ; curpos++)
        cout << *curpos;
}

int main() {
    float f = -123.45;
    vector<int> dump = dumper(f);
    float r = to_number<float>(dump);
    print_fields(dump);
    cout << endl << r;
}
