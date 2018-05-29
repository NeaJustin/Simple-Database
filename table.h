#ifndef TABLE_H
#define TABLE_H
#include<fstream>
#include<stdio.h>
#include<map>
#include<iomanip>
#include "database.h"
//this class will contain multiple databse
class Table{
 	public:
		Table(string table_name);
	private:
		void init();
		void synch();
		void ls();
		void del();
		void help();
		string table_name;
		ifstream read;
		ofstream write;
		map<string,Database*> table;
		bool empty;
	
};
		static  string USERNAME = "table";
		static  string PASSWORD = "database";
#endif
