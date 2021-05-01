#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

linked_list_t*
ll_create(unsigned int data_size)
{
    linked_list_t *list = malloc(sizeof(linked_list_t));

    list->data_size = data_size;
    list->head = NULL;
    list->size = 0;

    return list;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */

void ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
     if (list == NULL) {
    	printf("Nu a fost creata anterior o lista");
    	exit(2);
    }
    // luam un nod de parcurgere d ela inceputul listei
    ll_node_t *current = list->head;
   	ll_node_t *auxiliary = malloc(sizeof(ll_node_t)); // aloc memorie pentru nodul auxiliar
   	
    auxiliary->next = NULL;
   	auxiliary->data = malloc(list->data_size);
   
   	memcpy(auxiliary->data, new_data, list->data_size);

   	if ((int)n < 0) {
        printf("Pozitia nu este valida\n");
        return;
    } else if ((int)n >= (int)list->size) {
        //daca n ul dat este mai mare sau egal decat dimensiunea, exista mai multe cauzuri
        if (current == NULL) { // daca lista este goala
            list->head = auxiliary;
            auxiliary->next = NULL;
        } else {
            // daca lista nu e goala, inseamna ca trebuie sa inserez la finalul listeo
            while(current->next != NULL) {
                current = current->next;
            }
            current->next = auxiliary;
            auxiliary->next = NULL;
        }
    } else if ((int)n == 0) { // inserare la inceputul listei
        auxiliary->next = list->head;
        list->head = auxiliary;
    } else { //altfel, inserarea se face pe un nod ordinar
        for(int i = 0; i < (int)n-1; i++) {
            current = current->next;
        }
        auxiliary->next = current->next;
        current->next = auxiliary;
    }
    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    ll_node_t *current = list->head;
    ll_node_t *previous, *auxiliary;

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
    		return auxiliary;

    	} else if ((int)n >= (int)list->size) { // elimin de la sfarsit
    		for (int i = 0; i < (int)list->size - 2; i++) {
    			current = current->next;
    		}
    		auxiliary = current->next;
    		current->next = NULL;
    		return auxiliary;
    	} else { // elimin nod oarecare
    		for (int i = 0; i < (int)n; i++)  {
    			previous = current;
    			current = current->next;
    		}
    		previous->next = current->next;
    		return current;
    	}
    	list->size--;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t* list)
{
	return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void ll_free(linked_list_t** pp_list)
{
    ll_node_t *current = (*pp_list)->head;
    // parcurgem fiecare nod si eliberam memoria datelor din nod si a nodului
    // inainte de asta, modificam head ul
    while ((*pp_list)->head != NULL) {
        current = (*pp_list)->head;
        (*pp_list)->head = (*pp_list)->head->next;
        free(current->data);
        free(current);
    }

    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t* list)
{
    ll_node_t *current = list->head;
    
    // parcurgem fiecare nod si il afisam
    while(current != NULL) {
        printf("%d ", *(int*)current->data);
        current = current->next;
    }	
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t* list)
{
    ll_node_t *current = list->head;

    // parcurgem fiecare nod si il afisam
    while(current != NULL) {
        printf("%s ", (char *)current->data);
        current = current->next;
    }	
    printf("\n");
}
