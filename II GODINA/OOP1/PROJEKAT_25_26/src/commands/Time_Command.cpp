#include "Time_Command.h"
#include "Semantic_Error.h"
#include <iomanip>
#include <ctime>
#include <sstream>

#include "Console_Input_Stream.h"
#include "File_Input_Stream.h"
#include "Interpreter.h"

void Time::execute(Interpreter &interpreter) {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);

    std::ostringstream oss;
    oss << local->tm_hour << ":" << std::setw(2) << std::setfill('0')
        << local->tm_min << ":" << std::setw(2) << std::setfill('0') << local->tm_sec;

    os->write_line(oss.str());
}

void Time::validate() {
    if (!is->is_console())
        throw Semantic_Error("time does not allow input redirection");

    if (!arguments.empty())
        throw Semantic_Error("time does not accept arguments");

    if (!options.empty()) {
        throw Semantic_Error("time does not accept options");
    }
}
