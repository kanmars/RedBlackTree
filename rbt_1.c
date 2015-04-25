#include <stdio.h>
#include <stdlib.h>

const int RED = 0;
const int BLACK = 1;

typedef struct rb_node rb_node;

struct rb_node{
    rb_node* lchild, *rchild, *parent;
    int key, colour;
};
rb_node* root;

rb_node* get_node(rb_node* parent, int key);
void rb_insert(int key);
rb_node* rb_search(int key);
void rb_delete(int key);
rb_node* clock_wise(rb_node* node);
rb_node* counter_clock_wise(rb_node* node);
void show_rb_tree(rb_node* node);

rb_node* get_node(rb_node* parent, int key){
    rb_node *tmp = (rb_node*)malloc(sizeof(rb_node));
    tmp->key = key;
    tmp->colour = RED;
    tmp->parent = parent;
    tmp->lchild = tmp->rchild = NULL;
    return tmp;
}

rb_node* clock_wise(rb_node* node){
    if(node == NULL || node->lchild == NULL)
    return NULL;

    rb_node *rb_1=node, *rb_2=node->lchild, *rb_3=node->lchild->rchild;
    if(rb_1->parent != NULL){
    if(rb_1->parent->lchild == rb_1)
        rb_1->parent->lchild = rb_2;
    else
        rb_1->parent->rchild = rb_2;
    }else if(rb_1 == root){
    root = rb_2;
    }
    rb_2->parent = rb_1->parent;

    rb_1->parent = rb_2;
    rb_2->rchild = rb_1;

    rb_1->lchild = rb_3;
    if(rb_3 != NULL)rb_3->parent = rb_1;

    return rb_2;   
}

rb_node* counter_clock_wise(rb_node* node){
    if(node == NULL || node->rchild == NULL)
    return NULL;

    rb_node *rb_1=node, *rb_2=node->rchild, *rb_3=node->rchild->lchild;
    if(rb_1->parent != NULL){
    if(rb_1->parent->lchild == rb_1)
        rb_1->parent->lchild = rb_2;
    else
        rb_1->parent->rchild = rb_2;
    }
    else if(rb_1 == root){
    root = rb_2;
    }
    rb_2->parent = rb_1->parent;

    rb_1->parent = rb_2;
    rb_2->lchild = rb_1;

    rb_1->rchild = rb_3;
    if(rb_3 != NULL)rb_3->parent = rb_1;

    return rb_2;
}

rb_node* rb_search(int key){
    rb_node *p = root;
    while(p != NULL){
    if(key < p->key)
        p = p->lchild;
    else if(key > p->key)
        p = p->rchild;
    else
        break;
    }
    return p;
}

void rb_insert(int key){
    rb_node *p=root, *q=NULL;

    if(root == NULL){
		root = get_node(NULL, key);
    	root->colour = BLACK;
    	return;
    }

    while(p != NULL){
    	q = p;
    	if(key < p->key)
        	p = p->lchild;
		else if(key > p->key)
        	p = p->rchild;
    	else return;
    }

    if(key < q->key)
    	q->lchild = get_node(q, key);
    else
    	q->rchild = get_node(q, key);

    while(q != NULL && q->colour == RED){
    	p = q->parent;//p won't null, or BUG.

    	if(p->lchild == q){
        	if(q->rchild != NULL && q->rchild->colour == RED)
        	counter_clock_wise(q);       
        	q = clock_wise(p);
        	q->lchild->colour = BLACK;
    	}
    	else{
        	if(q->lchild != NULL && q->lchild->colour == RED)
        	clock_wise(q);
        	q = counter_clock_wise(p);
        	q->rchild->colour = BLACK;
    	}

    	q = q->parent;
    }
    root->colour = BLACK;
}

void show_rb_tree(rb_node* node){
    if(node == NULL)
    return;
    printf("(%d,%d)\n", node->key, node->colour);
    if(node->lchild != NULL){
    printf("[-1]\n");
    show_rb_tree(node->lchild);
    }
    if(node->rchild != NULL){
    printf("[1]\n");
    show_rb_tree(node->rchild);
    }
    printf("[0]\n");
}

