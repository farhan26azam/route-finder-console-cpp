#include "Admin.h"
#include "Paths.h"
#include "User.h"
#include "Locations.h"
#include<fstream>
#include <iostream>
using namespace std;

int main(){
    user * usr = new user;
    usr->menu();
    return 0;
}

