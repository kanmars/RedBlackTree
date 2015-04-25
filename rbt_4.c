#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>

#define RED 1
#define BLACK 0

#define OK 1
#define ERR 0
#define RES int

#define boolean int
#define YES 1
#define NO 0

#define LR int
#define LEFT 1
#define RIGHT 0
#define UNKNOWN 0


typedef struct node node;
typedef struct root_node rbt;
typedef int COLOR;

/**
 * �ڵ�ṹ��
 */
struct node{
	node * parent,* left,* right;
	COLOR color;
	int key;
	int value;	
};

/**
 * ������ṹ��
 */
struct root_node{
	node * root;
};


/**
 * ��־������ֱ�Ӵ�ӡһ����־
 */
int info(char * str){
	printf("%s\r\n",str);
}

/**
 * ��־��������һ������Ϊ�ַ�������,֮��Ϊ�ַ���
 */
int infox(int argc,...)
{
	va_list ap;
	int d = argc;
	va_start(ap,argc);
	while(d>0)
	{
		char * c = va_arg(ap,char * );
		printf("%s",c);
		d--;
	}
	printf("\r\n");
	va_end(ap);
}

/**
 * �ݹ��ӡ�ڵ�
 */
void nodeShowRecursion(node * n)
{
	if(n->left != NULL)
	{
		nodeShowRecursion(n->left);
	}
	printf("[node]this %8x,  parent %8x  , left %8x  , right %8x  ,  color %d  , key %8d , value %8d ;\r\n",
		n,n->parent,n->left,n->right,n->color,n->key,n->value);
	if(n->right != NULL)
	{
		nodeShowRecursion(n->right);
	}
}

/**
 * �ݹ��ӡ�ڵ���Ϣ
 */
void nodeShowRecursion_2(node * n)
{
	if(n==NULL)return;
	if(n->left != NULL)
	{
		nodeShowRecursion_2(n->left);
	}
	node * left = n->left;
	node * right = n->right;
	node * parent = n->parent;
	node nn ;
	nn.key = 0;
	nn.value = 0;
	nn.parent = 0;
	if(left == NULL) left = &nn;
	if(right == NULL)right = &nn;
	if(parent == NULL)parent = &nn;
	
	printf("[node]this %4d ,  parent %4d ,  left %4d  , right %4d  ,  color %2d  ;\r\n",
		n->key,parent->key,left->key,right->key,n->color);
	if(n->right != NULL)
	{
		nodeShowRecursion_2(n->right);
	}
}

/**
 * ��ȡ��ǰ�ڵ㴦�ڵڶ��ٲ�Ĳ���
 */
int getDeepOfNode(node * n)
{
	node * point = n;
	//���ڵ����0��
	int ceng = 0;
	while(1){
		if(point->parent == NULL)break;
		point = point->parent;
		ceng++;
	}
	return ceng;
}

/**
 * �ݹ���ʽ��ȡһ������������
 */
void getDeepOfRbt(rbt * r,node * point, int * iaddr){
	//��������r�Ľڵ㣬�ֱ��ȡÿ���ڵ�Ĳ�������������
	if(point -> left != NULL)
	{
		getDeepOfRbt(r,point->left,iaddr);
	}
	if(point -> right != NULL)
	{
		getDeepOfRbt(r,point->right,iaddr);
	}
	int thisDeep = getDeepOfNode(point);
	if(thisDeep > *iaddr) *iaddr = thisDeep;
}

/**
 * �ݹ��ӡ�ڵ�ͼ��
 */
void nodeShowRecursionGraphic(rbt * r,node * n)
{
	if(r==NULL||r->root==NULL||n==NULL)return;
	//��ź�����ĸ߶�	
	int rbt_deep = 0;
	//��ȡ���������߸߶�
	getDeepOfRbt(r,r->root,&rbt_deep);
	//��ȡ��ǰ�ڵ�ĸ߶�
	int this_deep = getDeepOfNode(n); 	
	if(n->left != NULL)
	{
		nodeShowRecursionGraphic(r,n->left);
	}
	node * left = n->left;
	node * right = n->right;
	node * parent = n->parent;
	node nn ;
	nn.key = 0;
	nn.value = 0;
	nn.parent = 0;
	if(left == NULL) left = &nn;
	if(right == NULL)right = &nn;
	if(parent == NULL)parent = &nn;

	int i = 0;
	for(i=0;i<rbt_deep - this_deep;i++){
		printf("\033[1;37;47m       \033[0m");
	}
	if(n->color == BLACK){
		printf("\033[37;30;47m %4d[%d]\033[0m",n->key,n->color);
	}else{
		printf("\033[1;31;47m %4d[%d]\033[0m",n->key,n->color);
	}
	for(i=0;i<this_deep;i++){
		printf("\033[1;37;47m       \033[0m");
	}
	printf("\r\n");
	//printf("%4d[%d]\r\n",n->key,n->color);
	if(n->right != NULL)
	{
		nodeShowRecursionGraphic(r,n->right);
	}
}

