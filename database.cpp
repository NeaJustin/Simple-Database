/*
  A simple database that is stores data
  in encrypted, this database is uses bintree
  to store data when programm is running.
  I did this, just for fun. :)
  Authour: Mohamed 
  Email: mohamedyousufmo@gmail.com
  
*/
#include<fstream>
#include<map>
#include<vector>
#include "bintree.cpp"
using namespace std;
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
                Form _root;
                ifstream read;
                ofstream write;
                string table_name;
                void help();
                void add();
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
          else
                continue;
        }
       synch();
}
void Database::help(){
    cout << " ------------INSTRUCTIONS-----------" << endl;
    cout << "| - To add data       -> type 'add' | " << endl;
    cout << "| - To delete data    -> type 'del' | " << endl;
    cout << "| - To update data    -> type 'upd' | " << endl;
    cout << "| - To list all data  -> type 'lst' | " << endl;
    cout << "| - To close database -> type 'stp' | " << endl;
    cout << " -----------------------------------  " << endl;
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
        int size = form.length() / 2;
        for(int i = 0; i < form.length(); i++){
                int a = (int) form[i];
                    a = a - size;
                form[i] = (char) a;
        }
}
void Database::decode(string &form){
        int size = form.length() / 2;
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
int main(){
        Form root("Root","root","root","root","root","root");
        Database d("tabel.txt",root);
}