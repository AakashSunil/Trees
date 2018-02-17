/*
*
*	Created by Aakash Sunil and Peter Hudson
*
*	Implementation of a 2-3 Tree - Creation and process of entering into the tree simulataneously
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 2
#define MIN 1

  struct trees_23 {
        int value[MAX + 1], count;
        struct trees_23 *links[MAX + 1];
  };

  struct trees_23 *root;

  /* creating new node */
  struct trees_23 * create(int val, struct trees_23 *child) {
        struct trees_23 *newNode;
        newNode = (struct trees_23 *)malloc(sizeof(struct trees_23));
        newNode->value[1] = val;
        newNode->count = 1;
        newNode->links[0] = root;
        newNode->links[1] = child;
        return newNode;
  }

  /* Places the value in appropriate position */
  void insert(int val, int pos, struct trees_23 *node, struct trees_23 *child) {
        int j = node->count;
        while (j > pos) {
                node->value[j + 1] = node->value[j];
                node->links[j + 1] = node->links[j];
                j--;
        }
        node->value[j + 1] = val;
        node->links[j + 1] = child;
        node->count++;
  }

  /* split the node when more than three values are in the node */
  void split (int val, int *pval, int pos, struct trees_23 *node, struct trees_23 *child, struct trees_23 **newNode) {
        int median, j;

        if (pos > MIN)
                median = MIN + 1;
        else
                median = MIN;

        *newNode = (struct trees_23 *)malloc(sizeof(struct trees_23));
        j = median + 1;
        while (j <= MAX) {
                (*newNode)->value[j - median] = node->value[j];
                (*newNode)->links[j - median] = node->links[j];
                j++;
        }
        node->count = median;
        (*newNode)->count = MAX - median;

        if (pos <= MIN) {
                insert(val, pos, node, child);
        } else {
                insert(val, pos - median, *newNode, child);
        }
        *pval = node->value[node->count];
        (*newNode)->links[0] = node->links[node->count];
        node->count--;
  }

  /* setting the value to the node */
  int setNode(int val, int *pval, struct trees_23 *node, struct trees_23 **child) {

        int pos;
        if (!node) {
                *pval = val;
                *child = NULL;
                return 1;
        }

        if (val < node->value[1]) {
                pos = 0;
        } else {
                for (pos = node->count;
                        (val < node->value[pos] && pos > 1); pos--);
                if (val == node->value[pos]) {
                        printf("Duplicates not allowed\n");
                        return 0;
                }
        }
        if (setNode(val, pval, node->links[pos], child)) {
                if (node->count < MAX) {
                        insert(*pval, pos, node, *child);
                } else {
                        split(*pval, pval, pos, node, *child, child);
                        return 1;
                }
        }
        return 0;
  }

  /* insert val in 2-3_Tree */
  void insertion(int val) {
        int flag, i;
        struct trees_23 *child;

        flag = setNode(val, &i, root, &child);
        if (flag)
                root = create(i, child);
  }
  
  /* Display() */
  void inorder(struct trees_23 *myNode) {
        int i;
        if (myNode) {
                for (i = 0; i < myNode->count; i++) {
                        inorder(myNode->links[i]);
                        
                        printf("%d ", myNode->value[i + 1]);
                        
                }
                inorder(myNode->links[i]);
        }
  }
  void display(struct trees_23 *ptr, int level)
{
    int i;	
    if (ptr!=NULL)
    {
    	//display(ptr->link[2], level + 1);
    	if(ptr->links[2]!=NULL)
    	{
    		for (i = 0; i < level+1 && ptr == root; i++)
            printf("        ");
			for(i = 0; i<ptr->count-1;i++)
				printf("%d ", ptr->links[2]->value[i+1]);
    		printf("\n");
		}
        display(ptr->links[1], level + 1);
        printf("\n");
        if (ptr == root)
        printf("Root -> ");
        for (i = 0; i < level && ptr != root; i++)
            printf("        ");
        for(i = 0; i<ptr->count;i++)
				printf("%d ", ptr->value[i+1]);
        display(ptr->links[0], level + 1);
    }
}

  int main() {
        int val[10],value, ch, i,var=0;
        time_t begin = 0, end = 0;
        while (1) {
                printf("1. Insertion and Display\n");
                printf("2. Exit\nEnter your choice:");
                scanf("%d", &ch);
                switch (ch) {
                        case 1:
                                printf("Enter input:");
                                scanf("%d",&value);
								insertion(value);
                          		printf("\n\n");
								display(root,1);								
                                printf("\n\n");
                                break;
                        case 2: 
                                exit(0);
                        default:
                                printf("U have entered wrong option!!\n");
                                break;
                }
                printf("\n");
        }
  }
