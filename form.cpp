/*
  Form Object
  written by Mohamed
*/
#include<iostream>
using namespace std;
class Form{
	public:
        Form();
	Form(string name, string age, string dob, string occup, string addr, string note);
	//getters
	string get_name(){return name;}
	string get_age(){return age;}
	string get_dob(){return dob;}
	string get_occup(){return occup;}
	string get_addr(){return addr;}
	string get_note(){return note;}
       	int get_key(){ return key;}
	 //setter
	void set_name(string name);
	void set_age(string age);
	void set_dob(string dob);
	void set_occup(string occup);
	void set_addr(string addr);
	void set_note(string note); 
	//formated
	string get_formated_string();
	//operator overloading
	bool operator >=(Form &temp); 
	bool operator ==(Form &temp);
	bool operator <(Form &temp);
	private:
	string name, dob, occup, addr, note, age;
        int key;
};
Form::Form(){
	//default constructor
	key = 0;
}
Form::Form(string name, string age, string dob, string occup, string addr, string note){
	this->name = name;
	this->age = age;
	this->dob = dob;
	this->occup = occup;
	this->addr = addr;
	this->note = note;
        key = 0;
	//generate a key
        for(int i = 0; i < name.size(); i++)
		key = key + (int) name[i];
//	cout << "The key is " << key << endl;
}
void Form::set_name(string name){
	this->name = name;
	//regenerate key
	key = 0;
	for(int i = 0; i < name.size(); i++) 
		key = key + (int) name[i];
}
void Form::set_age(string age){
	this->age = age;
}
void Form::set_dob(string dob){
	this->dob = dob;
} 
void Form::set_occup(string occup){
	this->occup = occup;
}
void Form::set_addr(string addr){
	this->addr = addr;
}
void Form::set_note(string note){
	this->note = note;
}
string Form::get_formated_string(){
	return name +"_" + age + "_" + dob + "_" + occup + "_" + addr + "_" + note;
}
bool Form::operator >=(Form &temp){
	if(key >= temp.get_key()) return true;
	return false;
}
bool Form::operator == (Form &temp){
	if(key == temp.get_key()) return true;
	return false;
}
bool Form::operator <(Form &temp){
	if(key < temp.get_key()) return true;
	return false;
}
// << overloading for the Form object
ostream &operator << (ostream &out, Form &data){
	out << "Name : " << data.get_name() << endl;
	out << "Age : " << data.get_age() << endl;
	out << "Date Of Birth : " << data.get_dob() << endl;
	out << "Occupation : " << data.get_occup() << endl;
	out << "Address : " << data.get_addr() << endl;
	out << "Note : " << data.get_note() << endl;
	out << "Key : " << data.get_key() << endl;
	return out;
}


