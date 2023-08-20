#ifndef INC_2021_FALL_PROJECT_GROUP_E_1_PATHS_H
#define INC_2021_FALL_PROJECT_GROUP_E_1_PATHS_H
#include "Locations.h"
#include "LinkedList.h"
#include "List.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;
class Path{
    //starting point of path
    Location * start;
    //ending point of path
    Location * stop;
    //paths list
    Lists<double> *list_of_paths;
   // Lists<Node*> * list_of_routes;
    List<Location*> * path1;
    List<Location*> * path2;
    List<Location*> * path3;
    List<Location*> * lst;

public:
    List<Location*> * all_possible_paths[3]={nullptr};
    Path(){
        start = nullptr;
        stop = nullptr;
        lst = new List<Location*>;
        list_of_paths = new Lists<double>;
        path1 = path2 = path3 = nullptr;
        remove("Files\\Paths.txt");
    }
    //menu for
    void menu(){
        int choice = -1;
        do{
            start = new Location;
            start->setName("INFORMATION TECHNOLOGY UNIVERSITY");
            cout << "     WELCOME TO MENU     \n";
            cout << "Enter 1 to find paths towards your destination\n";
            cout << "Option: \n";
            cin >> choice;
            if(choice==1){
                cin.ignore();
                lst->appendNode(start);
                //setting up the destination
                string destination;
                cout << "Please enter your destination : ";
                getline(cin,destination);
                for(int i=0;i<destination.length();i++){
                   destination[i] = toupper(destination[i]);
                }
                stop = new Location;
                stop->setName(destination);
                if(stop->getName()=="AMANAH MALL" ||stop->getName()=="METRO CASH AND CARRY"||stop->getName()=="ITTEFAQ HOSPITAL"||
                        stop->getName()=="BLOCK G MARKET"||stop->getName()=="BLOCK F MARKET") {
                    remove("Files\\INFORMATION TECHNOLOGY UNIVERSITY.txt");
                    ofstream newfile("Files\\INFORMATION TECHNOLOGY UNIVERSITY.txt");
                    newfile <<
                            "ITTEFAQ HOSPITAL_1.2_1\n"
                            << "BLOCK H MARKET_1.3_2\n"
                            << "BLOCK A MARKET_1.9_1";
                    newfile.close();
                }else if(stop->getName()=="BLOCK A MARKET" ||stop->getName()=="BLOCK B MARKET"||stop->getName()=="BLOCK C MARKET"||
                         stop->getName()=="BLOCK D MARKET"||stop->getName()=="MODEL TOWN PARK"){
                    remove("Files\\INFORMATION TECHNOLOGY UNIVERSITY.txt");
                    ofstream newfile("Files\\INFORMATION TECHNOLOGY UNIVERSITY.txt");
                    newfile <<
                            "BLOCK A MARKET_1.9_1\n"<<
                            "BLOCK H MARKET_1.3_2\n" <<
                            "ITTEFAQ HOSPITAL_1.2_1";
                    newfile.close();
                }else if(stop->getName()=="BLOCK E MARKET" ||stop->getName()=="DIVISIONAL PUBLIC SCHOOL"||stop->getName()=="BLOCK H MARKET"){
                    remove("Files\\INFORMATION TECHNOLOGY UNIVERSITY.txt");
                    ofstream newfile("Files\\INFORMATION TECHNOLOGY UNIVERSITY.txt");
                    newfile <<
                            "BLOCK H MARKET_1.3_2\n"<<
                            "BLOCK A MARKET_1.9_1\n"<<
                            "ITTEFAQ HOSPITAL_1.2_1";
                    newfile.close();
                }
                start->loadDataFromFile("INFORMATION TECHNOLOGY UNIVERSITY");
                findBestPath(start);
                //list_of_paths->bubbleSort();
                //cout << "COUNT : " <<list_of_paths->getCount()<<endl;
                list_of_paths->mergeSort(list_of_paths->getHead());
                list_of_paths->printList();
                //lst->printList();
//                path1->printList();
//                path2->printList();
//                path3->printList();

                //stop->loadDataFromFile(destination);
            }

            cout << "Continue program\t1\n";
            cout << "End program\t2\n";
            cin >> choice;
            if(choice==2){
                choice=-1;
            }
        }
        while (choice != -1);
    }
    Location * checked[20]= {nullptr};
    string checkedmore[169]={""};
    int counter=0,counter2=0;
    int foundcount=0;
    int sum=0;
    void findBestPath(Location * begin){
        counter2++;
        bool neighbor = false;
        bool recursion = false;
        bool startPartner = false;
        bool startPartnerPartner = false;
        bool allPartnersChecked = false;
        bool found = false;
        bool itself=false;
        int size = sizeof(begin->partners)/sizeof(begin->partners[0]);
        checked[counter]= begin;
        counter++;
        for (int i = 0; i < size; ++i) {
            if(foundcount< 4) {
                itself = false;
                string partner_name = begin->partners[i]->getName();
                checkedmore[sum] = partner_name;
                sum++;
                if (partner_name == start->getName()) {
                    itself = true;
                }

                if (partner_name == stop->getName() && !itself) {
                    found = true;
                    lst->appendNode(begin->partners[i]);
                    //sum = begin->partners[i]->getDistance() + begin->getDistance();
                    foundcount++;
                    //lst->printList();
                    if(lst->peek()->getName()==stop->getName()) {
                        if (foundcount == 1) {
                            path1 = new List<Location*>;
                            path1 = lst;
                            cout << "Destination found from " << begin->getName() << " at " << lst->sumDistances() << "kms at " << lst->sumTrafficLevels() << " traffic" << endl;
                            list_of_paths->appendNode(path1->sumDistances());
                            //path1->printListToFile();
                            path1->printList();
                            cout << "===============================================================\n";
                        } else if (foundcount == 2)  {
                            path2 = new List<Location *>;
                            path2 = lst;
                            cout << "Destination found from " << begin->getName() << " at " << lst->sumDistances() << "kms at " << lst->sumTrafficLevels() << " traffic" << endl;
                            list_of_paths->appendNode(path2->sumDistances());
                            //path2->printListToFile();
                            path2->printList();
                            cout << "===============================================================\n";
                        } else if (foundcount == 3) {
                            path3 = new List<Location *>;
                            path3 = lst;
                            cout << "Destination found from " << begin->getName() << " at " << lst->sumDistances() << "kms at " << lst->sumTrafficLevels() << " traffic" << endl;
                            list_of_paths->appendNode(path3->sumDistances());
                            //path3->printListToFile();
                            path3->printList();
                            cout << "===============================================================\n";
                        }

                    }
                    if(foundcount==3){
                        return;
                    }
                    lst->removeNonHeads();
                    findBestPath(start);
                    recursion = true;
                    //return sum;
                    //lst->printList();
                    break;
                }
            }
        }
        if(!found && foundcount < 4){
            for (int k = 0; k < size; ++k) {
                allPartnersChecked= false;
                startPartner = false;
                startPartnerPartner = false;
                bool isgreater=false;
                bool islongest=false;
                const string partner = begin->partners[k]->getName();
                int checkedcount=0;
                for (int j = 0; j < counter2; ++j) {
                    string checkedname = checked[j]->getName();
                    if(partner== checked[j]->getName()){
                        checkedcount+=1;
                        break;
                    }
                }
                for (int j = 0; j < sizeof(start->partners)/sizeof(start->partners[0]); ++j) {
                    if(begin == start->partners[j]){
                        startPartner = true;
                    }
                }
                if(startPartner){
                    for (int j = 0; j < sizeof(start->partners)/sizeof(start->partners[0]); ++j) {
                        if(partner == start->partners[j]->getName()) {
                            startPartnerPartner = true;
                        }
                    }
                }
                for (int m = 0; m < size; ++m) {
                    if(partner == start->partners[m]->getName() && begin != start){
                        startPartnerPartner= true;
                       recursion = true;
                    }
                }
                //read checker
//                if(k==0){
//                    if(begin->partners[0]->checkedcounter > begin->partners[1]->checkedcounter && begin->partners[0]->checkedcounter > begin->partners[1]->checkedcounter){
//                        isgreater=true;
//                    }
//                }
//                else if(k==1){
//                    if(begin->partners[1]->checkedcounter > begin->partners[0]->checkedcounter && begin->partners[1]->checkedcounter > begin->partners[2]->checkedcounter){
//                        isgreater=true;
//                    }
//                }
//                else if(k==2){
//                    if(begin->partners[2]->checkedcounter > begin->partners[0]->checkedcounter && begin->partners[2]->checkedcounter > begin->partners[1]->checkedcounter){
//                        isgreater=true;
//                    }
//                }


                if(partner!=start->getName() && partner!= begin->getName() && checkedcount<1 && partner!= stop->getName() && !startPartnerPartner) {
                    //lst->printList();
                    begin->partners[k]->loadDataFromFile(partner);
                    ///checking
                    for (int j = 0; j < counter2; ++j) {
                        for(int l=0; l< size; l++){
                            string a = checked[j]->getName();
                            string b = begin->partners[k]->partners[l]->getName();
                            if(a==b){
                                begin->partners[k]->partners[l]->checkedcounter++;
                            }
                        }
                    }
                    if(begin->partners[k]->partners[0]->checkedcounter >1 &&  begin->partners[k]->partners[1]->checkedcounter > 1 && begin->partners[k]->partners[2]->checkedcounter > 1){
                        allPartnersChecked = true;
                    }
                    //sum = sum + findBestPath(begin->partners[k]);
                    if(!allPartnersChecked) {
                        lst->appendNode(begin->partners[k]);
                        findBestPath(begin->partners[k]);
                    }
                    //return sum;
                }
//                else if(k==size-1){
//                    lst->removeNonHeads();
//                    findBestPath(start);
//                }

            }
        }
    }
    ~Path(){
        delete start;
        //ending point of path
        delete stop;

        delete path1;
        delete path2;
        delete path3;
        delete lst;
    }

};

void convertToUpperCase(string &filename){
    for(int i=0; i < filename.length() ; i++){
        filename[i] = toupper(filename[i]);
    }
}
//////////////////////////


#endif
