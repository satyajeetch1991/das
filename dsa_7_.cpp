#include <iostream>
#include <string>
#include <vector>
#include <list>
class HashTableSeparateChaining {
    struct Entry {
        std::string key;
        std::string value;        
        Entry(const std::string &key, const std::string &value) : key(key), value(value) {}
    };    
    std::vector<std::list<Entry>> table;
    int size;
public:
    HashTableSeparateChaining(int size) : size(size) {
        table.resize(size);
    }
    void put(const std::string &key, const std::string &value) {
        int index = std::abs(static_cast<int>(std::hash<std::string>{}(key))) % size;
        for (auto &entry : table[index]) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }
    int get(const std::string &key) {
        int index = std::abs(static_cast<int>(std::hash<std::string>{}(key))) % size;
        int comparisons = 0;
        for (const auto &entry : table[index]) {
            comparisons++;
            if (entry.key == key) {
                return comparisons;
            }
        }
        return comparisons;
    }
};
class HashTableLinearProbing {
    std::vector<std::string> keys;
    std::vector<std::string> values;
    int size;
public:
    HashTableLinearProbing(int size) : size(size), keys(size), values(size) {}
    void put(const std::string &key, const std::string &value) {
        int index = std::abs(static_cast<int>(std::hash<std::string>{}(key))) % size;
        for (int i = 0; i < size; i++) {
            if (keys[index].empty() || keys[index] == key) {
                keys[index] = key;
                values[index] = value;
                return;
            }
            index = (index + 1) % size;
        }
    }
    int get(const std::string &key) {
        int index = std::abs(static_cast<int>(std::hash<std::string>{}(key))) % size;
        int comparisons = 0;
        for (int i = 0; i < size; i++) {
            comparisons++;
            if (!keys[index].empty() && keys[index] == key) {
                return comparisons;
            }
            index = (index + 1) % size;
        }
        return comparisons;
    }
};
int main() {
    int size;
    std::cout << "Enter the size of the hash table: ";
    std::cin >> size;
    HashTableSeparateChaining separateChainingTable(size);
    HashTableLinearProbing linearProbingTable(size);
    int numberOfClients;
    std::cout << "Enter the number of clients: ";
    std::cin >> numberOfClients;
    std::cin.ignore();  // Consume newline
    for (int i = 0; i < numberOfClients; i++) {
        std::string name, phone;        
        std::cout << "Enter the name of client " << (i + 1) << ": ";
        std::getline(std::cin, name);
        std::cout << "Enter the phone number of " << name << ": ";
        std::getline(std::cin, phone);
        separateChainingTable.put(name, phone);
        linearProbingTable.put(name, phone);
    }
    std::string searchName;
    std::cout << "Enter the name to search for comparisons: ";
    std::getline(std::cin, searchName);
    int comparisonsSeparateChaining = separateChainingTable.get(searchName);
    int comparisonsLinearProbing = linearProbingTable.get(searchName);
    std::cout << searchName << " - Separate Chaining comparisons: " << comparisonsSeparateChaining << std::endl;
    std::cout << searchName << " - Linear Probing comparisons: " << comparisonsLinearProbing << std::endl;
    return 0;
}
// Enter the size of the hash table: 10
// Enter the number of clients: 3
// Enter the name of client 1: Alice
// Enter the phone number of Alice: 12345
// Enter the name of client 2: Bob
// Enter the phone number of Bob: 67890
// Enter the name of client 3: Charlie
// Enter the phone number of Charlie: 54321
// Enter the name to search for comparisons: Bob
// output 
// Bob - Separate Chaining comparisons: 1
// Bob - Linear Probing comparisons: 1