/**
 * ��ӡһ�ź����
 */
void rbtShow(rbt * r)
{
	printf("--------------------\r\n");
	nodeShowRecursion(r->root);
	printf("--------------------\r\n");
}


/**
 * ��ӡһ�ź����
 */
void rbtShowKV(rbt * r)
{
	printf("--------------------\r\n");
	nodeShowRecursion_2(r->root);
	printf("--------------------\r\n");
}
/**
 * ��ӡһ�ź����
 */
void rbtShowGraphic(rbt * r)
{
	printf("--------------------\r\n");
	//nodeShowRecursion(r->root);	
	//nodeShowRecursion_2(r->root);
	nodeShowRecursionGraphic(r,r->root);
	printf("--------------------\r\n");
}

/**
 * �жϸýڵ��Ƿ��Ǹ��ڵ����ڵ�,���Ϊ���ڵ㣬�򷵻ط�
 */
boolean isLeft(node * n)
{
	if(n->parent == NULL) return NO;
	if(n->parent->left == n) return YES;
	if(n->parent->right == n) return NO;
	return NO;
}
/**
 * �жϸýڵ��Ƿ��Ǹ��ڵ���ҽڵ�,���Ϊ���ڵ㣬�򷵻ط�
 */
boolean isRight(node * n)
{
	if(n->parent == NULL) return NO;
	if(n->parent->left == n) return NO;
	if(n->parent->right == n) return YES;
	return NO;
}

/**
 * ��ȡ��ǰ�ڵ���������
 */
LR getLR(node * n)
{
	if(isLeft(n))
	{
		return LEFT;
	}
	if(isRight(n))
	{
		return RIGHT;
	}
}

/**
 * ��ø��׽ڵ�
 */
node * getParent(node *n)
{
	if(n==NULL)return NULL;
	return n->parent;
}


/**
 * �������ڵ㣬����ýڵ�Ϊ���ڵ㣬���ߵ�һ��ڵ㣬���߸ýڵ�û������ڵ㣬����NULL
 */
node * getUncle(node * n)
{
	//����Ǹ��ڵ㣬����NULL
	if(n->parent == NULL) return NULL;
	//����ǵ�һ��Ľڵ㣬����NULL
	if(n->parent->parent == NULL) return NULL;
	//�ڶ�������
	//������ڵ������֧���򷵻�үү�ڵ���ҷ�֧
	if(isLeft(n->parent))
	{
		return n->parent->parent->right;
	}
	//������ڵ����ҷ�֧���򷵻�үү�ڵ�����֧
	if(isRight(n->parent))
	{
		return n->parent->parent->left;
	}
}

/**
 * ���үү�ڵ�
 */
node * getGrandFather(node * n)
{
	if(n->parent == NULL) return NULL;
	if(n->parent->parent != NULL) return n->parent->parent;
}


/**
 * ����һ���ڵ�
 */
node * nodeCreate()
{
	node * newnode = (node *) malloc(sizeof(node));
	memset(newnode,0,sizeof(node));
	return newnode;
}

/**
 * ɾ��һ���ڵ�
 */
void nodeDestory(node * oneNode)
{
	free(oneNode);
}
/**
 * �ݹ�ɾ��һ������
 */
void nodeDestoryRecursion(node * oneNode)
{
	if(oneNode->left != NULL)
	{
		nodeDestoryRecursion(oneNode->left);
	}
	if(oneNode->right != NULL)
	{
		nodeDestoryRecursion(oneNode->right);	
	}
	
	free(oneNode);
}

/**
 * ����k��rbt�ϲ�ѯ�ڵ���Ϣ
 */
