#include <iostream>
#include <list>
#include <unordered_map>

int main() {
	list <int> lst;
	lst.push_back(1);
	
	unordered_map <int, list <int>::iterator> umap;
	umap[1] = lst.begin();
	lst.push_back(2);
	umap[2] = lst.begin();
	lst.push_back(3);
	umap[3] = lst.begin();

	cout << umap[1] << endl << umap[2] << endl << umap[3] << endl;

	return 0;
}
