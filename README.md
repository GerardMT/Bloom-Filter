# Bloom Filter
A simple non-generic implementation of a Counting Bloom filter.

A more complete documentation can be found [here](docs/report/report.pdf).

## Implemented operations
- Insert a string. *O(1)*.
- Erase a string (can returna a false positive). *O(1)*.
- Test whether the collection contains a string (can return a false positive). *O(1)*.

## Requirements
The software requires the *Murmur3* C library which is included in [murmur3/](murmur3).

## Provided example
### Build and run
Clone the repository:

	git clone https://github.com/GerardMT/Bloom-Filter
	cd Bloom-Filter

Compile the code:

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ../
	make

Simply run:

	./bloom-filter

### Execution output
```
Error required: 0.1
File words: 9285
Array size: 44499
Hash functions: 4

contains lorem: 1
contains ultricies: 1
contains ut: 1
contains maximus: 1
contains australopitec: 0
insert australopitec
insert australopitec
contains australopitec: 1
erase australopitec: 1
contains australopitec: 1
erase australopitec: 1
contains australopitec: 0
erase australopitec: 0
```