#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


template <typename T>
T to_number(vector<int>* a) {
    unsigned long long int val = 0;
    int correction_shift = sizeof(T)*8 -1;
    for(unsigned long long int digit: *a) {
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

void print_fields(vector<int>* dump) {
    int lenexp;
    dump->size() == 64 ? lenexp = 11 : lenexp = 8 ;
    auto exp_end = next(dump->begin() + 1, lenexp);
    auto curpos = dump->begin() + 1;
    cout << dump->front() << ' ';
    for(curpos; curpos < exp_end ; curpos++)
        cout << *curpos;
    cout << ' ';
    for(curpos; curpos < dump->end() ; curpos++)
        cout << *curpos;
}

template <typename T>
T get_mantis(vector<int>* dump){
    int lenexp;
    T mantis = 0;
    dump->size() == 64 ? lenexp = 11 : lenexp = 8;
    auto mantbeg = next(dump->begin() +1, lenexp);
    int initial_pow = -1;
    for(auto it = mantbeg; it < dump->end(); it++) {
        mantis += *it * pow(2, initial_pow);
        initial_pow--;
    }
    return mantis;
}

int get_exponent(vector<int>* dump){
    int lenexp, expshift;
    int exponent = 0;
    dump->size() == 64 ? lenexp = 11 : lenexp = 8;
    dump->size() == 64 ? expshift = 1023 : expshift = 127;
    auto expend = next(dump->begin() +1, lenexp);
    for(auto it = dump->begin()+1; it < expend; it++) {
        exponent |= (*it << lenexp-1);
        lenexp--;
    }
    return exponent - expshift;
}

template <typename T>
T get_number_by_formula(vector<int>* dump) {
    T mantissa = get_mantis<T>(dump);
    int exponent = get_exponent(dump);
    T val = (1 + mantissa) * pow(2, exponent);
    if(dump->front() == 1) val *= -1;
    return val;
}


int main() {
    float f = -44.69;
    vector<int> dump = dumper(f);
    cout << "Binary fields: ";
    print_fields(&dump);
    cout << endl;
    cout << "Exponent: " << get_exponent(&dump) << endl;
    cout << "Mantissa: " << get_mantis<float>(&dump) << endl;
    cout <<  "From dump to number (using cast): " << to_number<float>(&dump) << endl;
    cout << "Using formula: " << get_number_by_formula<float>(&dump) << endl;
}
