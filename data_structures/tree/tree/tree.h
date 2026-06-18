#ifndef TREE_H
#define TREE_H

#include<stddef.h>
#include "../../../shared_structs/value/value.h"

#define MAX_TREE_DEPTH 1000

/* ---------- Definitions of structs ---------- */

typedef struct TreeNode TreeNode;

struct TreeNode {
    Value* val;
    TreeNode* left;
    TreeNode* right;
};

/* ---------- Construct and free methods ---------- */
TreeNode* constructTreeNode(Value* value);
TreeNode* constructTree(Value* value, TreeNode* left, TreeNode* right);
TreeNode* copyTreeNode(TreeNode* node);
TreeNode* copyTree(TreeNode* node);
TreeNode* emptyTree(void);
void freeTreeNode(TreeNode* node);
void freeTree(TreeNode* node);

/* ---------- Basic tree operations ---------- */
TreeNode* getLeaves(TreeNode* root);
int treeDepth(TreeNode* root);
int trimTree(TreeNode** root, size_t maxDepth);

/* ---------- Basic tree properties ---------- */
int isEmptyTree(TreeNode* root);
int isNonEmptyTree(TreeNode* root);
int isBST(TreeNode* root);
int isMinHeap(TreeNode* root);
int isMaxHeap(TreeNode* root);

/* ---------- Tree manipulation ---------- */
TreeNode* convertToBST(TreeNode* root);
TreeNode* convertToHeap(TreeNode* root);

#endif