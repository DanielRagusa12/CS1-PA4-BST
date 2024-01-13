/* COP 3502C Assignment 4 
This program is written by: Daniel Ragusa */

/*
This program will create a master binary search tree called the name tree
Each node in the name tree will hold a pointer to an item tree, which will also be a BST
This program will run many different functions on the master tree, and each nodes respective item trees
These functions will include inserting, deleting, summing, counting, and searching for nodes within all trees
Many functions will be almost exact copies, with one being used for name trees, and one for item trees
This program will take input from the in.txt file to create the trees
After building and printing the trees, the program will take queries from the in.txt file
These queries will call the respective functions named above, and the output will be printed to console as well as the out.txt output file.
This program will maintain the fundamental properties of a BST, while also performing all specified queries.

*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "leak_detector_c.h"



#define MAXLEN 31

FILE *outFile;






typedef struct itemNode 
{ 
  char name[MAXLEN]; 
  int count; 
  struct itemNode *left, *right; 
}itemNode; 
 
typedef struct treeNameNode 
{ 
  char treeName[MAXLEN]; 
  struct treeNameNode *left, *right; 
  itemNode *theTree; 
}treeNameNode;

treeNameNode* createTreeNameNode(char name[]);
treeNameNode* insertName(treeNameNode *root,treeNameNode *element);
void traverse_in_traverse(treeNameNode *root);
treeNameNode * searchNameNode(treeNameNode * root, char treeName[50]);



//my functions
void printTreeNames(treeNameNode *current_ptr);
void printItemNames(itemNode *current_ptr);
void free_memI(itemNode *root);





treeNameNode* createTreeNameNode(char name[])
{
  treeNameNode *temp=malloc(sizeof(treeNameNode));
  strcpy(temp->treeName,name);
  temp->left=NULL;
  temp->right=NULL;
  temp->theTree=NULL;

  return temp;
  
  
}

itemNode* createItemNode(char name[],int count)
{
  itemNode *temp=malloc(sizeof(itemNode));
  strcpy(temp->name,name);
  temp->left=NULL;
  temp->right=NULL;
  temp->count=count;

  return temp;
  
  
}

treeNameNode* insertName(treeNameNode *root,treeNameNode *element)
{
  if(root == NULL)
    return element;

  else
  {
    if(strcmp(root->treeName,element->treeName)<0)
    {
      if(root->right == NULL)
        root->right=element;
      else
        root->right = insertName(root->right, element);

    }
    else
    {
      if(root->left == NULL)
        root->left=element;
      else
        root->left  = insertName(root->left, element);
    }


    return root;


  }
  
  
  
}

itemNode* insertItem(itemNode *root,itemNode *element)
{
  if(root==NULL)
    return element;

  else
  {
    if(strcmp(root->name,element->name)<0)
    {
      if(root->right == NULL)
        root->right = element;
      else
        root->right = insertItem(root->right, element);

    }
    else
    {
      if(root->left == NULL)
        root->left = element;
      else
        root->left  = insertItem(root->left, element);
    }


    return root;


  }
  
  
  
  
}

treeNameNode* searchNameNode(treeNameNode *root, char treeName[])
{
  if(root==NULL)
    return NULL;
  
  if(strcmp(root->treeName,treeName)==0)
    return root;

  else if(strcmp(root->treeName,treeName)<0)
    return searchNameNode(root->right,treeName);
  else
    return searchNameNode(root->left,treeName);
  
  
}

itemNode* searchItemNode(itemNode *root, char itemName[])
{
  if(root==NULL)
    return NULL;
  
  if(strcmp(root->name,itemName)==0)
    return root;

  else if(strcmp(root->name,itemName)<0)
    return searchItemNode(root->right,itemName);
  else
    return searchItemNode(root->left,itemName);
  
  
}


int item_before(itemNode *root, char itemName[])
{
  
  if(root==NULL)
    return 0;

  else if (strcmp(root->name,itemName)<0) 
    {
        return 1 + item_before(root->left,itemName) + item_before(root->right,itemName);
    }
    else 
    {
        item_before(root->left,itemName);
    }
 
}

treeNameNode* buildNameTree(treeNameNode *root,int N,int I,FILE *infile)
{
  for(int i=0;i<N;i++)
    {
      char tempName[MAXLEN];
      fscanf(infile,"%s",tempName);
      treeNameNode *element=createTreeNameNode(tempName);
      root=insertName(root,element);
      
    }
  
  for(int i=0;i<I;i++)
    {
      char tempTreeName[MAXLEN];
      char tempItemName[MAXLEN];
      int tempCount;
      treeNameNode *found;

      
      fscanf(infile,"%s %s %d",tempTreeName,tempItemName,&tempCount);

      found=searchNameNode(root,tempTreeName);

      //printf("%s ",found->treeName);

      if(found!=NULL)
      {
        itemNode *element=createItemNode(tempItemName,tempCount);
        found->theTree=insertItem(found->theTree,element);
      }
      
      
      
      
      
    }

  return root;
  
}



void printTreeNames(treeNameNode *current_ptr)
{
  if(current_ptr != NULL)
  {
    printTreeNames(current_ptr->left);
    printf("%s ", current_ptr->treeName);
    fprintf(outFile,"%s ", current_ptr->treeName);
    printTreeNames(current_ptr->right);
  }
}

void printTreeNames2(treeNameNode *current_ptr)
{
  if(current_ptr != NULL)
  {
    printTreeNames2(current_ptr->left);
    printf("===%s===\n", current_ptr->treeName);
    fprintf(outFile,"===%s===\n", current_ptr->treeName);
    printItemNames(current_ptr->theTree);
    printf("\n");
    fprintf(outFile,"\n");
    printTreeNames2(current_ptr->right);
  }

  
  
  
}

int check_height(itemNode *root)
{
  if(root==NULL)
    return -1;

  int lheight=check_height(root->left);
  int rheight=check_height(root->right);

  if(lheight>rheight)
    return 1 + lheight;

  return 1 + rheight;
 

  
}

void height_balance (itemNode *root,int *lheight,int *rheight)
{
  
  *lheight=check_height(root->left);
  *rheight=check_height(root->right);
  
}


int count(itemNode *root)
{
  if(root==NULL)
    return 0;
  
  return root->count + count(root->left) + count(root->right);



}

int reduce(itemNode *root,int val)
{
  root->count=root->count-val;

  if(root->count<=0)
    return 0;

  else
    return 1;
  
  
  
}

treeNameNode* parentN(treeNameNode *root,treeNameNode *node) 
{

  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;

  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;

  // Look for node's parent in the left side of the tree.
  if (strcmp(root->treeName,node->treeName)>0)
    return parentN(root->left, node);

  // Look for node's parent in the right side of the tree.
  else
    return parentN(root->right, node);

  return NULL; // Catch any other extraneous cases.

}

itemNode* parentI(itemNode *root,itemNode *node) 
{

  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;

  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;

  // Look for node's parent in the left side of the tree.
  if (strcmp(root->name,node->name)>0)
    return parentI(root->left, node);

  // Look for node's parent in the right side of the tree.
  else
    return parentI(root->right, node);

  return NULL; // Catch any other extraneous cases.

}



int isLeafN(struct treeNameNode *node) 
{
  return (node->left == NULL && node->right == NULL);
}

int isLeafI(struct itemNode *node) 
{
  return (node->left == NULL && node->right == NULL);
}

// Returns 1 iff node has a left child and no right child.
int hasOnlyLeftChildN(treeNameNode *node) 
{
  return (node->left!= NULL && node->right == NULL);
}

int hasOnlyLeftChildI(itemNode *node) 
{
  return (node->left!= NULL && node->right == NULL);
}

// Returns 1 iff node has a right child and no left child.
int hasOnlyRightChildN(treeNameNode *node) 
{
  return (node->left== NULL && node->right != NULL);
}

int hasOnlyRightChildI(itemNode *node) 
{
  return (node->left== NULL && node->right != NULL);
}


treeNameNode *minValN(treeNameNode *root) 
{

  // Root stores the minimal value.
  if (root->left == NULL)
    return root;

  // The left subtree of the root stores the minimal value.
  else
    return minValN(root->left);
}

itemNode *minValI(itemNode *root) 
{

  // Root stores the minimal value.
  if (root->left == NULL)
    return root;

  // The left subtree of the root stores the minimal value.
  else
    return minValI(root->left);
}








treeNameNode *deleteN(treeNameNode *root,char name[]) 
{

  treeNameNode *delnode, *new_del_node, *save_node;
  treeNameNode *par;
  char save_name[MAXLEN];

  delnode = searchNameNode(root,name); // Get a pointer to the node to delete.
  
  free_memI(delnode->theTree);

  par = parentN(root, delnode); // Get the parent of this node.

  // Take care of the case where the node to delete is a leaf node.
  if (isLeafN(delnode)) 
  {// case 1

    // Deleting the only node in the tree.
    if (par == NULL) {
      free(root); // free the memory for the node.
      return NULL;
    }

    // Deletes the node if it's a left child.
    if (strcmp(par->treeName,name)>0) 
    {
      free(par->left); // Free the memory for the node.
      par->left = NULL;
    }

    // Deletes the node if it's a right child.
    else {
      free(par->right); // Free the memory for the node.
      par->right = NULL;
    }

    return root; // Return the root of the new tree.
  }

  // Take care of the case where the node to be deleted only has a left
  // child.
  if (hasOnlyLeftChildN(delnode)) 
  {

    // Deleting the root node of the tree.
    if (par == NULL) {
      save_node = delnode->left;
      free(delnode); // Free the node to delete.
      return save_node; // Return the new root node of the resulting tree.
    }

    // Deletes the node if it's a left child.
    if (strcmp(par->treeName,name)>0) 
    {
      save_node = par->left; // Save the node to delete.
      par->left = par->left->left; // Readjust the parent pointer.
      free(save_node); // Free the memory for the deleted node.
    }

    // Deletes the node if it's a right child.
    else 
    {
      save_node = par->right; // Save the node to delete.
      par->right = par->right->left; // Readjust the parent pointer.
      free(save_node); // Free the memory for the deleted node.
    }

    return root; // Return the root of the tree after the deletion.
  }

  // Takes care of the case where the deleted node only has a right child.
  if (hasOnlyRightChildN(delnode)) 
  {

    // Node to delete is the root node.
    if (par == NULL) {
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }

    // Delete's the node if it is a left child.
    if (strcmp(par->treeName,name)>0) 
    {
      save_node = par->left;
      par->left = par->left->right;
      free(save_node);
    }

    // Delete's the node if it is a right child.
    else {
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }
    return root;
  }
//if your code reaches hear it means delnode has two children
  // Find the new physical node to delete.
  new_del_node = minValN(delnode->right);
  printf("MIN VAL == %s\n",new_del_node->treeName);

  strcpy(save_name,new_del_node->treeName);
  delnode->theTree=new_del_node->theTree;

  deleteN(root, save_name);  // Now, delete the proper value.

  // Restore the data to the original node to be deleted.
  strcpy(delnode->treeName,save_name);

  return root;
}



itemNode *deleteI(itemNode *root,char name[]) 
{

  itemNode *delnode, *new_del_node, *save_node;
  itemNode *par;
  char save_name[MAXLEN];

  delnode = searchItemNode(root,name); // Get a pointer to the node to delete.

  par = parentI(root, delnode); // Get the parent of this node.

  // Take care of the case where the node to delete is a leaf node.
  if (isLeafI(delnode)) 
  {// case 1

    // Deleting the only node in the tree.
    if (par == NULL) {
      free(root); // free the memory for the node.
      return NULL;
    }

    // Deletes the node if it's a left child.
    if (strcmp(par->name,name)>0) 
    {
      free(par->left); // Free the memory for the node.
      par->left = NULL;
    }

    // Deletes the node if it's a right child.
    else {
      free(par->right); // Free the memory for the node.
      par->right = NULL;
    }

    return root; // Return the root of the new tree.
  }

  // Take care of the case where the node to be deleted only has a left
  // child.
  if (hasOnlyLeftChildI(delnode)) 
  {

    // Deleting the root node of the tree.
    if (par == NULL) {
      save_node = delnode->left;
      free(delnode); // Free the node to delete.
      return save_node; // Return the new root node of the resulting tree.
    }

    // Deletes the node if it's a left child.
    if (strcmp(par->name,name)>0) 
    {
      save_node = par->left; // Save the node to delete.
      par->left = par->left->left; // Readjust the parent pointer.
      free(save_node); // Free the memory for the deleted node.
    }

    // Deletes the node if it's a right child.
    else 
    {
      save_node = par->right; // Save the node to delete.
      par->right = par->right->left; // Readjust the parent pointer.
      free(save_node); // Free the memory for the deleted node.
    }

    return root; // Return the root of the tree after the deletion.
  }

  // Takes care of the case where the deleted node only has a right child.
  if (hasOnlyRightChildI(delnode)) 
  {

    // Node to delete is the root node.
    if (par == NULL) {
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }

    // Delete's the node if it is a left child.
    if (strcmp(par->name,name)>0) 
    {
      save_node = par->left;
      par->left = par->left->right;
      free(save_node);
    }

    // Delete's the node if it is a right child.
    else {
      save_node = par->right;
      par->right = par->right->right;
      free(save_node);
    }
    return root;
  }
//if your code reaches hear it means delnode has two children
  // Find the new physical node to delete.
  new_del_node = minValI(delnode->right);
  

  strcpy(save_name,new_del_node->name);
  delnode->count=new_del_node->count;

  deleteI(root, save_name);  // Now, delete the proper value.

  // Restore the data to the original node to be deleted.
  strcpy(delnode->name,save_name);

  return root;
}








void printItemNames(itemNode *current_ptr)
{
  if(current_ptr != NULL)
  {
    printItemNames(current_ptr->left);
    printf("%s ", current_ptr->name);
    fprintf(outFile,"%s ", current_ptr->name);
    printItemNames(current_ptr->right);
  }
  
}

void traverse_in_traverse(treeNameNode *root)
{
  printTreeNames(root);
  printf("\n");
  fprintf(outFile,"\n");

  printTreeNames2(root);

  
}


void free_memI(itemNode *root)
{
  if(root==NULL)
    return;

  free_memI(root->left);
  free_memI(root->right);

  free(root);
}


void free_memN(treeNameNode *root)
{
  if(root==NULL)
    return;
  free_memI(root->theTree);
  
  free_memN(root->left);
  free_memN(root->right);


  free(root);
}




int main(void) 
{
  atexit(report_mem_leak);
  
  //Read Data
  
  FILE *infile;
  infile=fopen("in.txt","r");
  
  outFile=fopen("out.txt","w");
  

  int N,I,Q; //N = num trees, I = num items, Q = num queries 
  fscanf(infile,"%d %d %d",&N,&I,&Q);
  
  treeNameNode *tree_root=NULL;

  tree_root=buildNameTree(tree_root,N,I,infile); //building entire tree
 
  traverse_in_traverse(tree_root); //printing entire tree

  
  char command[MAXLEN];

  for(int i=0;i<Q;i++)
    {
      fscanf(infile,"%s",command);
      
      if(strcmp(command,"search")==0)
      {
        char tempTreeName[MAXLEN];
        char tempItemName[MAXLEN];
        fscanf(infile,"%s %s",tempTreeName,tempItemName);

        treeNameNode *foundTree;
        itemNode *foundItem;

        foundTree=searchNameNode(tree_root,tempTreeName);
        if(foundTree==NULL)
        {
          printf("%s does not exist\n",tempTreeName);
          fprintf(outFile,"%s does not exist\n",tempTreeName);
          
        }
          
        else
        {
          foundItem=searchItemNode(foundTree->theTree,tempItemName);
          if(foundItem==NULL)
          {
            printf("%s not found in %s\n",tempItemName,tempTreeName);
            fprintf(outFile,"%s not found in %s\n",tempItemName,tempTreeName);
            
          }
            
          else
          {
            printf("%d %s found in %s\n",foundItem->count,foundItem->name,foundTree->treeName);
            fprintf(outFile,"%d %s found in %s\n",foundItem->count,foundItem->name,foundTree->treeName);
            
          }
            
        }

        
      }


      if(strcmp(command,"item_before")==0)
      {
        char tempTreeName[MAXLEN];
        char tempItemName[MAXLEN];
        fscanf(infile,"%s %s",tempTreeName,tempItemName);

        treeNameNode *foundTree;
        itemNode *foundItem;

        foundTree=searchNameNode(tree_root,tempTreeName);

        if(foundTree!=NULL)
        {
          foundItem=searchItemNode(foundTree->theTree,tempItemName);

          if(foundItem!=NULL)
          {
            int itemBeforeCount=item_before(foundTree->theTree,tempItemName);

            printf("item before %s: %d\n",foundItem->name,itemBeforeCount);
            fprintf(outFile,"item before %s: %d\n",foundItem->name,itemBeforeCount);
            
          }
          
        }

      }


      if(strcmp(command,"height_balance")==0)
      {
        char tempTreeName[MAXLEN];
        int lheight=0,rheight=0;

        fscanf(infile,"%s",tempTreeName);

        treeNameNode *foundTree=searchNameNode(tree_root,tempTreeName);
        

        if(foundTree!=NULL)
        {
          
          height_balance(foundTree->theTree,&lheight,&rheight);

          int diff=lheight-rheight;

          if(abs(diff)>1)
          {
            printf("%s: left height %d, right height %d, difference %d, not balanced\n",foundTree->treeName,lheight,rheight,abs(diff));
            fprintf(outFile,"%s: left height %d, right height %d, difference %d, not balanced\n",foundTree->treeName,lheight,rheight,abs(diff));
            
          }
            

          else
          {
            printf("%s: left height %d, right height %d, difference %d, balanced\n",foundTree->treeName,lheight,rheight,abs(diff));
            fprintf(outFile,"%s: left height %d, right height %d, difference %d, balanced\n",foundTree->treeName,lheight,rheight,abs(diff));
            
          }
            
            

          
        }

        
        
      }

      if(strcmp(command,"count")==0)
      {
        char tempTreeName[MAXLEN];
        fscanf(infile,"%s",tempTreeName);

        treeNameNode *foundTree=searchNameNode(tree_root,tempTreeName);

        if(foundTree!=NULL)
        {
          int result=count(foundTree->theTree);
          printf("%s count %d\n",foundTree->treeName,result);
          fprintf(outFile,"%s count %d\n",foundTree->treeName,result);
        }
        
      }

      if(strcmp(command,"delete")==0)
      {
        char tempTreeName[MAXLEN];
        char tempItemName[MAXLEN];
        fscanf(infile,"%s %s",tempTreeName,tempItemName);

        treeNameNode *foundTree;
        itemNode *foundItem;

        foundTree=searchNameNode(tree_root,tempTreeName);

        if(foundTree!=NULL)
        {
          foundItem=searchItemNode(foundTree->theTree,tempItemName);

          if(foundItem!=NULL)
          {
            foundTree->theTree=deleteI(foundTree->theTree,foundItem->name);

            printf("%s deleted from %s\n",tempItemName,foundTree->treeName);
            fprintf(outFile,"%s deleted from %s\n",tempItemName,foundTree->treeName);
            

            
          }
          
        }

        

        

        

        
      }

      if(strcmp(command,"delete_name")==0)
      {
        char tempTreeName[MAXLEN];
        fscanf(infile,"%s",tempTreeName);

        treeNameNode *foundTree;

        foundTree=searchNameNode(tree_root,tempTreeName);

        if(foundTree!=NULL)
        {
          tree_root=deleteN(tree_root,foundTree->treeName);
          printf("%s deleted\n",tempTreeName);
          fprintf(outFile,"%s deleted\n",tempTreeName);
          
          
        }

        
        
        
      }

      if(strcmp(command,"reduce")==0)
      {
        char tempTreeName[MAXLEN];
        char tempItemName[MAXLEN];
        int tempCount;
        fscanf(infile,"%s %s %d",tempTreeName,tempItemName,&tempCount);

        treeNameNode *foundTree;
        itemNode *foundItem;

        foundTree=searchNameNode(tree_root,tempTreeName);

        if(foundTree!=NULL)
        {
          foundItem=searchItemNode(foundTree->theTree,tempItemName);

          if(foundItem!=NULL)
          {
            int result=reduce(foundItem,tempCount);

            printf("%s reduced\n",foundItem->name);
            fprintf(outFile,"%s reduced\n",foundItem->name);

            if(result==0)
            {
              foundTree->theTree=deleteI(foundTree->theTree,foundItem->name);
              
            }

           
            
          }
          
        }
      }

      
      
    }


  free_memN(tree_root);




  


  

  


  
  

  return 0;
}