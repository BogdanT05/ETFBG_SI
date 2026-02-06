#include "sorting.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include "utils.h"
#include "Maja_Heuristic.h"
#include "Marko_Heuristic.h"
#include "Sort.h"
#include "image.h"
#include "image_processor.h"

void print_menu() {
    std::cout << " ================================================ \n";
    std::cout << " |                                                |\n";
    std::cout << " |   1. Rekonstrukcija slike (Marko heuristika)   |\n";
    std::cout << " |   2. Rekonstrukcija slike (Maja heuristika)    |\n";
    std::cout << " |   3. Poredjenje algoritama                     |\n";
    std::cout << " |   0. Izlaz                                     |\n";
    std::cout << " |                                                |\n";
    std::cout << " ================================================ \n";
}

void run_marko() {
    std::string in, out;
    int c;

    std::cout << "Ulazni fajl: ";
    std::cin >> in;
    in = "../datoteke/" + in;

    std::cout << "Izlazni fajl: ";
    std::cin >> out;

    std::cout << "Unesite c: ";
    std::cin >> c;

    SortingAlgorithm* alg = new Marko_Heuristic(c);

    Stopwatch sw;
    sw.start();
    ImageProcessor::reconstructImage(in.c_str(), out.c_str(), alg);
    long long t = sw.stop();

    std::cout << "Vreme izvrsavanja: " << t << " ms\n";

    delete alg;
}

void run_maja() {
    std::string in, out;
    int c;

    std::cout << "Ulazni fajl: ";
    std::cin >> in;
    in = "../datoteke/" + in;

    std::cout << "Izlazni fajl: ";
    std::cin >> out;

    std::cout << "Unesite c: ";
    std::cin >> c;

    SortingAlgorithm* alg = new Std_Sort();

    Stopwatch sw;
    sw.start();
    ImageProcessor::reconstructImage(in.c_str(), out.c_str(), alg);
    long long t = sw.stop();

    std::cout << "Vreme izvrsavanja: " << t << " ms\n";

    delete alg;
}

void compare_algorithms() {
    int c;
    std::cout << "Unesite c: ";
    std::cin >> c;

    std::vector<std::string> images = {
        "image_1_asc.txt",
        "image_1_desc.txt",
        "image_1_rand.txt",
        "image_2_asc.txt",
        "image_2_desc.txt",
        "image_2_rand.txt",
        "image_3_asc.txt",
        "image_3_desc.txt",
        "image_3_rand.txt",
        "image_4_asc.txt",
        "image_4_desc.txt",
        "image_4_rand.txt"
    };

    std::ofstream out("rezultati.txt");
    if (!out.is_open()) {
        std::cerr << "Ne mogu da otvorim rezultati.txt\n";
        return;
    }

    out << std::left
    << std::setw(20) << "Slika"
    << std::setw(15) << "Marko(ms)"
    << std::setw(15) << "Maja(ms)"
    << std::setw(15) << "Std(ms)"
    << "\n";

    Stopwatch sw;
    for (const auto& imgFile : images) {

        SortingAlgorithm* marko = new Marko_Heuristic(c);
        sw.start();
        ImageProcessor::reconstructImage(
            ("../datoteke/" + imgFile).c_str(),
            "out_marko.txt",
            marko
        );
        long long t_marko = sw.stop();
        delete marko;

        SortingAlgorithm* maja = new Maja_Heuristic(c);
        sw.start();
        ImageProcessor::reconstructImage(
            ("../datoteke/" + imgFile).c_str(),
            "out_maja.txt",
            maja
        );
        long long t_maja = sw.stop();
        delete maja;

        SortingAlgorithm* stl = new Std_Sort();
        sw.start();
        ImageProcessor::reconstructImage(
            ("../datoteke/" + imgFile).c_str(),
            "out_std.txt",
            stl
        );
        long long t_std = sw.stop();
        delete stl;

        out << std::left
        << std::setw(20) << imgFile
        << std::setw(15) << t_marko
        << std::setw(15) << t_maja
        << std::setw(15) << t_std
        << "\n";
    }

    out.close();
    std::cout << "Rezultati upisani u fajl: rezultati.txt\n";
}

int main(){
    bool running = true;
    while (running) {
        print_menu();

        int choice;
        std::cout << "Vas izbor: ";
        std::cin >> choice;

        switch (choice) {
            case 0:
                running = false;
                break;
            case 1:
                run_marko();
                break;
            case 2:
                run_maja();
                break;
            case 3:
                compare_algorithms();
                break;
            default:
                std::cout << "Nepostojeca opcija!\n";
        }
    }
    return 0;
}