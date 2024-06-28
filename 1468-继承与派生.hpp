#ifndef LSQ_HPP
#define LSQ_HPP

#include <iostream>
#include <cstdio>

template <typename T>
class LinkedList
{
private:
    int length = 0;
protected:
    struct Node{
        Node *nxt, *pre;
        T content;
        Node(const T& p): content(p),nxt{nullptr},pre{nullptr} {};
    };
    Node *head={nullptr}, *tail={nullptr};
public:   
    LinkedList(){};
    LinkedList(const LinkedList<T> &list){
        if(list.head!=nullptr){
            length = list.length;
            head = new Node(list.head->content);
            head->pre = nullptr; head->nxt = nullptr;
            Node *pl = list.head->nxt, *p = head, *cur;
            while(pl!=nullptr){
                cur = new Node(pl->content);
                //cur = malloc(sizeof(Node));
                //(*cur) = (*pl);
                p->nxt = cur;
                cur->pre = p;
                cur->nxt = nullptr;
                p = cur;
                pl = pl->nxt;
            }
            tail = p;
        }
    }
    ~LinkedList(){
        Node *p = head, *cur = nullptr;
        if(head!=nullptr) cur = head->nxt;
        delete head;
        while(cur!=nullptr){
            p = cur;
            cur = p->nxt;
            delete p;  // delete[] WA
        }
        length = 0;
        head = tail = nullptr;
    }
    void pushFront(const T& ele){
        //Node *p = (Node*)malloc(sizeof(Node));
        //p->content = ele;
        Node *p = new Node(ele);
        if(head == nullptr){
            p->nxt = nullptr;
            head = p;
            tail = p;
        }
        else{
            p->nxt = head;
            head->pre = p;
            head = p;
        }
        p->pre = nullptr;
        length++;
    }
    void pushBack(const T& ele){
        //Node *p = (Node*)malloc(sizeof(Node));
        //p->content = ele;
        Node *p = new Node(ele);
        if(tail == nullptr){
            p->pre = nullptr;
            head = p;
            tail = p;
        }
        else{
            p->pre = tail;
            tail->nxt = p;
            tail = p;
        }
        p->nxt = nullptr;
        length++;
    }
    T popFront(){
        if(head == nullptr) return T();
        length--;
        T tmp = head->content;
        Node *p = head->nxt;
        delete head;
        head = p;
        if(head == nullptr) tail = nullptr;
        else head->pre = nullptr;
        //print();
        return tmp;
    }
    T popBack(){
        if(tail == nullptr) return T();
        length--;
        T tmp = tail->content;
        Node *p = tail->pre;
        delete tail;
        tail = p;
        if(tail == nullptr) head = nullptr;
        else tail->nxt = nullptr;
        //print();
        return tmp;
    }
    int size() const {return length;}
    void print() const {
        Node *p = head;
        while(p!=nullptr){
            std::cout<<(p->content)<<" ";
            p = p->nxt;
        }
        std::cout<<std::endl;
    }
    virtual const char* name() {return "";}
    virtual T peak() {return T();}
    virtual T pop() {return T();}
    virtual void push(T val) {};
};

template <typename T>
class Stack: public LinkedList<T>
{
public:
    Stack(): LinkedList<T>(){};
    ~Stack(){};
    virtual const char* name() {return "Stack";}
    virtual T peak(){
        if(this->head == nullptr) return T();
        return this->head->content;
    }
    virtual T pop() {return LinkedList<T>::popFront();}
    virtual void push(T val) {this->pushFront(val);}
};

template <typename T>
class Queue: public LinkedList<T>
{
public:
    Queue(): LinkedList<T>(){};
    ~Queue(){};
    virtual const char* name() {return "Queue";}
    virtual T peak(){
        if(this->head == nullptr) return T();
        return LinkedList<T>::head->content;
    }
    virtual T pop() {return this->popFront();}
    virtual void push(T val) {this->pushBack(val);}
};

#endif