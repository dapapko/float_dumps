#include <iostream>
#include <fstream>
using namespace std;


template <typename T>
int* dumper(T a) {
    int size = sizeof(T)*8;
    int* dump = new int[size];
    auto val = *reinterpret_cast<unsigned long long int*>(&a);
    unsigned long long int mask = 1;
    int digit;
    int shift = 0;
    for (int i = size - 1; i >=0; i--) {
        digit = (val & mask) >> shift;
        shift++;
        mask <<= 1;
        dump[i] = digit;
    }
    return dump;
}


template <typename T>
void write(int* arr) {
    fstream out("file.txt", ios::out);
    if (!out.is_open()) {
        cout << "File can't be opened." << endl;
        exit(1);
    }
    for (int i = 0; i < sizeof(T) * 8; i++) {
        out << arr[i];
    }
    out.close();
}

template <typename T>
void read_from_file() {
    int size = sizeof(T)*8;
    fstream file("dump.txt");
    if (!file.is_open()) {
        cout << "File can't be opened." << endl;
        exit(1);
    }
    char* arr = new char[size];
    for (int i = 0; i < size; i++)
        cout << arr[i];
    dump.close();
}

int main() {
    float d = -23.65;
    int* dump = toDump(d);
    for(int i=0; i < sizeof(d)*8; i ++)
        cout << dump[i];
    cout << endl;
    write_to_file<float>(dump);
    read_from_file<float>();
}
