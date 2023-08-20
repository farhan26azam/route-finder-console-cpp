#ifndef INC_2021_FALL_PROJECT_GROUP_E_1_ADMIN_H
#define INC_2021_FALL_PROJECT_GROUP_E_1_ADMIN_H

#include<fstream>
#include <iostream>
#include<string>
#include<stdio.h>
#include<iomanip>
#include<Windows.h>
using namespace std;
class Admin {
	string read_file;
	string password;

	void Read_Password_form_file() {
		ifstream f;
		f.open("Password.txt");
		while (!f.eof()) {
			getline(f, read_file);
		}
		f.close();
	}
	bool Admin_login() {
		cout << "Enter the password:";
		cin >> password;
		Read_Password_form_file();
		if (password.compare(read_file) == 0)
			return true;
		return false;
	}
	void Menu() {
		cout << "\t\t\t <<<<<<< WELCOME >>>>>>> \t\t\t\n";
		cout << "\t\t\t 1-Insertion \t\t\t\n";
		cout << "\t\t\t 2-Display location \t\t\t\t\n";
		cout << "\t\t\t 3-Display linked list \t\t\t\n";
		cout << "\t\t\t 4-Serach and del \t\t\t\n";
		cout << "\t\t\t 5-Updata file \t\t\t\n";
		cout << "\t\t\t 6-Display update linkes \t\t\t\n";
	}
	class Location {
		friend class Admin;
		Location* next;
		string Name, ngbr1, ngbr2, ngbr3;
		double dis1, dis2, dis3;
		int trf1, trf2, trf3;

	};
	Location* insert_newloc;
	Location* update_locations;

	void Insertion() {
		string Loc_name, n1, n2, n3;

		cin.ignore();
		cout << "Enter the new location name : ";
		getline(cin, Loc_name);


		cout << "Enter the Ngbr1 of " << " " << Loc_name << " : ";
		getline(cin, n1);
		cout << "Enter the Ngbr3 of " << " " << Loc_name << " : ";
		getline(cin, n2);
		cout << "Enter the Ngbr3 of " << " " << Loc_name << " : ";
		getline(cin, n3);
		ifstream fin;
		fin.open("Locations.txt");
		string store;
		bool isValid;
		while (getline(fin, store)) {
			if (store != n1 || store != n2 || store != n3)
				isValid = false;
		}

		double d1, d2, d3;
		cout << "Enter the distance of " << n1 << " from  " << Loc_name << " : ";
		cin >> d1;
		cout << "Enter the distance of " << n2 << " from  " << Loc_name << " : ";
		cin >> d2;
		cout << "Enter the distance of " << n3 << " from  " << Loc_name << " : ";
		cin >> d3;

		int t1, t2, t3;
		cout << "Enter the trfic condition at route " << " " << n1 << " : ";
		cin >> t1;
		cout << "Enter the trfic condition at route " << " " << n2 << " : ";
		cin >> t2;
		cout << "Enter the trfic condition at route " << " " << n3 << " : ";
		cin >> t3;
		if (t1 > 5 || t2 > 5 || t3 > 5) {
			cout << "Trafic condition are scaled out of 5\n";
			return;
		}

		_IN_it(Loc_name, n1, n2, n3, d1, d2, d3, t1, t2, t3);

	}
	void Read_locations_file() {
		ifstream fin;
		string print;
		fin.open("Locations.txt");
		while (!fin.eof()) {
			getline(fin, print);
			cout << print << endl;
		}
		fin.close();
	}
	void _IN_it(string n, string nbr1, string nbr2, string nbr3, double d1, double d2, double d3, int t1, int t2, int t3)
	{
		Location* itr = new Location;
		itr->Name = n;
		//Updata_locatio_txt(itr->Name);

		itr->ngbr1 = nbr1;
		itr->ngbr2 = nbr2;
		itr->ngbr3 = nbr3;

		itr->dis1 = d1;
		itr->dis2 = d2;
		itr->dis3 = d3;

		itr->trf1 = t1;
		itr->trf2 = t2;
		itr->trf3 = t3;
		itr->next = NULL;

		if (ISpresent(itr->ngbr1) && ISpresent(itr->ngbr2) && ISpresent(itr->ngbr3)) {
			ofstream fout1;
			fout1.open("Locations.txt", ios_base::app);//Adding new loc in our Locations.txt at the endfout1 << itr->Name << endl;
			cout << endl;
			fout1 << itr->Name << endl;
			fout1.close();





			fstream fout_1;
			fout_1.open(itr->ngbr1 + ".txt", ios_base::app);
			fout_1 << endl;
			fout_1 << itr->Name << "_" << itr->dis1 << "_" << itr->trf1 << endl;
			fout_1.close();



			fstream fout_2;
			fout_2.open(itr->ngbr2 + ".txt", ios_base::app);         fout_2 << endl;
			fout_2 << itr->Name << "_" << itr->dis2 << "_" << itr->trf2 << endl;
			fout_2.close();



			fstream fout_3;
			fout_3.open(itr->ngbr3 + ".txt", ios_base::app);
			fout_3 << endl;
			fout_3 << itr->Name << "_" << itr->dis3 << "_" << itr->trf3 << endl;
			fout_3.close();



			if (insert_newloc == NULL)
				insert_newloc = itr;

			else {
				Location* _trs_ = insert_newloc;
				while (_trs_->next != nullptr)
					_trs_ = _trs_->next;
				_trs_->next = itr;
			}
			ofstream fout(itr->Name + ".txt"); // new txt of new location
			fout << itr->ngbr1 << "_" << itr->dis1 << "_" << itr->trf1 << endl;
			fout << itr->ngbr2 << "_" << itr->dis2 << "_" << itr->trf2 << endl;
			fout << itr->ngbr3 << "_" << itr->dis3 << "_" << itr->trf3 << endl;
			fout.close();
			//fstream fout1;
		}

	}

