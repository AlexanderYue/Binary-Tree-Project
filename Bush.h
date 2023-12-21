#pragma once
#include <iostream>
#include <fstream>
using namespace std;


struct BushNode{
    int key; 
    bool prefMin, prefMax = false;
    BushNode *parent, *left, *right;
    BushNode(int k, BushNode* up = nullptr, BushNode* r = nullptr, BushNode* l = nullptr) {
        key=k; parent=up; left=l; right=r; }
};

class Bush{
public:
    Bush();
    ~Bush();
    void InsertLeft(int value, int level);
    void InsertRight(int value, int level);
    void InsertRightEnd(int i, int value);
    void FindMinimum(ofstream &file);
    void FindMaximum(ofstream &file);
    BushNode* BuildTree(int** array, int size, int row, int col);
    void setRoot(int** array, int size, int row, int col);
    void printTreeInOrder();
private:
    BushNode* root;
    int FindMinimumT(BushNode* node);
    int FindMaximumT(BushNode* node);
    void printTreeInOrderT(BushNode* node);
    int min, max;
};

Bush::Bush(){
    root = nullptr;
    min = 0;
    max = 0;
      //new BushNode(value);
}

Bush::~Bush(){
    delete root->left;
    delete root->right;
    delete root;
}
void Bush::InsertRight(int value, int level){
      BushNode* current = root;
        while (current->right!=nullptr)
          {
        current = current->right;
          }
      root->right = new BushNode(value, root);
}
void Bush::InsertLeft(int value, int level){
      BushNode* current = root;
      while(current->left!=nullptr)
        {
          current = current->left;
        }
      root->left = new BushNode(value, root);
}
void Bush::setRoot(int** array, int size, int row, int col)
{
    root = BuildTree(array, size, 0, 0);
    cout<<root->key;
}
BushNode* Bush::BuildTree(int** array, int size, int row, int col) {
    if (row >= size) {
        return nullptr;
    }

    BushNode* newNode = new BushNode(array[row][col]);
    //fout << array[row][col] << " xd  ";
    newNode->left = BuildTree(array, size, row + 1, col);
    newNode->right = BuildTree(array, size, row + 1, col + 1);
    return newNode;
}
void Bush::printTreeInOrder() {
    printTreeInOrderT(root);
    std::cout << std::endl; // End the line after printing the tree
}

void Bush::printTreeInOrderT(BushNode* node) {
    if (node) {
        printTreeInOrderT(node->left);
        std::cout << node->key << " ";
        printTreeInOrderT(node->right);
    }
}
void Bush::FindMinimum(ofstream &fout) {
  min += FindMinimumT(root);
  BushNode* current = root;
  fout << min << endl;
  while(current->left!=nullptr && current->right!=nullptr)
    {
      fout<<current->key<< ", ";
      if (current->left->prefMin)
      {
        current = current->left;
      }
      else
      {
        current=current->right;
      }
    }
  fout<<current->key;
  fout<<endl;
}

int Bush::FindMinimumT(BushNode* node){
    if (node==nullptr)
    {
      return 9999;
    }
    if (node->left == nullptr && node->right == nullptr)
    {
      return node->key;
    }
      int leftMin = FindMinimumT(node->left);
      int rightMin = FindMinimumT(node->right);

      if (leftMin<=rightMin)
      {
        //fout<<"LEFT:" << node->key + leftMin << endl;
        //minList.Push(node->key);
        node->left->prefMin = true;
        node->right->prefMin = false;
        return node->key + leftMin;
      }
    //fout<<"RIGHT: "<< node->key + rightMin << endl;
    //minList.Push(node->key);
    node->left->prefMin = false;
    node->right->prefMin = true;
    return node->key + rightMin;
  }

void Bush::FindMaximum(ofstream &fout) {
    max += FindMaximumT(root);
 // End the line after printing the tree
    //maxList.print();
    BushNode* current = root;
    fout<<max<<endl;
    while(current->left!=nullptr && current->right!=nullptr)
      {
        fout<<current->key<< ", ";
        if (current->left->prefMax)
        {
          current = current->left;
        }
        else
        {
          current=current->right;
        }
      }
    fout<<current->key;
    fout<<endl;
}

int Bush::FindMaximumT(BushNode* node){
  /*if (node==nullptr)
  {
    return -9999;
  }*/
  if (node->left == nullptr && node->right == nullptr)
  {
    //maxList.Push(node->key);
    return node->key;
  }
    int leftMax = FindMaximumT(node->left);
    int rightMax = FindMaximumT(node->right);

  if (leftMax>=rightMax )
    {
      //fout<<"LEFT:" << node->key << endl;
      //maxList.Push(node->key);
      node->left->prefMax = true;
      node->right->prefMax = false;
      return node->key + leftMax;
    }
  //fout<<"RIGHT: "<< node->key << endl;
  //maxList.Push(node->key);
  node->right->prefMax = true;
  node->left->prefMax = false;
  return node->key + rightMax;
}
