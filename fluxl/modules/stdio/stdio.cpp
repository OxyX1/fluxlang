#include <iostream>
#include <string>
#include <cstdlib>

use namespace std::string;

class stdio {
    int out(string text) {
        std::cout << text << std::endl;
        return 0;
    }

    int in(string text) {
        string& text2 = text;
        std::cin << text2 << std::endl;
        return 0;
    }

    int flush() {
        std::flush;
        return 0;
    }
}