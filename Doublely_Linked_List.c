#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
	int  value;  // value (int) of this list item 
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
	int  size;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLList;


// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	struct DLList *L;

	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here

// O(n) since traverse numbers in the file list only once
DLList *CreateDLListFromFileDlist(const char *filename)
{
	FILE *file;
	struct DLListNode *n_node;  //next node
    struct DLListNode *p_node;  //prev node
	//struct DLListNode *n_Node;	
    struct DLList *L = newDLList();
    n_node = L->first;
    p_node = L->last;
	int n=0;
	int p=0;
    int number=0;
    int count=0;
    if (filename == "stdin"){                        //stdin input
        char buf[10];
            while (fgets(buf, sizeof buf, stdin) != NULL && (buf[0] != '\n')){
                number = atoi(buf);
                if(count==0){                       //generate first node
                    n_node = newDLListNode(number);
                    n_node->prev = NULL;
                    L->first = n_node;
                    count++;
                }
                else{
                    while (n_node->next!=NULL){     //for each input number generate a new node and link it
                        n_node = n_node->next;
                    }
                    n_node->next = newDLListNode(number);
                    p_node = n_node;
                    n_node = n_node->next;
                    n_node->prev = p_node;
                    L->last = n_node;
                    n_node->next = NULL;
                }
        }
        return L;
    }
    else{
        file = fopen(filename,"r");
        while (1){                          //read file one by one, and generate list nodes till EOF
            fscanf(file,"%d",&n);
            if (n!=32){                 //not space 32=' '
                if(count==0){
                    n_node = newDLListNode(n);
                    n_node->prev = NULL;
                    L->first = n_node;
                    count++;
                }
                else{
                    while (n_node->next!=NULL){
                        n_node = n_node->next;
                    }
                    n_node->next = newDLListNode(n);           //scan each number in the file and create a node and link it 
                    p_node = n_node;
                    n_node = n_node->next;                  //same code for stdin input, should combine it into a function...
                    n_node->prev = p_node;
                    L->last = n_node;
                    n_node->next = NULL;	
                }
            }
                //link node to previous node next node = NULL
            if(getc(file)==EOF){
                break;
            }
        }
    }
        fclose(file);
  	return L;
}

// clone a DLList
// put your time complexity analysis for cloneList() here

// O(n) since traverse the original list only once
DLList *cloneList(struct DLList *u)
{
    struct DLList *clone = newDLList();
    struct DLListNode *u_node; 
    struct DLListNode *n_node;  //next node
    struct DLListNode *p_node;  //prev node
    int original_value;
    u_node = u->first;
    
    if (u_node != NULL){             //generate the first node for clone list
        n_node = newDLListNode(u_node->value);
        clone->first = n_node;
        n_node->prev = NULL;
        u_node = u_node->next;
    }

    while (u_node != NULL){                 //traverse list u, for each value create new node add to list clone
        original_value = u_node->value;
        n_node->next = newDLListNode(original_value);
        p_node = n_node;
        n_node = n_node->next;
        n_node->prev = p_node;
        clone->last = n_node;
        u_node = u_node->next;
    }
    n_node->next = NULL;
   
    
    return clone;
  
}

// compute the union of two DLLists u and v
// O(u*v) 
    // Use simplest naive approach since other method requires sorting an linked list.
DLList *setUnion(struct DLList *u, struct DLList *v)
{
    struct DLListNode *u_node;
    struct DLListNode *p_node;
    struct DLListNode *v_node;
    struct DLList *Union;
    int present=0;
    Union = cloneList(u);       // clone a list into the result list first
    u_node = Union->first;      //init list pointer
    v_node = v->first;
    //for each node in v not present in u add to the end of Union
    while(v_node != NULL){
        while (u_node->next != NULL){
            if (v_node->value == u_node->value){
                present = 1;
            }
            u_node = u_node->next;
        }
        if (present == 0){
            p_node = u_node;
            u_node->next = newDLListNode(v_node->value);
            u_node = u_node->next;
            u_node->prev = p_node;
        }
        present = 0;
        v_node = v_node->next;
        u_node = Union->first;
    }
    return Union;
}

// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here
// O(u*v)
DLList *setIntersection(struct DLList *u, struct DLList *v)
{
    struct DLListNode* u_node;
    struct DLListNode* p_node;
    struct DLListNode* v_node;
    struct DLList *inter = newDLList();
    struct DLListNode* i_node;
    int count = 0;
    i_node = inter->first;
    u_node = u->first;      //init list pointer
    v_node = v->first;
    
    //for each node in v not present in u add to the end of inter
    while(v_node ->next != NULL){
        while (u_node->next != NULL){
            if (v_node->value == u_node->value){
                if (count == 0){
                    i_node = newDLListNode(v_node->value);
                    inter->first = i_node;             // point list first position to the node
                    i_node->prev = NULL;
                    i_node->next = NULL;
                    count++;
                }
                else{
                    i_node->next = newDLListNode(v_node->value);
                    p_node = i_node;
                    i_node = i_node->next;
                    i_node->prev = p_node;
                   // printf("%d \n",v_node->value);
                }

            }
            u_node = u_node->next;
        }
        
        u_node = u->first;
        v_node = v_node->next;
    }
    i_node->next = NULL;
    return inter;
}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here:
// O(n) traverse each node in the DLList once
void freeDLList(struct DLList *L)
{
    struct DLListNode *f_node;  //node to be free
    struct DLListNode *n_node;  //next node
    n_node = L->first;
    
    while (n_node!=NULL){
        f_node = n_node;
        n_node = n_node->next;
        free(f_node); 
    }
}


// display items of a DLList
// put your time complexity analysis for printDDList() here
// O(n) traverse each node in the DLList once
void printDLList(struct DLList *u)
{

    struct DLListNode* current_node;
    current_node = u->first;                //point to first node,
                       // printf("%d \n", current_node->value);
    while (current_node->next!=NULL){          // access every node and print it value
        printf("%d  \n", current_node->value);
        current_node = current_node->next;
    }
    printf("%d  \n", current_node->value);
}


int main()
{
 DLList *list1, *list2, *list3, *list4;

 list1=CreateDLListFromFileDlist("File1.txt");
 printDLList(list1);

 list2=CreateDLListFromFileDlist("File2.txt");
 printDLList(list2);

 list3=setUnion(list1, list2);
 printDLList(list3);

 list4=setIntersection(list1, list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 printf("please type all the integers of list1\n");
 list1=CreateDLListFromFileDlist("stdin");

 printf("please type all the integers of list2\n");
 list2=CreateDLListFromFileDlist("stdin");

 list3=cloneList(list1);
 printDLList(list3);
 list4=cloneList(list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 return 0; 
 return 0; 
}


