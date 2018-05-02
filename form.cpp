/*
  Form Object
  written by Mohamed
*/
#include "form.h"
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



