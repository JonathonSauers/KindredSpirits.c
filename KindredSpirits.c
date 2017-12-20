// Jonathon Sauers
// jo046326
// COP 3502, Spring 2017
// KindredSpirits.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KindredSpirits.h"

// Counts the nodes of a given tree.
// Used for the array size of traversals.
int treeSize(node *a)
{
  if(a == NULL)
    return 0;

  return 1 + treeSize(a->left) + treeSize(a->right);
}

// Creates a new tree node.
// Based off create_node function given.
node *createNode(int data)
{
	node *n = malloc(sizeof(node));

	n->data = data;
	n->left = n->right = NULL;

	return n;
}

// The recursive part of preorderArray.
// Stores the traversal in array.
int *preorderArrayHelper(node *root, int *array)
{
  *array++ = root->data;

  if(root->left)
    array = preorderArrayHelper(root->left, array);
  if(root->right)
    array = preorderArrayHelper(root->right, array);

  return array;
}

// Finds the preorder traversal and returns it in the form of an array.
int *preorderArray(node *root, int size)
{
  // The array will be equal to the amount of nodes in a tree.
  // This is where the treeSize function helped.
  int *array = calloc(size, sizeof(int));

  if(root)
  {
    preorderArrayHelper(root, array);
    return array;
  }
  else
  {
    free(array);
    return NULL;
  }
}

// The recursive part of postorderArray.
// Stores the traversal in array.
int *postorderArrayHelper(node *root, int *array)
{
  if(root->left)
    array = postorderArrayHelper(root->left, array);
  if(root->right)
    array = postorderArrayHelper(root->right, array);

  *array++ = root->data;

  return array;
}

// Finds the postorder traversal and returns it in the form of an array.
int *postorderArray(node *root, int size)
{
  // The array will be equal to the amount of nodes in a tree.
  // This is where the treeSize function helped.
  int *array = calloc(size, sizeof(int));

  if(root)
  {
    postorderArrayHelper(root, array);
    return array;
  }
  else
  {
    free(array);
    return NULL;
  }
}

// Recursively checks if trees are reflections of one another.
// Returns 1 if they are the same, 0 otherwise.
int isReflection(node *a, node *b)
{
  int n = 0;

  // The empty trees are the same.
  if(a == NULL && b == NULL)
    return 1;

  // If one tree is empty but not the other, they are different.
  else if(a == NULL || b == NULL)
    return 0;

  // If the data at the nodes being compared is different, the trees differ.
  else if(a->data != b->data)
    return 0;

  // Must both return 1 in order to be reflections.
  n += isReflection(a->left, b->left);
  n += isReflection(a->right, b->right);

  return (n = 2) ? 1 : 0;
}

// Returns a pointer to a new reflected node.
// This is done recursively by swapping the right and left subtrees.
node *makeReflection(node *root)
{
  node *reflected;

  if(root == NULL)
     return NULL;

  else
  {
    reflected = createNode(0);
    reflected->data = root->data;
    reflected->left = makeReflection(root->right);
    reflected->right = makeReflection(root->left);

    return reflected;
  }
}

// Recursive function to help the kindredSpirits function.
// Returns 1 if they are Kindred Spirits, 0 otherwise.
int check_Kindred_Helper(node *a, node *b, int size)
{
  // Initialized to account for entrance into while loop.
  int i = -1;
  int *array1 = calloc(size, sizeof(int));
  int *array2 = calloc(size, sizeof(int));

  // Gets the traversals in the form of arrays.
  array1 = preorderArray(a, size);
  array2 = postorderArray(b, size);

  // Make sure to go all the way through the traversal arrays.
  while(size != 0)
  {
    size--;
    i++;

    if(array1[i] != array2[i])
    {
      free(array1);
      free(array2);
      return 0;
    }
  }
  free(array1);
  free(array2);
  return 1;
}

// Checks if the preorder of node A equals the postorder of node B.
// Returns 1 if they are Kindred Spirits, 0 otherwise.
int kindredSpirits(node *a, node *b)
{
  int n = 0, sizeA = 0, sizeB = 0;

  // Empty trees are Kindred Spirits.
  if(a == NULL && b == NULL)
    return 1;

  // If there is one node, checks if the values are the different
  // or the same. Returns 0 or 1, respectively.
  if(a->right == NULL && a->left == NULL && b->right == NULL && b->left == NULL)
    return (a->data != b->data) ? 0 : 1;

  // Gets the size of the trees. Used to set up the traversal array lengths
  sizeA = treeSize(a);
  sizeB = treeSize(b);

  // If the sizes are different, there is no way they can be Kindred Spirits.
  if(sizeA != sizeB)
    return 0;

  // Each individually will return 1 if a and b are Kindred Spirits.
  n += check_Kindred_Helper(a, b, sizeA);
  n += check_Kindred_Helper(b, a, sizeA);

  return (n > 0) ? 1 : 0;
}

// How difficult I found this assignment.
double difficultyRating(void)
{
  return 3.0;
}

// How long it took me to complete this assignment.
double hoursSpent(void)
{
  return 10.0;
}
