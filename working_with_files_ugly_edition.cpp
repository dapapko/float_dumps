#include <iostream>
#include <fstream>
using namespace std;


template<typename T>
int* dumper(T number) {
    int* dump = new int[sizeof(T)*8];
    unsigned long long int value = *reinterpret_cast<unsigned long long int *>(&number);
    unsigned long long int mask = 1;
    int digit;
    int correction_shift = 0;
    for (int i = sizeof(T) * 8 - 1; i >= 0; i--) {
        digit = (value & mask) >> correction_shift;
        dump[i] = digit;
        correction_shift++;
        mask <<= 1;
    }
    return dump;
}


template <typename T>
void write_array_to_file(int array[]) {
    ofstream out;
    out.open("dump.txt");
    if (!out.is_open())
    {
        cout << "Writing error";
        exit(1);
    }
    for(int i=0; i < sizeof(T)*8;i++)
        out << array[i];
    out.close();
}


template <typename T>
char* read_from_file(){
    char* content = new char[sizeof(T)*8];
    ifstream dump_file("dump.txt");
    if (!dump_file.is_open())
    {
        cout << "Reading error";
        exit(1);
    }
    dump_file.getline(content, sizeof(T)*8);
    dump_file.close();
    return content;
}


template <typename T>
void print_dump(char* dump) {
    for(int i=0; i < sizeof(T)*8;i++)
        cout << dump[i];
}


int main() {
    float n = 12.34;
    int* dump = dumper(n);
    write_array_to_file<float>(dump);
    char* dump_from_file = read_from_file<float>();
    print_dump<float>(dump_from_file);
    delete[] dump;
    delete[] dump_from_file;
}


