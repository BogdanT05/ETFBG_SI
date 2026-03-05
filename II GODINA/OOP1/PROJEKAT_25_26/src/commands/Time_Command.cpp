#include "Time_Command.h"
#include "Semantic_Error.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include "Console_Input_Stream.h"
#include "File_Input_Stream.h"

void Time::execute(Interpreter &interpreter) {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    std::ostringstream oss;

    if (options.empty())
        oss << local->tm_hour << ":" << std::setw(2) << std::setfill('0')
            << local->tm_min << ":" << std::setw(2) << std::setfill('0') << local->tm_sec;
    else {
        if (options[0][1] == 'h')
            oss << local->tm_hour << std::setw(2) << std::setfill('0');
        else if (options[0][1] == 'm')
            oss << local->tm_min << std::setw(2) << std::setfill('0');
        else
            oss << local->tm_sec << std::setw(2) << std::setfill('0');
    }

    os->write_line(oss.str());
}

void Time::validate() {
    if (!is->is_console())
        throw Semantic_Error("time does not allow input redirection");

    if (!arguments.empty())
        throw Semantic_Error("time does not accept arguments");

    if (options.size() > 1) {
        throw Semantic_Error("time accepts at most 1 option");
    }

    if (!options.empty() && options[0][1] != 'h' && options[0][1] != 'm' && options[0][1] != 's')
        throw Semantic_Error("Invalid option for time");
}