node * nodeSearch(rbt * r,int k)
{
	node * point= NULL;
	point = r->root;
	if(r->root==NULL)return NULL;
	while(1)
	{
		//�����ǰ��key��Ŀ��ֵ��ȣ��򷵻�
		if(point->key == k)
		{
			break;
		}
		//�����ǰ��key����Ŀ��key���������֧
		else if(point->key > k)
		{
			if(point->left != NULL)
			{
				point = point->left;
			}else{
				point = NULL;
				break;
			}
		}
		else if(point->key < k)
		{
			if(point->right != NULL)
			{
				point = point->right;
			}else{
				point = NULL;
				break;
			}
		}
	}
	return point;
}
/**
 * ����һ��������ṹ��
 */
rbt * rbtCreate()
{
	rbt * r = (rbt *) malloc(sizeof(rbt));
	memset(r,0,sizeof(rbt));
	return r;
}

/**
 * ɾ��һ��������Ľṹ��
 */
void rbtDestory(rbt * r)
{
	nodeDestoryRecursion(r->root);
	free(r);	
}





/**
 * ����� ��ӹ��̵��Զ�ƽ��
 */
RES rbtAddBalance(rbt * r, node * n)
{
	//�����ƽ���Ϊ�������
	//CASE 1 ������Ǹ��ڵ㣬��Ӱ��ƽ��
	if(n->parent == NULL)
	{
		n->color = BLACK;
		return OK;
	}
	//CASE 2 ���ڵ�Ϊ��ɫ����Ӱ��ƽ��
	if(n->parent->color == BLACK)
	{
		return OK;
	}
	//CASE 3 ���ڵ�Ϊ��ɫ������ڵ�Ϊ��ɫ
	//��Ѹ��׽ڵ������ڵ�Ϳ�ڣ��޸�үү�ڵ�Ϊ��ɫ��Ȼ���үү�ڵ����ƽ��
	if(getParent(n)->color == RED && getUncle(n)!=NULL && getUncle(n)->color == RED)
	{
		getParent(n)->color = BLACK;
		getUncle(n)->color  = BLACK;
		getGrandFather(n)->color = RED;
		rbtAddBalance(r, getGrandFather(n));
		return OK;
	}
	//CASE 4 ���ڵ�Ϊ��ɫ������ڵ�Ϊ��ɫ��
	//���½ڵ��븸�ڵ�ķ�����죨һ��Ϊ��ڵ㣬һ��Ϊ�ҽڵ㣩
	//��Ҫ�ֱ������������������
	//ʹ�½ڵ��븸�ڵ�Ľڵ㷽����ͬ��ͬΪ��ڵ����ͬΪ�ҽڵ㣩��֮��ת��5����
	if(getParent(n)->color == RED && ( getUncle(n)==NULL || getUncle(n)->color == BLACK ) &&
	(getLR(n) != getLR(getParent(n)))
	)
	{
		node * pre_n = n;
		node * pre_p = getParent(n);
		node * pre_u = getUncle(n);
		node * pre_g = getGrandFather(n);
		//�½ڵ㽨�����游�ڵ�Ĺ�ϵ
		if(isLeft(pre_p))
		{
			//ԭ���ڵ�����ڵ�
			//�����½ڵ����游�ڵ����֧�Ĺ�ϵ
			pre_n->parent = pre_g;
			pre_g->left = pre_n;
		}else{
			//ԭ���ڵ����ҽڵ�
			//�����½ڵ����游�ڵ��ҷ�֧�Ĺ�ϵ
			pre_n->parent = pre_g;
			pre_g->right = pre_n;
		}
		//�������ڵ����½ڵ�Ĺ�ϵ,���ƶ��½ڵ㱻�Ķ����Ӻ���
		if(isLeft(pre_n)){
			//�޸ĺ��pre_n�ڵ���pre_g�����֧
			//����pre_p�ڵ���pre_n�ڵ����֧�Ĺ�ϵ
			//��pre_n����ڵ㸳��pre_p���ҽڵ�(ʵ���ǰѴ���pre_pС��pre_n��key����pre_n����ڵ㻮�鵽pre_p���ҽڵ�)
			pre_p->parent = pre_n;
			pre_p->right  = pre_n->left;
			pre_n->left   = pre_p;
		}else{
			//�޸ĺ��pre_n�ڵ���pre_g���ҷ�֧
			//����pre_p�ڵ���pre_n�ڵ��ҷ�֧�Ĺ�ϵ
			//��pre_n���ҽڵ㸳��pre_p����ڵ�(ʵ���ǰ�С��pre_p����pre_n��key,��pre_n���ҽڵ㻮�鵽pre_p����ڵ�)
			pre_p->parent = pre_n;
			pre_p->left   = pre_n->right;
			pre_n->right  = pre_p;
		}
		//��pre_p��ʼ�Զ�ƽ��
		rbtAddBalance(r, pre_p);
		return OK;
	}
	//CASE 5 ���ڵ�Ϊ��ɫ������ڵ�Ϊ��ɫ
	//���½ڵ��븸�ڵ�ķ�����ͬ(ͬΪ��ڵ����ͬΪ�ҽڵ�)
	//���游�ڵ��½������ڵ����������游�ڵ�Ϳ�죬���ڵ�Ϳ��
	if(getParent(n)->color == RED && ( getUncle(n)==NULL || getUncle(n)->color == BLACK ) &&
	(getLR(n) == getLR(getParent(n)))
	)
	{	//��ȡ�ڵ�׼�������û����Ϊ��
		node * pre_n = n;
		node * pre_p = getParent(n);
		node * pre_u = getUncle(n);
		node * pre_g = getGrandFather(n);
		node * pre_gp= getParent(getGrandFather(n));
		LR pre_p_lr = getLR(pre_p);
		//����pre_gp��pre_p�Ĺ�ϵ
		if(pre_gp!=NULL)	
		{
			if(isLeft(pre_g)){
				//���pre_g��pre_gp�����֧
				//����pre_p��pre_gp�����֧�Ĺ�ϵ
				pre_p->parent = pre_gp;
				pre_gp->left = pre_p;
			}else{
				//���pre_g��pre_gp���ҷ�֧ 
				//����pre_p��pre_gp���ҷ�֧�Ĺ�ϵ
				pre_p->parent = pre_gp;
				pre_gp->right = pre_p;
				
			}
			
		}else{
			//���pre_gp�����ڣ���ԭpre_gΪrbt�ĸ��ڵ�
			pre_p->parent = NULL;
			//�޸�r->root��ֵ
			r->root = pre_p;
		}
		//����pre_p��pre_g�Ĺ�ϵ�����һ����֧����
		if(pre_p_lr == LEFT){
			//������ƶ�֮ǰ��pre_p��pre_g�����֧
			//��pre_p���ҷ�֧����pre_g�����֧(ʵ�����ǰѴ���pre_pС��pre_g��key����pre_p���ҷ�֧���鵽pre_g�����֧)
			//����pre_p���ҷ�֧��pre_g�Ĺ�ϵ 
			pre_g->left = pre_p->right;
			if(pre_p->right!=NULL)pre_p->right->parent = pre_g;
			pre_g->parent = pre_p;
			pre_p->right = pre_g;
		}else{
			//������ƶ�֮ǰ��pre_p��pre_g���ҷ�֧
			//��pre_p�����֧����pre_g���ҷ�֧(ʵ�����ǰ�С��pre_p����pre_g��key����pre_p�����֧���鵽pre_g���ҷ�֧)
			//����pre_p�����֧��pre_g�Ĺ�ϵ 
			pre_g->right = pre_p->left;
			if(pre_p->left!=NULL)pre_p->left->parent = pre_g;
			pre_g->parent = pre_p;
			pre_p->left = pre_g;
		}
		//����Ϳɫ,�游�ڵ�Ϳ�죬���ڵ�Ϳ��
		pre_g->color = RED; 
		pre_p->color = BLACK; 
		return OK;
	}
}