	void Diplay_location_linked_list() {


		if (insert_newloc != nullptr) {
			Location* i = insert_newloc;
			cout << "New Location inserted \n";
			cout << "             \n";
			cout << "             \n";

			while (i != nullptr) {
				cout << i->Name << endl;
				i = i->next;
			}
			cout << "             \n";
			cout << "             \n";
			cout << "Neighbours of new location\n";
			Location* j = insert_newloc;
			while (j != nullptr) {
				cout << j->ngbr1 << "_" << j->dis1 << "_" << j->trf1 << endl;
				cout << j->ngbr2 << "_" << j->dis2 << "_" << j->trf2 << endl;
				cout << j->ngbr3 << "_" << j->dis3 << "_" << j->trf3 << endl;
				j = j->next;
			}
		}
		else
			cout << "Empty\n";

	}
	void del_from_neighbour(string location) {

		string store_location_name = "";
		ifstream fin(location + ".txt");
		getline(fin, store_location_name);
		fin.close();
		string file_1 = "";
		for (int i = 0; i < store_location_name.find("_"); i++)
			file_1 += store_location_name[i];
		file_1 += ".txt";
		const char* U = file_1.c_str();
		ifstream fin_1;
		fin_1.open(U);
		string g;
		ofstream fout_1("Tem.txt");

		while (getline(fin_1, g))
		{

			if (g.find(location) != string::npos)
			{
			}
			else
				fout_1 << g << endl;

		}
		fin_1.close();
		fout_1.close();
		remove(file_1.c_str());
		rename("Tem.txt", file_1.c_str());

		// for second file
		int lengh_of_prevFile = store_location_name.length();
		string name_of_file_2;
		fstream  f(location + ".txt", ios::in || ios::out);
		f.seekg(lengh_of_prevFile + 2);
		getline(f, name_of_file_2);
		f.close();
		//cout << name_of_file_2 << endl;           name of second file

		string file_name_2 = "";
		for (int i = 0; i < name_of_file_2.find("_"); i++) {

			file_name_2 += name_of_file_2[i];

		}
		file_name_2 += ".txt";             //making it text file

		ofstream fout_second_temp("Temp2.txt");
		ifstream fin_read_from_sec_file;
		fin_read_from_sec_file.open(file_name_2.c_str());
		string read_in2;
		while (getline(fin_read_from_sec_file, read_in2))
		{
			if (read_in2.find(location) != string::npos) {}
			else
				fout_second_temp << read_in2 << endl;
		}
		fout_second_temp.close();
		fin_read_from_sec_file.close();

		remove(file_name_2.c_str());
		rename("Temp2.txt", file_name_2.c_str());







		// for file last file;

		fstream fal(location + ".txt");
		string name_of_third_file;
		ifstream fin__;
		fin__.open(location + ".txt");
		while (!fin__.eof()) {
			getline(fin__, name_of_third_file);
		}
		fin__.close();
		//int leght = name_of_file_2.length();
		//leght += lengh_of_prevFile;
		//fal.seekg( leght + 2);
		//fal >> name_of_third_file;

		cout << name_of_third_file << endl;
		string file_get_name_3 = "";
		for (int i = 0; i < name_of_third_file.find("_"); i++)
			file_get_name_3 += name_of_third_file[i];
		file_get_name_3 += ".txt";

		ofstream fout_3("Temp3.txt");
		ifstream  read_file_3;
		read_file_3.open(file_get_name_3.c_str());
		string thid_data;
		while (getline(read_file_3, thid_data)) {
			if (thid_data.find(location) != string::npos) {}
			else
				fout_3 << thid_data << endl;
		}
		fout_3.close();
		read_file_3.close();
		remove(file_get_name_3.c_str());
		rename("Temp3.txt", file_get_name_3.c_str());
	}
	void Del_location_and_text_file(string location_name) {

		ifstream fin;
		fin.open("Locations.txt");
		string str;
		ofstream fout("T.txt");
		while (getline(fin, str)) {
			if (location_name != str) {
				fout << str << endl;
			}
		}
		fin.close();
		fout.close();


		const char* jr = "Locations.txt";
		remove(jr);
		rename("T.txt", "Locations.txt");

		string _exe1_ = ".txt";
		string files = location_name + _exe1_;
		const char* del_tion = files.c_str();
		remove(del_tion);










		// also need to del there neigbores form their file


	}

