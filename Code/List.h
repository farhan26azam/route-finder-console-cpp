#ifndef INC_2021_FALL_PROJECT_GROUP_E_1_LIST_H
#define INC_2021_FALL_PROJECT_GROUP_E_1_LIST_H
#include <iostream>
using namespace std;
//node class
template <typename typ>
class Nodes{
private:
    typ node_value;
public:
    Nodes *next_node;
    Nodes *previous_node;
    Nodes(){node_value = 0;}
    ~Nodes(){
        delete next_node;
        delete previous_node;
    }
    void setValue(typ value){
            node_value = value;
    }
    typ getValue() const{
            return node_value;
    }
    Nodes* getNextNode() const{
            return next_node;
    }
    void setNextNode(Nodes* new_node){
            next_node = new_node;
    }
    Nodes * getPreviousNode(){
            return previous_node;
    }
    void setPreviousNode(Nodes* last_node){
            previous_node = last_node;
    }
    };
//linklist
template <typename t>
    class Lists{
    private:

        //count
        int count=-1;
        //top
        Nodes<t>* top;
    public:
        //head
        Nodes<t>*head;
        //tail
        Nodes<t>*tail;
        Lists(){
            head = nullptr;
            tail = nullptr;
            count=0;
        }
        //destructor
        ~Lists(){
            if(head== nullptr){
            }
            else{
                while (head!= nullptr) {
                    Nodes<t>*ptr = head;
                    head = head->getNextNode();
                    delete ptr;
                }
            }
        }
        //setters
        void setHead(Nodes<t>* new_head){
            head = new_head;
        }
        void setTail(Nodes<t>*new_tail){
            tail = new_tail;
        }
        void setCount(int new_count){
            count = new_count;
        }
        //getters
        Nodes<t>* getHead()const{
            return head;
        }
        Nodes<t>* getTail() const{
            return tail;
        }
        int getCount() const{
            return count;
        }
        //inserts
        //append
        void appendNode(t value){
            Nodes<t>* temp = new Nodes<t>;
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
        //prepend
        void prependNode(t value){
            Nodes<t> * temp = new Nodes<t>;
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
        void insertAtIndex(Nodes<t>** present, t value, int index){
            if(index<0 || index >count){
                cout << "Invalid index out of range.\n";
            }else{
                while(index--){
                    if(index==0){
                        Nodes<t> * temp = new Node<t>;
                        temp->setValue(value);
                        temp->setPreviousNode((*present)->previous_node);
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
            Nodes<t>*ptr = head;
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
            Nodes<t>*third_last = tail->previous_node->getPreviousNode();
            Nodes<t>*second_last = tail->previous_node;//cout << "\nGood 165.\n";
            second_last->setPreviousNode(third_last);//cout << "\nGood 167.\n";
            //delete second_last->getNextNode();
            second_last->setNextNode(nullptr);//cout << "\nGood 168.\n";
            tail = second_last;//cout << "\nGood 169.\n";
            count--;
        }
        //print
        void printList(){
            cout << "List of distances: \n";
            Nodes<t>* head_store= head;
            int count_store = count;
            if(head== nullptr){
                cout << "List is empty.\n";
                return;
            }
            while(count_store!= 0){
                if(count_store==count){
                    cout << "Best option is the path with distance " << head_store->getValue() << "kms." << endl;
                }else if(count_store==count-1){
                    cout << "Second best option is the path with distance " << head_store->getValue() << "kms." << endl;
                }else if(count_store==count-2){
                    cout << "Third best option is the path with distance " << head_store->getValue() << "kms." << endl;
                }
                head_store = head_store->getNextNode();
                count_store--;
            }
            cout << "\n";
        }
        //menu
        //STACK FUNCTIONS
        //top
        void setTop(){
            top = tail;
        }
        //push at top
        void pushAtTop(t value){
            Nodes<t> * temp = new Nodes<t>;
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
            Nodes<t>* second_last = head;
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
        int peek()const{
            if(head!= nullptr || count > 0)
            {return tail->getValue();}
            else{cout << "The list is empty!\n";}
        }
        //DOUBLY LINKED LIST EXTRA FUNCTIONS
        //delete at index
        void deleteAtIndex(Nodes<t>** present, int index){
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
                count--;
            }

        }
        //delete using search
        void deleteValue(t value){
            Nodes<t> * temp = head;
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
        int findMax(){
            int max=-20000;
            for( Nodes<t> * temp = head; temp!= nullptr; temp= temp->getNextNode()){
                if(temp->getValue() > max){
                    max = temp->getValue();
                }
            }
            return max;
        }


        //bubble sort
        void swapData(Nodes<t> *first, Nodes<t> *second)
        {
            t value = first->getValue();
            first->setValue(second->getValue());
            second->setValue(value);
        }
        // Perform bubble sort
        void bubbleSort()
        {
            if (this->head == nullptr)
            {
                return;
            }
            bool task = true;
            // Get first node
            Nodes<t> *start = this->head;
            while (task == true)
            {
                task = false;
                while (start != nullptr && start->getNextNode() != nullptr)
                {
                    if (start->getValue() > start->getNextNode()->getValue())
                    {
                        this->swapData(start, start->getNextNode());
                        // Active the next iteration
                        task = true;
                    }
                    // Visit to next node
                    start = start->getNextNode();
                }
                // Get first node
                start = this->head;
            }
        }
        //MERGE SORT
        Nodes<t> *split(Nodes<t> *head1)
        {
            Nodes<t> *fast = head1,*slow = head1;
            while (fast->getNextNode() && fast->getNextNode()->getNextNode())
            {
                fast = fast->getNextNode()->getNextNode();
                slow = slow->getNextNode();
            }
            Nodes<t> *temp = slow->getNextNode();
            slow->setNextNode(nullptr);
            return temp;
        }
        Nodes<t> *merge(Nodes<t> *first, Nodes<t> *second)
        {
            // If first linked list is empty
            if (!first)
                return second;

            // If second linked list is empty
            if (!second)
                return first;

            // Pick the smaller value
            if (first->getValue() < second->getValue())
            {
                first->setNextNode(merge(first->getNextNode(),second));
                first->getNextNode()->setPreviousNode(first);
                first->setPreviousNode(nullptr);
                return first;
            }
            else
            {
                second->setNextNode(merge(first,second->getNextNode()));
                second->getNextNode()->setNextNode(second);
                second->setPreviousNode(nullptr);
                return second;
            }
        }
        Nodes<t> *mergeSort(Nodes<t> * head2)
        {
            if (!head2 || !head2->getNextNode())
                return head2;
            Nodes<t> *second = split(head2);

            // Recur for left and right halves
            head2 = mergeSort(head2);
            second = mergeSort(second);

            // Merge the two sorted halves
            return merge(head2, second);
        }
    };

#endif
