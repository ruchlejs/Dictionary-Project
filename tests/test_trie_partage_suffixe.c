#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100

// Fonction qui échange deux éléments dans un tableau
void swap(char **a, char **b) {
    char *temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction qui compare deux chaînes de caractères pour le tri
int compare(char *a, char *b, int suffix_len) {
    return strcmp(a + suffix_len, b + suffix_len);
}

// Fonction qui trie un sous-tableau d'un tableau donné
void quicksort_suffix(char **arr, int start, int end, int suffix_len) {
    if (start < end) {
        int pivot_index = start;
        char *pivot_value = arr[end];

        for (int i = start; i < end; i++) {
            if (compare(arr[i], pivot_value, suffix_len) < 0) {
                swap(&arr[i], &arr[pivot_index]);
                pivot_index++;
            }
        }
        swap(&arr[pivot_index], &arr[end]);

        quicksort_suffix(arr, start, pivot_index - 1, suffix_len);
        quicksort_suffix(arr, pivot_index + 1, end, suffix_len);
    }
}

// Fonction qui trie un tableau donné en partageant les suffixes communs entre les éléments
void shared_suffix_sort(char **arr, int size) {
    int i, k;
    for (i = 1; i < size; i++) {
        k = 0;
        while (arr[i-1][k] == arr[i][k] && k < strlen(arr[i-1])) {
            k++;
        }
        quicksort_suffix(arr, i-1, i, k);
    }
}

// Fonction qui affiche un tableau de chaînes de caractères
void print_arr(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

// Exemple d'utilisation
int main() {
    char *arr[] = {"hello", "hell", "he", "world", "wor", "wonderful", "won", "wonder"};
    int size = sizeof(arr)/sizeof(arr[0]);

    shared_suffix_sort(arr, size);
    print_arr(arr, size);

    return 0;
}
