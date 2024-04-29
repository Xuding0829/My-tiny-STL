#include <iostream>
#include <stdexcept>
#include <stdlib.h>
using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node* next;
    Node(const T& value): data(value), next(nullptr){}
};

template <typename T>
class Mystack{
private:
    Node<T>* topNode;
    void clear() {
        while (!empty()) {
            pop();
        }
    }
public:
    Mystack(): topNode(nullptr){}

    ~Mystack(){
        clear();
    }
    
    bool empty(){
        return topNode == nullptr;
    }

    T& top(){
        if(empty()){
            exit(0);
        }
        else return topNode->data;
    }

    size_t size(){
        size_t count = 0;
        Node<T>* current = topNode;
        while (current) {
            ++count;
            current = current->next;
        }
        return count;
    }

    void pop(){
        if(!empty()){
            Node<T>* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    void push(const T& value){
        Node<T>* newNode = new Node<T>(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    template< class... Args >
    void emplace(Args&&... args){
        Node<T>* newNode = new Node<T>(T(forward<Args>(args)...));
        newNode->next = topNode;
        topNode = newNode;
    }

    void swap(Mystack& other) noexcept{
        std::swap(topNode, other.topNode);
    }

    friend void swap(Mystack<T>& lhs, Mystack<T>& rhs) noexcept{
        lhs.swap(rhs);
    }

    bool operator==(const Mystack& other){
        Node<T>* current1 = topNode;
        Node<T>* current2 = other.topNode;

        while(current1 && current2){
            if(current1->data != current2->data) return false;
            else{
                current1 = current1->next;
                current2 = current2->next;
            }
        }

        return current1 == nullptr && current2 == nullptr;
    }

    bool operator!=(const Mystack& other){
        return !(*this == other);
    }

    bool operator<(const Mystack& other){
        Node<T>* current1 = topNode;
        Node<T>* current2 = other.topNode;
        Mystack<T> st;
        Mystack<T> st_;
        while(current1 && current2){
            st.push(current1->data);
            st_.push(current2->data);
            current1 = current1->next;
            current2 = current2->next;
        }
        while(current1){
            st.push(current1->data);
            current1 = current1->next;
        }
        while(current2){
            st_.push(current2->data);
            current2 = current2->next;
        }
        while(!st.empty() && !st_.empty()){
            //cout << st.top() << st_.top();
            if(st.top() > st_.top()) return false;
            else{
                st.pop();
                st_.pop();
            }
        }
        if(!st.empty()) return false;
        else return true;
    }

    bool operator<=(const Mystack& other){
        if(*this < other || *this == other) return true;
        else return false;
    }

    bool operator>(const Mystack& other){
        Node<T>* current1 = topNode;
        Node<T>* current2 = other.topNode;
        
        Mystack<T> st;
        Mystack<T> st_;

        while(current1 && current2){
            st.push(current1->data);
            st_.push(current2->data);
            current1 = current1->next;
            current2 = current2->next;
        }

        while(current1){
            st.push(current1->data);
            current1 = current1->next; 
        }

        while(current2){
            st_.push(current2->data);
            current2 = current2->next;
        }

        while(!st.empty() && !st_.empty()){
            if(st.top() < st_.top()) return false;
            else{
                st.pop();
                st_.pop();
            }
        }

        if(!st_.empty()) return false;
        else return true;
    }

    bool operator>=(const Mystack& other){
        if(*this == other || *this > other) return true;
        else return false;
    }

    class Iterator {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* startNode) : current(startNode) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(topNode);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};



