#ifndef AVL_H
#define AVL_H

#include"BST.h"


template<class VALUE_TYPE>
class AVLTree : public BST<VALUE_TYPE>{
public:
    AVLTree(){
        BST<VALUE_TYPE>::root=nullptr;
        BST<VALUE_TYPE>::node_num=0;
    }

    void insert(VALUE_TYPE _value){
        TNode<VALUE_TYPE>* node=BST<VALUE_TYPE>::insert(_value);
        vector<TNode<VALUE_TYPE>*> g_p_v=find_g_p_v_1(node);
        if(!g_p_v.empty()){   // if has unbananced node
            TNode<VALUE_TYPE>* old_parent=rotate_at(g_p_v[0],g_p_v[1],g_p_v[2]);
            if(old_parent)BST<VALUE_TYPE>::update_height_upper(old_parent);
        }
        if(!balance_check(BST<VALUE_TYPE>::root)) cout<<"Error!!! The Tree has not balanced !!!"<<endl;
    }

    void remove(VALUE_TYPE _value){
        TNode<VALUE_TYPE>* node=BST<VALUE_TYPE>::remove(_value);
        vector<TNode<VALUE_TYPE>*> g_p_v=find_g_p_v_2(node);
        if(!g_p_v.empty()){   // if has unbananced node
            TNode<VALUE_TYPE>* old_parent=rotate_at(g_p_v[0],g_p_v[1],g_p_v[2]);
            if(old_parent)BST<VALUE_TYPE>::update_height_upper(old_parent);
        }
        if(!balance_check(BST<VALUE_TYPE>::root)) cout<<"Error!!! The Tree has not balanced !!!"<<endl;
    }


private:

    TNode<VALUE_TYPE>* getmin(TNode<VALUE_TYPE>* _a){
        if(_a && _a->left)
            return getmin(_a->left);
        else
            return _a;
    }

    vector<TNode<VALUE_TYPE>*> find_g_p_v_1(TNode<VALUE_TYPE>* _node){
        TNode<VALUE_TYPE>* g=_node;
        while(g && (BST<VALUE_TYPE>::balance(g)!=-2 && BST<VALUE_TYPE>::balance(g)!=2)){
            g=g->parent;
        }
        if(!g) return {};
        TNode<VALUE_TYPE>* p=_node->value > g->value ? g->right : g->left;
        TNode<VALUE_TYPE>* v=_node->value > p->value ? p->right : p->left;
        return {g,p,v};
    }

    vector<TNode<VALUE_TYPE>*> find_g_p_v_2(TNode<VALUE_TYPE>* _node){
        TNode<VALUE_TYPE>* g=_node;
        TNode<VALUE_TYPE>* p;
        TNode<VALUE_TYPE>* v;
        while(g && (BST<VALUE_TYPE>::balance(g)!=-2 && BST<VALUE_TYPE>::balance(g)!=2)){
            g=g->parent;
        }
        if(!g) return {};
        if(BST<VALUE_TYPE>::balance(g)==2){
            p=g->left;
            if(BST<VALUE_TYPE>::balance(g->left)>=0) v=p->left;
            else v=p->right;
        }
        else{
            p=g->right;
            if(BST<VALUE_TYPE>::balance(g->right)<=0) v=p->right;
            else v=p->left;
        }
        return {g,p,v};
    }

    TNode<VALUE_TYPE>* rotate_at(TNode<VALUE_TYPE>* _g,TNode<VALUE_TYPE>* _p,TNode<VALUE_TYPE>* _v){
        TNode<VALUE_TYPE>* old_parent=_g->parent;
        int flag;
        if (old_parent==nullptr) flag=0;
        else if (old_parent->left==_g) flag=1;
        else flag=2;

        TNode<VALUE_TYPE>* a; TNode<VALUE_TYPE>* b; TNode<VALUE_TYPE>* c;
        TNode<VALUE_TYPE>* T0; TNode<VALUE_TYPE>* T1; TNode<VALUE_TYPE>* T2; TNode<VALUE_TYPE>* T3;
        if(_g->left==_p){
            if(_p->left==_v){   //left left
                a=_v; b=_p; c=_g;
                T0=a->left; T1=a->right; T2=b->right; T3=c->right;
            }
            else {   //left right
                a=_p; b=_v; c=_g;
                T0=a->left; T1=b->left; T2=b->right; T3=c->right;
            }
        }
        else {
            if(_p->left==_v){   //right left
                a=_g; b=_v; c=_p;
                T0=a->left; T1=b->left; T2=b->right; T3=c->right;
            }
            else {   //right right
                a=_g; b=_p; c=_v;
                T0=a->left; T1=b->left; T2=c->left; T3=c->right;
            }
        }
        TNode<VALUE_TYPE>* tmp=connect34(a,b,c,T0,T1,T2,T3);
        if(flag==0) {BST<VALUE_TYPE>::root=tmp;BST<VALUE_TYPE>::root->parent=nullptr;}
        else if(flag==1) {old_parent->left=tmp;tmp->parent=old_parent;}
        else {old_parent->right=tmp;tmp->parent=old_parent;}
        return old_parent;
    }

    TNode<VALUE_TYPE>* connect34(TNode<VALUE_TYPE>* _a,TNode<VALUE_TYPE>* _b,TNode<VALUE_TYPE>* _c,TNode<VALUE_TYPE>* _T0,TNode<VALUE_TYPE>* _T1,TNode<VALUE_TYPE>* _T2,TNode<VALUE_TYPE>* _T3){
        _a->left =_T0; if(_T0) _T0->parent=_a;
        _a->right=_T1; if(_T1) _T1->parent=_a; BST<VALUE_TYPE>::update_height(_a);
        _c->left =_T2; if(_T2) _T2->parent=_c;
        _c->right=_T3; if(_T3) _T3->parent=_c; BST<VALUE_TYPE>::update_height(_c);
        _b->left =_a; _a->parent=_b;
        _b->right=_c; _c->parent=_b; BST<VALUE_TYPE>::update_height(_b);
        return _b;
    }


    bool balance_check (TNode<VALUE_TYPE>* _root){
        if(_root==nullptr) return true;
        return balance_check(_root->left) && balance_check(_root->right) && BST<VALUE_TYPE>::balance(_root)>-2 && BST<VALUE_TYPE>::balance(_root)<2;
    }

};

#endif // AVL_H