void rb_delete(int key){
    rb_node *v = rb_search(key), *u, *p, *c, *b;
    int tmp;
	//���û�ҵ���ɾ���ڵ㣬ֱ�ӷ���
    if(v == NULL) return;

    u = v;
	//�����ڵ���ҽڵ㶼���ڣ��������������ҵ�������滻�ڵ�u
    if(v->lchild != NULL && v->rchild != NULL){
    	u = v->rchild;
    	while(u->lchild != NULL){
        	u = u->lchild;
    	}
    	tmp = u->key;
    	u->key = v->key;//�뱻ɾ���ڵ�������ݽ�����ʹ����ת��Ϊɾ���滻�ڵ������  case3ת��Ϊcase2
    	v->key = tmp;
    }

    //u is the node to free.
    if(u->lchild != NULL)
    	c = u->lchild;	//�� ��ɾ���ڵ������Ӵ���ʱ��c=�����
    else 
    	c = u->rchild; //����c = �Ҷ���

    p = u->parent;//��ȡ����ɾ���ڵ�ĸ��ڵ�
    if(p != NULL){
    	//remove u from rb_tree.
    	if(p->lchild == u)
        	p->lchild = c;
    	else
        	p->rchild = c;
    }
    else{
    //u is root.
    	root = c;
    	free((void*)u);
    	return;
    }

    //u is not root and u is RED, this will not unbalance.
    if(u->colour == RED){
    free((void*)u);
    return;
    }

    free((void*)u);
    u = c;

    //u is the first node to balance.
    while(u != root){
    if(u != NULL && u->colour == RED){
        //if u is RED, change it to BLACK can finsh.
        u->colour = BLACK;
        return;
    }

    if(u == p->lchild)
        b = p->rchild;
    else
        b = p->lchild;

    printf("%d\n", b->key);

    //b is borther of u. b can't be null, or the rb_tree is must not balance.
    if(b->colour == BLACK){
        //If b's son is RED, rotate the node.
        if(b->lchild != NULL && b->lchild->colour == RED){
        if(u == p->lchild){
            b = clock_wise(b);
            b->colour = BLACK;
            b->rchild->colour = RED;

            p = counter_clock_wise(p);
            p->colour = p->lchild->colour;
            p->lchild->colour = BLACK;
            p->rchild->colour = BLACK;
        }
        else{
            p = clock_wise(p);
            p->colour = p->rchild->colour;
            p->rchild->colour = BLACK;
            p->lchild->colour = BLACK;
        }

        return;
        }
        else if(b->rchild != NULL && b->rchild->colour == RED){
        if(u == p->rchild){
            b = counter_clock_wise(b);
            b->colour = BLACK;
            b->lchild->colour = RED;

            p = clock_wise(p);
            p->colour = p->rchild->colour;
            p->rchild->colour = BLACK;
            p->lchild->colour = BLACK;
        }
        else{
            p = counter_clock_wise(p);
            p->colour = p->lchild->colour;
            p->lchild->colour = BLACK;
            p->rchild->colour = BLACK;
        }       
        return;
        }
        else{//if b's sons are BLACK, make b RED and move up u.
        b->colour = RED;
        u = p;
        p = u->parent;
        continue;
        }
    }
    else{
        if(u == p->lchild){
        p = counter_clock_wise(p);
        p->colour = BLACK;
        p->lchild->colour = RED;
        p = p->lchild;
        }
        else{
        p = clock_wise(p);
        p->colour = BLACK;
        p->rchild->colour = RED;
        p = p->rchild;
        }
    }
    }
    root->colour = BLACK;
}

int main(){
    int i;
    root = NULL;
    for(i = 1; i <= 10; i++){   
    rb_insert(i);
    }
    rb_delete(9);
    rb_delete(3);
    rb_delete(7);
    show_rb_tree(root);
    printf("\n");
    return 0;
}