/**
 * ��һ��rbt���key��k��value��v�Ľڵ�
 */
int rbtAdd(rbt * r , int k, int v)
{
	node * newnode = nodeCreate();
	newnode->parent = NULL;
	newnode->key = k;
	newnode->value = v;
	newnode->color = RED;
	//CASE 1 ����ڵ����
	if( r->root == NULL )
	{
		r->root = newnode;
		rbtAddBalance(r, newnode);
		return OK;
	}
	
	node * point= NULL;
	point = r->root;
	//���ҵ����ڵ�
	while(1)
	{
		//�����ǰ��key��Ŀ��ֵ��ȣ��򷵻�
		if(point->key == k)
		{
			//����Ѿ����ڣ��򷵻�ERR
			return ERR;
		}
		//�����ǰ��key����Ŀ��key���������֧
		else if(point->key > k)
		{
			//����ýڵ����ڵ㲻���ڣ���ǰ�ڵ�Ϊ���Ľڵ�
			if(point->left == NULL)
			{
				newnode->parent = point;
				point->left = newnode;
				//�Բ���ڵ����ƽ��
				rbtAddBalance(r, newnode);
				return OK;
			}
			point = point->left;
		}
		else if(point->key < k)
		{
			//����ýڵ���ҽڵ㲻���ڣ���ǰ�ڵ�Ϊ���Ľڵ�
			if(point->right == NULL)
			{
				newnode->parent = point;
				point->right = newnode;
				//�Բ���ڵ����ƽ��
				rbtAddBalance(r, newnode);
				return OK;
			}
			point = point->right;
		}
	}
	return ERR;
}

