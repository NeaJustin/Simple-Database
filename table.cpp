#include "table.h"
using namespace std;
Form root("Root","root","root","root","root","root");
Table::Table(string table_name){
	this->table_name = table_name;  
       string tb_name = "";
	read.open(table_name.c_str());
	if(!read.is_open()){
		cout << "The table doesnt " << table_name << " doesnt exits" << endl;
		cout << "creating new table. " << endl;
		write.open(table_name.c_str());
		write.close();
		cout << "Table has been created, now you can add databases." << endl;	
		empty = true;
	}else{ 
		empty = false;
		cout << "The table " << table_name << " exits." << endl;
		while(getline(read,tb_name)){
		   //this will add the database name 
		   //and will create the database		
		   table.insert(make_pair(tb_name, new Database(tb_name,root)));		
		}	
	}
	init();
}
void Table::init(){
      string command = "";
      string db = ""; 
	if(empty){
	 cout << "At the Moment, there is no database, now you need to add. " << endl;
	 cout << "Enter to 'stop' to stop adding." << endl;
       while(db != "stop"){
         AddDatabase:
        cout <<  "Enter the name of the database : " << endl;
         cout << ">";
	 cin >> db;
  	  if(db != "stop")
	  table.insert(make_pair(db, new Database(db,root)));
	}
    
	}
       cout << "Now, you can add data to database ('stop' to terminate). " << endl;
	ls();
       cout << "THE SIZE " << table.size() << endl;
       while(command != "stop"){
          cout << ">";
	   cin >> command;
          if(command == "cd"){
 	       cout << "which database you want use ? " << endl;
	       cin >> command;
		table[command]->init();	
	}else if(command == "ls") ls();
	 else if(command == "adb") goto AddDatabase;
	else
		continue;	
	}
	synch(); 
      cout << "Good bye" << endl;	
}
void Table::synch(){
		write.open(table_name.c_str());
 map<string,Database*>::iterator it = table.begin();
   while(it != table.end()){
       write << it->first << endl;
	it++;
   }
  write.close();
}
void Table::ls(){
  map<string,Database *>::iterator it = table.begin();
  //print list 	
   cout << "------------ Databases ------------" << endl;
   while(it != table.end()){
       cout << it->first << endl;
	it++;
   }
   cout << "-----------------------------------" << endl;
}
int main(){
	Table test("db.txt");
}
