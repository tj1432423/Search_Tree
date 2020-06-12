
//#include "BST.h"
#include "AVL.h"

//using namespace std;
template<class TREE_TYPE>
void insertNodetest(TREE_TYPE &avl_tree){
    avl_tree.insert(5);avl_tree.print();
    avl_tree.insert(6);avl_tree.print();
    avl_tree.insert(7);avl_tree.print();
    avl_tree.insert(3);avl_tree.print();
    avl_tree.insert(4);avl_tree.print();
    avl_tree.insert(16);avl_tree.print();
    avl_tree.insert(5);avl_tree.print();
    avl_tree.insert(8);avl_tree.print();
    avl_tree.insert(3);avl_tree.print();
    avl_tree.insert(8);avl_tree.print();
    avl_tree.insert(9);avl_tree.print();
    avl_tree.insert(10);avl_tree.print();
    avl_tree.insert(11);avl_tree.print();
    avl_tree.insert(12);avl_tree.print();
}
template<class TREE_TYPE>
void delNodetest(TREE_TYPE &avl_tree){
    avl_tree.remove(6);avl_tree.print();
    avl_tree.remove(11);avl_tree.print();
    avl_tree.remove(12);avl_tree.print();
    avl_tree.remove(3);avl_tree.print();
    avl_tree.remove(3);avl_tree.print();
    avl_tree.remove(5);avl_tree.print();
    avl_tree.remove(9);avl_tree.print();
    avl_tree.remove(12);avl_tree.print();
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
    return 0;
}


