#include "Error.h"

void Error::print(const std::string &line){
    std::cerr << line << '\n';

    if (position() >=0) {
        for (int i = 0; i < position(); i++)
            std::cerr << " ";

        for (int i = 0; i < std::max(1, length()); i++)
            std::cerr << "^";

        std::cerr << '\n';
    }

    std::cerr << "Error: " << message() << "\n";
}
