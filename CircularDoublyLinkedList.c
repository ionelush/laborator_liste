#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    // se alcoa memorie pentru lista si se adauga metadatele ei
    // includem si tail pentru a usura scrierea
    doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));

    list->data_size = data_size;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    // pentru a avea o complexitate de maxim O(n), vom efectua parcurgerea listei
    // pana la n % list->size, deoarece lista este circulara si valorile se repeta
    // in aceasta
    dll_node_t *current = list->head;
    int position = n % list->size;

    if ((int)n < 0) {
        printf("Pozitia nodului dat nu este valida.");
        exit(2);
    } else {
        for (int i = 0; i < position; i++) {
            current = current->next;
        } 
    }  
    return current;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    if (list == NULL) {
        printf("Nu a fost creata anterior o lista");
        exit(2);
    }
    // luam un nod de parcurgere de la inceputul listei
    dll_node_t *current = list->head;
    // aloc memorie pentru nodul auxiliar si il initializez
    dll_node_t *auxiliary = malloc(sizeof(dll_node_t));
    
    auxiliary->next = NULL;
    auxiliary->prev = NULL;
    auxiliary->data = malloc(list->data_size);
    memcpy(auxiliary->data, data, list->data_size);

    if ((int)n < 0) {
        printf("Pozitia nu este valida\n");
        exit(2);

    } else if ((int)n >= (int)list->size) {
        //daca n ul dat este mai mare sau egal decat dimensiunea, exista mai multe cauzuri
        if (list->head == NULL) { // daca lista este goala
            list->head = auxiliary;
            list->tail = auxiliary;
            auxiliary->next = list->head;
            auxiliary->prev = list->head;

        } else {
            // daca lista nu e goala, inseamna ca trebuie sa inserez la finalul listei
            // ma folosesc de tail pentru a avea complexitatea O(1)
            list->tail->next = auxiliary;
            auxiliary->prev = list->tail;
            auxiliary->next = list->head;
            list->head->prev = auxiliary;
            list->tail = auxiliary;
        }

    } else if ((int)n == 0) { // inserare la inceputul listei

        auxiliary->next = list->head;
        list->head->prev = auxiliary;
        auxiliary->prev = list->tail;
        list->tail->next = auxiliary;
        list->head = auxiliary;

    } else { //altfel, inserarea se face pe un nod ordinar
        for(int i = 0; i < (int)n-1; i++) {
            current = current->next;
        }

        auxiliary->next = current->next;
        current->next->prev = auxiliary;
        auxiliary->prev = current;
        current->next = auxiliary;
    }
    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    dll_node_t *current = list->head;
    dll_node_t *auxiliary;

    if (list == NULL) {
        printf("Nu a fost creata anterior o lista");
        exit(2);
    }

    if ((int)n < 0) {
        printf("Pozitia nodului nu este valida");
        exit(2);

    } else if (list->head == NULL) {
        printf("Nu au fost adaugate noduri in lista");
        exit(2);
        } else if ((int)n == 0) { // stergem la inceput
            auxiliary = list->head;
            list->head = auxiliary->next;
            list->head->prev = list->tail;
            list->tail->next = list->head;
            list->size--;
            return auxiliary;

        } else if ((int)n >= (int)list->size - 1) { // elimin de la sfarsit
            
            auxiliary = list->tail;
            list->tail = auxiliary->prev;
            list->tail->next = list->head;
            list->head->prev = list->tail;
            list->size--;
            return auxiliary;

        } else { // elimin nod oarecare
            for (int i = 0; i < (int)n; i++)  {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            list->size--;
            return current;
        }
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    dll_node_t *current = (*pp_list)->head;
    // parcurgem fiecare nod si eliberam memoria datelor din nod si a nodului
    // inainte de asta, modificam head ul
    for (int i = 0; i < (int)(*pp_list)->size; i++) {
        current = (*pp_list)->head;
        if (current != (*pp_list)->tail) {
            (*pp_list)->head = (*pp_list)->head->next;
        }
        free(current->data);
        free(current);
    }

    free(*pp_list);
}
