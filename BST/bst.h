#include <ostream>
#include <iostream>

/*
A lot of this code is directly taken from Data Structures and Algorithms in C++ by Mark Allen Weiss 3rd Edition
there is a section about how to implement a binary tree 
*/
class BinarySearchTree
{
  public: 
    // struct for the nodes that will be stored in the binary tree
    struct BinaryNode
    {
       // element that is stored in the node
       int element;
       
       // pointers to left and right child nodes
       BinaryNode *left;
       BinaryNode *right;
       
       //constructor but for a struct
       BinaryNode( const int & theElement, BinaryNode *lt, BinaryNode *rt)
          : element( theElement ), left( lt ), right( rt ) { }
    };

    // default constructor, constructor 
    BinarySearchTree();
    BinarySearchTree( const BinarySearchTree & rhs );
    // destructor
    ~BinarySearchTree();
 
    const int & findMin() const;
    const int & findMax() const;
    bool contains( const int & x ) const;
    void printTreeSorted( std::ostream & out ) const;
    void printTreePreOrder( std::ostream & out ) const;
    void printTreePostOrder( std::ostream & out ) const;

    void makeEmpty();
    void pinsert( const int & x );
    void premove( const int & x );

    const BinarySearchTree & operator=( const BinarySearchTree & rhs );

    BinaryNode *root;
  private:
    //pointer to root node of tree

    // private functions
    void insert( const int & x, BinaryNode * & t ) const; 
    void remove( const int & x, BinaryNode * & t ) const;
    BinaryNode * findMin( BinaryNode *t ) const;
    BinaryNode * findMax( BinaryNode *t ) const;
    bool contains( const int & x, BinaryNode *t ) const;
    void makeEmpty( BinaryNode * & t );
    BinaryNode * clone( BinaryNode *t ) const;
    void printSubTreeSorted( BinaryNode *t, std::ostream & out ) const;
    void printSubTreePreOrder( BinaryNode *t, std::ostream & out ) const;
    void printSubTreePostOrder( BinaryNode *t, std::ostream & out ) const;
};
