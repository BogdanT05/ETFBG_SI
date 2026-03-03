#include "Date_Command.h"
#include "Semantic_Error.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Interpreter.h"

void Date::execute(Interpreter &interpreter) {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);

    std::ostringstream oss;
    oss << (local->tm_year + 1900) << "-" << std::setw(2) << std::setfill('0')
        << (local->tm_mon+1) << "-" << std::setw(2) << std::setfill('0') << local->tm_mday;

    os->write_line(oss.str());
}

void Date::validate() {
    if (!is->is_console())
        throw Semantic_Error("date does not allow input redirection");

    if (!arguments.empty())
        throw Semantic_Error("date does not accept arguments");

    if (!options.empty()) {
        throw Semantic_Error("date does not accept options");
    }
}
