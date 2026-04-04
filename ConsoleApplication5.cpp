#include <iostream>
#include <fstream>
#include <ctime>

struct LogRecord {
    int id;
    int timestamp;
    float value;
    char status;
};

int main() {

    std::srand(static_cast<unsigned>(time(nullptr)));
    const char* filename = "File.bin";
    const int count = 10;

    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cout << "Error: Невозможно открыть файл" << std::endl;
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        LogRecord record;
        record.id = i + 1;
        record.timestamp = std::rand() % 100000;
        record.value = (std::rand() % 1000) / 10.0f;
        record.status = 'A' + (std::rand() % 4);

        outFile.write(reinterpret_cast<const char*>(&record), sizeof(LogRecord));
    }
    outFile.close();

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) return 1;

    std::cout << "ID\tTimestamp\tValue\tStatus" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    LogRecord readRecord;
    while (inFile.read(reinterpret_cast<char*>(&readRecord), sizeof(LogRecord))) {
        std::cout << readRecord.id << "\t"
            << readRecord.timestamp << "\t\t"
            << readRecord.value << "\t"
            << readRecord.status << std::endl;
    }

    inFile.clear();
    inFile.seekg(0, std::ios::end);
    long fileSize = static_cast<long>(inFile.tellg());

    std::cout << "\nFile size: " << fileSize << " bytes" << std::endl;

    inFile.close();
    return 0;
}