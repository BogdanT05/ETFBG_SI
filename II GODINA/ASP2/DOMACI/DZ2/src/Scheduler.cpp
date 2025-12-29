#include "Scheduler.h"

// Algoritam obrade:
// 1. Nadji najmanji proces, tj najlevlji i obradi ga.
// 2. Azuriraj vremena cekanja za ostale cvorove, po potrebi izbaci i ubaci
// 3. Nastavi dalje sa obradom dok ne obradis sve procese

bool Scheduler::step(std::ostream &os) const {
    if (!tree234 || tree234->is_empty()) return false;
    Process* running = tree234->extract_min();

    os << "U OBRADI: " << running->get_name() << "\n";
    int remaining = running->time_to_complete - running->execution_time;
    int delta = std::min(time_slice, remaining);

    running->execution_time += delta;
    running->waiting_time += delta;

    os << "DELTA = " << delta << "\n";

    tree234->update(delta);

    if (running->execution_time < running->time_to_complete) {
        tree234->insert_node(running);
    } else {
        os << "OBRADJENO: " << running->get_name() << "\n";
    }

    if (!tree234->is_empty()) {
        os << "\n234 STABLO NAKON OBRADE:\n";
        tree234->print_tree234(os);
    }

    os << "\n---------------------------------\n";
    os.flush();
    return !tree234->is_empty();
}

void Scheduler::run(std::ostream &os) const {
    int stepNo = 1;
    while (step(os)) {
        os << "===== KORAK " << stepNo++ << " =====\n";
    }
}
