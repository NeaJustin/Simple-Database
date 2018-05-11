#ifndef BINTREE_H
#define BINTREE_H
#include "form.h"
#include "cout_operator.h"
#include<iostream>
class BinNode{	
	public:
	BinNode(Form &value);
	BinNode* right_child;
	BinNode* left_child;
	Form value;
	
};

class Bintree{
	public:
	Bintree(Form value);
	void add(Form value);
	Form search(Form value);
	void del(Form value);
	void print_preorder();
	unsigned int get_size(){ return size;}
	
	protected:
	void b_add(Form &value, BinNode* &node);
	void b_preorder(BinNode* &node);
	void b_leftsub(BinNode* &node, BinNode *&actual);
	Form b_search(Form &value, BinNode* &node);
	void b_del(Form &value,BinNode* &node);
	BinNode* root;
	unsigned int size;
};

#endif
