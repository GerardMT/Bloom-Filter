
#include <iostream>
#include <fstream>
#include <cmath>
#include "bloom_filter_string.hpp"

using namespace std;

int main() {
    fstream file;
    string filename("../data/lorem_ipsum.txt");
    file.open(filename);
    if (!file.is_open()) {
        cout << "Could not open file " << filename << endl;
        return 1;
    }

    string word;
    unsigned int n = 0;
    while (file >> word) {
        ++n;
    }

    float e = 0.1; // error (from 0 to 1)
    auto m = static_cast<unsigned int>(ceil(-static_cast<float>(n) * log(e) / (log(2) * log(2)))); // size of the array
    auto k = static_cast<unsigned int>(ceil(-log2(e))); // number of hash functions

    cout << "Error required: " << e << "\n";
    cout << "File words: " << n << "\n";
    cout << "Array size: " << m << "\n";
    cout << "Hash functions: " << k << "\n";
    cout << endl;

    bloom_filter_string filter(m, n / m, k);

    file.clear();
    file.seekg(0, ios::beg);
    while (file >> word) {
        filter.insert(word);
    }

    string val;

    val = "lorem";
    cout << "contains " << val << ": " << filter.contains(val) << endl;

    val = "ultricies";
    cout << "contains " << val << ": " << filter.contains(val) << endl;

    val = "ut";
    cout << "contains " << val << ": " << filter.contains(val) << endl;

    val = "maximus";
    cout << "contains " << val << ": " << filter.contains(val) << endl;


    val = "australopitec";
    cout << "contains " << val << ": " << filter.contains(val) << endl;
    cout << "insert " << val << endl;
    filter.insert(val);
    cout << "insert " << val << endl;
    filter.insert(val);
    cout << "contains " << val << ": " << filter.contains(val) << endl;
    cout << "erase " << val << ": " << filter.erase(val) << endl;
    cout << "contains " << val << ": " << filter.contains(val) << endl;
    cout << "erase " << val << ": " << filter.erase(val) << endl;
    cout << "contains " << val << ": " << filter.contains(val) << endl;
    cout << "erase " << val << ": " << filter.erase(val) << endl;

    return 0;
}