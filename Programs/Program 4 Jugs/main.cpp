#include "Jug.h"
#include <iostream>

using namespace std;

int main() {

   string solution;
	Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
   if (head.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl << endl;

	Jug head1( 3, 5, 4, 1, 1, 1, 1, 1, 2);   
   if (head1.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl << endl;

}
