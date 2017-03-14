/*
 * Linux Kernel Style Link List Example
 *
 * Author: Justin Wong <justin.w.xd@gmail.com>
 * Date: Jan. 31, 2014
 */

#include <stdio.h>
#include <stdlib.h>



struct tree_head {
	struct list_head* root;
};

struct list_head {
    struct list_head* left;
	struct list_head* right;
};

#define LIST_HEAD_INIT(name) { NULL }
#define LIST_HEAD(name) struct tree_head name = LIST_HEAD_INIT(name)



#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define container_of(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type,member) );})

#ifndef offsetof
#define offsetof(type, member) ((size_t) &((type *)0)->member)
#endif




int list_add(struct tree_head *head, struct list_head *new);
int list_add_node(struct list_head *head, struct list_head *new);
int print_node(struct list_head *head);
int print_head(struct tree_head *head);
	
	
struct my_node {
    int data;
    struct list_head list;
};

int list_add(struct tree_head *head, struct list_head *new)
{
    if (head == NULL)
        return -1;
	else if (head->root == NULL)
		head->root = new;
	else
		list_add_node(head->root,new);
    return 0;
}

int list_add_node(struct list_head *head, struct list_head *new)
{
    if(list_entry(head, struct my_node, list)->data == list_entry(new,struct my_node,list) -> data){
		return -1;
	}else if(list_entry(head, struct my_node, list)->data < list_entry(new,struct my_node,list) -> data){
		if(head->left)
			list_add_node(head->left, new);
		else 
			head -> left = new;
	}else {
		if(head->right)
			list_add_node(head->right, new);
		else 
			head -> right = new;	
	}	
	return 0;
}

int print_node(struct list_head *head)
{
    if(NULL != head){
		struct my_node *node = list_entry(head, struct my_node, list) ;
		printf("%d ",node->data);
		print_node(node->list.left);
		print_node(node->list.right);
	}
	return 0;
}

int print_head(struct tree_head *head)
{
    if (head == NULL)
        return -1;
	print_node(head->root);
    return 0;
}

int list_destroy(struct list_head* head){
	if(head){
		list_destroy(head->left);
		list_destroy(head->right);
		struct my_node* node= list_entry(head, struct my_node, list);
		free(node);
	}
	return 0;
}


int tree_destroy(struct tree_head* head){ 
	if(head->root)
		list_destroy(head->root);
	return 0;
}	


int main(int argc, const char *argv[])
{
    LIST_HEAD(my_list);
	int i;
    for ( i=0; i < 10; i++) {
        struct my_node *node = malloc(sizeof(struct my_node));
        node->data = i;
		node->list.right = NULL;
		node->list.left = NULL;
        list_add(&my_list, &(node->list));
    }
	print_head(&my_list);
	tree_destroy(&my_list);
    return 0;
}


