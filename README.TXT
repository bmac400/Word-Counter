Word Freak
Bryan McCafferyy
The program, wordfreak, takes files from four different ways and counts the total occurences of each individual word. It stores these
values in a hash table, which is an array of 26 binary search trees. One hash item and binary search tree for each letter. The hashing
algorythm is taking the ascii value of the first letter of the word, and subtracting 65 so a is 0, and z is 25. There is then an array of
hash items that points to a bstnode. Each node can have possibly two children, where the right node is greater than the parent node, and 
the left node is less than parent node. This allows for an inorder traversal of the tree, which is also alphabetical for each individual 
letter. All functions in relation to the BST use recursion if it needs to traverse the tree.



Video https://youtu.be/p0JrL6Cx10g
