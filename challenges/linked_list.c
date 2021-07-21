#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *data;
    struct node *prev;
    struct node *next;
} node_t;

typedef struct {
    node_t *head;
    node_t *tail;
    size_t size;
} list_t;


// Create and initialize linked list
list_t *create_list()
{
    list_t *new_list = malloc(sizeof(list_t));
    if (new_list == NULL) return NULL;

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->size = 0;

    return new_list;
}


// Deallocate linked list
int free_list(list_t *list)
{
    node_t *tmp = list->head;

    while (tmp != NULL) {
        list->head = tmp->next;
        free(tmp);

        tmp = list->head;
    }

    free(list);
    return 0;
}


// Insert string into linked list
int insert_list(list_t *list, char *str)
{
    if (str == NULL) return 1;

    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) return 1;

    new->data = str;
    new->next = NULL;
    new->prev = NULL;

    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
        list->size++;
    } else {
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
        list->size++;
    }

    return 0;
}


// Find string in linked list
// Returns NULL if string isn't found
char *find_list(list_t *list, char *str)
{
    if (str == NULL) return NULL;

    node_t *tmp = list->head;

    while (tmp != NULL) {
        if (strcmp(tmp->data, str) == 0) return tmp->data;

        tmp = tmp->next;
    }

    return NULL;
}


// Delete string from linked list
int delete_list(list_t *list, char *str)
{
    if (str == NULL) return 1;

    node_t *tmp = list->head;

    while (tmp != NULL) {
        if (strcmp(tmp->data, str) == 0) {
            if (list->head != tmp && list->tail != tmp) {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
            }

            if (list->head == tmp) {
                list->head = tmp->next;
                if (list->head != NULL) {
                    list->head->prev = NULL;
                }
            }

            if (list->tail == tmp) {
                list->tail = tmp->prev;
                if (list->tail != NULL) {
                    list->tail->next = NULL;
                }    
            }

            free(tmp);
            list->size--;
            return 0;
        }
        
        tmp = tmp->next;
    }

    return 1;
}



int main(void)
{
    list_t *my_list = create_list();

    char *my_strs[] = {"123", "456", "789", "0AB", "CDE", "FGH", "IJK", "LMN", "OPQ", "RST", "UVW", "XYZ"};


    for (int i = 0; i < 12; ++i)
        insert_list(my_list, my_strs[i]);

    printf("Found: %s\n", find_list(my_list, my_strs[5]));

    delete_list(my_list, my_strs[7]);

    printf("List size: %ld\n", my_list->size);

    free_list(my_list);

    return 0;
}
