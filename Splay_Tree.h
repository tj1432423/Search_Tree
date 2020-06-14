#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include"BST.h"



template<class VALUE_TYPE>
class SPLAY_TREE : public BST<VALUE_TYPE>{
public:
    SPLAY_TREE(){
        BST<VALUE_TYPE>::root=nullptr;
        BST<VALUE_TYPE>::node_num=0;
    }

    void insert(VALUE_TYPE _value){
        TNode<VALUE_TYPE>* node=BST<VALUE_TYPE>::insert(_value);
        BST<VALUE_TYPE>::root=splay(node);
    }



    TNode<VALUE_TYPE>* search(VALUE_TYPE _value){
        TNode<VALUE_TYPE>* node=BST<VALUE_TYPE>::search(_value);
        BST<VALUE_TYPE>::root=splay(node);
        return BST<VALUE_TYPE>::root;
    }

    void remove(VALUE_TYPE _value){
        cout<<"Try to remove "<<_value<<" !!!";
        TNode<VALUE_TYPE>* node=search(_value);
        if(node && node->value==_value){
            if(node->right){
                TNode<VALUE_TYPE>* tmp=BST<VALUE_TYPE>::getmin(node->right);
                    node->value=tmp->value;
                    if(tmp->parent->left==tmp){
                        tmp->parent->left=tmp->right;
                        if(tmp->right) tmp->right->parent=tmp->parent;
                    }
                    else{
                        tmp->parent->right=tmp->right;
                        if(tmp->right) tmp->right->parent=tmp->parent;
                    }
                    BST<VALUE_TYPE>::update_height_upper(tmp->parent);
                    free(tmp);
                    BST<VALUE_TYPE>::root=node;
//                }

            }
            else {
                if(node->left) node->left->parent=nullptr;
                BST<VALUE_TYPE>::root=node->left;
                free(node);
            }
            BST<VALUE_TYPE>::node_num--;
            cout<<"The num of nodes is "<<BST<VALUE_TYPE>::node_num<<" !!!"<<endl;
        }
        else {
            cout<<"The num of nodes is unchanged : "<<BST<VALUE_TYPE>::node_num<<" !!!"<<endl;
        }

    }

private:
    TNode<VALUE_TYPE>* splay(TNode<VALUE_TYPE>* _node){
        while(_node && _node->parent && _node->parent->parent){
            if(_node->parent->parent->left==_node->parent){
                if(_node->parent->left==_node){
                    zig(_node->parent);
                    _node=zig(_node);
                }
                else {
                    _node=zig(zag(_node));
                }
            }
            else {
                if(_node->parent->left==_node){
                    _node=zag(zig(_node));
                }
                else {
                    zag(_node->parent);
                    _node=zag(_node);
                }
            }
        }
        if(_node && _node->parent){
            if(_node->parent->left==_node) _node=zig(_node);
            else _node=zag(_node);
        }
        return _node;
    }

    TNode<VALUE_TYPE>* zig(TNode<VALUE_TYPE>* _node){
        if(_node==nullptr || _node->parent==nullptr) return _node;
        TNode<VALUE_TYPE>* old_parent=_node->parent->parent;
        int flag;
        if(old_parent==nullptr) flag=0;
        else if(old_parent->left==_node->parent) flag=1;
        else flag=2;
        _node->parent->left=_node->right;
        if(_node->right) _node->right->parent=_node->parent;
        _node->right=_node->parent;
        _node->parent->parent=_node;
        _node->parent=old_parent;
        if(flag==1) old_parent->left=_node;
        else if(flag==2) old_parent->right=_node;
        BST<VALUE_TYPE>::update_height(_node->right);
        BST<VALUE_TYPE>::update_height_upper(_node);
        return _node;
    }

    TNode<VALUE_TYPE>* zag(TNode<VALUE_TYPE>* _node){
        if(_node==nullptr || _node->parent==nullptr) return _node;
        TNode<VALUE_TYPE>* old_parent=_node->parent->parent;
        int flag;
        if(old_parent==nullptr) flag=0;
        else if(old_parent->left==_node->parent) flag=1;
        else flag=2;
        _node->parent->right=_node->left;
        if(_node->left) _node->left->parent=_node->parent;
        _node->left=_node->parent;
        _node->parent->parent=_node;
        _node->parent=old_parent;
        if(flag==1) old_parent->left=_node;
        else if(flag==2) old_parent->right=_node;
        BST<VALUE_TYPE>::update_height(_node->left);
        BST<VALUE_TYPE>::update_height_upper(_node);
        return _node;
    }

};




#endif // SPLAY_TREE_H
