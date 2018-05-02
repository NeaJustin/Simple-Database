#ifndef FORM_H
#define FORM_H
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

#endif
