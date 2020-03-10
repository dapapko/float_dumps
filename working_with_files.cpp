// Версия, поддерживающая операции чтения дампа из файла и записи в файл
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

template<typename T>
vector<int> dumper(T a) {
    unsigned long long int value = *reinterpret_cast<unsigned long long int *>(&a);
    vector<int> dump = vector<int>();
    unsigned long long int mask = 1;
    int digit;
    int correction_shift = 0;
    for (int i = 0; i < sizeof(T) * 8; i++) {
        digit = (value & mask) >> correction_shift;
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

void writeTo(vector<int>* content) {
    ofstream target;
    target.open("dump.txt");
    target << "Dump: ";
    for(int digit: *content)
        target << digit;
    target << endl;
    target.close();
}

string read_and_print() {
    std::string dump_str;
    std::ifstream dump_file("dump.txt");
    while (dump_file >> dump_str);
    return dump_str;
}

int main() {
    double f = -44.69;
    vector<int> dump = dumper<double>(f);
    cout << "From vector: ";
    for(int digit: dump)
        cout << digit;
    cout << endl;
    writeTo(&dump);
    string content = read_and_print();
    cout << "From file: " << content;
}