/**
 * ����� ɾ�����̵��Զ�ƽ����
 */
RES rbtDelBalance(rbt * r, node * n)
{
	
	//CASE 1 �����ɾ���ڵ�û���ӽڵ㣬��ֱ��ɾ��
	if(n->left == NULL && n->right ==NULL)
	{
		if(r->root == n){
			//���ɾ�����Ǹ��ڵ㣬��ֱ��ɾ����������r->rootΪNULL
			nodeDestory(n);
			r->root = NULL;
			return OK;
		}else{
			//���ɾ���Ĳ��Ǹ��ڵ㣬��ɾ���ýڵ㣬�����ø��ڵ��ָ��Ϊ��
			if(isLeft(n)){
				//���ɾ��������ڵ�
				getParent(n)->left = NULL;
				nodeDestory(n);
				return OK;
			}else{
				//���ɾ�������ҽڵ�
				getParent(n)->right = NULL;
				nodeDestory(n);
				return OK;
			}
		}
	}
	//CASE 2 �����ɾ���ڵ���һ���ӽڵ�
	if((n->left == NULL && n->right !=NULL) || (n->left != NULL && n->right ==NULL))
	{
		//��ȡ�ӽڵ�
		node * c = NULL;//�ӽڵ�
		if(n->left != NULL)
		{
			c = n->left;
		}else{
			c = n->right;
		}
		
		//CASE 2.1	����ӽڵ��Ǻ�ɫ��
		//���غ��壺����Ϊ��ɫ
		//ִ�в�����ֱ��ɾ��,�ӽڵ�����Լ���λ�ã��ӽڵ��޸�Ϊ��ɫ
		if(c->color == RED)
		{
			//���n�Ǹ��ڵ�
			if( r->root == n )
			{
				//����ɫ�ӽڵ㽻��root������ɾ��n�����Ҹ���ɫ�ӽڵ�ͿɫΪ��ɫ
				r->root = c;
				r->root->color = BLACK;
				c->parent = NULL;
				nodeDestory(n);
				return OK;
			}else{
				//���n���Ǹ��ڵ�
				node * pre_p = getParent(n);
				node * pre_x = c;
				//����ɫ�ӽڵ㽻��pre_p
				if(isLeft(n))
				{
					pre_p->left = pre_x;
					pre_x->parent = pre_p;
				}else{
					pre_p->right = pre_x;
					pre_x->parent = pre_p;
				}
				//ɾ��n�����Ҹ���ɫ�ӽڵ�ͿɫΪ��ɫ
				pre_x->color = BLACK;
				nodeDestory(n);
				return OK;
			}
		}
		
		//CASE 2.2  ����ӽڵ��Ǻ�ɫ��
		//���غ��壺��
		//ִ�в�����ɾ���ýڵ�,���ӽڵ��������λ��,���ӽڵ�������һ�����ʵ�λ��Ϳ��
		if(c->color == BLACK)
		{
			//DOSTH ɾ���ڵ�Ĳ���
			//���n�Ǹ��ڵ�
			if( r->root == n )
			{
				//���ӽڵ㽻��root������ɾ��n�����Ҹ���ɫ�ӽڵ�ͿɫΪ��ɫ
				r->root = c;
				r->root->color = BLACK;
				c->parent = NULL;
				nodeDestory(n);
				return OK;//��֧���ڵ㣬ֱ��ɾ������
			}else{
				//���n���Ǹ��ڵ�
				node * pre_p = getParent(n);
				node * pre_x = c;
				//���ӽڵ㽻��pre_p
				if(isLeft(n))
				{
					pre_p->left = pre_x;
					pre_x->parent = pre_p;
				}else{
					pre_p->right = pre_x;
					pre_x->parent = pre_p;
				}
				COLOR n_color = n->color;
				//ɾ��n�ڵ�
				nodeDestory(n);
				//���n����ɫ�Ǻ�ɫ�ģ���ֱ�ӷ��سɹ�
				if(n_color == RED)
				return OK;
				
			}
			//DOSTH ɾ���ڵ���������Ͻ���ƽ��
			//�滻��ԭ�ڵ�n�����٣�c�Ľڵ㱻�������n��
			//ѭ������,���滻����ӽڵ�������һ�����ʵ�λ��Ϳ��
			//���£���c�Ľڵ㱻�����n�Ϻ󣬾���n
			n = c;
			while(1)
			{
				//DOSTH ����Ѿ��������ϴ����˸��ڵ㣬���޸ĸ��ڵ�Ϊ��ɫ������
				if(r->root == n)
				{
					r->root->color = BLACK;
					return OK;
				}	
				//��ǰ��ķ�֧�У����r->root == n ,��ֱ���޸���ɫ���˳�
				//��ˣ��˴��ض����Ǹ��ڵ㣬n->parent��һ�����ڵ�
				//pΪ���׽ڵ�
				node * p = NULL;
				p = n->parent;
				//wΪ����ڵ�
				node * w = NULL;
				if(isLeft(n)){
					//���n����ڵ㣬������ڵ�Ϊ���ڵ���ҽڵ�
					w = n->parent->right;
				}else{
					//���n���ҽڵ㣬������ڵ�Ϊ���ڵ����ڵ�
					w = n->parent->left;
				}
				//үү�ڵ㲻һ������
				node * gp = n->parent->parent;
				
				//CASE 2.2.1  �滻��n���ֵܽڵ�wΪ��ɫ
				//���غ��壺n���ֵܽڵ�w�Ķ��Ӷ��Ǻ�ɫ(һ��������������)
				//			���׽ڵ�p �Ǻ�ɫ
				//ִ�в�������Ҫ����һ������������ɾ���ڵ�ķ�֧����+1����
				//�ı���ת�������ڵ����ɫ,ת�����Ϊ2��3��4
				if(w->color == RED)
				{
					//��n�����֧���ҷ�֧�ֱ���
					if(isLeft(n)){
						//nΪ���֧�������������Ҹı�p��w����ɫ(������ɫ��ͬ)
						//������Ϊ��1��w����ڵ�ҵ�p���ҽڵ�
						//			2��p��parentָ��w
						//			3��w����ڵ�ָ��p
						p->right = w->left;
						p->parent = w;
						w->left = p;
					}else{
						//nΪ�ҷ�֧�������������Ҹı�p��w����ɫ(������ɫ��ͬ)
						//������Ϊ��1��w���ҽڵ�ҵ�p����ڵ�
						//			2��p��parentָ��w
						//			3��w���ҽڵ�ָ��p
						p->left = w->right;
						p->parent = w;
						w->right = p;
					}	
					//��ɫ����
					COLOR tmp;
					tmp = w->color;
					w->color = p->color;
					p->color = tmp;
					//����w��gp�Ĺ���
					if(gp == NULL){
						//ԭp�ڵ�Ϊ���ڵ�
						r->root = w;
						w->parent = NULL;
					}else if(gp!=NULL && gp->left == p){
						gp->left = w;
					}else if(gp!=NULL && gp->right == p){
						gp->right = w;
					}
					//n = n;
					continue;
				}
				//CASE 2.2.2 �滻��n���ֵܽڵ�wΪ��ɫ,��w���ӽڵ㶼�Ǻ�ɫ����NIL
				//���غ��壺n��w�ĸ��ڵ�ɺ�ɺڣ������Ҳ���һ����
				//ִ�в�����w��ɫ�޸�Ϊ��ɫ��������ƽ�⣬֮����pΪ��ʼ�����¿�ʼƽ�⡣
				//			��������Ϊ�����Խ�������֧�ĺڽڵ���-1,�����ϵݹ�
				if(
					w->color == BLACK 
					&& (w->left == NULL ||  w->left->color == BLACK )
					&& (w->right== NULL ||  w->right->color == BLACK ) 
				)
				{
					w->color = RED;
					n = p;
					continue;	
				}
				//CASE 2.2.3 �滻��n���ֵܽڵ�wΪ��ɫ,��w��ͬ���ӽڵ�Ϊ��ɫ��������Ϊ��ɫ
				//���غ��壺��
				//ִ�в�������w��������ӽ���������������ɫ��ת��Ϊ4����
				//			
				if(w->color ==BLACK){
					//����滻����ֵܽڵ�wΪ��ɫ
					LR w_lr = getLR(w);
					if(w_lr == RIGHT){
						//n�Ǹ��ڵ����ڵ�,w�Ǹ��ڵ���ҽڵ�
						//���w��ͬ���ӽڵ�Ϊ��ɫ�������ӽڵ�Ϊ��ɫ
						if(
							(w->right==NULL || w->right->color == BLACK) 
							&& (w->left !=NULL && w->left->color == RED ))
						{
							node * w_left = w->left;
							//���w����ڵ��w��������
							p->right = w_left;
							w_left->parent = p;
							w->parent = w_left;
							w->left = w_left->right;
							w_left->right->parent = w;
							w_left->right = w;
							//���ҽ���w��w_left����ɫ
							COLOR tmp;
							tmp = w->color;
							w->color = w_left->color;
							w_left->color = tmp;
							//֮��n���䣬��������
							continue;
						}//������������� 2.2.2����2.2.4����
					}else{
						//n�Ǹ��ڵ���ҽڵ�,w�Ǹ��ڵ����ڵ�
						//���w��ͬ���ӽڵ�Ϊ��ɫ�������ӽڵ�Ϊ��ɫ	
						if(
							(w->left==NULL || w->left->color == BLACK) 
							&& (w->right !=NULL && w->right->color == RED ))
						{
							node * w_right = w->right;
							//���w���ҽڵ��w��������
							p->left= w_right;
							w_right->parent = p;
							w->parent = w_right;
							w->right= w_right->left;
							w_right->left->parent = w;
							w_right->left = w;
							//���ҽ���w��w_left����ɫ
							COLOR tmp;
							tmp = w->color;
							w->color = w_right->color;
							w_right->color = tmp;
							//֮��n���䣬��������
							continue;
						}//������������� 2.2.2����2.2.4����

					}
				}
				//CASE 2.2.4 �滻��n���ֵܽڵ�wΪ��ɫ,��w��ͬ���ӽڵ�Ϊ��ɫ
				//���غ��壺n�˺�ɫ�ڵ���1����Ҫ����n���ڵ�λ�ý�����������������Ȼ�󷴷����ֲ�һ����ɫ�������ƽ��
				//ִ�в���������p��w����ɫ������w������ת��Ȼ��wͬ���ӽڵ��úڣ����ƽ��
				if(w->color ==BLACK){
					//����滻����ֵܽڵ�wΪ��ɫ
					LR w_lr = getLR(w);
					if(w_lr == RIGHT){
						//n�Ǹ��ڵ����ڵ�,w�Ǹ��ڵ���ҽڵ�
						//���w��ͬ���ӽڵ�Ϊ��ɫ
						if(w->right!=NULL && w->right->color == RED)
						{
							//����p��w����ɫ
							COLOR tmp;
							tmp = w->color;
							w->color = p->color;
							p->color = tmp;
							//����w������ת,�˴�w������������
							node * w_left = w->left;

							p->right = w_left;
							w_left->parent = p;
							
							w->left = p;
							p->parent = w;
	
							//����w��gp�Ĺ���
							if(gp == NULL){
								//ԭp�ڵ�Ϊ���ڵ�
								r->root = w;
								w->parent = NULL;
							}else if(gp!=NULL && gp->left == p){
								gp->left = w;
							}else if(gp!=NULL && gp->right == p){
								gp->right = w;
							}
							//Ȼ��wͬ���ӽڵ��ú�
							w->right->color = BLACK;
							//�������ƽ��
							return OK;
						}//����������֧����
					}else{
						//n�Ǹ��ڵ���ҽڵ�,w�Ǹ��ڵ����ڵ�
						//���w��ͬ���ӽڵ�Ϊ��ɫ
						if(w->left!=NULL && w->left->color == RED)
						{
							//����p��w����ɫ
							COLOR tmp;
							tmp = w->color;
							w->color = p->color;
							p->color = tmp;
							//����w������ת,�˴�w������������
							node * w_right = w->right;

							p->left = w_right;
							w_right->parent = p;
							
							w->right = p;
							p->parent = w;
	
							//����w��gp�Ĺ���
							if(gp == NULL){
								//ԭp�ڵ�Ϊ���ڵ�
								r->root = w;
								w->parent = NULL;
							}else if(gp!=NULL && gp->left == p){
								gp->left = w;
							}else if(gp!=NULL && gp->right == p){
								gp->right = w;
							}
							//Ȼ��wͬ���ӽڵ��ú�
							w->right->color = BLACK;
							//�������ƽ��
							return OK;
						}//����������֧����

					}
				}
			}
		}
	}
	//CASE 3 �����ɾ���ڵ��������ӽڵ�
	if(n->left != NULL && n->right !=NULL)
	{
		//�����������ҵ���С���滻�ڵ�y��x��y����������ɫ�������
		node * y = n->right;
		while(y->left != NULL)
		{
			y = y->left;
		}
		n->key = y->key;
		n->value = y->value;
		//ת��Ϊɾ��y������?(yֻ���ҽڵ�)
		return rbtDelBalance(r,y);	
	}
}

