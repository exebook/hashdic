#include "iostream"
#include "hash.h"

using namespace std;

/*
	enumeration callback
	make sure you set right type for value and user data.
*/
bool callback(void *key, int count, int *value, void *user) {
	cout << (char*)user << (char*) key << " = " << *value << endl;
	return true;
}


int main() {
	jshash<int> H; // specify your value type, (here int).
	
	H.add((void*)"hello", 5); 
	/*
		Keys are void* (any binary data).
		As you notice, there is no value parameter, you set it later.
	*/
	
	*H.result = 111; // set value of the most recent added/found pair
	
	if (H.add((void*)"hello", 5)) {
		cout << "key already exists, modifying" << endl;
		*H.result = 555;
	}
	
	H.add((void*)"world", 5);
	*H.result = 777;
	
	if (H.find((void*)"hello", 5))
		cout << "hello = " << *H.result << endl;
	else
		cout << "hello not found" << endl;
		
	if (H.find((void*)"there", 5))
		cout << "there = " << *H.result << endl;
	else
		cout << "there not found" << endl;
		
	if (H.find((void*)"world", 5)) {
		/*
			find and update the value.
		*/
		*H.result += 1;
	}
	
	/*
		just iterate over all entries.
		user data can be zero (here string).
	*/
	H.forEach(callback, (char*)"for each: ");
}
