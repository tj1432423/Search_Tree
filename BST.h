#ifndef BST_H
#define BST_H

#include<malloc.h>
#include<vector>
#include <iostream>

using namespace std;

template<class VALUE_TYPE>
class TNode{
public:
    TNode():height(1),left(nullptr),right(nullptr),parent(nullptr){}
    VALUE_TYPE value;
    int height;
    TNode* left;
    TNode* right;
    TNode* parent;
};

template<class VALUE_TYPE> class BST{
public:
    BST():node_num(0),root(nullptr){}

    TNode<VALUE_TYPE>* insert(VALUE_TYPE _value){
        cout<<"Try to insert "<<_value<<" !!!";
        TNode<VALUE_TYPE>* node=find(_value,root);
        if(node==nullptr){
            root=new TNode<VALUE_TYPE>();
            node_num++;
            root->value=_value;
            root->parent=root->left=root->right=nullptr;
            root->height=1;
            cout<<"The num of nodes is "<<node_num<<" !!!"<<endl;
            return root;
        }
        else if(node->value!=_value){
            //vector<TNode<VALUE_TYPE>*> g_p_v;
            if(node->value>_value){
                node->left=new TNode<VALUE_TYPE>();
                node_num++;
                node->left->value=_value;
                node->left->left=node->left->right=nullptr;
                node->left->parent=node;
                node->left->height=1;
                update_height_upper(node);
                cout<<"The num of nodes is "<<node_num<<" !!!"<<endl;
                return node->left;
            }else if(node->value<_value){
                node->right=new TNode<VALUE_TYPE>();
                node_num++;
                node->right->value=_value;
                node->right->left=node->right->right=nullptr;
                node->right->parent=node;
                node->right->height=1;
                update_height_upper(node);
                cout<<"The num of nodes is "<<node_num<<" !!!"<<endl;
                return node->right;
            }
        }
        cout<<"The num of nodes is unchanged : "<<node_num<<" !!!"<<endl;
        return node;
    }

    TNode<VALUE_TYPE>* remove(VALUE_TYPE _value){
        cout<<"Try to remove "<<_value<<" !!!";
        TNode<VALUE_TYPE>* node=find(_value,root);

        if(node && node->value==_value){
            if(!node->left || !node->right)
                return remove_node_if_has_1_child_or_not(node);
            else{
                return remove_node_if_has_2_child(node);
            }
        }
        cout<<"The num of nodes is "<<node_num<<" !!!"<<endl;
        return node;
    }

    TNode<VALUE_TYPE>* search(VALUE_TYPE _value){
        return find(_value,root);
    }

    void print(){
        inorder_traversal(root);
        cout<<endl;
    }

    int size(){return node_num;}

    int height(){return root->height;}

    ~BST(){empty();}

protected:
    void update_height_upper(TNode<VALUE_TYPE>* _node){
        while(_node){
            int tmp_height=_node->height;
            update_height(_node);
            if(tmp_height==_node->height) return; // The height of tree is unchanged, the update is finished.
            _node=_node->parent;
        }
    }

    void update_height(TNode<VALUE_TYPE>* _node){
        if(_node){
            if(!_node->left && !_node->right) _node->height=1;
            else if (!_node->left && _node->right) _node->height=_node->right->height+1;
            else if (_node->left && !_node->right) _node->height=_node->left->height+1;
            else _node->height=_node->left->height > _node->right->height ? (_node->left->height+1) : (_node->right->height+1);
        }
    }

    int balance(TNode<VALUE_TYPE>* _node){
        if(_node==nullptr) return 0;
        if(!_node->left && !_node->right) return 0;
        else if (!_node->left && _node->right) return -_node->right->height;
        else if (_node->left && !_node->right) return _node->left->height;
        else return _node->left->height-_node->right->height;
    }

    int node_num;

    TNode<VALUE_TYPE>* root;

private:

    TNode<VALUE_TYPE>* find(VALUE_TYPE _value,TNode<VALUE_TYPE>* _root){
        if(_root == nullptr)  return _root;
        if(_root->value > _value){
            if(_root->left) return find(_value,_root->left);
            else return _root;
        }
        else if(_root->value < _value){
            if(_root->right) return find(_value,_root->right);
            else return _root;
        }
        else return _root;
    }

    TNode<VALUE_TYPE>* remove_node_if_has_2_child(TNode<VALUE_TYPE>* _a){
        TNode<VALUE_TYPE>* after=getmin(_a->right);
        _a->value=after->value;
        //swap(a,after);
        return remove_node_if_has_1_child_or_not(after);
    }

    TNode<VALUE_TYPE>* remove_node_if_has_1_child_or_not(TNode<VALUE_TYPE>* _a){
        TNode<VALUE_TYPE>* res_parent;
        if(_a->parent==nullptr){
            if(!_a->left && !_a->right) root=nullptr;
            else if(_a->left){
                root=_a->left;
                _a->left->parent=nullptr;
            }else{
                root=_a->right;
                _a->right->parent=nullptr;
            }
            return nullptr;
        }else{
            if(_a->parent->left==_a){
                if(_a->left){
                    _a->parent->left=_a->left;
                    _a->left->parent=_a->parent;
                }else{
                    _a->parent->left=_a->right;
                    if(_a->right)
                        _a->right->parent=_a->parent;
                }
            }else{
                if(_a->left){
                    _a->parent->right=_a->left;
                    _a->left->parent=_a->parent;
                }else{
                    _a->parent->right=_a->right;
                    if(_a->right)
                        _a->right->parent=_a->parent;
                }
            }
            res_parent=_a->parent;
            update_height_upper(res_parent);

        }
        delete(_a);
        node_num--;
        cout<<"The num of nodes is "<<node_num<<" !!!"<<endl;
        return res_parent;
    }

    TNode<VALUE_TYPE>* getmin(TNode<VALUE_TYPE>* _a){
        if(_a && _a->left)
            return getmin(_a->left);
        else
            return _a;
    }

    void postorder_traversal (TNode<VALUE_TYPE>* _root){
        if(_root==nullptr) return;
        postorder_traversal(_root->left);
        postorder_traversal(_root->right);
        cout<<"The node "<<_root->value<<" has been removed !!!"<<endl;
        //free(_root);
        delete (_root);
        node_num--;
    }

    void inorder_traversal(TNode<VALUE_TYPE>* _root){
        if(_root==nullptr) return;
        inorder_traversal(_root->left);
        cout<<" -> "<<_root->value;
        inorder_traversal(_root->right);
    }

    void empty(){
        postorder_traversal(root);
        root=nullptr;
        cout<<"All of the nodes has been removed !!!"<<endl;
        cout<<"The num of nodes is "<<node_num<<" !!!"<<endl;
    }
};

#endif // BST_H
