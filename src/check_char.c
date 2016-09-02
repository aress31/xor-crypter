#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool check_key(char* key, int key_length) {
	/** Check the key and return a boolean if the key is correct or not.
	Arguments:
	key 		-- the key
	key_length 	-- the key length
	Returns:
	A boolean
	*/
	int i = 0;
	char c;
  
  	while (i < key_length){
		c = key[i];
      
		if(!((c>=65 && c<=90)||(c>=97&&c<=122)||c==33 ||c==39||c==40
		    ||c==41||c==44||c==45||c== 46||c==58||c==59||c==63
		    ||c==95||c==123||c==125||(c>=48 && c<=57)))
			return false;

		else
		    i++;
	}
	return true;
}
