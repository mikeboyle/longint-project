/**
 * Programmer: Mike Boyle
 * Date: 2022-03-10
 * Purpose: Header file for node struct, used in DoublyLinkedList
 *
 */
#ifndef NODE_H
#define NODE_H

template <class T>
struct Node
{
    T data;
    Node *prev;
    Node *next;
};

#endif