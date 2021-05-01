#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

// functia va returna numarul de elemente pare din lista si le va afisa
int print_pare(linked_list_t* list)
{
    int elem_pare = 0;
    printf("Elementele pare din lista:\n");
    ll_node_t *current = list->head;
    while (current != NULL) {
        if (*(int *)current->data % 2 == 0) {
            elem_pare++;
            printf("%d ", *(int *)current->data);
        }
        current = current->next;
    }
    printf("\n");
}

// functia va sterge elementele pare din lista si va afisa lista dupa stergere
void sterge_pare(linked_list_t* list, int elem_pare)
{
    for (int i = 0; i < elem_pare; i++) {
        ll_node_t *current = list->head;
        int position = 0;
        while (current != NULL) {
            if (*(int *)current->data % 2 == 0) {
               ll_node_t *removed = ll_remove_nth_node(list, position);
                position--;
                free(removed->data);
                free(removed);
                break;
            }
            current = current->next;
            position++;
        }
    }
    printf("Lista dupa stergerea elementelor pare:\n");
    ll_print_int(list);
}

int main ()
{
    // n = nr de noduri ale listei, x = data nodului
    int n;
    int *x = malloc(sizeof(int));
    scanf("%d", &n);
    linked_list_t* list = ll_create(sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", x);
        ll_add_nth_node(list, list->size, x);
    }
    free(x);

    printf("Lista initiala:\n");
    ll_print_int(list);
    
    int elem_pare = print_pare(list);

    sterge_pare(list, elem_pare);

    ll_free(&list);
    return 0;
}
