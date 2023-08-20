#include "Paths.h"
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include "Locations.h"
#include<iostream>
using namespace std;
//node class
template <typename typ>
class Node{
private:
    typ node_value;
public:
    Node *next_node;
    Node *previous_node;
    Node(){
        next_node = nullptr;
        previous_node = nullptr;
        node_value = nullptr;
    }
    ~Node(){
        delete node_value;
        delete next_node;
        delete previous_node;
    }
    void setValue(typ value){
        node_value = value;
    }
    typ getValue() const{
        return node_value;
    }
    Node* getNextNode() const{
        return next_node;
    }
    void setNextNode(Node* new_node){
        next_node = new_node;
    }
    Node * getPreviousNode() const {
        return previous_node;
    }
    void setPreviousNode(Node* last_node){
        previous_node = last_node;
    }
};
//linklist
template <typename ty>
class List{
private:
    //head
    Node<ty>*head;
    //tail
    Node<ty>*tail;
    //count
    int count=-1;
    //top
    Node<ty>* top;
    //friend class
public:
    //constructor
    List(){
        head = nullptr;
        tail = nullptr;
        count=0;
    }
    //parametrized constructor
    List(Node<ty> * header){
        head = header;
    }
    //destructor
    ~List(){
        if(head== nullptr){
        }
        else{
            while (head!= nullptr) {
                Node<ty>*ptr = head;
                head = head->getNextNode();
                delete ptr;
            }
        }
    }
    //setters
    void setHead(Node<ty>* new_head){
        head = new_head;
    }
    void setTail(Node<ty>*new_tail){
        tail = new_tail;
    }
    void setCount(int new_count){
        count = new_count;
    }
    //getters
    Node<ty>* getHead()const{
        return head;
    }
    Node<ty>* getTail() const{
        return tail;
    }
    int getCount() const{
        return count;
    }
    //inserts
    //append
    void appendNode(ty value){
        if(head== nullptr){
            Node<ty> * temp = new Node<ty>;
            temp->setValue(value);
            temp->setNextNode(nullptr);
            if(head== nullptr){
                setHead(temp);
                setTail(temp);
                temp = nullptr;
            }else {
                tail->setNextNode(temp);
                temp->setPreviousNode(tail);
                setTail(temp);
            }
            setCount(count+1);
        }else if( value == this->peek()->getPartnerNumber(0) || value == this->peek()->getPartnerNumber(1)
        || value == this->peek()->getPartnerNumber(2)){
            Node<ty> * temp = new Node<ty>;
            temp->setValue(value);
            temp->setNextNode(nullptr);
            if(head== nullptr){
                setHead(temp);
                setTail(temp);
                temp = nullptr;
            }else {
                tail->setNextNode(temp);
                temp->setPreviousNode(tail);
                setTail(temp);
            }
            setCount(count+1);
        }
    }
    //prepend
    void prependNode(Location * value){
        Node<ty> * temp = new Node<ty>;
        temp->setValue(value);
        head->setPreviousNode(temp);
        temp->setNextNode(head);
        temp->setPreviousNode(nullptr);
        if(head== nullptr) {
            setTail(temp);
            //temp = nullptr;
        }
        setHead(temp);
        setCount(count+1);
    }
    //insert at index
    void insertAtIndex(Node<ty>** present, Location * value, int index){
        if(index<0 || index >count){
            cout << "Invalid index out of range.\n";
        }else{
            while(index--){
                if(index==0){
                    Node<ty> * temp = new Node<ty>;
                    temp->setValue(value);
                    temp->setPreviousNode((*present)->previous_node);
                    //(*present)->previous_node->setNextNode(temp);
                    temp->setNextNode(*present);
                    *present = temp;
                }
                else
                {
                    present = &(*present)->next_node;
                }
            }
            count++;
        }

    }
    //deletions
    void deleteFirstNode(){
        Node<ty>*ptr = head;
        setHead(head->getNextNode());
        head->setNextNode(head->getNextNode());

        head->setPreviousNode(nullptr);

        //delete head;
        count--;
    }
    //delete tail
    void deleteTail(){
        if(head== nullptr){
            return;
        }
        if(head->getNextNode()== nullptr){
            delete head;
            count--;
            return;
        }
        Node<ty>*third_last = tail->previous_node->getPreviousNode();
        Node<ty>*second_last = tail->previous_node;//cout << "\nGood 165.\n";
        second_last->setPreviousNode(third_last);//cout << "\nGood 167.\n";
        //delete second_last->getNextNode();
        second_last->setNextNode(nullptr);//cout << "\nGood 168.\n";
        tail = second_last;//cout << "\nGood 169.\n";
        count--;
    }
    //print
    void printList(){
        cout << "Path :  ";
        Node<ty>* head_store= head;
        int count_store = count;
        if(head== nullptr){
            cout << "List is empty.\n";
            return;
        }
        cout << " From ";
        while(count_store!= 0){
            cout << head_store->getValue()->getName();
            if(head_store!= head) {
                cout << " for " << head_store->getValue()->getDistance() << "kms";
            }
            int result = rand() % 3;
            if(head_store!= tail) {
                if(result==0){
                    cout << " go to ";
                }else if(result==1){
                    cout << " then move towards ";
                }
                else if(result== 2){
                    cout << " now turn towards ";
                }
            }
            head_store = head_store->getNextNode();
            count_store--;
        }
        cout << "\n";
    }

