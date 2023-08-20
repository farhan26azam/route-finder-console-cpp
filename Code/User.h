#ifndef INC_2021_FALL_PROJECT_GROUP_E_1_USER_H
#define INC_2021_FALL_PROJECT_GROUP_E_1_USER_H

//code here
#include<string>
#include<fstream>
#include<iostream>
#include <iomanip>
#include "Paths.h"
using namespace std;

class user {
    string name;
    double distance;
    int traffic_level;
public:

    Path * p;
    user* partners[3] = { nullptr };

    user() {
        name = "";
        distance = 0;
        traffic_level = 0;
        p=nullptr;
    }

    void setName(string name_a) {
        name = name_a;
    }

    string getName() {
        return name;
    }

    void setPartners(user* partners_a) {
        *partners = partners_a;
    }

    void setDistance(double distance_a) {
        distance = distance_a;
    }

    double getDistance() { return distance; }

    void setTrafficLevel(int traffic_level_a) {
        traffic_level = traffic_level_a;
    }

    int getTrafficLevel() {
        return traffic_level;
    }

    void setPartnerNumber(int index, user* partner) {
        partners[index] = partner;
    }

    user* getPartnerNumber(int index) {
        return partners[index];
    }

    void trafficLevel(const string& name_of_location) { //Tells the traffic level on the path in range 1 to 5.

        int count = 0;
        string filename = "Files\\ " +name_of_location + ".txt";
        cout << filename;
        ifstream readfile(filename);
        string data;
        bool first = false, second = false, check1 = false, check2 = false;
        while (getline(readfile, data)) {
            string partner = "";
            string traffic = "";
            char store = '0';
            for (int i = 0; (int)store != 0; i++) {
                store = data[i];

                if (store == '_' && !check1) {
                    first = true;
                    check1 = true;
                }

                else if (store == '_' && !check2) {
                    second = true;
                    check2 = true;
                }

                if (!first && store != '_') {
                    partner += store;
                }

                else if (!second && store != '_') {
                    distance += store;
                }

                else if (store != '_' && (int)store != 0) {
                    traffic += store;
                }
            }

            auto* add = new user;
            add->setName(partner);
            add->setTrafficLevel(stoi(traffic));
            setPartnerNumber(count, add);
            first = false, second = false, check1 = false, check2 = false;
            count++;

        }

        readfile.close();
        for (int i = 0; i < 3; ++i) {

            cout << "Traffic level to " << this->getPartnerNumber(i)->getName() << " is (1 to 5) :" << this->getPartnerNumber(i)->getTrafficLevel() << endl;
        }
    }

    void locationData(const string& name_of_location) {  //Gives the complete details of the location.
        int count = 0;
        string filename = "Files\\" +name_of_location + ".txt";
        ifstream readfile(filename);
        string data;
        bool first = false, second = false, check1 = false, check2 = false;
        while (getline(readfile, data)) {
            string partner = "";
            string distance = "";
            string traffic = "";
            char store = '0';
            for (int i = 0; (int)store != 0; i++) {
                store = data[i];

                if (store == '_' && !check1) {
                    first = true;
                    check1 = true;
                }

                else if (store == '_' && !check2) {
                    second = true;
                    check2 = true;
                }

                if (!first && store != '_') {
                    partner += store;
                }

                else if (!second && store != '_') {
                    distance += store;
                }

                else if (store != '_' && (int)store != 0) {
                    traffic += store;
                }
            }

            auto* add = new user;
            add->setName(partner);
            add->setDistance(stod(distance));
            add->setTrafficLevel(stoi(traffic));
            setPartnerNumber(count, add);
            first = false, second = false, check1 = false, check2 = false;
            count++;
        }

        readfile.close();

    }

    void displayDetails() {
        for (int i = 0; i < 3; ++i) {
            cout << "Partner :" << this->getPartnerNumber(i)->getName() << endl;
            cout << "Distance :" << this->getPartnerNumber(i)->getDistance() << "Km" << endl;
            cout << "Traffic Level :" << this->getPartnerNumber(i)->getTrafficLevel() << endl;
        }
    }


    void adjDistance(const string& n1, const string& n2) { //Gives the distance between two adjacent locations.

        locationData(n1);
        if ((this->getPartnerNumber(0)->getName() == n2)) {
            cout << "They are partners!" << endl;
            cout << "Distance between the adjacent locations is :" << this->getPartnerNumber(0)->getDistance() << "Km." << endl;
        }
        else if ((this->getPartnerNumber(1)->getName() == n2)) {
            cout << "They are partners!" << endl;
            cout << "Distance between the adjacent locations is :" << this->getPartnerNumber(1)->getDistance() << "Km" << endl;
        }
        else if ((this->getPartnerNumber(2)->getName() == n2)) {
            cout << "They are partners!" << endl;
            cout << "Distance between the adjacent locations is :" << this->getPartnerNumber(2)->getDistance() << "Km" << endl;
        }
        else {
            cout << "They are not partners!" << endl;


        }

    }

    bool isPresent(string loc) {  //Tells that a certain location is present or not.
        ifstream fin;
        fin.open("Files\\Locations.txt");
        string data;
        while (getline(fin, data))
        {
            if (data == loc) {
                return true;
            }
        }
        cout << "Invalid Location! ";
        return false;
    }

    int menu() {
        int op;
        string n1, n2;

        do {
            cout << endl;
            cout << "------------------------USER MENU------------------------" << endl;
            cout << endl;
            cout << "     Press 1 to find traffic levels." << endl;
            cout << "     Press 2 to find location data." << endl;
            cout << "     Press 3 to find distance between adjacent locations." << endl;
            cout << "     Press 4 to get best path." << endl;
            cout << "     Press 0 to exit." << endl;
            cout << endl;
            cout << "----------------------------------------------------------" << endl;
            cout << "Your choice :";
            cin >> op;
            switch (op) {
            case 1:
                cout << "Enter the name of location in caps :" << endl;
                cin.ignore();
                getline(cin, n1);
                if (isPresent(n1)) {
                    trafficLevel(n1);
                }
                else {
                    cout << "Please add the location first." << endl;
                }
                system("pause");

                break;
            case 2:
                cout << "Enter the Location to find Data in caps :" << endl;
                cin.ignore();
                getline(cin, n1);
                if (isPresent(n1)) {
                    locationData(n1);
                    displayDetails();
                }
                else {
                    cout << "Please add the location first." << endl;
                }
                system("pause");

                break;
            case 3:
                cout << "Enter location 1 :" << endl;
                cin.ignore();
                getline(cin, n1);
                if (isPresent(n1)) {
                    cout << "Enter location 2 :" << endl;
                    getline(cin, n2);
                    if (isPresent(n2)) {
                        adjDistance(n1, n2);
                    }
                }
                else {
                    cout << "Please add the location first." << endl;
                }
                system("pause");

                break;
                case 4:
                    p=new Path;
                    p->menu();

            }
        } while (op != 0);
        return 0;
    }
};

#endif
