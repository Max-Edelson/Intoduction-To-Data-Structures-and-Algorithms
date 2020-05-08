#include <iostream>
#include <limits>
#include "BSTree.h"

using namespace std;

void printOrders(BSTree tree) {
  cout << "Preorder = ";
  tree.preOrder( );
  cout << endl << "Inorder = ";
  tree.inOrder( );
  cout << endl << "Postorder = ";
  tree.postOrder( );
  cout << endl << endl;
}

int menu() {
  int choice = 0;
  cout << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Smallest" << endl
    << "6. Largest" << endl
    << "7. Height" << endl
    << "8. Quit" << endl;
  cin >> choice;
  
  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice;
}

int main( ) {
    // Pass all your tests before running the executable main

    BSTree tree;

    int choice = menu();

    string entry;
  
    while (choice != 8) {
    
        if (choice == 1) {
          cout << "Enter string to insert: " << endl;
		getline(cin, entry);
		tree.print();
		tree.insert(entry);
		tree.print();
        } else if (choice == 2) {
          cout << "Enter string to remove: " << endl;
		getline(cin, entry);
		tree.print();
		tree.remove(entry);
		tree.print();
        } else if (choice == 3) {
		printOrders(tree);
        } else if (choice == 4) {
          cout << "Enter string to search for: ";
		getline(cin, entry);
		if (!tree.search(entry))
			cout << endl << "Not Found" << endl;
		else
			cout << endl << "Found" << endl;
        } else if (choice == 5) {
          cout << "Smallest: ";
		string smallest = tree.smallest();
		cout << smallest << endl;
        } else if (choice == 6) {
          cout << "Largest: ";
		string largest = tree.largest();
		cout << largest << endl;
        } else if (choice == 7) {
          cout << "Enter string: " << endl;;
		getline(cin, entry);
		int heightOfEntry = tree.height(entry);
		cout << "Height of subtree rooted at " << entry << ": " << heightOfEntry << endl<< endl;
        }
	else if (choice == '8')
		break;
        //fix buffer just in case non-numeric choice entered
        choice = menu();
    }
    return 0;
}


