/**
 * Programmer: Mike Boyle
 * Date: 2022-03-10
 * Purpose: Implementation file for ListIterator class.
 *
 */
#include "ListIterator.h"
#include <exception>
#include <stdexcept>

template <class T>
ListIterator<T>::ListIterator()
{
    curr = NULL;
}

template <class T>
ListIterator<T>::ListIterator(Node<T> *node)
{
    curr = node;
}

template <class T>
ListIterator<T>::~ListIterator()
{
}

template <class T>
bool ListIterator<T>::hasNext() const
{
    return curr != NULL;
}

template <class T>
bool ListIterator<T>::hasPrev() const
{
    return curr != NULL;
}

template <class T>
T ListIterator<T>::next()
{
    if (!hasNext())
        throw std::out_of_range("no more elements");

    T next = curr->data;
    curr = curr->next;

    return next;
}

template <class T>
T ListIterator<T>::prev()
{

    if (!hasPrev())
        throw std::out_of_range("no more elements");

    T next = curr->data;
    curr = curr->prev;

    return next;
}

template <class T>
T ListIterator<T>::operator*()
{
    return curr->data;
}
