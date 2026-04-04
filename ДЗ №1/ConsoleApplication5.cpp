#include <iostream>
#include <fstream>
#include <ctime>

struct Item {
    int id;
    long code;
    float val;
    bool active;
};
int main() {
    srand(time(0));
    const char* f = "log.bin";
    std::ofstream out(f, std::ios::binary);
    for (int i = 0; i < 10; ++i) {
        Item it = { i + 1, rand() % 90L, (rand() % 10) / 2.0f, rand() % 2 == 0 };
        out.write(reinterpret_cast<char*>(&it), sizeof(Item));
    }
    out.close();
    std::ifstream in(f, std::ios::binary);
    Item temp;
    std::cout << "ID\tCODE\tVAL\tactive\n---\t---\t---\t---\n";
    while (in.read(reinterpret_cast<char*>(&temp), sizeof(Item))) {
        std::cout << temp.id << "\t" << temp.code << "\t" << temp.val << "\t" << temp.active << "\n";
    }
    in.clear();
    in.seekg(0, std::ios::end);
    std::cout << "\nSize: " << in.tellg() << " bytes" << std::endl;

    return 0;
}