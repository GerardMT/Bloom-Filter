
#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <vector>
#include <string>

using namespace std;

class bloom_filter_string {
public:
    typedef unsigned int containers_size_type;
    typedef unsigned int elements_size_type;
    typedef unsigned long hash_type;
    typedef unsigned short hash_size_type;

    struct ElementOverflow : public exception {
        const char *what () const noexcept override {
            return "Element overflow. Use a bigger number of elements and check that the hash function is uniform.";
        }
    };

    bloom_filter_string(containers_size_type containers, elements_size_type elements, hash_size_type hashs);

    /**
     * Insert a string.
     * @param s string to insert.
     */
    void insert (const string &s);

    /**
     * Erase an string. Can return a false positive.
     * @param s string to erase.
     * @return true if the string was erased (or a false positive). false if the string has not been found.
     */
    bool erase (const string &s);

    /**
     * Test whether the collection contains a string. Can return a false positive.
     * @param s string to test.
     * @return true if the collection contains the string (or a false positive). false if the collection does not contain the string.
     */
    bool contains (const string &s) const;

private:
    containers_size_type _container_size;
    elements_size_type _elements_size;
    hash_size_type _hash_size;

    vector<elements_size_type> _container;

    hash_type hash(const string &s) const;
};

#endif //BLOOM_FILTER_HPP
