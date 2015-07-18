#hashdic

##fast, small (200 LOC), C/C++, hash table based key/value dictionary, auto-grow, MurMur, linked list based buckets.

For my [jslike][1] library (JavaScript like convenient `var` in C++) I needed a dictionary solution to lookup keys inside objects.

[1]:https://github.com/exebook/jslike

The goal was to have a solution fast enough, (not more than 3 times slower than best industrial quality solutions), but with only a hundred lines of code so that any living person could comprehend the code entirely, thus making jslike an education-friendly project.

My first attempt was [trie4d][2], which was quite fast but, but then I decided to give a try to old good hash tables. I created this hash table, which is about the same speed but uses few times less memory.

Trie still has an advantage of that it does not need to resize, thus giving more leveled performance, and of course it allows to search by prefix (descend from current node). But huge advantage of this hash table is that it uses almost 4 times less memory than trie4d of some examples.

[2]:https://github.com/exebook/trie4d

Public domain MurMur hash function is used, but can be replaced with better hash function when/if one will be found one day on this planet.

I compared performance with v8 JavaScript objects, which are fastest I know (let me know if you know better key/value dictionary implementation), and hashdic is twice faster on insertion and 1.7 slower on lookup. (And probably 100 times less code). This comparison cannot be take seriously, but gives some approximation of the efficiency.

As for memory, on my test of 96680 english words from English dictionary, with 
average size of a key 10.169 and int64 value, the structure used  6,427,538 bytes.

It has few global variables to configure resize parameters, i.e. resize factor and resize threshold.

###Example usage (hello.cpp)

```cpp
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
```