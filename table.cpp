#include "table.h"
using namespace std;
Form root("Root","root","root","root","root","root");
Table::Table(string table_name){
 
	this->table_name = table_name;  
        string tb_name = "";
	 string c , d= "";	
	bool done = false;       
	while(done != true){
       cout << " Authentication " << endl;
       cout << " Username : " ;
	cin >> c;
       cout << " Password : " ;
	cin >> d;
	if(USERNAME == c && PASSWORD == d) done = true;
	else 
		cout << "Wrong username or password." << endl; 	
	}
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
         // cout << "[Table]->";
	  cin >> db;
  	 
  	  if(db != "stop")
	  table.insert(make_pair(db, new Database(db,root)));
         }
       }
          cout << "Now, you can add data to database ('stop' to terminate). " << endl;
	  ls();
	   goBack:
          cout << "Number of databases : " << table.size() << endl;
         while(command != "stop"){
           cout << "[Table]>";
	   cin >> command;
          if(command == "cd"){
 	       cout << "which database you want use ? " << endl;
	       cin >> command;
   	       if(table.find(command) == table.end()) cout << "Invalid Database. " << endl;
 	       else
	       	table[command]->init();	
	}else if(command == "ls") ls();
	 else if(command == "adb"){ 
		goto AddDatabase;
			
	}
	 else if(command == "dlb") del();
	else if(command == "clr") cout << "\033[2J\033[1;1H" << endl;
	 else if(command == "help") help();
         else
		if(command != "stop") cout << "Invalid command, type 'help'. " << endl;	
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
void Table::help(){
 cout << "---------------- Instructions ----------------------" << endl;
 cout <<"|  - To list the table        -> type 'ls'           |" << endl;
 cout <<"|  - To switch to database    -> type 'cd'           |" << endl;
 cout <<"|  - To add new database      -> type 'adb'          |" << endl;
 cout <<"|  - To clear screen          -> type 'clr'          |" << endl;
 cout <<"|  - To delete a database     -> type 'dlb'          |" << endl;
 cout <<"|  - To terminate the databse -> type 'stop'         |" << endl;
 cout <<" ----------------------------------------------------" << endl;
}
void Table::del(){
  string db;
  cout << "Name of the database : ";
  cin >> db;
  if(remove(db.c_str()) != 0){cout << "Invalid database " << endl;}
  else
     table.erase(db);
}
void Table::ls(){
  map<string,Database *>::iterator it = table.begin();
   //print list 	
   cout << "------------ Databases ------------" << endl;
    while(it != table.end()){
        cout << it->first << " -- No of Records: " << it->second->get_size() - 1 <<endl;
	it++;
   }
   cout << "-----------------------------------" << endl;
}
int main(){
	Table test("db.txt");
}
