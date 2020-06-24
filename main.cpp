
//#include "BST.h"
#include "AVL.h"
#include "Splay_Tree.h"
#include "Red_Black_Tree.h"

//using namespace std;
template<class TREE_TYPE>
void insertNodetest(TREE_TYPE &_tree){
    _tree.insert(5);_tree.print();
    _tree.insert(6);_tree.print();
    _tree.insert(7);_tree.print();
    _tree.insert(3);_tree.print();
    _tree.insert(4);_tree.print();
    _tree.insert(16);_tree.print();
    _tree.insert(5);_tree.print();
    _tree.insert(8);_tree.print();
    _tree.insert(3);_tree.print();
    _tree.insert(8);_tree.print();
    _tree.insert(9);_tree.print();
    _tree.insert(10);_tree.print();
    _tree.insert(11);_tree.print();
    _tree.insert(12);_tree.print();
}

template<class TREE_TYPE>
void SearchNodetest(TREE_TYPE &_tree){
    _tree.search(6);
    _tree.search(7);
    _tree.search(11);
    _tree.search(15);
}

template<class TREE_TYPE>
void delNodetest(TREE_TYPE &_tree){
    _tree.remove(6);_tree.print();
    _tree.remove(11);_tree.print();
    _tree.remove(12);_tree.print();
    _tree.remove(3);_tree.print();
    _tree.remove(3);_tree.print();
    _tree.remove(5);_tree.print();
    _tree.remove(9);_tree.print();
    _tree.remove(12);_tree.print();
}

int main(){
    cout<<"-----------AVL Tree-------------"<<endl;
    AVLTree<float> avl_tree;
    insertNodetest<AVLTree<float>>(avl_tree); // 测试构建AVL树
    cout<<"size="<<avl_tree.size()<<"   "<<"height="<<avl_tree.height()<<endl;
    delNodetest<AVLTree<float>>(avl_tree);    // 测试删除AVL树节点

    cout<<"-----------BST Tree-------------"<<endl;
    BST<float> bst_tree;
    insertNodetest<BST<float>>(bst_tree); // 测试构建AVL树
    cout<<"size="<<bst_tree.size()<<"   "<<"height="<<bst_tree.height()<<endl;
    delNodetest<BST<float>>(bst_tree);    // 测试删除AVL树节点

    cout<<"-----------Splay Tree-------------"<<endl;

    SPLAY_TREE<float> splay_tree;
    insertNodetest<SPLAY_TREE<float>>(splay_tree); // 测试构建Splay树
    cout<<"size="<<splay_tree.size()<<"   "<<"height="<<splay_tree.height()<<endl;
    SearchNodetest<SPLAY_TREE<float>>(splay_tree); // 测试构建Splay树
    delNodetest<SPLAY_TREE<float>>(splay_tree);    // 测试删除Splay树节点

    cout<<"-----------Red Black Tree-------------"<<endl;

    RED_BLACK_TREE<int> rb_tree;
    insertNodetest<RED_BLACK_TREE<int>>(rb_tree); // 测试构建red_black树
    cout<<"size="<<rb_tree.size()<<"   "<<"height="<<rb_tree.height()<<endl;
    SearchNodetest<RED_BLACK_TREE<int>>(rb_tree); // 测试构建red_black树
    delNodetest<RED_BLACK_TREE<int>>(rb_tree);    // 测试删除red_black树节点

    return 0;
}


