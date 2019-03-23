#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

struct Node{
  Node *L, *R;
  char op;
  string value;
  Node(string v);
  Node(char op1, Node* L1, Node* R1);
  Node(istream& infile);
  string print();
  Node* deriv();
  
};

Node::Node(string v){                        // primitive constructor
  value = v;
  op = 'P';   // convention: 'P' in op denotes primitive formula.
  L = NULL;
  R = NULL;
}

Node::Node(char op1, Node* L1, Node* R1){  // recursive constructor
  value = "";
  op    = op1;
  L   = L1;
  R   = R1;
}

Node::Node(istream &infile){
  char c=infile.get();
  if(((c >= '0' && c <= '9') ||     // is it a primitive formula?
     (c >= 'a' && c <= 'z') ||
     (c >= 'A' && c <= 'Z'))&&
     (c!='c')&&(c!='s')){
    L=R=NULL; op='P'; value = c;
  }
  else if(c == '('){              // does it start a non-primitive formula?
    L = new Node(infile);            // recursively get the L formula
    op = infile.get(); 
    if((op == 'c')||(op == 's')) R=NULL;  
    else R = new Node(infile);
    if(infile.get() != ')') 
      cout << "No matching parenthesis.\n";
  }
  else cout << "Error in input.\n";
}

string Node::print(){
  if (op=='P') return value;
  string res,right_operand;
  if((op != 'c')&&(op != 's')) right_operand = (*R).print();
  else right_operand = "";
  res = '(' + (*L).print() + op + right_operand + ')';
  return res;
}

Node* Node::deriv(){
  Node *left,*right,*temp,*zero;
  switch(op){
    case 'P': if(value[0] >= '0' && value[0] <= '9') return new Node("0");
              else return new Node("1");

    case '+': return new Node('+',(*L).deriv(),(*R).deriv());

    case '*': left = new Node('*',(*L).deriv(),R);
              right = new Node('*',L,(*R).deriv());
              return new Node('+',left,right);

    case 'c': temp = new Node('s',L,NULL);
              right = new Node('*',temp,(*L).deriv());
              zero = new Node("0");
              return new Node('-',zero,right);
    case 's': left = new Node('c',L,NULL);
              return new Node('*',left,(*L).deriv());
    default: return NULL;
  }
}


int main(){
  Node z(cin);
  cout << z.print() << endl;
  cout << z.deriv()->print() << endl;
}
