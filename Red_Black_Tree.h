#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include"BST.h"


template<class VALUE_TYPE>
class RED_BLACK_TREE : public BST<VALUE_TYPE>{
public:
    RED_BLACK_TREE(){
        BST<VALUE_TYPE>::root=nullptr;
        BST<VALUE_TYPE>::node_num=0;
    }

    TNode<VALUE_TYPE>* insert(VALUE_TYPE _value){
        TNode<VALUE_TYPE>* node=BST<VALUE_TYPE>::insert(_value);
        if(node==BST<VALUE_TYPE>::root)  node->color=node->BLACK;
        else slove_double_red(node);
        return node;
    }

    TNode<VALUE_TYPE>* remove(VALUE_TYPE _value){
        cout<<"Try to remove "<<_value<<" !!!";
        TNode<VALUE_TYPE>* node=BST<VALUE_TYPE>::search(_value);
        if(node && node->value == _value){
            if(node->left && node->right){
                TNode<VALUE_TYPE>* tmp=BST<VALUE_TYPE>::getmin(node->right);
                node->value=tmp->value;
                node=tmp;
            }
            TNode<VALUE_TYPE>* child;
            if(node->left) child=node->left;
            else if(node->right) child=node->right;
            else child=nullptr;
            if(  is_black(node) && is_black(child) ) {
                BB(node);//Black and Black
            }
            else{
                RB(node,child);    //Red and Black
            }
            TNode<VALUE_TYPE>* res=node->parent;
            delet_node(node,child);
            cout<<"The num of nodes is "<<BST<VALUE_TYPE>::node_num<<" !!!"<<endl;
            return res;
        }
        cout<<"The num of nodes is "<<BST<VALUE_TYPE>::node_num<<" !!!"<<endl;
        return node;
    }

    void BB(TNode<VALUE_TYPE>* _x){
        TNode<VALUE_TYPE>* p=_x->parent;
        if(p){
            TNode<VALUE_TYPE>* s= p->right==_x ? p->left : p->right;
            if(s->color==s->BLACK){
                if(!is_black(s->left) || !is_black(s->right)) {
                    BB_1(_x,s,_x->parent);
                }
                else BB_2(s,_x->parent);
            }
            else {
                BB_3(_x,s,_x->parent);
            }
        }
    }



    void BB_2(TNode<VALUE_TYPE>* _s,TNode<VALUE_TYPE>* _p){
        if(!is_black(_p)) BB_2R(_s,_p);
        else BB_2B(_s,_p);

    }

    void BB_2R(TNode<VALUE_TYPE>* _s,TNode<VALUE_TYPE>* _p){
        _p->color=_p->BLACK;
        _s->color=_s->RED;
    }

    void BB_2B(TNode<VALUE_TYPE>* _s,TNode<VALUE_TYPE>* _p){
        _s->color=_s->RED;
        BB(_p);
    }

    void BB_3(TNode<VALUE_TYPE>* _x,TNode<VALUE_TYPE>* _s,TNode<VALUE_TYPE>* _p){
        TNode<VALUE_TYPE>* old_parent=_p->parent;
        int flag;
        if(!old_parent) flag=0;
        else if (old_parent->left==_p) flag=1;
        else flag=2;

        if(_x==_p->right){
            _p->left=_s->right;
            if(_s->right) _s->right->parent=_p;
            _s->right=_p;
            if(_p) _p->parent=_s;
        }
        else {
            _p->right=_s->left;
            if(_s->left) _s->left->parent=_p;
            _s->left=_p;
            if(_p) _p->parent=_s;
        }

        if(flag==0){
            BST<VALUE_TYPE>::root=_s;
            if(_s) _s->parent=nullptr;
        }
        else if (flag==1) {
            old_parent->left=_s;
            if(_s) _s->parent=old_parent;
        }
        else {
            old_parent->right=_s;
            if(_s) _s->parent=old_parent;
        }
        _s->color=_s->BLACK;
        _p->color=_p->RED;

        BST<VALUE_TYPE>::update_height(_p);
        BST<VALUE_TYPE>::update_height(_s);
        BST<VALUE_TYPE>::update_height_upper(_s->parent);

        BB(_x);
    }

    void delet_node(TNode<VALUE_TYPE>* _node,TNode<VALUE_TYPE>* _child){
        TNode<VALUE_TYPE>* parent=_node->parent;
        if(parent){
            if(parent->left==_node) parent->left=_child;
            else parent->right=_child;
            if(_child) _child->parent=parent;
        }
        else {
            BST<VALUE_TYPE>::root=_child;
            if(_child) _child->parent=nullptr;
        }
        delete _node;
        BST<VALUE_TYPE>::update_height_upper(parent);
        BST<VALUE_TYPE>::node_num--;
    }

