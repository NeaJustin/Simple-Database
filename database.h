#ifndef DATABASE_H
#define DATABASE_H
#include<fstream>
#include<map>
#include<vector>
#include "bintree.h"
enum UpdateFlag{name,age,dob,addr,occup,note};
class Database : public Bintree{
        public:
                Database(string table_name, Form _root);
                //this fuction will read all the data from the file
                //and will insert it to the binary search tree
                void init();
                void synch();
                void encode(string &form);
                void decode(string &form);
                string get_db_name(){return table_name;}
                Form make_form(string form);
        private:
           //     Form _root;
                ifstream read;
                ofstream write;
                string table_name;
                void help();
                void add();
		  void del();
	         void ser();
		  void upd();
		  void upd_(BinNode* &root,Form &data ,string update ,string flag);
                void h_synch(BinNode* &root, ofstream &write);
};

#endif
