#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include "bintree.cpp"
using namespace std;
class Database : public Bintree{
	public:
		Database(string table_name, Form _root);
 	private:
		//this fuction will read all the data from the file
		//and will insert it to the binary search tree
		void init();
		void synch();
		void encode(string &form);
		void decode(string &form);
		string get_db_name(){return table_name;}
		Form make_form(string form);
		Form _root;
		ifstream read;
		ofstream write;
		string table_name;
		void help();
		void add();
		void clr();
		void del();
  		void upd();
		void h_upd(BinNode* &root,Form data,int i,string value);
		void h_synch(BinNode* &root, ofstream &write);
};
Database::Database(string table_name, Form _root): Bintree(_root){
	  
	this->table_name = table_name;
	string temp = "";
	read.open(table_name.c_str());
	if(!read.is_open()){
		cout << "The table " << table_name << " doesn't exists." << endl;
		cout << "creating new table. " << endl;
		write.open(table_name.c_str());
		write.close();
		cout << "Table has been created, now you can start adding the data." << endl; 	
	}else{
		cout << "The table " << table_name << " exists. " << endl;
	     	while(getline(read,temp)){	
			decode(temp);
		        Form row = make_form(temp);
		        Bintree::add(row);
		}
		read.close();
	}
	init();
}
void Database::init(){
	cout << "---------------------------------------------------------" << endl;
	cout << "|                   Database is ready                   |" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "Need help? --> type 'help'." << endl;
        string command = "";
	while(command != "stp"){
	  cout << ">";
	  cin >> command;
	  if(command == "help") help();
          else if(command == "add") add(); 
	  else if(command == "lst") Bintree::print_preorder();
	  else if(command == "clr") clr(); 
 	  else if(command == "del") del();
	  else if(command == "upd") upd();
	  else	
	  	continue;
	}
       synch();	
}
void Database::help(){
    cout << " -------------INSTRUCTIONS-----------" << endl;
    cout << "| - To add data        -> type 'add' | " << endl;
    cout << "| - To delete data     -> type 'del' | " << endl;
    cout << "| - To update data     -> type 'upd' | " << endl;
    cout << "| - To list all data   -> type 'lst' | " << endl;
    cout << "| - To search for data -> type 'ser' | " << endl;
    cout << "| - To close database  -> type 'stp' | " << endl;
    cout << "| - To clear screen    -> type 'clr' | " << endl;
    cout << " ------------------------------------  " << endl; 	
}
void Database::add(){
    cout << "NOTE: For spaces use '-'." << endl;
    string cmd ="";
    Form data;
    cout << "Enter the name : ";
    cin >> cmd;
    data.set_name(cmd);
  //  cout << endl;
    cout << "Enter the age : " ;
    cin >> cmd;
    data.set_age(cmd);
  //  cout << endl;
    cout << "Enter the dob (mm/dd/yyyy) : ";
    cin >> cmd;
    data.set_dob(cmd);
   // cout << endl;
    cout << "Enter the occupation : ";
    cin >> cmd;
   // getline(cin,cmd);
    data.set_occup(cmd);
   // cout << endl;
    cout << "Enter the address : ";
    cin >> cmd;
   // getline(cin,cmd);
    data.set_addr(cmd);
   // cout << endl;
    cout << "Enter some notes : ";
    cin >> cmd;
   // getline(cin,cmd);
    data.set_note(cmd);
    Bintree::add(data);
}
void Database::synch(){
   write.open(table_name.c_str());
   h_synch(Bintree::root,write);
   write.close();
}
void Database::h_synch(BinNode* &root, ofstream &write){
     if(root == 0) return;
     string data = root->value.get_formated_string();
     encode(data);
     if(root->value.get_name() != "Root")
     	write << data << endl;
     h_synch(root->left_child,write);
     h_synch(root->right_child,write);
}
void Database::encode(string &form){
	int size = form.length() / 2;
	for(int i = 0; i < form.length(); i++){
		int a = (int) form[i];
		    a = a - size;
		form[i] = (char) a;				
	}	
}
void Database::clr(){
	//copied from stackover flow
        cout << "\033[2J\033[1;1H";
}
void Database::del(){
   string name = "";
   cout << "Enter the Name : ";
   cin >> name;
   Form d(name,"","","","","");
   Bintree::del(d);
}
void Database::decode(string &form){
	int size = form.length() / 2;
	for(int i = 0; i < form.length() ; i++){
		int a = (int) form[i];
		    a = a + size;
		form[i] = (char) a;
	}
}
void Database::upd(){
   string name;
  
   cout << "Enter the Name : " << endl;
   cin >> name;
   Form data(name,"","","","","");
   cout << "What you want to update, Name (nme) or Date of Birth (dob) or Age (age) or Address (add) or Occupation (occ) or Notes (not)." << endl;
   string upd_ = "";
   cin >> upd_;   
   if(upd_ == "nme"){
     cout << "Enter the Name : " ;
     cin >> upd_;
     h_upd(root,data,0,upd_); 
   }else if(upd_ == "dob"){
     cout << "Enter the Date of Birth (mm/dd/yyyy) : " ;
     cin >> upd_;
     h_upd(root,data,2,upd_);
   }else if(upd_ == "age"){
     cout << "Enter the Age : " ;
     cin >> upd_;
     h_upd(root,data,1,upd_);
   }else if(upd_ == "add"){
     cout << "Enter the Address : " ;
     cin >> upd_;
     h_upd(root,data,4,upd_);
   }else if(upd_ == "occ"){
     cout << "Enter the Occupation : " ;
     cin >> upd_;
     h_upd(root,data,5,upd_);
   }else if(upd_ == "not"){
     cout << "Enter the Notes : " ;
     cin >> upd_;
     h_upd(root,data,3,upd_);
   }else
	return;
}
void Database::h_upd(BinNode* &root,Form data,int i, string value){

	if(root == 0) return;
        if(data == root->value){
	    if(i == 0) root->value.set_name(value);
	    else if(i == 1) root->value.set_age(value);
	    else if(i == 2) root->value.set_dob(value);
	    else if(i == 3) root->value.set_note(value);
	    else if(i == 4) root->value.set_addr(value);
	    else if(i == 5) root->value.set_occup(value);
	    else
		return;
	    cout << "***UPDATED***" << endl;
    	    Form d = root->value;
  	    cout << d << endl;
	}else if(data >= root->value) 
		h_upd(root->right_child,data,i,value);
	else
		h_upd(root->left_child,data,i,value);
        
}
Form Database::make_form(string form){
     	int _count = 0;
	vector<string> f;
	string data = "";	
	for(int i = 0; i < form.size(); i++){
		if(form[i] == '_'){
			f.push_back(data);
			_count++;
			data = "";
		}else
			data = data + form[i];
	}
	//last one
		f.push_back(data);
        //now return form
	return Form(f[0],f[1],f[2],f[3],f[4],f[5]);
}
int main(){
	Form root("Root","root","root","root","root","root");
	Database d("tabel.txt",root);	
}
