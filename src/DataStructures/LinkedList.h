    //
// Created by eduardo218 on 4/5/21.
//

#ifndef C__SERVER_LINKEDLIST_H
#define C__SERVER_LINKEDLIST_H

#include <ostream>
#include <string>
using namespace std;

template<typename T>
class Node {
public:
    friend ostream &operator<<(ostream &os, const Node &node) {
        os << "value: " << node.value;
        return os;
    }

private:
    T value; /*!< Value stored in the node.*/
public:
    Node(T value) : value(value) {}

private:
    Node *next;
public:
    const T &getValue() const {
        return value;
    }

    void setValue(const T &newValue) {
        Node::value = newValue;
    }

    Node *getNext() const {
        return next;
    }

    void setNext(Node *newNext) {
        Node::next = newNext;
    }
    /*!<Pointer to the newNext node in the list..*/

};

template<typename T>
class LinkedList {

public:
    Node<T> *head = nullptr; /*!< Head of the list.*/
    Node<T> *tail = nullptr;/*!< Length of the list.*/
    int len{};

    LinkedList() {
        this->head = NULL;
        this->len = 0;
        this->tail = NULL;
    }


    Node<T> *getHead() const {
        return head;
    }

    /**>
     * Method for deleting a Node of the list.
     * @tparam T Generic data type, must have equal operator.
     * @param element T type element to eliminate from the list.
     */
    void del(T element) {

        if (element == this->head->getValue()) {
            this->head = this->head->getNext();
            this->len--;
        } else {
            Node<T> *tmp = this->head;
            for (int i = 0; i < (this->len - 1); ++i) {
                if (tmp->getNext()->getValue() == element) {
                    tmp->setNext(tmp->getNext()->getNext());
                    this->len--;
                    return;
                } else {
                    tmp = tmp->getNext();
                }
            }
        }
    }

    /**>
     * Method used for adding an element to the end of the list.
     * @param element: Type int object
     */
    void append(T element) {
        /**> Memory assignment for the Node*/
        auto *newElement = (Node<T> *) (malloc(sizeof(Node<T>)));
        /**> Creating the Node instance in the memory space assigned*/
        newElement = new(newElement) Node<T>(element);

        if (this->head == nullptr) {
            this->head = this->tail = newElement;
        } else {
            this->tail->setNext(newElement);
            this->tail = newElement;
        }
        this->len += 1;

    }

    /**>
     * Method for showing the list on the console.
     */
    void show() const {

        if (this->head == nullptr) {
            cout << "[]";
        } else {
            cout << "[";
            Node<T> *tmp = this->head;
            for (int i = 0; i < (this->len - 1); ++i) {
                cout << tmp->getValue() << ", ";
                tmp = tmp->getNext();
            }
            cout << tmp->getValue() << "]" << "\n";
        }
    }

    /**>
     * Method for getting an element of the list given its position on a zero-based index.
     * @tparam T T Generic data type, must have equal operator.
     * @param i zero-based index of the element.
     * @return NULL if the index its out of bound, or the element.
     */
    T get(int i) {

        if (i >= this->len) {
            throw std::out_of_range("Index out of range");
        }
        Node<T> *tmp = this->head;
        for (int j = 0; j < i; ++j) {

            tmp = tmp->getNext();

        }
        return tmp->getValue();
    }

    bool boolSearch(T element) {
        bool result = false;
        Node<T> *tmp = this->head;
        //cout << "Searching: " << element << "\n";
        for (int i = 0; i < (this->len); ++i) {
            if (tmp->getValue() == element) {
                //cout << "Found it!!\n";

                result = true;
                break;
            }
            //cout << "Visiting: " << tmp->getValue() << "\n";
            tmp = tmp->getNext();
        }
        return result;
    }

    /**>
     * Method for deleting the first element of the list.
     * @tparam T Generic data type, must have equal operator.
     */
    void delHead() {
        this->del(this->head->getValue());
    }

    void delTail() {
        del(this->get(this->len - 1));
    }

    int getLen() {
        return this->len;
    }
};


#endif //C__SERVER_LINKEDLIST_H
