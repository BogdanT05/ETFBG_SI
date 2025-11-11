#ifndef STARI_ROKOVI_SORTED_LIST_H
#define STARI_ROKOVI_SORTED_LIST_H

int sorted_seq_search(int list[], int key, int length);
int* sorted_seq_search_multiple(int list[], int keys[], int length_list, int length_keys);
int binary_search(int list[], int key, int length);
int binary_search_extended(int elements[], int positions[], int key, int capacity);
int binary_search_unknown_size(int list[], int key);
int interpolation_search(int list[], int key, int length);

#endif //STARI_ROKOVI_SORTED_LIST_H