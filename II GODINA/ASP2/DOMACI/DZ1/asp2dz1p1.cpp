#include <iostream>
#include <random>

void read_temperatures(int temperatures[], int &length) {
    std::cout << "Unesite broj merenja: ";
    std::cin >> length;

    if (length < 1 || length > 365) {
        length = -1;
        return;
    } // Provera validnosti merenja

    std::cout << "Unesite merenja za dane redom: ";
    for (int i = 0; i < length; i++) {
        std::cin >> temperatures[i];
    }
}

void generate_temperatures(int temperatures[], int &length) {
    int min, max;

    std::cout << "Unesite broj merenja za generisanje: ";
    std::cin >> length;

    if (length < 1 || length > 365) {
        length = -1;
        return;
    }

    std::cout << "Unesite gornju i donju granicu: ";
    std::cin >> min >> max;

    // Generisanje pseudoslucajnih brojeva - source: https://en.cppreference.com/w/cpp/numeric/random.html
    std::random_device random_dev;
    std::mt19937 gen(random_dev());
    std::uniform_int_distribution<int> uniform_dist(min, max);

    for (int i = 0; i < length; i++) {
        temperatures[i] = uniform_dist(gen);
    }

    // Bubble sort
    for (int i = 0; i < length-1; i++) {
        for (int j = i+1; j < length; j++) {
            if (temperatures[i] > temperatures[j]) {
                int temp = temperatures[i];
                temperatures[i] = temperatures[j];
                temperatures[j] = temp;
            }
        }
    }
}

// Struktrura za cuvanje pozicija
struct Position {
    int pos;
    int last;
    int first;

    explicit Position(int p, int l = -1, int f = -1) : pos(p), last(l), first(f){}
};

Position find_temperature(int temperature, const int temperatures[], const int &length) {
    int low = 0;
    int high = length-1;
    int mid = 0;
    int position = -1;

    // Binarna pretraga u kojoj trazimo ili trazeni el ili najblizi
    while (low <= high) {
        mid = low + (high-low)/2;

        if (temperatures[mid] == temperature) {
            position = mid;
            break;
        }
        if (temperatures[mid] > temperature) high = mid-1;
        if (temperatures[mid] < temperature) low = mid+1;
    }

    // Ao ne nadjemo odg poziciju vracamo rezultat
    if (position == -1) return Position(-1, mid-1, mid);

    // Pretraga za broj pojavljivanja
    int last;
    int first = last = position;

    // Dokle god se ponavljaju pomeramo se gore i dole
    while (temperatures[first] == temperature) first--;
    while (temperatures[last] == temperature) last++;

    first++;
    last--;

    return Position(position, last, first);
}

void search_interval(int min, int max, const int temperatures[], const int &length) {
    // Vracamo pozicije min ili max ako postoji ili najblizih
    Position low = find_temperature(min, temperatures, length);
    Position high = find_temperature(max, temperatures, length);

    int lower = low.first;
    int higher = high.last;

    // Ispisujemo sve izmedju lower i higher
    std::cout << lower << " " << higher;
    std::cout << "Temperature u zadatom opsegu se pojavljuju u danima: \n";
    for (int i = lower; i <= higher; i++) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

void print_temperatures(const int temperatures[], const int &length) {
    for (int i = 0; i < length; i++) {
        std::cout << temperatures[i] << " ";
    }
    std::cout << std::endl;
}

void print_menu() {
    const std::string BLUE  = "\033[34m";
    const std::string RESET = "\033[0m";

    std::cout << BLUE;
    std::cout << " =========================================\n";
    std::cout << " |                                        |\n";
    std::cout << " |   1. Unesite temperature sa ulaza      |\n";
    std::cout << " |   2. Generisite temperature iz opsega  |\n";
    std::cout << " |   3. Pronadji temperaturu              |\n";
    std::cout << " |   4. Pronadji interval pojavljivanja   |\n";
    std::cout << " |   0. Izlaz                             |\n";
    std::cout << " |                                        |\n";
    std::cout << " =========================================\n";
    std::cout << RESET;
}

int main() {
    bool b = true;
    int length = -1, min, max;
    int temperatures[365];

    while (b) {
        print_menu();
        int choice;
        std::cout << "Vas izbor: ";
        std::cin >> choice;

        switch (choice) {
            default:
                break;
            case 0:
                b = false;
                break;
            case 1:
                // Citamo i ispisujemo, ako je nevalidno iskacemo iz programa
                read_temperatures(temperatures, length);
                if (length < 0) throw std::out_of_range("Invalid range!");
                print_temperatures(temperatures, length);
                break;
            case 2:
                // Generisemo, takodje proveravamo validnost
                generate_temperatures(temperatures, length);
                if (length < 0) throw std::out_of_range("Invalid range!");
                print_temperatures(temperatures, length);
                break;
            case 3: {
                // Provera da li niz postoji
                if (length < 0) throw std::runtime_error("Array does not exist!");
                int temperature;

                std::cout << "Unesite temperaturu za pretragu: ";
                std::cin >> temperature;

                Position pos = find_temperature(temperature, temperatures, length);
                if (pos.pos == -1) {
                    std::cout << "Temperatura se ne javlja u nizu! \n";
                    break;
                }

                // U zavisnosti da li se pojavljuje vise ili jedan ispisujemo razlicit string
                if (pos.pos == pos.last && pos.pos == pos.first) std::cout << "Temperatura se pojavljuje na dan: " << pos.pos << std::endl;
                else std::cout << "Temperatura se pojavljuje prvi i poslednji put na dane: " << pos.first <<", " << pos.last << std::endl;

                break;
            }

            case 4:
                // Provera da li niz postoji
                if (length < 0) throw std::runtime_error("Array does not exist!");

                std::cout << "Unesite opseg (min, max): ";
                std::cin >> min >> max;
                search_interval(min, max, temperatures, length);

                break;
        }
    }

    return 0;
}