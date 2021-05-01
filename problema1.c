#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularDoublyLinkedList.h"

typedef struct angajat angajat;
struct angajat
{
    char* nume;
    char* telefon;
    char* post;
};

void read_angajat(doubly_linked_list_t* list, int n)
{
    angajat* read_angajat = malloc(sizeof(angajat));
    read_angajat->nume = malloc(40 * sizeof(char));
    read_angajat->telefon = malloc (12 * sizeof(char));
    read_angajat->post = malloc(40 * sizeof(char));
    
    // numele trebuie sa contina numele si prenumele legate, fara spatiu
    scanf("%s %s %s", read_angajat->nume, read_angajat->telefon, read_angajat->post);

    dll_add_nth_node(list, n, read_angajat);
}

void print_angajati(doubly_linked_list_t* list)
{
    dll_node_t *current = list->head;
    for (int i = 0; i < list->size; i++) {
        printf("Nume angajat: %s - Telefon angajat: %s - Post angajat: %s\n", (char *)((angajat *)(current->data))->nume, (char *)((angajat *)(current->data))->telefon, (char *)((angajat *)(current->data))->post);
        current = current->next;
    }
}

void add_after_mechanic(doubly_linked_list_t* list)
{
    dll_node_t *current = list->head;
    int position = 0;
    for (int i = 0; i < list->size; i++) {
        if (strcmp((char *)((angajat *)(current->data))->post, "mecanic") == 0) {
            position++;
            break;
        }
        printf("ocupatieeeeeeeeeee: %s pozitieeeeeeeee: %d", (char *)((angajat *)(current->data))->post, position);
        current = current->next;
        position++;
    }
    read_angajat(list, position);
}

void remove_after_telephone(doubly_linked_list_t* list, char* telefon)
{
    dll_node_t *current = list->head;
    int position = 0;
    for (int i = 0; i < list->size; i++) {
        if (strcmp((char *)((angajat *)(current->data))->telefon, telefon) == 0) {
            break;
        }
        current = current->next;
        position++;
    }
    dll_node_t* removed = dll_remove_nth_node(list, position);
    free(((angajat *)(removed->data))->nume);
    free(((angajat *)(removed->data))->telefon);
    free(((angajat *)(removed->data))->post);
    free(removed->data);
    free(removed);
    free(telefon);
}

void free_memory(doubly_linked_list_t* list)
{
    dll_node_t *current = (list)->head;
    // parcurgem fiecare nod si eliberam memoria datelor din nod si a nodului
    // inainte de asta, modificam head ul
    for (int i = 0; i < (int)(list)->size; i++) {
        current = (list)->head;
        if (current != (list)->tail) {
            (list)->head = (list)->head->next;
        }
        free(((angajat *)(current->data))->nume);
        free(((angajat *)(current->data))->telefon);
        free(((angajat *)(current->data))->post);
        free(current->data);
        free(current);
    }

    free(list);
}
int main()
{
    doubly_linked_list_t* list = dll_create(sizeof(angajat));
    printf("Task1: introduceti 6 angajati\n");
    for (int i = 0; i < 3; i++)
        read_angajat(list, list->size);
    print_angajati(list);
    
    printf("Task2: introduceti angajatul care va fi adaugat dupa al 3-lea angajat\n");
    read_angajat(list, 3);
    print_angajati(list);

    printf("Task3: introduceti angajatul care va fi adaugat dupa cel care este mecanic\n");
    add_after_mechanic(list);
    print_angajati(list);

    printf("Task4: introduceti numarul de telefon al angajatului care trebuie sters:\n");
    char* telefon = malloc(12 * sizeof(char));
    printf("Telefon angajat de sters: ");
    scanf("%s", telefon);
    remove_after_telephone(list, telefon);
    print_angajati(list);

    free_memory(list);
    return 0;
}
