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
    std::ofstream out;
    out.open("dump.txt");
    if (!out.is_open())
    {
       cout << "Writing error";
       exit(1);
    }
    for(int i=0; i < sizeof(T)*8;i++) 
        out << array[i];
}


template <typename T>
char* read_from_file(){
    char* content = new char[sizeof(T)*8];
    ifstream dump("dump.txt");
    if (!dump.is_open())
    {
        cout << "Reading error";
        exit(1);
    }
    int i=0;
    while( !dump.eof() && i < sizeof(T)*8)
    {
        dump.get(content[i]);
        i++;
    }
    return content;
}


template <typename T>
void print_from_file() {
    char* dump_from_file = read_from_file<T>();
    for(int i=0; i < sizeof(T)*8;i++)
        cout << dump_from_file[i];
    delete[] dump_from_file;
}


int main() {
    double n = 12.34;
    int* dump = dumper(n);
    write_array_to_file<double>(dump);
    print_from_file<double>();
    delete[] dump;
}
