# Trie_vs_BBST_vs_HashMap_StringSearch_DataStructures_CPP
    COMPARISON:
    Data structures for string searching
Linked List 
vs. 
Balanced Binary Search Tree 
vs.
Trie
vs.
Hash Map

In this section different data structures will be discussed and the specifics/details of
their implementation.
1.1 Linear list
Taken from C++ standard library, this data structure is a simple linked list with
O (1) insertion time complexity, however O(n) traversal time.
1.2 Balanced Binary Search Tree
This data structure optimizes the search time by balancing the tree data structure it
uses for storing strings with time complexity of O (log n) for insertion/deletion/search.
1.3 Trie
Trie is an efficient information reTrieval data structure. Using Trie, search
complexities can be brought to optimal limit (key length). If we store keys in binary
search tree, a well-balanced BST will need time proportional to M * log N, where M is
maximum string length and N is number of keys in tree. Using Trie, we can search the
key in O(M) time. However, the penalty is on Trie storage requirements.
The trie in this project was implemented as simple as it is with only two functions
available: insert and search.
1.4 Hash map
A simple data structure that uses the principle of hashing to store strings. The
hash function implemented here is the same as in Rabin Karp algorithm. As for the
choice between linear probing and linked list hash map, I chose linked lists, for the sake
of efficiency. Complexity: O(n) for calculating hash, where n – size of the string) and
O(m) the average length of the linked lists in the hash map.
2. Methodology
2.1 Alphabet
For the size of the alphabet, I used 26. For this reason, I implemented the code to
convert all the characters in the text to lowercase and if the character is not a letter
then convert it to space.
2.2 Wordlist and Text
As for the wordlist, I downloaded it from the internet/GitHub (link in the references
below). The text is taken from one of the Harry Potter books.
2.3 Time measurements
For the dictionary creation, the time was measured overall, not each time refreshing
during the insertion, but rather total time taken for the whole process, which is
getline() function from wordlist and insertion.
As for the search, it was specifically measured with refreshments each time before
search and summing it up for each word with the total number of words 4152.
