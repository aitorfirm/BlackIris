#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <nlohmann/json.hpp> 

std::string random_hex(int len) {
    const char* chars = "0123456789abcdef";
    std::string out;
    for (int i = 0; i < len; ++i)
        out += chars[rand() % 16];
    return out;
}

int main() {
    srand(time(0));
    std::string aes = random_hex(64);
    std::string xor_key = random_hex(32);

    nlohmann::json j;
    j["aes"] = aes;
    j["xor"] = xor_key;

    std::ofstream ofs("keys.json");
    ofs << j.dump(2);
    std::cout << "Rotated keys saved to keys.json\n";
    return 0;
}
