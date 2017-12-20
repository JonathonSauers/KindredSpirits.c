#ifndef __KINDREDSPIRITS_H
#define __KINDREDSPIRITS_H

typedef struct node
{
	// Each node holds a single integer.
	int data;

	// Pointers to the node's left and right children.
	struct node *left, *right;
} node;


// Functional Prototypes

int isReflection(node *a, node *b);

node *makeReflection(node *root);

int kindredSpirits(node *a, node *b);

double difficultyRating(void);

double hoursSpent(void);

#endif
