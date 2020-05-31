
#include "bloom_filter_string.hpp"
#include "../murmur3/murmur3.h"

bloom_filter_string::bloom_filter_string(containers_size_type containers, elements_size_type elements, hash_size_type hashs) {
    _container.resize(containers);
    for (containers_size_type i = 0; i < containers; ++i) {
        _container[i] = static_cast<elements_size_type>(0);
    }

    _container_size = containers;
    _elements_size = elements;
    _hash_size = hashs;
}

void bloom_filter_string::insert (const string &s) {
    string key(s);
    for (bloom_filter_string::hash_size_type i = 0; i < _hash_size; ++i) {
        key.append(to_string(i));
        hash_type p = hash(key);

        if (_container[p] >= _elements_size - 1) {
          throw ElementOverflow();
        }

        ++_container[p];
        key.pop_back();
    }
}

bool bloom_filter_string::erase (const string &s) {
    string key(s);
    for (bloom_filter_string::hash_size_type i = 0; i < _hash_size; ++i) {
        key.append(to_string(i));
        hash_type p = hash(key);

        if (_container[p] > 0) {
            --_container[p];
        } else {
            return false;
        }

        key.pop_back();
    }

    return true;
}

bool bloom_filter_string::contains (const string &s) const {
    string key(s);
    for (bloom_filter_string::hash_size_type i = 0; i < _hash_size; ++i) {
        key.append(to_string(i));
        hash_type p = hash(key);

        if (_container[p] == 0) {
            return false;
        }

        key.pop_back();
    }

    return true;
}

bloom_filter_string::hash_type bloom_filter_string::hash (const string &s) const {
    hash_type h;
    MurmurHash3_x86_32(s.c_str(), s.size(), 0, &h);
    return h % _container_size;
}
