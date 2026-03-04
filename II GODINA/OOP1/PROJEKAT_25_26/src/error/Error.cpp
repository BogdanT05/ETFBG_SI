#include "Error.h"

void Error::print(const std::string &line, std::ostream& os) const {
    os << line << '\n';

    if (position() >=0) {
        for (int i = 0; i < position(); i++)
            os << " ";

        for (int i = 0; i < std::max(1, length()); i++)
            os << "^";

        os << '\n';
    }

    os << "Error: " << message() << "\n";
}
