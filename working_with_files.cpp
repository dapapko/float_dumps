// Версия, поддерживающая операции чтения дампа из файла и записи в файл
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


template<typename T>
vector<int> dumper(T number) {
    unsigned long long int value = *reinterpret_cast<unsigned long long int *>(&number);
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



void write_to_file(vector<int>* content) {
    ofstream target;
    target.open("dump.txt");
    for(int digit: *content)
        target << digit;
    target << endl;
    target.close();
}


string read_from_file() {
    std::string dump_str;
    std::ifstream dump_file("dump.txt");
    dump_file >> dump_str;
    dump_file.close();
    return dump_str;
}


int main() {
    double f = -44.69;
    vector<int> dump = dumper<double>(f);
    cout << "From vector: ";
    for(int digit: dump)
        cout << digit;
    cout << endl;
    write_to_file(&dump);
    string content = read_from_file();
    cout << "From file:   " << content << endl;
}
