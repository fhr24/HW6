#include <iostream>
#include <vector>

class Cache {
private:
    std::vector<int> cache;
    int cacheSize;
    int blockSize;
    int numCacheLines;
    int offsetBits;
    int indexBits;
    int hits;
    int misses;

    int getIndex(int address) {
        return (address >> offsetBits) & (numCacheLines - 1);
    }

public:
    Cache(int cacheSize, int blockSize) : cacheSize(cacheSize), blockSize(blockSize) {
        numCacheLines = cacheSize / blockSize;
        offsetBits = static_cast<int>(log2(blockSize));
        indexBits = static_cast<int>(log2(numCacheLines));
        cache.resize(numCacheLines, -1); // -1 represents an invalid block
        hits = 0;
        misses = 0;
    }

    void access(int address) {
        int index = getIndex(address);

        if (cache[index] == address) {
            // Cache hit
            hits++;
        } else {
            // Cache miss
            cache[index] = address;
            misses++;
        }
    }

    void printStatistics() {
        std::cout << "Cache Size: " << cacheSize << " bytes\n";
        std::cout << "Block Size: " << blockSize << " bytes\n";
        std::cout << "Number of Cache Lines: " << numCacheLines << "\n";
        std::cout << "Hits: " << hits << "\n";
        std::cout << "Misses: " << misses << "\n";
        double hitRatio = static_cast<double>(hits) / (hits + misses);
        std::cout << "Hit Ratio: " << hitRatio << "\n";
    }
};

int main() {
    int cacheSize, blockSize, numAccesses;
    std::cout << "Enter Cache Size (bytes): ";
    std::cin >> cacheSize;
    std::cout << "Enter Block Size (bytes): ";
    std::cin >> blockSize;

    Cache cacheSimulator(cacheSize, blockSize);

    std::cout << "Enter the number of memory accesses: ";
    std::cin >> numAccesses;

    for (int i = 0; i < numAccesses; i++) {
        int address;
        std::cout << "Access " << i + 1 << " - Enter memory address: ";
        std::cin >> address;
        cacheSimulator.access(address);
    }

    cacheSimulator.printStatistics();

    return 0;
}