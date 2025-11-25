#ifndef LINKEDLIST_T_H
#define LINKEDLIST_T_H
#include <stddef.h>

typedef struct node_t {
    void *data;
    struct node_t *next;
} node_t;

typedef struct linkedlist_t
{
    node_t *head;
    size_t length;
} linkedlist_t;

#ifndef LINKEDLIST_T_IMPLEMENTATION_H
#define LINKEDLIST_T_IMPLEMENTATION_H 
#include <stdlib.h>
#include <assert.h>

linkedlist_t create_linkedlist();
void reset_linkedlist(linkedlist_t *ll);
void free_linkedlist(linkedlist_t *ll);
node_t * create_node(void *input_data);
void add_node(linkedlist_t * ll, node_t * node);
void append_node(linkedlist_t *ll, node_t *node);
void delete_node(linkedlist_t *ll, node_t *node);

linkedlist_t create_linkedlist() {
    linkedlist_t list = {0};
    list.length = 0;
    list.head = NULL;

    return list;
}

void reset_linkedlist(linkedlist_t *ll)
{
    assert(ll != NULL);
    if (ll->head == NULL) { return; }

    node_t *current = ll->head;
    node_t *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    ll->head = NULL;
    ll->length = 0;
}

void free_linkedlist(linkedlist_t *ll) 
{
    assert(ll != NULL);

    if (ll->head != NULL) {
        reset_linkedlist(ll);
    }

    free(ll);
}

node_t * create_node(void *input_data) {
    assert(input_data != NULL);
    
    node_t *node = (node_t*)malloc(sizeof(node_t));
    assert(node != NULL);

    node->next = NULL;
    node->data = input_data;

    return node;
}

void append_node(linkedlist_t *ll, node_t *node) {
    assert(ll != NULL && node);
    assert(node->next == NULL);

    if (ll->head == NULL) 
    {
        add_node(ll, node);
        return;
    }

    node_t *temp = ll->head;
    while (temp->next != NULL) { 
        temp = temp->next; 
    }
            
    temp->next = node;
    ll->length += 1;
}

void add_node(linkedlist_t * ll, node_t * node) {
    assert(ll != NULL && node != NULL);

    node_t *temp = ll->head;
    ll->head = node;
    node->next = temp;
   
    ll->length += 1;
}

void delete_node(linkedlist_t *ll, node_t *node) {
    assert(ll != NULL && node != NULL);
    if (ll->head == NULL) { return; }

    if (ll->head == node) 
    {
        node_t *temp = ll->head->next;
        ll->head = temp;
    } else
    {
        node_t * current = ll->head;
        while (current != NULL && current->next != node)
        {
           current = current->next;
        }

        if (current == NULL) 
        {
            return;
        }

        current->next = node->next;
    }

    free(node->data);
    free(node);
    ll->length -= 1;
}


#endif //implementation
#endif //queue