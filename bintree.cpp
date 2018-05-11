//written by Mohamed 
#include "bintree.h"
using namespace std;
BinNode::BinNode(Form &value){
	this->value = value;
	right_child = 0;
	left_child = 0;
}
Bintree::Bintree(Form value){
	root = new BinNode(value);
	size = 1;
}
void Bintree::add(Form value){
	b_add(value, root);
	size = size + 1;
}
void Bintree::b_add(Form &value, BinNode* &node){
        if(node == 0){
	//	cout << value << endl;	
		node = new BinNode(value);
	} 
	else if(value >= node->value){
	//	cout << "Above "<< node->value << endl;
		b_add(value, node->right_child);
	}else{
		b_add(value, node->left_child);
	}
}
Form Bintree::search(Form value){
	return b_search(value, root);
}
Form Bintree::b_search(Form &value, BinNode* &node){
	if(node == 0)  return Form("NOT FOUND","","","","","");
	if(value == node->value){
		return node->value;
	}else if(value >= node->value){
		return b_search(value, node->right_child);
	}else{
		return b_search(value, node->left_child);
	}
	
}
void Bintree::print_preorder(){
	b_preorder(root);
}
void Bintree::b_preorder(BinNode* &node){
	if(node == 0) return;
	 if(node->value.get_name() != "Root")
          cout << node->value << endl;
	b_preorder(node->left_child);
	b_preorder(node->right_child);
}
void Bintree::del(Form value){
      // BinNode* *temp = b_look(value,root,1);
	b_del(value,root);
}
//helper function for delete
void Bintree::b_leftsub(BinNode* &node, BinNode* &actual){
	if(node->right_child == 0 && node->left_child == 0){
		actual->value = node->value;
		node = 0;
	}else if(node->right_child == 0 && node->left_child != 0){
		actual->value = node->value;
		node = node->left_child;
	}else{
		b_leftsub(node->right_child, actual);
	}
}
void Bintree::b_del(Form &value,BinNode* &node){
      if(value == node->value){
		//if it has no child
		size--; 
		if(node->right_child == 0 && node->left_child == 0)
			node = 0;
		else if(node->right_child != 0 && node->left_child == 0){
			node = node->right_child;
		}else if(node->right_child == 0 && node->left_child != 0){
			node = node->left_child;
		}else{
			b_leftsub(node->left_child, node);
		}	
	}else if(value >= node->value) 
		b_del(value,node->right_child);
	else 
		b_del(value,node->left_child);	
}

/*
int main(){
  	Bintree test(56);
	test.add(86);
	test.add(75);
	test.add(72);
	test.add(76);
	test.add(77);
	test.add(78);
	test.add(98);
	test.add(97);
	test.add(110);
	test.add(77);
	test.print_preorder();
	cout << "The size of the tree " << test.get_size() << endl;
 	test.del(86);
	test.del(77);
	test.del(98);
	test.del(56);
	cout << endl;
	test.print_preorder();
	cout << "The size of the tree " << test.get_size() << endl;

	Form t1("Mohamed","144","03/4/1891","Trader","U.S","He's very calm");
	Form t2("Jack","124","03/4/1891","Trader","U.S","He's very calm");
        Form t3("Baskar","144","03/4/1891","Trader","U.S","He's very calm");
	Form t4("Jony","144","03/4/1891","Trader","U.S","He's very calm");
	Bintree test(t1);
	test.add(t2);
	test.add(t3);
	test.add(t4);
	test.print_preorder();
	  Form tw("Basr","1","0","Ter","","H");
	if(test.search(tw).get_name() != "NOT FOUND") cout << "Found " << endl;
	else
		cout << " It's not found " << endl;
	//	test.del(tw);
	test.print_preorder();

}
*/