    void printListToFile(){
        fstream fout("Files\\Paths.txt",ios::out | ios::app);
        Node<ty>* head_store= head;
        int count_store = count;
        if(head== nullptr){
            fout << "EMPTY PATH\n";
            return;
        }
        fout << this->sumDistances()<<">";
        while(count_store!= 0){
            fout<< head_store->getValue()->getName();
            if(head_store!= tail) {
                fout << ">";
            }
            head_store = head_store->getNextNode();
            count_store--;
        }
        fout << "\n";
        fout.close();
    }

    ostream & operator << (ostream &out)
    {
        Node<ty> * head_store = head;
        int count_store = count;
        if(head_store== nullptr){
            out << "EMPTY LIST.\n";
        }
        while(count_store!=0) {
            out << head_store->getValue()->getName();
            if (head_store != tail) {
                head_store = head_store->getNextNode();
                count_store--;
            }
        }
        return out;
    }
    //remove all members other than head
    void removeNonHeads(){
        while(count>1){
            deleteTail();
        }
    }
    //sum distances
    double sumDistances(){
        double total_distance=0;
        Node<ty> * temp = head;
        for( ; temp!= nullptr; temp = temp->getNextNode()){
            total_distance += temp->getValue()->getDistance();
        }
        return total_distance;
    }

    double sumTrafficLevels(){
        double total_traffic=0;
        int counter=0;
        Node<ty> * temp = head;
        for( ; temp!= nullptr; temp = temp->getNextNode()){
            total_traffic += temp->getValue()->getTrafficLevel();
            counter++;
        }
        if(counter>1) {
            double average = total_traffic / counter;
            return average;
        }else{
            return total_traffic;
        }
    }
    //STACK FUNCTIONS
    //top
    void setTop(){
        top = tail;
    }
    //push at top
    void pushAtTop(Location * value){
        Node<ty> * temp = new Node<ty>;
        temp->setValue(value);
        temp->setNextNode(nullptr);
        if(head== nullptr){
            setHead(temp);
            setTail(temp);
            temp = nullptr;
        }else {
            tail->setNextNode(temp);
            setTail(temp);
        }
        setCount(count+1);
    }
    //pop from top
    void popFromTop(){
        if(head== nullptr){
            return;
        }
        if(head->getNextNode()== nullptr){
            delete head;
            delete tail;
            count=0;
            return;
        }
        Node<ty>* second_last = head;
        while (second_last->getNextNode()->getNextNode()!= nullptr){
            second_last = second_last->getNextNode();
        }
        tail=second_last;
        second_last->setNextNode(nullptr);
        //delete (second_last->getNextNode());
        count--;
    }
    //empty checker
    bool isEmpty() const{
        if(head== nullptr || count < 1){
            return true;
        }
        else{
            return false;
        }
    }
    //peek
    Location * peek()const{
        if(head!= nullptr || count > 0)
        {return tail->getValue();}
        else{cout << "The list is empty!\n";
            return nullptr;
        }
    }
    //DOUBLY LINKED LIST EXTRA FUNCTIONS
    //delete at index
    void deleteAtIndex(Node<ty>** present, int index){
        if(index<0 || index >count){
            cout << "Invalid index out of range.\n";
        }else{
            while(index--){
                if(index==0){
                    //Node * temp = new Node;
                    ((*present))->getNextNode()->setPreviousNode(((*present)->getPreviousNode()));
                    ((*present))->getPreviousNode()->setNextNode(((*present)->getNextNode()));
                    delete (&(*present));
                }
                else
                {
                    present = &(*present)->next_node;
                }
            }
<<<<<<< HEAD
            new_node->setNextNode(current->getNextNode());
            current->setNextNode(new_node);
        }
    }
    
};
=======
            count--;
        }

    }
    //deep copy constructor
    List(List& sample){
        head = sample.head;
        Node<ty> * temp = head;
        Node<ty> * temp2 = sample.head;
        while(temp2->getNextNode()!=nullptr){
            temp = temp2;
            temp = temp->getNextNode();
            temp2 = temp2->getNextNode();
        }
    }
    //delete using search
    void deleteValue(Location * value){
        Node<ty> * temp = head;
        while(temp!= nullptr){
            //cout << "temp->value :" << temp->getValue() <<endl;
            if(temp->getValue()==value){
                //Node * temp = new Node;
                temp->previous_node->next_node = temp->next_node;
                temp->next_node->previous_node = temp->previous_node;
                count--;
                //cout << "temp->value inside:" << temp->getValue() <<endl;
                //temp= nullptr;
            }
            else
            {
                //cout << "temp->value else:" << temp->getValue() <<endl;
                temp = temp->next_node;
            }

        }

    }
>>>>>>> 6c9b344c5d4f600a57433a425f58dc498d797d5e

};
/////////////////////////////////////////////////