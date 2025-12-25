#ifndef DZ2_PROCESS_H
#define DZ2_PROCESS_H
#include <string>


class Process {
private:
    std::string name;
    int time_to_complete, maximum_waiting_time;
    int waiting_time, execution_time;

public:
    Process();
    Process(std::string name, int time_to_complete, int maximum_waiting_time, int waiting_time, int execution_time);

    [[nodiscard]] std::string get_name() const {return name;}

    void update_time_to_complete(int update);
    void update_maximum_waiting_time(int update);

    [[nodiscard]] int get_time_to_complete() const {return time_to_complete;}
    [[nodiscard]] int get_maximum_waiting_time() const {return maximum_waiting_time;}

    void update_waiting_time(int update);
    void update_execution_time(int update);

    [[nodiscard]] int get_waiting_time() const {return waiting_time;}
    [[nodiscard]] int get_execution_time() const {return execution_time;}
};


#endif //DZ2_PROCESS_H