	void Dltion_Class() {
		//called here for deletion
		string Name;
		cin.ignore();
		cout << "Enter the name of location to be deleted:";
		getline(cin, Name);
		if (ISpresent(Name))
		{

			del_from_neighbour(Name);
			Del_location_and_text_file(Name);
			//	Del_from_neigbore_also(Name);
				//cin.ignore();

		}
	}




	void Updata_locations(string Loc_name)
	{




		if (ISpresent(Loc_name)) {

			string  n1, n2, n3;

			// after update we also need to update our text files;


			cout << "Enter the Ngbr1 of " << " " << Loc_name << " : ";
			getline(cin, n1);
			cout << "Enter the Ngbr3 of " << " " << Loc_name << " : ";
			getline(cin, n2);
			cout << "Enter the Ngbr3 of " << " " << Loc_name << " : ";
			getline(cin, n3);

			double d1, d2, d3;
			cout << "Enter the distance of " << n1 << " from  " << Loc_name << " : ";
			cin >> d1;
			cout << "Enter the distance of " << n2 << " from  " << Loc_name << " : ";
			cin >> d2;
			cout << "Enter the distance of " << n3 << " from  " << Loc_name << " : ";
			cin >> d3;

			int t1, t2, t3;
			cout << "Enter the trfic condition at route " << " " << n1 << " : ";
			cin >> t1;
			cout << "Enter the trfic condition at route " << " " << n2 << " : ";
			cin >> t2;
			cout << "Enter the trfic condition at route " << " " << n3 << " : ";
			cin >> t3;


			fstream clr;
			clr.open(Loc_name + ".txt", ios::trunc);
			clr.close();

			Location* _edit_ = new Location;
			_edit_->ngbr1 = n1;
			_edit_->ngbr2 = n2;
			_edit_->ngbr3 = n3;
			_edit_->dis1 = d1;
			_edit_->dis2 = d2;
			_edit_->dis3 = d3;
			_edit_->trf1 = t1;
			_edit_->trf2 = t2;
			_edit_->trf3 = t3;
			_edit_->next = nullptr;
			if (update_locations == nullptr)
				update_locations = _edit_;
			else {
				Location* trvrs = update_locations;
				while (trvrs->next != nullptr) {
					trvrs = trvrs->next;
				}
				trvrs->next = _edit_;
			}
			// copying if found in temp file
			if (ISpresent(_edit_->ngbr1) && ISpresent(_edit_->ngbr2) && ISpresent(_edit_->ngbr3))
			{
				fstream f_edit;
				f_edit.open(Loc_name + ".txt", ios::out);
				f_edit << _edit_->ngbr1 << "_" << _edit_->dis1 << "_" << _edit_->trf1 << endl;
				f_edit << _edit_->ngbr2 << "_" << _edit_->dis2 << "_" << _edit_->trf2 << endl;
				f_edit << _edit_->ngbr3 << "_" << _edit_->dis3 << "_" << _edit_->trf3 << endl;
				f_edit.close();






				ofstream f_ngbr1("Temp1.txt");
				ofstream f_ngbr2("Temp2.txt");
				ofstream f_ngbr3("Temp3.txt");

				string str1, str2, str3;
				ifstream f1;
				f1.open(_edit_->ngbr1 + ".txt");             // loc
				while (getline(f1, str1)) {
					if (Loc_name != str1)
					{
						f_ngbr1 << str1 << endl;
					}
				}

				f1.close();
				f_ngbr1.close();


				fstream _append("Temp1.txt", ios_base::app);
				//_append << endl;
				_append << Loc_name << "_" << _edit_->dis1 << "_" << _edit_->trf1 << endl;
				_append.close();









				string exe = ".txt";
				string j = _edit_->ngbr1 + exe;
				const char* convrt = j.c_str();
				const char* t = j.c_str();
				remove(convrt);;
				rename("Temp1.txt", t);






				//string str_2;

				ifstream f2;
				f2.open(_edit_->ngbr2 + ".txt");
				while (getline(f2, str2)) {
					if (Loc_name != str2) {
						f_ngbr2 << str2 << endl;
					}
				}
				f2.close();
				f_ngbr2.close();


				fstream _append1("Temp2.txt", ios_base::app);
				_append1 << endl;
				_append1 << Loc_name << "_" << _edit_->dis2 << "_" << _edit_->trf2 << endl;
				_append1.close();


				//string exe = ".txt";
				string i = _edit_->ngbr2 + exe;
				const char* convrti = i.c_str();
				const char* y = i.c_str();
				remove(convrti);;
				rename("Temp2.txt", y);






				ifstream f3;
				f3.open(_edit_->ngbr3 + ".txt");
				//	string str3;
				while (getline(f3, str3)) {
					if (Loc_name != str3) {
						f_ngbr3 << str3 << endl;
					}
				}
				f3.close();
				f_ngbr3.close();



				fstream _append3("Temp3.txt", ios_base::app);
				_append3 << endl;
				_append3 << Loc_name << "_" << _edit_->dis3 << "_" << _edit_->trf3 << endl;
				_append3.close();


				//string exe = ".txt";
				string k = _edit_->ngbr3 + exe;
				const char* convrtio = k.c_str();
				const char* o = k.c_str();
				remove(convrtio);;
				rename("Temp3.txt", o);
			}

		}


	}

