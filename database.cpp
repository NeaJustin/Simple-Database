/*
  A simple database that is stores data
  in encrypted, this database is uses bintree
  to store data when programm is running.
  I did this, just for fun. :)
  Authour: Mohamed 
  Email: mohamedyousufmo@gmail.com
  
*/
#include "database.h"
#include "cout_operator.h"
using namespace std;
Database::Database(string table_name, Form _root): Bintree(_root){

        this->table_name = table_name;
        string temp = "";
        read.open(table_name.c_str());
        if(!read.is_open()){
                cout << "The database " << table_name << " doesn't exists." << endl;
                cout << "creating new database. " << endl;
                write.open(table_name.c_str());
                write.close();
                cout << "Database has been created, now you can start adding the data." << endl;
        }else{
                cout << "The Database " << table_name << " exists. " << endl;
                while(getline(read,temp)){
                        decode(temp);
                        Form row = make_form(temp);
                        Bintree::add(row);
                }
                read.close();
        }
        //init();
}
void Database::init(){
        cout << "---------------------------------------------------------" << endl;
        cout << "|                   Database is ready                   |" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "Need help? --> type 'help'." << endl;
        string command = "";
        while(command != "stp"){
          cout << "Database:"<<table_name << ">";
          cin >> command;
          if(command == "help") help();
          else if(command == "add") add();
          else if(command == "lst") Bintree::print_preorder();
          else if(command == "rcd") cout << "# records: " << Bintree::get_size() - 1 << endl;
  	   else if(command == "clr") cout << "\033[2J\033[1;1H" << endl;
	   else if(command == "ser") ser();
	   else if(command == "del") del();
	   else if(command == "upd") upd();
          else 
                if(command != "stp")
			cout << "Invalid Command, type 'help'." << endl;					
		  
        }
       cout << "Good Bye!" << endl;
       synch();
}
void Database::help(){
    cout << " ------------INSTRUCTIONS--------------" << endl;
    cout << "| - To add data          -> type 'add' | " << endl;
    cout << "| - To delete data       -> type 'del' | " << endl;
    cout << "| - To update data       -> type 'upd' | " << endl;
    cout << "| - To list all data     -> type 'lst' | " << endl;
    cout << "| - To search data       -> type 'ser' | " << endl;
    cout << "| - To see # of enteries -> type 'rcd' | " << endl;
    cout << "| - To clear screen      -> type 'clr' | " << endl;
    cout << "| - To close database    -> type 'stp' | " << endl;
    cout << " --------------------------------------  " << endl;
}
void Database::del(){
   string name = "";
   cout << "Enter the Name : ";
   cin >> name;
   string addr;
   cout << "Enter the address : ";
   cin >> addr;
   Form d(name,"","","",addr,"");
   Bintree::del(d);
}
void Database::upd(){
  string name,addr;
  cout << "Enter Name : ";
  cin >> name;
  cout << "Enter address: ";
  cin >> addr;
  Form data(name,"","","",addr,"");
  data = Bintree::search(data);
  if(data.get_name() != "NOT FOUND") {
         cout << "--------------------- RECORD ---------------------" << endl;
	  cout << data << endl;
	  cout << "--------------------------------------------------" << endl;
    }
  else{ 
	cout << "The name " << name << " is not found! " << endl; 
  	return;
  }
  cout << "What do you want to update (name,age,dob,addr,occup,note)." << endl;
  string update;
  cin >> update;
  cout << "Enter the data : " << endl;
  string data_;
  cin >> data_;
  upd_(Bintree::root, data, data_,update);
}
void Database::upd_(BinNode* &root, Form &data,string update ,string flag){
 if(data == root->value){
	if(flag == "name") root->value.set_name(update);	
  else if(flag == "age")root->value.set_age(update);
  else if(flag == "dob")root->value.set_dob(update);
  else if(flag == "addr")root->value.set_addr(update);
  else if(flag == "occup")root->value.set_occup(update);
  else if(flag == "note")root->value.set_note(update);
  else 
	cout << "Invalid command!" << endl;	
	}else if(data >= root->value){
		return  upd_(root->right_child,data,update ,flag);
	}else{
		return upd_(root->left_child,data,update ,flag);
	}

}
void Database::ser(){
  string name,addr;
  cout << "Enter the Name : ";
  cin >> name;
  cout << "Enter address: ";
  cin >> addr;
  Form data(name,"","","",addr,"");
  data = Bintree::search(data);
  if(data.get_name() != "NOT FOUND"){
         cout << "--------------------- RECORD ---------------------" << endl;
	  cout << data << endl;
	  cout << "--------------------------------------------------" << endl;
  
    }else 
	cout << "The name " << name << " is not found! " << endl; 
}
void Database::add(){
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
    data.set_occup(cmd);
   // cout << endl;
    cout << "Enter the address : ";
    cin >> cmd;
    data.set_addr(cmd);
   // cout << endl;
    cout << "Enter some notes : ";
    cin >> cmd;
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
        int size = table_name.length() / 2;
        for(int i = 0; i < form.length(); i++){
                int a = (int) form[i];
                    a = a - size;
                form[i] = (char) a;
        }
}
void Database::decode(string &form){
        int size = table_name.length() / 2;
        for(int i = 0; i < form.length() ; i++){
                int a = (int) form[i];
                    a = a + size;
                form[i] = (char) a;
        }
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
/*
int main(){
        Form root("Root","root","root","root","root","root");
        Database d("tabel.txt",root);
	 d.init();
}
*/
