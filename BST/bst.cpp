/*
As with the .h file, much of this code is directly taken from the class text book 3rd edition
*/

#include "bst.h"
#include <vector>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/**
* Constructor 
*/
BinarySearchTree::BinarySearchTree()
{
  root = NULL; // the only thing that needs to be set is this
}
/**
* Destructor for the tree
*/ 
BinarySearchTree::~BinarySearchTree()
{
  makeEmpty();
}

/**
* Internal method to make subtree empty.
*/
void BinarySearchTree::makeEmpty( BinaryNode * & t )
{
  if( t != NULL ) 
  {
    makeEmpty( t->left ); //recursive call to the left child
    makeEmpty( t->right ); //recursive call to the right child
    delete t; //free the memory
  }
  t = NULL;
}

//defining private functions first

/**
* Internal method to test if an item is in a subtree.
* x is the item to search for.
* t is the node that roots the subtree.
*/
bool BinarySearchTree::contains( const int & x, BinaryNode *t ) const
{
  if( t == NULL )
    return false;
  else if( x < t->element ) 
    return contains( x, t->left ); //continue searching tree
  else if( t->element < x )
    return contains( x, t->right ); //continue searching tree
  else
    return true; // match
}

// do we need to implement non private version for find min and find max?
BinarySearchTree::BinaryNode * BinarySearchTree::findMin( BinaryNode *t ) const
{
  if( t == NULL ) // if the tree is empty return nothing
    return NULL;
  if( t->left == NULL ) // if no node to left must be minimum root case
    return t;
  return findMin( t->left ); //uses recursion to find the min
}

BinarySearchTree::BinaryNode * BinarySearchTree::findMax( BinaryNode *t ) const
{
  if( t != NULL ) // make sure that the tree is not empty 
    while( t->right != NULL ) // keep going right until the right node is non existant
      t = t->right; // replace the previous node with one found
}

void BinarySearchTree::insert( const int & x, BinarySearchTree::BinaryNode * & t ) const
{
  if( t == NULL )
    t = new BinarySearchTree::BinaryNode( x, NULL, NULL ); // construct new node
  else if( x < t->element )
    insert( x, t->left ); //recursive call, node argument is left child 
  else if( t->element < x )
    insert( x, t->right ); //recursive call, node right is right child 
  else
    ; // duplicate, dont insert
}

BinarySearchTree::BinaryNode * findMin( BinarySearchTree::BinaryNode *t ) 
{
  if( t == NULL)
    return NULL;
  if( t->left == NULL)
    return t;
  return findMin( t->left );
}

void BinarySearchTree::remove( const int & x, BinarySearchTree::BinaryNode * & t ) const
{
  if( t == NULL )
    return; // Item not found, do nothing.
  if( x < t->element ) 
    remove( x, t->left ); // recursive call, left child 
  else if( t->element < x )
    remove( x, t->right ); // recursive call, right child
  else if( t->left != NULL && t->right != NULL) // two children
  {
    t->element = findMin( t->right )->element; // 
    remove( t->element, t->right );
  }
  else
  {
    BinarySearchTree::BinaryNode *oldNode = t; 
    t = ( t->left != NULL ) ? t->left : t->right;
    delete oldNode; // free the memory
  }
}

BinarySearchTree::BinaryNode * findMax( BinarySearchTree::BinaryNode *t) 
{
  if( t == NULL)
    while( t->right != NULL)
      t = t->right;
  return t;
}

//public member functions calling private recursive member functions

/** 
* Returns true if x is found in the tree.
*/
bool BinarySearchTree::contains( const int & x) const
{
  return contains( x, root );
}

/**
* Insert x into the tree; duplicates are ignored, named pinsert because I was having compile issues with two insert functions
*/
void BinarySearchTree::pinsert( const int & x )
{
  insert( x, root );
}

/**
* Remove x from the tree. Nothing is done if x is not found
*/
void BinarySearchTree::premove( const int & x)
{
  remove( x, root );
}

void BinarySearchTree::makeEmpty()
{
  makeEmpty( root ); 
}

/**
* Print the tree contents in sorted order.
*/
void BinarySearchTree::printTreeSorted( ostream & out = cout ) const
{
  if( root == NULL )
    out << "Empty tree" << endl;
  else
  {
    printSubTreeSorted( root, out);
    out << endl;
  }
}

/**
* Internal method to print a subtree rooted at t in sorted order.
*/
void BinarySearchTree::printSubTreeSorted( BinarySearchTree::BinaryNode *t, ostream & out ) const
{
  if( t != NULL )
  {
    printSubTreeSorted( t->left, out );
    out << t->element << ", ";
    printSubTreeSorted( t->right, out);
  }
}

void BinarySearchTree::printTreePreOrder( ostream & out = cout ) const
{
  if( root == NULL )
    out << "Empty tree" << endl;
  else
  {
    printSubTreePreOrder( root, out);
    out << endl;
  }
}

void BinarySearchTree::printSubTreePreOrder( BinarySearchTree::BinaryNode *t, ostream & out ) const
{
  if( t != NULL )
  {
    out << t->element << ", ";
    printSubTreePreOrder( t->left, out );
    printSubTreePreOrder( t->right, out);
  }
} 

void BinarySearchTree::printTreePostOrder( ostream & out = cout ) const
{
  if( root == NULL )
    out << "Empty tree" << endl;
  else
  {
    printSubTreePostOrder( root, out);
    out << endl;
  } 
}

void BinarySearchTree::printSubTreePostOrder( BinarySearchTree::BinaryNode *t, ostream & out ) const
{
  if( t != NULL )
  {
    printSubTreePostOrder( t->left, out );
    printSubTreePostOrder( t->right, out);
    out << t->element << ", ";
  }
}

// Handle the operations to show that the BST is working
int main(int argc, char *argv[])
{
  ifstream inputFile; // declare file stream 
  string line; // string variable to store each line from file
  inputFile.open(argv[1]);// open the file we want work with
  
  vector<int> values;
  if(inputFile.is_open())
  {
    while(getline(inputFile, line))
    {
      stringstream lineStream(line);
      int value;
      while(lineStream >> value)
      {
        values.push_back(value);
      }
    }
  }
  else
  {
    inputFile.close();
    cout << "unable to read input file" << endl;
  }

  BinarySearchTree tree;//create the tree we want to work with
  int end = values.size();

  //loop over values using insert on each value
  for(int index = 0; index < end; index++)
  {
    tree.pinsert(values[index]);
  }

  cout << "sorted order" << endl;
  tree.printTreeSorted();//print out the sorted tree
  cout << "post order" << endl;
  tree.printTreePostOrder();
  cout << "pre order" << endl;
  tree.printTreePreOrder();
}
