#include <iostream>
#include <cstring>

using namespace std;

class btn { // binary tree node class
public:
  int value;
  btn* left;
  btn* right;

  // constructor requires setting its value
  btn(int val) {
    value = val;
    left = nullptr;
    right = nullptr;
  }

  // destructor
  ~btn() {
    
  }

  // set left child
  void setLeft(btn* node) {
    left = node;
  }

  // set right child
  void setRight(btn* node) {
    right = node;
  }

  // get left
  btn* getLeft() {
    return left;
  }

  // get the right child
  btn* getRight() {
    return right;
  }

  // get the char value
  int getValue() {
    return value;
  }
};

void add(btn* &head, btn* current, btn* added);
void print(btn* current, int depth);
void search(btn* current, int val);
void delHead(btn* &head, btn* temp);

bool exists = false;
int main() {
  // instructions
  cout << "'ADD' to add a number" << endl;
  cout << "'DELETE' to delete a number" << endl;
  cout << "'SEARCH' to see if a number exists" << endl;
  cout << "'PRINT' to print the tree" << endl;
  cout << "'QUIT' to leave" << endl;
  
  btn* head = new btn(0);

  while (true) {
    char cmd[8];
    cin.getline(cmd, 8);
    
    if (strcmp(cmd, "ADD") == 0) { // add command
      int num;
      cout << "add num: ";
      cin >> num;
      btn* added = new btn(num);
      add(head, head, added);
    }
    else if (strcmp(cmd, "PRINT") == 0) {
      print(head, 0);
    }
    else if (strcmp(cmd, "SEARCH") == 0) {
      int num;
      cout << "which num: ";
      cin >> num;
      search(head, num);
      if (exists == true) {
	cout << "exists" << endl;
	exists = false;
      }
      else {
	cout << "doesn't exist" << endl;
      }
    }
    else if (strcmp(cmd, "DELETE") == 0) {
      int num;
      cout << "which num: ";
      cin >> num;
      
      if (head->getValue() == num) { // deleting the head. use next larger
	btn* temp = head->getRight();
        delHead(head, temp);
      }
    }
    else if (strcmp(cmd, "QUIT") == 0) {
      break;
    }
    cout << endl;
  }
  
  return 0;
}

void add(btn* &head, btn* current, btn* added) {
  if (head->getValue() == 0) { // empty
    head = added;
  }

  if (current->getValue() < added->getValue()) { // value is bigger so go right
    if (current->getRight() == nullptr) {
      current->setRight(added);
      return;
    }
    add(head, current->getRight(), added); // recurse right
  }
  
  if (current->getValue() > added->getValue()) { // value is less so go left
    if (current->getLeft() == nullptr) {
      current->setLeft(added);
      return;
    }
    //cout << "happen";
    add(head, current->getLeft(), added); // recurse left
  }
}

void print(btn* current, int depth) {
  if (current == nullptr) {
    return;
  }
  print(current->getRight(), depth + 1);
  for (int i = 0; i < depth; i++) {
    cout << "  ";
  }
  
  cout << current->getValue() << endl; // print the value
  print(current->getLeft(), depth + 1);
}

//bool exists = false;
void search(btn* current, int val) {
  if (current == nullptr) {
    return;
  }
  
  if (current->getValue() == val) {
    exists = true;
  }

  // go through the children
  if (current->getValue() < val) { // value is bigger so go right
    search(current->getRight(), val); // recurse right
  }

  if (current->getValue() > val) { // value is less so go left
    search(current->getLeft(), val); // recurse left
  }
}

void delHead(btn* &head, btn* temp) {
  //temp = head->getRight();
  while (temp->getLeft()->getLeft() != nullptr) {
    temp = temp->getLeft();
  }
  
  // setup new head
  btn* newHead = new btn(temp->getLeft()->getValue());
  newHead->setRight(head->getRight());
  newHead->setLeft(head->getLeft());

  // remove it from the tree by replacing its spot with its right
  btn* temp2 = temp->getLeft()->getRight();
  temp->getLeft()->~btn();
  temp->setLeft(temp2);

  head = newHead;
  //cout << "val" << temp->getValue();
}
