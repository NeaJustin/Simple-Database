#ifndef TABLE_H
#define TABLE_H
#include<fstream>
#include<map>
#include "database.h"
//this class will contain multiple databse
class Table{
 	public:
		Table(string table_name);
	private:
		void init();
		void synch();
		void ls();
		string table_name;
		ifstream read;
		ofstream write;
		map<string,Database*> table;
		bool empty;
};
#endif