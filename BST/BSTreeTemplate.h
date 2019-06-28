  #include <iostream>
  #include <iomanip>
  #include <climits>
  #include <sstream>
  #include <cstring>

  using namespace std;

  #ifndef BSTREETEMPLATE_H
  #define BSTREETEMPLATE_H

  template <class TreeEntry>
          class BinarySearchTree {
                  public:
                          BinarySearchTree();
                          ~BinarySearchTree();
                          bool empty();
                          bool full();
                          void clear();
                          bool search(TreeEntry x);
                          void insert(TreeEntry x);
                          bool remove(TreeEntry x);
                          void print();
                          string toString();
                          int nodes();
                          int leaves();
                          int height();
                          TreeEntry minimum();
                          TreeEntry maximum();
                          TreeEntry secondMinimum();

                  private:
                          // definicao de estruturas
                          struct TreeNode;

                          typedef TreeNode * TreePointer;

                          struct TreeNode {
                                  TreeEntry entry;
                                  TreePointer leftNode, rightNode;
                          };

                          // campos
                          TreePointer root;

                          // metodos
                          void clear(TreePointer & t);
                          bool iSearch(TreeEntry x);
                          bool rSearch(TreeEntry x, TreePointer & t);
                          bool remove(TreeEntry x, TreePointer & p);
                          void delMin(TreePointer & q, TreePointer & r);
                          void preOrder(TreePointer & t);
                          void inOrder(TreePointer & t);
                          void postOrder(TreePointer & t);
                          void print(TreePointer & t, int s);
                          string toString(TreePointer & t);
                          int nodes(TreePointer & t);
                          int leaves(TreePointer & t);
                          int height(TreePointer & t);
          };

  //------------------------------------------------------------
  template <class TreeEntry>
          BinarySearchTree <TreeEntry>::BinarySearchTree() {
                  root = NULL;
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          BinarySearchTree <TreeEntry>::~BinarySearchTree() {
                  clear();
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          bool BinarySearchTree <TreeEntry>::empty() {
                  return (root == NULL);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          bool BinarySearchTree <TreeEntry>::full() {
                  return false;
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::clear() {
                  clear(root);
                  root = NULL;
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::clear(TreePointer & t) {
                  if (t != NULL) {
                          clear(t->leftNode);
                          clear(t->rightNode);
                          delete t;
                  }
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          bool BinarySearchTree <TreeEntry>::search(TreeEntry x) { // basta escolher uma unica implementacao do metodo de busca
                  // return iSearch(x);
                  return rSearch(x, root);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          bool BinarySearchTree <TreeEntry>::iSearch(TreeEntry x) {
                  TreePointer t = root;

                  while (t != NULL && t->entry != x)
                          if (x <t->entry)
                                  t = t->leftNode; // procurar subarvore esquerda
                          else
                                  t = t->rightNode; // procurar subarvore direita

                  return (t != NULL);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          bool BinarySearchTree <TreeEntry>::rSearch(TreeEntry x, TreePointer & t) {
                  if (t == NULL)
                          return false; // x nao encontrado

                  if (x <t->entry)
                          return rSearch(x, t->leftNode);
                  else
                  if (x> t->entry)
                          return rSearch(x, t->rightNode);
                  else // x == t->entry
                          return true;
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::insert(TreeEntry x) {
                  TreePointer p = NULL, q = root, r;

                  while (q != NULL) {
                          p = q;
                          if (x <q->entry)
                                  q = q->leftNode;
                          else
                                  q = q->rightNode;
                  }

                  r = new TreeNode;
                  r->entry = x;
                  r->leftNode = NULL;
                  r->rightNode = NULL;

                  if (p == NULL)
                          root = r; // arvore vazia
                  else
                  if (x <p->entry)
                          p->leftNode = r;
                  else
                          p->rightNode = r;
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          bool BinarySearchTree <TreeEntry>::remove(TreeEntry x) {
                  return remove(x, root);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          bool BinarySearchTree <TreeEntry>::remove(TreeEntry x, TreePointer & p) {
                  TreePointer q;

                  if (p == NULL)
                          return false; // elemento inexistente

                  if (x <p->entry)
                          return remove(x, p->leftNode);
                  else
                  if (x> p->entry)
                          return remove(x, p->rightNode);
                  else // remover p->
                  {
                          q = p;
                          if (q->rightNode == NULL)
                                  p = q->leftNode;
                          else
                          if (q->leftNode == NULL)
                                  p = q->rightNode;
                          else
                                  delMin(q, q->rightNode);
                          delete q;
                          return true;
                  }
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::delMin(TreePointer & q, TreePointer & r) {
                  if (r->leftNode != NULL)
                          delMin(q, r->leftNode);
                  else {
                          q->entry = r->entry;
                          q = r;
                          r = r->rightNode;
                  }
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::print(TreePointer & t, int s) {
                  int i;

                  if (t != NULL) {
                          print(t->rightNode, s + 3);
                          for (i = 1; i <= s; i++)
                                  cout <<" ";
                          cout <<setw(6) <<t->entry <<endl;
                          print(t->leftNode, s + 3);
                  }
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::print() {
                  print(root, 0);
                  cout <<endl <<"Pre-ordem" <<endl;
                  preOrder(root);
                  cout <<endl <<"Em-ordem" <<endl;
                  inOrder(root);
                  cout <<endl <<"Pos-ordem" <<endl;
                  postOrder(root);
                  cout <<endl;
          }

  //------------------------------------------------------------
  template <class TreeEntry>
          string BinarySearchTree <TreeEntry>::toString() {
                  return toString(root);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          string BinarySearchTree <TreeEntry>::toString(TreePointer & t) {
                  if (t != NULL)
                          return toString(t->leftNode) +
                                  static_cast <ostringstream *> ( & (ostringstream() <<t->entry))->str() + " " +
                                  toString(t->rightNode);
                  else
                          return ""; // subarvore vazia, nada a fazer
          }

  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::preOrder(TreePointer & t) {
                  if (t != NULL) {
                          cout <<t->entry <<",";
                          preOrder(t->leftNode);
                          preOrder(t->rightNode);
                  }
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::inOrder(TreePointer & t) {
                  if (t != NULL) {
                          inOrder(t->leftNode);
                          cout <<t->entry <<",";
                          inOrder(t->rightNode);
                  }
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          void BinarySearchTree <TreeEntry>::postOrder(TreePointer & t) {
                  if (t != NULL) {
                          postOrder(t->leftNode);
                          postOrder(t->rightNode);
                          cout <<t->entry <<",";
                  }
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          int BinarySearchTree <TreeEntry>::nodes() {
                  return nodes(root);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          int BinarySearchTree <TreeEntry>::nodes(TreePointer & t) {
                  if (t == NULL)
                          return 0;
                  else
                          return 1 + nodes(t->leftNode) + nodes(t->rightNode);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          int BinarySearchTree <TreeEntry>::leaves() {
                  return leaves(root);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          int BinarySearchTree <TreeEntry>::leaves(TreePointer & t) {
                  if (t == NULL)
                          return 0;
                  else
                  if (t->leftNode == NULL && t->rightNode == NULL)
                          return 1;
                  else
                          return leaves(t->leftNode) + leaves(t->rightNode);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          int BinarySearchTree <TreeEntry>::height() {
                  return height(root);
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          int BinarySearchTree <TreeEntry>::height(TreePointer & t) {
                  if (t == NULL)
                          return -1;
                  else {
                          int L, R;
                          L = height(t->leftNode);
                          R = height(t->rightNode);
                          if (L> R) return L + 1;
                          else return R + 1;
                  }
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          TreeEntry BinarySearchTree <TreeEntry>::minimum() {
                  TreePointer t = root;

                  if (t == NULL) {
                          cout <<"Arvore vazia" <<endl;
                          return INT_MIN;
                  }
                  while (t->leftNode != NULL)
                          t = t->leftNode; // procurar subarvore esquerda

                  return t->entry;
          }
  //------------------------------------------------------------
  template <class TreeEntry>
          TreeEntry BinarySearchTree <TreeEntry>::maximum() {
                  TreePointer t = root;

                  if (t == NULL) {
                          cout <<"Arvore vazia" <<endl;
                          return INT_MAX;
                  }
                  while (t->rightNode != NULL)
                          t = t->rightNode; // procurar subarvore direita

                  return t->entry;
          }
  //------------------------------------------------------------
  // pre: existir 2 ou mais elementos distintos na BST
  // pos: segundo menor valor da BST é retornado
  template <class TreeEntry>
          TreeEntry BinarySearchTree <TreeEntry>::secondMinimum() {

                  TreePointer t = root, ant_t = NULL;
                  int secondMinimum = INT_MIN;

                  // caso a raiz aponte para nulo, ou seja, a arvore estiver vazia...
                  if (t == NULL) {
                          cout <<"Arvore vazia" <<endl;
                          return secondMinimum;

                    // caso exista apenas um elemento na arvore...
                  } else if (t->leftNode == NULL && t->rightNode == NULL) {
                          cout <<"Arvore com um elemento" <<endl;
                          return secondMinimum;

                    // senão, caso exista 2 elementos ou mais na arvore...
                  } else {


                          /* --- Busca de candidatos --- */

                          // caso exista filho esquerdo, encontrar último elemento a esquerda
                          if (t->leftNode != NULL) {

                                  while (t->leftNode != NULL) {

                                          if (t == root) {
                                                  ant_t = root;
                                                  t = ant_t->leftNode;
                                          } else {
                                                  ant_t = ant_t->leftNode;
                                                  t = ant_t->leftNode;
                                          }

                                  }

                            // caso nao exista filho esquerdo, entao segundo menor valor estara a direita
                          } else {

                                  t = t->rightNode;

                                  // encontra segundo menor valor do lado direito da arvore.
                                  while (t->leftNode != NULL) {
                                          t = t->leftNode;

                                  }

                          }

                          /* --- Retorna segundo menor valor --- */
                          // se ha filho esquerdo da raiz
                          if (root->leftNode != NULL) {

                                  // se ultimo elemento à esquerda tiver descendente direito
                                  if (t->rightNode != NULL) {

                                          t = t->rightNode;

                                          while (t->leftNode != NULL) {
                                                  t = t->leftNode;

                                          }

                                          secondMinimum = t->entry;

                                    // se nao tiver, entao
                                  } else {
                                          secondMinimum = ant_t->entry;
                                  }

                            // se nao houver filho esquerdo da raiz, segundo menor valor estara a direita
                          } else {

                                  secondMinimum = t->entry;

                          }

                          return secondMinimum;

                  }

          }
  //------------------------------------------------------------

  # endif /* BSTREETEMPLATE_H */