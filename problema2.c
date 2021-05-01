#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

void remove_node_x(linked_list_t* list, int x)
{
    printf("Lista inainte de stergerea lui x:\n");
    ll_print_int(list);
    ll_node_t *current = list->head;
    int position = 0;
    while (current != NULL) {
        if (*(int *)current->data == x) {
            ll_node_t *removed = ll_remove_nth_node(list, position);
            position--;
            free(removed->data);
            free(removed);
            break;
        }
        current = current->next;
        position++;
    }
    printf("Lista dupa stergerea lui x:\n");
    ll_print_int(list);
}

int main(int argc, char* argv[]) {
    
    // Exemplu continut fisier de intrare se afla in fisierul test.txt
	FILE *input;

	if (argc != 2) {
		printf("Usage:%s input_file \n", argv[0]);
		return -1;
	}

	input = fopen(argv[1], "rt");
    if (!input) {
		printf("Failed to load %s\n", argv[1]);
		return -1;
	}

    linked_list_t* list = ll_create(sizeof(int));
	int x; // nodul care va fi citit
    fscanf(input, "%d", &x);
    while (!feof(input)) {
        ll_add_nth_node(list, list->size, &x);
        fscanf(input, "%d", &x);
    }
	fclose(input);
    printf("Introduceti valoarea lui x = ");
    scanf("%d", &x);
    remove_node_x(list, x);
    ll_free(&list);
	return 0;
}
