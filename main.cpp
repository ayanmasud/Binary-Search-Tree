/*Binary Search Tree. Add, delete, search, and print to a binary tree
  Author: Ayan Masud
  Date: 3/14/25
 */
  
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>

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

// prototypes
void add(btn* &head, btn* current, btn* added);
void print(btn* current, int depth);
void search(btn* current, int val);
void delHead(btn* &head, btn* temp);
void del(btn* &head, btn* current, int val);

bool exists = false; // bool used over 2 functions to determine if the number is in the tree
int main() {
  // instructions
  cout << "'ADD' to add a number" << endl;
  cout << "'DELETE' to delete a number" << endl;
  cout << "'SEARCH' to see if a number exists" << endl;
  cout << "'PRINT' to print the tree" << endl;
  cout << "'QUIT' to leave" << endl;
  
  btn* head = new btn(0); // head of the tree
  
  while (true) {
    char cmd[8];
    cin.getline(cmd, 8);
    
    if (strcmp(cmd, "ADD") == 0) { // add command
      cout << "through file (f) or manually (m)? ";
      char fm[2];
      cin.getline(fm, 2);
      if (strcmp(fm, "m") == 0) { // manually add numbers to the tree
	int num;
	cout << "add num: ";
	cin >> num;
	btn* added = new btn(num);
	add(head, head, added);
      }
      else if (strcmp(fm, "f") == 0) { // add through file
	// prepare the tree using file
	ifstream file("nums.txt");
	if (file.is_open()) {
	  string line;
	  while (getline(file, line)) {
	    stringstream ss(line);
	    string word;
	    while (ss >> word) { // string stream helps with the splitting by spaces
	      int num = stoi(word); // convert the string to int
	      btn* added = new btn(num);
	      add(head, head, added);
	    }
	  }
	  file.close();
	} else { // files not there
	  cout << "Unable to open file";
	}
      }
    }
    else if (strcmp(cmd, "PRINT") == 0) { // print command
      print(head, 0);
    }
    else if (strcmp(cmd, "SEARCH") == 0) { // search command
      int num;
      cout << "which num: ";
      cin >> num;
      search(head, num);
      if (exists == true) { // tells you if it exists or not
	cout << "exists" << endl;
	exists = false;
      }
      else {
	cout << "doesn't exist" << endl;
      }
    }
    else if (strcmp(cmd, "DELETE") == 0) { // delete command
      int num;
      cout << "which num: ";
      cin >> num;
      
      if (head->getValue() == num) { // deleting the head. use next larger
	btn* temp = head->getRight();
        delHead(head, temp);
      }
      else { // deleting other than head
	del(head, head, num);
      }
    }
    else if (strcmp(cmd, "QUIT") == 0) { // quit command
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
  if (current == nullptr) { // stop
    return;
  }
  print(current->getRight(), depth + 1); // sideways tree so print rights
  for (int i = 0; i < depth; i++) { // add spaces based off the depth
    cout << "  ";
  }
  
  cout << current->getValue() << endl; // print the value
  print(current->getLeft(), depth + 1); // then print lefts
}

//bool exists = false;
void search(btn* current, int val) {
  if (current == nullptr) { // stop
    return;
  }
  
  if (current->getValue() == val) { // found the value
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

void del(btn* &head, btn* current, int val) { // uses a method similar to the search function
  if (current == nullptr) { // stop
    return;
  }
  
  if (current->getLeft()->getValue() == val && current->getLeft()->getLeft() == nullptr && current->getLeft()->getRight() == nullptr) { // left is the one to delete and it has no child
    current->getLeft()->~btn();
    current->setLeft(nullptr);
    return;
  }
  if (current->getRight()->getValue() == val && current->getRight()->getLeft() == nullptr && current->getRight()->getRight() == nullptr) { // right is the one to delete and it has no child
    current->getRight()->~btn();
    current->setRight(nullptr);
    return;
  }

  // only left child deletion with one child
  if (current->getLeft() != nullptr && current->getLeft()->getValue() == val) {
    btn* nodeToDelete = current->getLeft();
    if (nodeToDelete->getLeft() == nullptr && nodeToDelete->getRight() != nullptr) { // only has one right
      current->setLeft(nodeToDelete->getRight());
      delete nodeToDelete;
      return;
    }
    if (nodeToDelete->getLeft() != nullptr && nodeToDelete->getRight() == nullptr) { // only has one left
      current->setLeft(nodeToDelete->getLeft());
      delete nodeToDelete;
      return;
    }
  }

  // only right child deletion with one child
  if (current->getRight() != nullptr && current->getRight()->getValue() == val) {
    btn* nodeToDelete = current->getRight();
    if (nodeToDelete->getLeft() == nullptr && nodeToDelete->getRight() != nullptr) { // only has one right
      current->setRight(nodeToDelete->getRight());
      delete nodeToDelete;
      return;
    }
    if (nodeToDelete->getLeft() != nullptr && nodeToDelete->getRight() == nullptr) { // only has one left
      current->setRight(nodeToDelete->getLeft());
      delete nodeToDelete;
      return;
    }
  }
  
  if (current->getValue() == val) { // found!
    /*if (current->getLeft() != nullptr && current->getRight() == nullptr) { // 1 child left
      btn* temp = current->getLeft();
      current->value = current->getLeft()->getValue();
      current->setLeft(current->getLeft()->getRight());
      current->setRight(current->getLeft()->getLeft());
      temp->~btn();
      return;
    }
    if (current->getLeft() == nullptr && current->getRight() != nullptr) { // 1 child right
      btn* temp = current->getRight();
      current->value = current->getRight()->getValue();
      current->setRight(current->getRight()->getRight());
      current->setLeft(current->getRight()->getLeft());
      temp->~btn();
      return;
      }*/
    if (current->getLeft() != nullptr && current->getRight() != nullptr) { // 2 children
      btn* temp = current->getRight();
      
      if (current->getRight()->getLeft() == nullptr) { // right doesnt have a left
	btn* temp3 = current->getRight();
	current->value = current->getRight()->getValue();
	current->setRight(current->getRight()->getRight());
	temp3->~btn();
	return;
      }
      
      // similar to the deletion of head
      while (temp->getLeft()->getLeft() != nullptr) {
	temp = temp->getLeft();
      }
      
      // setup the replacer
      int newVal = temp->getLeft()->getValue();
      
      
      // remove it from the tree by replacing its spot with its right
      btn* temp2 = temp->getLeft()->getRight();
      temp->getLeft()->~btn();
      temp->setLeft(temp2);
      
      current->value = newVal;
      return;
    }
  }

  // go through the children
  if (current->getValue() < val) { // value is bigger so go right
    del(head, current->getRight(), val); // recurse right
  }

  if (current->getValue() > val) { // value is less so go left
    del(head, current->getLeft(), val); // recurse left
  }
}

void delHead(btn* &head, btn* temp) {
  if (temp->getLeft() == nullptr) { // right doesnt have a left
    btn* temp3 = head->getRight();
    head->value = head->getRight()->getValue();
    head->setRight(head->getRight()->getRight());
    temp3->~btn();
    return;
  }
  
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

  head = newHead; // set head as the new head
}
