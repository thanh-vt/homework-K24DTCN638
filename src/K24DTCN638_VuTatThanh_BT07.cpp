#include <iostream>
#include <fstream>
#include "util.h"
#include "K24DTCN638_VuTatThanh_BT07.h"


int main() {
    std::string filename = "K24DTCN638_VuTatThanh_BT07.txt";
    std::ifstream file(filename); // Mở file để đọc
    if (!file) {
        std::cerr << "Khong the mo file input " << filename << std::endl;
        return 1;
    }

    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Khong co dong tiep theo" << std::endl;
        return 2;
    }
    const int total_tests = parse_int(line);
    if (total_tests < 1 || total_tests > 100) {
        std::cerr << "T phai lon hon hoac bang 1 va nho hon hoac bang 100" << std::endl;
        return 2;
    }
    for (int i = 0; i < total_tests; i++) {
        if (!std::getline(file, line)) {
            std::cerr << "Khong co dong tiep theo" << std::endl;
            return 2;
        }
        const long n = parse_long(line);
        if (n < 0) return 2;
        if (n < 1) {
            std::cout << "N phai lon hon hoac bang 1" << std::endl;
            return 2;
        }
        if (n > 10000000000) {
            std::cout << "N phai nho hon hoac bang 10000000000" << std::endl;
            return 2;
        }
        print_factorization(n);
    }

    file.close();

    return 0;
}

void print_factorization(long n) {
    while (n % 2 == 0) {
        std::cout << 2 << " ";
        n /= 2;
    }

    for (long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            std::cout << i << " ";
            n /= i;
        }
    }

    if (n > 2) {
        std::cout << n;
    }

    std::cout << std::endl;
}
