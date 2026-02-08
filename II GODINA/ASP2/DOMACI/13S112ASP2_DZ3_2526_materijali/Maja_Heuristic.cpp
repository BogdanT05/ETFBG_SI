#include "Maja_Heuristic.h"

#include <cmath>
#include <stack>

Maja_Heuristic::Maja_Heuristic(int c) : c(c){}

// Bubble sort radi tako sto sortira dva susedna elementa i veci od njih pomera u desno
// Na taj nacin najveci element se propagira na kraj niza i taj posupak se ponavlja dok niz ne postane soritran
void Maja_Heuristic::bubble_sort(const Image *img, int left, int right, SortingDirection direction) {
    for (int i = left; i <= right; i++) {
        for (int j = left; j < right - (i - left); j++) {
            int a = img->getElement(j);
            int b = img->getElement(j + 1);

            if ((direction == ASCENDING  && a > b) || (direction == DESCENDING && a < b))
                img->swapElements(j, j + 1);
        }
    }
}

// Particija se sortira oko pivot elementa na nacin da se za pivot bira najdesniji element u particiji
// Nakon cega se ostali elementi pocevsi od prvog u toj particiji porede sa pivotom
// Kroz niz se prolazi sa dva pokazivaca jedan koji ide kroz svaki element i pomera se na kraju svake iteracije
// A drugi se pomera samo kada se naidje na element manji od pivota, kada nadjemo element manji od pivota
// Vrsimo zamenu tog elementa i poslednje pozicije na kojoj se nalaze sve elementi manji od pivota
// Na kraju petlje pivot stavljamo ispred svih elemenata koji su manji od njega i tako dobijamo particiju
// U kojoj su svi levo manji a desno veci od pivota
int Maja_Heuristic::partition(const Image *img, int left, int right, SortingDirection direction) {
    int pivot = img->getElement(right);
    int i = left - 1;

    for (int j = left; j < right; j++) {
        int value = img->getElement(j);

        if ((direction == ASCENDING  && value < pivot) || (direction == DESCENDING && value > pivot)) {
            i++;
            img->swapElements(i, j);
        }
    }

    img->swapElements(i + 1, right);
    return i + 1;
}


// iterativna implementacija quick sorta i bubble sorta spojena u jednu funkciju koje
// cine majinu heuristiku, na stek se stavlja indeksi levog, desnog elementa i dubina do koje se islo
// u svakom koraku dubina raste za jedan
// Kada dubina same particije nakon skidanja sa steka predje max dubinu prelazi se na bubble sort
void Maja_Heuristic::sort(const Image *img, SortingDirection direction) {
    int n = img->getElementCount();
    int max_depth = c * std::log2(n);

    struct Interval {
        int left, right, depth;
    };

    std::stack<Interval> stack;
    stack.push({0, n - 1, 0});

    while (!stack.empty()) {
        auto [left, right , depth] = stack.top();
        stack.pop();

        if (left >= right) continue;
        if (depth >= max_depth) {
            bubble_sort(img, left, right, direction);
            continue;
        }

        int p = partition(img, left, right, direction);

        stack.push({left, p - 1, depth + 1});
        stack.push({p + 1, right, depth + 1});
    }
}
