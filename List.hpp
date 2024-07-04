// Name: Ruth Massock
// 6/11/2024
// Assignment 2 COP4530
#ifndef DL_LIST_HPP
#define DL_LIST_HPP

#include "List.h"

// Definitions for const_iterator class
template <typename T>
List<T>::const_iterator::const_iterator() : current{nullptr} {}

template <typename T>
const T& List<T>::const_iterator::operator*() const {
    return retrieve();
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++() {
    current = current->next; // Move to the next node
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
    const_iterator old = *this; // Store the current iterator
    ++(*this); // Increment the iterator to move to the next node
    return old; // Return the stored iterator
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--() {
    current = current->prev; // Move to the previous node
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
    const_iterator old = *this; // Store the current iterator
    --(*this); // Decrement the iterator to move to the previous node
    return old; // Return the stored iterator
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator& rhs) const {
    return current == rhs.current; // Check if two iterators point to the same node
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator& rhs) const {
    return current != rhs.current; // Check if two iterators point to different nodes
}

template <typename T>
T& List<T>::const_iterator::retrieve() const {
    return current->data; // Retrieve the data of the current node
}

template <typename T>
List<T>::const_iterator::const_iterator(Node* p) : current{p} {}

// Definitions for iterator class
template <typename T>
List<T>::iterator::iterator() {}

template <typename T>
T& List<T>::iterator::operator*() {
    return const_iterator::retrieve(); // Dereference the iterator to retrieve data
}

template <typename T>
const T& List<T>::iterator::operator*() const {
    return const_iterator::operator*(); // Dereference the iterator to retrieve data
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++() {
    this->current = this->current->next; // Move to the next node
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    iterator old = *this; // Store the current iterator
    ++(*this); // Increment the iterator to move to the next node
    return old; // Return the stored iterator
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--() {
    this->current = this->current->prev; // Move to the previous node
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    iterator old = *this; // Store the current iterator
    --(*this); // Decrement the iterator to move to the previous node
    return old; // Return the stored iterator
}

template <typename T>
List<T>::iterator::iterator(Node* p) : const_iterator{p} {}

// Definitions for List class
template <typename T>
List<T>::List() {
    init(); // Initialize the list
}

template <typename T>
List<T>::List(const List& rhs) {
    init(); // Initialize the list
    for (auto& x : rhs)
        push_back(x); // Copy elements from rhs to the list
}

template <typename T>
List<T>::List(List&& rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template <typename T>
List<T>::List(int num, const T& val) {
    init(); // Initialize the list
    for (int i = 0; i < num; ++i)
        push_back(val); // Add num elements with value val to the list
}

template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
    init(); // Initialize the list
    for (auto itr = start; itr != end; ++itr)
        push_back(*itr); // Copy elements from the range [start, end) to the list
}

template <typename T>
List<T>::List(std::initializer_list<T> iList) {
    init(); // Initialize the list
    for (auto& x : iList)
        push_back(x); // Copy elements from the initializer list to the list
}

template <typename T>
List<T>::~List() {
    clear(); // Clear the list
    delete head;
    delete tail;
}

template <typename T>
const List<T>& List<T>::operator=(const List& rhs) {
    List copy = rhs; // Create a copy of rhs
    std::swap(*this, copy); // Swap the contents of *this and the copy
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList) {
    clear(); // Clear the list
    for (auto& x : iList)
        push_back(x); // Copy elements from the initializer list to the list
    return *this;
}

template <typename T>
int List<T>::size() const {
    return theSize; // Return the size of the list
}

template <typename T>
bool List<T>::empty() const {
    return size() == 0; // Check if the list is empty
}

template <typename T>
void List<T>::clear() {
    while (!empty())
        pop_front(); // Remove elements from the front until the list becomes empty
}

template <typename T>
void List<T>::reverse() {
    if (empty()) return; // If the list is empty, do nothing
    Node* current = head->next;
    Node* prev = nullptr;
    Node* next = nullptr;
    while (current != tail) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    std::swap(head->next, tail->prev); // Swap the head's next and tail's prev to reverse the list
    head->next->prev = head;
    tail->prev->next = tail;
}

template <typename T>
T& List<T>::front() {
    return *begin(); // Return a reference to the first element
}

template <typename T>
const T& List<T>::front() const {
    return *begin(); // Return

}

template <typename T>
T& List<T>::back() {
    return *(--end());
}

template <typename T>
const T& List<T>::back() const {
    return *(--end());
}

template <typename T>
void List<T>::push_front(const T& val) {
    insert(begin(), val);
}

template <typename T>
void List<T>::push_front(T&& val) {
    insert(begin(), std::move(val));
}

template <typename T>
void List<T>::push_back(const T& val) {
    insert(end(), val);
}

template <typename T>
void List<T>::push_back(T&& val) {
    insert(end(), std::move(val));
}

template <typename T>
void List<T>::pop_front() {
    erase(begin());
}

template <typename T>
void List<T>::pop_back() {
    erase(--end());
}

template <typename T>
void List<T>::remove(const T& val) {
    for (auto itr = begin(); itr != end();) {
        if (*itr == val)
            itr = erase(itr);
        else
            ++itr;
    }
}

template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred) {
    for (auto itr = begin(); itr != end();) {
        if (pred(*itr))
            itr = erase(itr);
        else
            ++itr;
    }
}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
    for (auto itr = begin(); itr != end(); ++itr) {
        os << *itr;
        if (itr.current->next != tail)
            os << ofc;
    }
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
    return const_iterator(head->next);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const {
    return const_iterator(tail);
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val) {
    Node* p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{val, p->prev, p}};
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& val) {
    Node* p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{std::move(val), p->prev, p}};
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) {
    Node* p = itr.current;
    iterator retVal{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retVal;
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) {
    for (auto itr = start; itr != end;)
        itr = erase(itr);
    return end;
}

template <typename T>
void List<T>::init() {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

// Non-member functions
template <typename T>
bool operator==(const List<T>& lhs, const List<T>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    auto itr1 = lhs.begin();
    auto itr2 = rhs.begin();
    while (itr1 != lhs.end() && itr2 != rhs.end()) {
        if (*itr1 != *itr2)
            return false;
        ++itr1;
        ++itr2;
    }
    return true;
}

template <typename T>
bool operator!=(const List<T>& lhs, const List<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& lst) {
    lst.print(os);
    return os;
}

#endif // DL_LIST_HPP
