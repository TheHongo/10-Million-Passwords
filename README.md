04/22/2025 - Brody Michaels

DISCLAIMER: THIS PROJECT IS NOT A REAL OR VALID WAY TO CHECK IF YOUR PASSWORD IS SECURE OR NOT.

This project was created for the purpose of checking if your password is secure or not. It checks a database of 10 million
passwords and if your password is found then you will be given a rank of where that password places in the database listing. 
Ranks go from most common, 1, to least common, 10 million. Otherwise, if your password is not found you will be considered to 
have a secure password. 

The implementation uses a Trie and a Hash Table seperately. The Trie uses a node structure with vectors of characters while the 
hash table uses a array of doubly linked list chaining collision avoidence. 

To use:
Simply run, type your password into the bar, and hit enter or check! You will be provided with the passwords rank if found or a 
message stating it is a secure password. At the bottom left your 5 most recent password searches are shown. At the bottom right
the time taken to search for your password using the Trie and Hash table are shown in microseconds.

You are now ready to check your password! What are you waiting for? Get going!
