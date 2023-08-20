#ifndef INC_2021_FALL_PROJECT_GROUP_E_1_LOCATIONS_H
#define INC_2021_FALL_PROJECT_GROUP_E_1_LOCATIONS_H
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
//Location class will be like node class which will be linked in paths
class Location{
    string name;
    double distance;
    int traffic_level;
public:
    //list of partners
    Location * partners[3]={nullptr};
    //constructor
    Location(){
        name = "";
        distance=0;
        traffic_level=0;
        checkedcounter=0;
    }
    // name setter
    void setName(string name_a){
        name=name_a;
    }
    //name getter
    string getName(){
        return name;
    }
    //partners setter
    void setPartners(Location *partners_a){
        *partners = partners_a;
    }
    //distance setter
    void setDistance(double distance_a){
        distance= distance_a;
    }
    //distance getter
    double getDistance(){return distance;}
    //traffic level setter
    void setTrafficLevel(int traffic_level_a){
        traffic_level = traffic_level_a;
    }
    //traffic level getter
    int getTrafficLevel(){
        return traffic_level;
    }
    //this function sets a partner at certain index of current location
    //used in loading data from file
    void setPartnerNumber(int index , Location* partner){
        partners[index] = partner;
    }
    // to access a partner through index
    Location * getPartnerNumber(int index){
        return partners[index];
    }
    //this function gets all the data about partner locations from the location file and returns the number of partners
    int loadDataFromFile(const string& name_of_location){
        //count will count partners
        int count=0;
        //filename store name of location file
        string filename = "Files\\" + name_of_location + ".txt";
        //creating the fstream object
        ifstream readfile(filename);
        //data will store characters line by line
        string data;
        //these booleans help in identifying information
        bool first = false, second = false,check1= false, check2= false;
        while (getline(readfile, data)) {
            //empty strings
            string partner="";
            string distance="";
            string traffic="";
            //store will store each character on a line
            char store= '0';
            for( int i=0; (int)store!= 0; i++){
                store = data[i];
                //first case to check if we are reading the name
                if(store == '_' && !check1){
                    first = true;
                    check1 = true;
                }
                //second case to check is we are reading the distance
                else if(store == '_' && !check2){
                    second = true;
                    check2 = true;
                }
                //storing name in partner
                if(!first && store != '_'){
                    partner += store;
                }
                //storing distance in distance
                else if(!second && store != '_'){
                    distance+= store;
                }
                //storing traffic level in traffic
                else if(store!='_' && (int)store!=0){
                    traffic += store;
                }
            }
            //creating a location object to store the data from file
            auto * add = new Location;
            add->setName(partner);
            add->setDistance(stod(distance));
            add->setTrafficLevel(stoi(traffic));
            //setting the object as a partner to current location
            setPartnerNumber(count,add);
            //resetting the previous booleans
            first = false, second = false,check1= false, check2= false;
            //incrementing partner number
            count++;
        }
        //closing the file
        readfile.close();
        return count;
    }
    // DISPLAY DETAILS
    void displayDetails(){
        for (int i = 0; i < 3; ++i) {
            cout << this->getPartnerNumber(i)->getName()<<endl;
            cout << this->getPartnerNumber(i)->getDistance()<<endl;
            cout << this->getPartnerNumber(i)->getTrafficLevel()<<endl;
        }
    }
    int checkedcounter;
};
#endif
