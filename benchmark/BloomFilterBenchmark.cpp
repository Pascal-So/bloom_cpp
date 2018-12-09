#include <BloomFilter.hpp>
#include <hayai.hpp>
#include <string>
#include "minimal_console_outputter.hpp"

constexpr unsigned filterSize = 1000000;
constexpr double errorRate = 0.000001;

std::string benchmark_files_prefix;

// To see the actual benchmarks, scroll down to the end of the file

BloomFilter makeIntsFilter(const unsigned N, const double errorRate) {
    BloomFilter filter(N, errorRate);
    for (unsigned i = 0; i < N; ++i) {
        filter.add(std::to_string(i));
    }
    return filter;
}

class FilterFixture : public ::hayai::Fixture {
    BloomFilter filter {0,errorRate};

public:
    virtual void SetUp() {
        filter = makeIntsFilter(filterSize, errorRate);
    }

    void lookupContainedElement() {
        const auto elem = std::to_string(rand() % filterSize);
        filter.contains(elem);
    }

    void lookupNotContainedElement() {
        const auto elem = "foo " + std::to_string(rand() % 1000);
        filter.contains(elem);
    }

    void writeToFile(const std::string& filename) {
        filter.writeToFile(filename);
    }
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " + std::string(argv[0]) + " BENCHMARK_FILES_PREFIX\n";
        std::cerr << "\n";
        std::cerr << "       BloomFilterBenchmark needs to write some data to files\n";
        std::cerr << "       while running the benchmarks. You can provide the\n";
        std::cerr << "       directory and an optional prefix in the argument.\n";
        std::cerr << "       Note that you need to add a trailing slash if you\n";
        std::cerr << "       only provide a directory without filename prefix!\n";
        std::cerr << "\n";
        return 1;
    }

    // Having a mutable global for this is not the nicest solution, but
    // I couldn't think of a nicer way to pass variables to the fixture.
    benchmark_files_prefix = std::string(argv[1]);

    hayai::MinimalConsoleOutputter consoleOutputter;

    hayai::Benchmarker::AddOutputter(consoleOutputter);
    hayai::Benchmarker::RunAllTests();
}


// To disable individual benchmarks, add the prefix DISABLED_ to the
// test name, e.g. DISABLED_AddEntries

BENCHMARK(BloomFilter, AddEntries, 5, 1) {
    makeIntsFilter(filterSize, errorRate);
}
BENCHMARK_(BloomFilter, lookupContainedElement, FilterFixture, 3, 1000) {
    lookupContainedElement();
}
BENCHMARK_(BloomFilter, lookupNotContainedElement, FilterFixture, 3, 1000) {
    lookupNotContainedElement();
}
BENCHMARK_(BloomFilter, writeToFile, FilterFixture, 1, 5) {
    writeToFile(benchmark_files_prefix + "-bloom.bin");
}
