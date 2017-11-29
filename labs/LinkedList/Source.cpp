#include <iostream>
#include "List.h"

using namespace std;

int main()
{
	List list;
	list.add(2.5);
	list.add(7.9);
	list.add(12.6);
	list.displayList();
	cout << '\n';
	list.remove(2.5);
	//list.remove(7.9);
	//list.remove(12.6);
	list.displayList();
	cout << endl;
	return 0;
}