	void Update_linked_display()
	{
		if (update_locations != nullptr) {
			Location* i = update_locations;
			cout << "New Location inserted \n";
			cout << "             \n";
			cout << "             \n";

			while (i != nullptr) {
				cout << i->Name << endl;
				i = i->next;
			}
			cout << "             \n";
			cout << "             \n";
			cout << "Neighbours of new location\n";
			Location* j = update_locations;
			while (j != nullptr) {
				cout << j->ngbr1 << "_" << j->dis1 << "_" << j->trf1 << endl;
				cout << j->ngbr2 << "_" << j->dis2 << "_" << j->trf2 << endl;
				cout << j->ngbr3 << "_" << j->dis3 << "_" << j->trf3 << endl;
				j = j->next;
			}
		}
		else
			cout << "Empty\n";
	}
	bool ISpresent(string loc) {
		ifstream fin;
		fin.open("Locations.txt");
		string data;
		while (getline(fin, data))
		{
			if (data == loc) {
				cout << "present\n";
				return true;
			}
		}
		cout << "Not precent\n";
		return false;

	}
	void upgarade() {
		string loc;
		cin.ignore();
		cout << "Enter the location name:";
		getline(cin, loc);

		Updata_locations(loc);
	}


	void Del_Neighbours_aslo(string loc) {          //loc name    
		string str1_data;
		ifstream fin_opeN;
		fin_opeN.open(loc + ".txt");
		getline(fin_opeN, str1_data);         //get first neigbhour
		fin_opeN.close();

		ofstream fout("Temp.txt");
		ifstream fin_ngbr1;
		fin_ngbr1.open(str1_data + ".txt"); //open first neigbour .txt
		string data_;
		while (getline(fin_ngbr1, data_)) {
			if (loc != data_) {  // if loc is not eqaul data write it in tmep file;
				fout << data_ << endl;
			}
		}
		fout.close();
		fin_ngbr1.close();



		string r = str1_data + ".txt";
		const char* jr = r.c_str();
		const char* dle_it = r.c_str();
		remove(jr);
		rename("Temp.txt", dle_it);

		/*string _exe1_ = ".txt";
		string files = location_name + _exe1_;
		const char* del_tion = files.c_str();
		remove(del_tion);*/


	}





public:
	void Sel() {
		if (Admin_login()) {
			while (true) {
				int opt;
				Menu();
				cin >> opt;
				if (opt == 1) {
					Insertion();
				}
				else if (opt == 4) {

					Dltion_Class();
				}
				else if (opt == 2)
					Read_locations_file();
				else if (opt == 3)
					Diplay_location_linked_list();
				else if (opt == 5)
					upgarade();
				else if (opt == 6)
					Update_linked_display();

			}
		}
		else
			cout << "Error\n";
	}

	Admin() { update_locations = insert_newloc = NULL; }
	~Admin() {}
};




void Creation() {
	ofstream fout("Locations.txt");
	fout << "information technology university" << endl;
	fout << "ittefaq hospital" << endl;
	fout << "model town park" << endl;
	fout << "amanah mall" << endl;
	fout << "matro cash and carry" << endl;
	fout << "divisional public school" << endl;
	fout << "block a market" << endl;
	fout << "block b market" << endl;
	fout << "block c market" << endl;
	fout << "block d market" << endl;
	fout << "block e market" << endl;
	fout << "block f market" << endl;
	fout << "block g market" << endl;
	fout << "block h market" << endl;

}


#endif



