/**
 * ��rbt��ɾ��һ��keyΪk�Ľڵ�
 */
RES rbtDel(rbt * r,int k)
{
	node * y = nodeSearch(r,k);
	if(y == NULL) return OK;
	return rbtDelBalance(r,y);
}



int main(int argc,char ** argv)
{
	info("���������ʼ");
	infox(4,"���ߣ�","���� ","����:","kanmars@kanmars.ra");
	infox(3,"�ο����ϣ�","�������ͷ��β����ɾ��ȫ��չʾ","http://blog.csdn.net/v_july_v/article/details/6284050");
	infox(3,"�ο����ϣ�","�����͸���˽�","http://blog.chinaunix.net/uid-26575352-id-3061918.html");
	infox(3,"�ο����ϣ�","�����ɾ��","http://blog.csdn.net/spch2008/article/details/9338923");
	//����һ��rootָ��
	rbt * r = rbtCreate();
	//���һ�����ڵ�
	RES res = 0;
	res = rbtAdd(r,4,11);
	res = rbtAdd(r,3,33);
	res = rbtAdd(r,2,22);
	res = rbtAdd(r,5,55);
	res = rbtAdd(r,16,1616);
	res = rbtAdd(r,12,1212);
	res = rbtAdd(r,14,1414);
	res = rbtAdd(r,6,66);
	res = rbtAdd(r,11,1111);
	res = rbtAdd(r,1,11);
	res = rbtAdd(r,99,9999);
	res = rbtAdd(r,8,88);
	res = rbtAdd(r,7,77);
	res = rbtAdd(r,9,99);
	res = rbtAdd(r,13,1313);
	res = rbtAdd(r,17,1717);
	res = rbtAdd(r,15,1515);
	res = rbtAdd(r,18,1818);
	res = rbtAdd(r,20,2020);
	res = rbtAdd(r,21,2121);
	res = rbtAdd(r,30,3030);
	res = rbtAdd(r,29,2929);
	res = rbtAdd(r,25,2525);
	res = rbtAdd(r,22,2222);
	res = rbtAdd(r,23,2323);
	res = rbtAdd(r,26,2626);
	res = rbtAdd(r,50,5050);
	res = rbtAdd(r,35,3535);
	res = rbtAdd(r,40,4040);
	res = rbtAdd(r,41,4141);
	res = rbtAdd(r,45,4545);
	res = rbtAdd(r,43,4343);
	int i = 0;
	for(i=0;i<argc;i++){
		int num = atoi(argv[i]);
		rbtDel(r,num);
		rbtShow(r);
	}
	int rbtDeep = 0;
	getDeepOfRbt(r,r->root, &rbtDeep);
	printf("�����Ĳ���Ϊ %8d\r\n",rbtDeep);
	rbtShowGraphic(r);
//	node * n_2 =  nodeSearch(r,11);
//	printf("%d\r\n",n_2->value);
}

