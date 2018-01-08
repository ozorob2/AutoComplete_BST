# AutoComplete_BST

Note: to follow this tutorial you will need gcc to be downloaded on your machine
follow this tutorial to get it http://gcc.gnu.org/install/download.html

To run this code you will need to have all three file
in the same location then once you navigate to the folder containing the files
use gcc main.c bst.c -o AutoCompleteBST -Wall to compile them together
and finally run the program by typing ./AutoCompleteBST

After starting the program you will be need to give a file name some test files are given   
type the filename exactly as it is\
 
ex: fortune100.txt
    ** Starting Autocomplete **
    ** Ready **
 
Then there are some features that can be used seperately from the autosuggest
such as the stats feature which lets you know how the tree was built

  stats
  **Tree count:  1000
  **Tree Height: 22

also the add feature which allows you to add nodes to the tree and 
the find feature which lets you look up a node as well as it's weight ex:

  find WalMart
  **Not found...
  add 1000 WalMart
  **Added
  find WalMart
  WalMart: 1000

Finally the autoSuggest Feature where you type in the number of results you want to see and a substring of the word
you are looking for and it will suggest all nodes containing the substring ordered by weight of node ex:

 suggest 5 American
 ** [Sub-tree root:  (American Intl. Group,62402)]
 ** [Sub-tree count: 200]
 ** [Num matches:    12]
 American Intl. Group: 62402
 American Electric Power: 61257
 American Express: 22582
 American Standard: 7465
 American Family Ins. Grp.: 5109
