#include "cout_operator.h"
ostream& operator << (ostream &out, Form &data){
	out << "Name : " << data.get_name() << endl;
	out << "Age : " << data.get_age() << endl;
	out << "Date Of Birth : " << data.get_dob() << endl;
	out << "Occupation : " << data.get_occup() << endl;
	out << "Address : " << data.get_addr() << endl;
	out << "Note : " << data.get_note() << endl;
	out << "Key : " << data.get_key() << endl;
	return out;
}
