# hnStat

A (hopefully) fast and efficient TSV parser.

The assignment took about 10 hours to complete.

## Usage

Build with:
```
cmake . && make
```

Run with:
```
hnStat distinct [--from <timestamp>] [--to <timestamp>] <input_file>
hnStat top <nb_top_queries> [--from <timestamp>] [--to <timestamp>] <input_file>
```

## Architecture

The build system uses CMake.

The code is split across several files and classes.

- **main.cpp** parses the first part of the command-line and executes the appropriate subcommand
- **ISubcommand.h** provides an interface implemented by both subcommands, 'distinct' and 'top'
- **Distinct.cpp/h** and **Top.cpp/h**  execute their respective subcommand

## Benchmarks

While they are specific to the machine onto which I am running the application, these benchmarks give an idea on the complexity of the operations.
All the benchmarks are performed without '--from' or '--to' options.

### 'distinct' results

The 'distinct' subcommand has 3 different implementations, plus a reference one.

1. Filling a vector with all the search strings, without removing duplicates. This only serves as a reference point to compare the other solutions
2. Filling a vector with all the search strings, then sorting it, then removing the consecutive duplicates with std::unique
3. Filling an std::set, which automatically discards duplicates
4. Filling an std::unordered_set, which does the same as std::set but with a different internal implementation

|         | 0. std::vector (does not count) | 1. std::vector + std::unique | 2. std::set | 3. std::unordered_set |
| --- | --- | --- | --- | --- |
| Results (avg. of 5 runs) | 240ms | 905ms | 915ms | 550ms |

### 'top 10' results

The 'top' subcommand has 2 different implementations.

3. Filling an std::map, with the key being the search string, and the value the number of occurrences
4. Filling an std::unordered_map, same as above

|         | 1. std::map | 2. std::unordered_map
| --- | --- | --- |
| Results (avg. of 5 runs) | 1025ms | 585ms |

## Complexity

The benchmarks give an overall idea on the performance of the subcommands, but it is also interesting to take a look at the complexity of the implementations, both in terms of memory and speed.

For the complexity calculations, `n` is the number of lines in the input file.

### distinct

For the 'distinct' subcommand, std::set and std::unordered_set differ essentially by their internal implementation. We will also take a look at the std::vector + std::unique implementation.

- 1. std::vector is a contiguous array in memory, so it is the most efficient space-wise. Its space complexity is O(n). It also provides decent speed, which is the sum of the insertions, the sorting, and the deduplicating. Insertion takes O(1) per item thus O(n) for all items, sorting takes O(n log n) according to https://en.cppreference.com/w/cpp/algorithm/sort, and deduplicating takes O(n) according to http://www.cplusplus.com/reference/algorithm/unique/. Thus it takes O(n + n log n + n) or more simply O(n log n) by removing the constants.
- 2. std::set is often implemented with a red-black tree. According to http://www.cplusplus.com/reference/set/set/insert/, for n elements inserted the time complexity is O(n log (m+n)), with m the size of the container. Assuming it is using a tree, its space complexity is O(n) plus some overhead due to storing pointers to the nodes.
- 3. std::unordered_set is implemented with a hash table divided into buckets, according to the standard. Insertion is O(1) per item according to https://en.cppreference.com/w/cpp/container/unordered_set/insert, thus O(n) for all items. Its space complexity is O(n) plus some overhead due to having buckets and hashes pointing to the actual data.

If memory is an issue, the first solution with the vector is clearly the best one, as it has no memory overhead. It is also slightly more efficient than the std::set solution.

If performance is desired, the third solution with the unordered set is the best one, as it inserts each item in constant time.

### top

For the 'top' subcommand, we will see std::map and std::unordered_map, which are analogous to std::set and std::unordered_set respectively.

- 1. std::map, like std::set, is often implemented with a red-black tree. It has the same complexity, so O(n log (m + n)) in time and O(n) in space.
- 2. std::unordered_map, like std::unordered_set, is implemented with a hash table divided into buckets. It has the same complexity, so O(n) in time and O(n) in space.

If memory is an issue, std::map might be preferred for slightly less overhead.

If performance is desired, the second solution with the unordered map is the best one, as it inserts each item in constant time.

After the insertion, the second part of the algorithm for both solutions is the same: we browse each item of the map and insert the biggest ones we find into a vector. The complexity of this operation is O(n).

## Ideas for improvements

This application could be further improved by:

- Improving the command-line parser, by better handling optional and required arguments, and being more resilient to user input
- Writing tests and documentation