    void BB_1(TNode<VALUE_TYPE>* _x,TNode<VALUE_TYPE>* _s,TNode<VALUE_TYPE>* _p){

        TNode<VALUE_TYPE>* a;
        TNode<VALUE_TYPE>* b;
        TNode<VALUE_TYPE>* c;
        TNode<VALUE_TYPE>* T0;
        TNode<VALUE_TYPE>* T1;
        TNode<VALUE_TYPE>* T2;
        TNode<VALUE_TYPE>* T3;

        TNode<VALUE_TYPE>* t;

        TNode<VALUE_TYPE>* old_parent=_p->parent;
        int flag;
        if(!old_parent) flag=0;
        else if (old_parent->left==_p) flag=1;
        else flag=2;


        int color_tmp;
        if(_p->color==_p->RED) color_tmp=0;
        else color_tmp=1;

        if(_p->right==_x){
            if(!is_black(_s->left) ){
                t=_s->left;
                a=t;  b=_s;   c=_p;
                T0=t->left;
                T1=t->right;
                T2=_s->right;
                T3=_x;
            }
            else {
                t=_s->right;
                a=_s;  b=t;   c=_p;
                T0=_s->left;
                T1=t->left;
                T2=t->right;
                T3=_x;
            }
        }
        else {
            if(!is_black(_s->left) ){
                t=_s->left;
                a=_p;  b=t;   c=_s;
                T0=_x;
                T1=t->left;
                T2=t->right;
                T3=_s->right;
            }
            else {
                t=_s->right;
                a=_s;  b=t;   c=_p;
                T0=_x;
                T1=_s->left;
                T2=t->left;
                T3=t->right;
            }
        }
        TNode<VALUE_TYPE>* tmp=connect34(a,b,c,T0,T1,T2,T3);

        BST<VALUE_TYPE>::update_height_upper(tmp->parent);

        if(flag==0) {
            BST<VALUE_TYPE>::root=tmp;
            tmp->parent=nullptr;
        }
        else if (flag==1) {
            old_parent->left=tmp;
            tmp->parent=old_parent;
        }
        else {
            old_parent->right=tmp;
            tmp->parent=old_parent;
        }

        tmp->color=color_tmp==0 ? tmp->RED : tmp->BLACK;
        tmp->left->color=tmp->left->BLACK;
        tmp->right->color=tmp->right->BLACK;
    }



    void RB(TNode<VALUE_TYPE>* _x,TNode<VALUE_TYPE>* _r){
        if(_r) _r->color=_r->BLACK;
        if(_x) _x->color=_x->BLACK;
    }


private:
    void slove_double_red(TNode<VALUE_TYPE>* _node){
        if(_node && _node->color==_node->RED && _node->parent && _node->parent->color==_node->parent->RED){ //double_red
            TNode<VALUE_TYPE>* x=_node;
            TNode<VALUE_TYPE>* p=x->parent;
            TNode<VALUE_TYPE>* g=p->parent;
            TNode<VALUE_TYPE>* u;
            if(p==g->left) u=g->right;
            else u=g->left;
            if(u==nullptr || u->color==u->BLACK){ //uncle is black
                TNode<VALUE_TYPE>* old_parent=g->parent;
                int flag;
                if(old_parent==nullptr) flag=0;
                else if (old_parent->left==g) flag=1;
                else flag=2;
                TNode<VALUE_TYPE>* a;TNode<VALUE_TYPE>* b;TNode<VALUE_TYPE>* c;
                TNode<VALUE_TYPE>* T0;TNode<VALUE_TYPE>* T1;TNode<VALUE_TYPE>* T2;TNode<VALUE_TYPE>* T3;
                if(p == g->left){
                    if(x == p->left){ //left-left
                        a=x;b=p;c=g;
                        T0=x->left;
                        T1=x->right;
                        T2=p->right;
                        T3=g->right;
                    }
                    else { //left-right
                        a=p;b=x;c=g;
                        T0=p->left;
                        T1=x->left;
                        T2=x->right;
                        T3=g->right;
                    }
                }
                else {
                    if(x == p->left){ //right-left
                        a=g;b=x;c=p;
                        T0=g->left;
                        T1=x->left;
                        T2=x->right;
                        T3=p->right;
                    }
                    else { //right-right
                        a=g;b=p;c=x;
                        T0=g->left;
                        T1=p->left;
                        T2=x->left;
                        T3=x->right;
                    }
                }
                a->color=c->RED;
                b->color=b->BLACK;
                c->color=c->RED;
                TNode<VALUE_TYPE>* tmp=connect34(a,b,c,T0,T1,T2,T3);
                if(flag==0) {
                    BST<VALUE_TYPE>::root=tmp;
                    tmp->color=tmp->BLACK;
                }
                else if (flag==1) old_parent->left=tmp;
                else old_parent->right=tmp;
                tmp->parent=old_parent;
                BST<VALUE_TYPE>::update_height_upper(old_parent);
            }
            else{   //uncle is red
                g->color=g->RED;
                p->color=p->BLACK;
                u->color=u->BLACK;
                if(g->parent==nullptr) g->color=g->BLACK;
                slove_double_red(g);
            }
        }
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

    bool is_black(TNode<VALUE_TYPE>* _node){
        return (!_node || _node->color == _node->BLACK);
    }
};




#endif // RED_BLACK_TREE_H
