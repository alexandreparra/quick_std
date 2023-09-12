// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD 3-Clause.

#pragma once

#include <stdlib.h>
#include <stdio.h>

struct node {
    struct node *next;
    void        *data;
};

typedef struct node QsNode;

typedef struct {
    QsNode *head;
    size_t data_size;
} QsLinkedList;

QsNode *create_node(void *data, size_t data_size) {
    QsNode *node = malloc(sizeof(QsNode));
    node->data   = malloc(data_size);
    memcpy(node->data, data, data_size);

    node->next = NULL;
    return node;
}

QsLinkedList *qs_linked_list_alloc(void *init_value, size_t data_size) {
    QsLinkedList *list = malloc(sizeof(QsLinkedList));
    list->data_size    = data_size;
    list->head         = create_node(init_value, data_size);
    return list;
}

void qs_linked_list_append(QsLinkedList *list, void *data) {
    QsNode *current_node = list->head;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    current_node->next = create_node(data, list->data_size);
}

void *qs_linked_list_get(QsLinkedList *list, size_t pos) {
    QsNode *current_node = list->head;

    for (size_t i = 0; i < pos; i += 1) {
        if (current_node->next == NULL) {
            return NULL;
        }

        current_node = current_node->next;
    }

    return current_node->data;
}

/**
 * @return 0 if remove was successful and 1 if the index didn't exist.
 */
int qs_linked_list_remove(QsLinkedList *list, size_t pos) {
    if (pos == 0) {
        if (list->head->next != NULL) {
            QsNode *temp = list->head;
            list->head   = list->head->next;

            free(temp->data);
            free(temp);
            return 0;
        }

        free(list->head->data);
        list->head->data = NULL;
        return 0;
    }

    QsNode *current_node = list->head;

    for (size_t i = 0; i < pos - 1; i += 1) {
        if (current_node->next == NULL) {
            return 1;
        }

        current_node = current_node->next;
    }

    QsNode *to_remove = current_node->next;

    if (to_remove == NULL)
        return 1;

    if (current_node->next->next != NULL) {
        current_node->next = current_node->next->next;
    } else {
        current_node->next = NULL;
    }

    free(to_remove->data);
    free(to_remove);

    return 0;
}

void qs_linked_list_reverse(QsLinkedList *list) {
    QsNode *new_head = NULL;

    while (list->head != NULL) {
        QsNode *temp = list->head;
        list->head = list->head->next;
        temp->next = new_head;
        new_head = temp;
    }

    list->head = new_head;
}

void qs_linked_list_for_each(QsLinkedList *list, void (*func)(void *)) {
    QsNode *current_node = list->head;

    while (current_node != NULL) {
        func(current_node->data);
        current_node = current_node->next;
    }
}
