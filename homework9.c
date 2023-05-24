/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int deleteBothSide(Node * ptr);//양쪽 자식 노드 할당해제하는 함수
int freeBST(Node* head); /* free all memories allocated to the tree */
/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);
        //명령받기

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); //트리 초기화
			break;
		case 'q': case 'Q':
			freeBST(head); //트리 전체 할당해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);//값 받아서
			insert(head, key);//적절한 위치에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);//값 받아서
			deleteLeafNode(head, key);//일치하는 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);//값 받아서
			ptr = searchIterative(head, key);//일치하는 노드를 반복구조로 찾기
			if(ptr != NULL)//일치하는 노드가 있으면
				printf("\n node [%d] found at %p\n", ptr->key, ptr);//위치 출력
			else//없으면
				printf("\n Cannot find the node [%d]\n", key);//출력
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);//값 받아서
			ptr = searchRecursive(head->left, key);//일치하는 노드를 재귀구조로 찾기
			if(ptr != NULL)//일치 노드 있으면
				printf("\n node [%d] found at %p\n", ptr->key, ptr);//위치 출력
			else//없으면
				printf("\n Cannot find the node [%d]\n", key);//출력
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);//중위순회로 트리 출력
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);//전위순회로 트리 출력
			break;
		case 't': case 'T':
			postorderTraversal(head->left);//후위순회로 트리출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            //정의되지 않은 입력시 에러 메세지
			break;
		}

	}while(command != 'q' && command != 'Q');//종료 명령시 종료

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
    if( ptr!= NULL){//ptr이 NULL이 아닌 동안 반복

        inorderTraversal(ptr->left);//왼쪽 자식 노드로 재귀호출
        printf("[%d] ", ptr->key);//현재 노드 값 출력
        inorderTraversal(ptr->right);//오른쪽 자식 노드로 재귀호출
        
    }

}

void preorderTraversal(Node* ptr)
{
    if( ptr!= NULL){//ptr이 NULL이 아닌 동안 반복
        printf("[%d] ", ptr->key);//현재 노드 값 출력
        preorderTraversal(ptr->left);//왼쪽 자식 노드로 재귀호출
        preorderTraversal(ptr->right);//오른쪽 자식 노드로 재귀호출
        
    }
}

void postorderTraversal(Node* ptr)
{

    if( ptr!= NULL){//ptr이 NULL이 아닌 동안 반복

        postorderTraversal(ptr->left);//왼쪽 자식 노드로 재귀호출
        postorderTraversal(ptr->right);//오른쪽 자식 노드로 재귀호출
        printf("[%d] ", ptr->key);//현재 노드 값 출력

        
    }
}


int insert(Node* head, int key)
{
    Node* cur = head;//현재 노드를 가리킬 포인터
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    //새로운 노드 동적할당 및 초기화

    if(head->left == NULL) {head->left = newNode; return 0;}//만약 트리가 비어 있으면 새 노드를 헤드 왼쪽에 연결

    else {//아니면
        cur = cur->left; //현재 노드를 왼쪽 자식 노드로
    }
    
    while(cur->left != NULL || cur->right != NULL){//현재노드가 리프노드가 아닐 동안 반복
        if(key < cur->key)  {//만약 현재노드값보다 입력값이 작으면
            if(cur->left == NULL) break;//만약 현재노드 왼쪽 자식이 비어 있으면 반복종료
            cur = cur->left;//현재노드를 왼쪽 자식노드로
        }

        else if( key > cur->key){//현재노드보다 입력값이 크면
            if(cur->right == NULL) break;//만약 현재노드 오른쪽 자식이 비어 있으면 반복종료
            cur = cur->right;//현재 노드를 오른쪽 자식노드로
        }

        else {printf("값 중복\n\n"); return 1;}//값 중복이면 에러 메세지 출력
    }

    if(key < cur->key)  cur->left = newNode;//만약 입력값이 현재노드값보다 작으면 새 노드를 현재노드의 왼쪽 자식으로 연결
    else if(key > cur->key)  cur->right = newNode;//만약 입력값이 현재노드값보다 크면 새 노드를 현재노드의 오른족 자식으로 연결

}

int deleteLeafNode(Node* head, int key){
    if(head->left == NULL) return 0;//트리 비어 있으면 종료

    Node* cur = head->left;//현재노드를 가리키는 포인터에 루트노드
    Node* back = NULL;//뒤 노드에 널

    while(cur->left != NULL || cur->right != NULL){//현재노드가 리프노드가 아닐 동안 반복


        if(key < cur->key){//만약 입력값이 현재노드값보다 작으면
            back = cur;//뒤노드를 현재노드로
            cur = cur->left; //현재노드를 왼쪽 자식 노드로
            if(cur->key < key){ printf("일치값 없음\n\n"); return 0;}//만약 일치값이 없으면 출력하고 함수종료
        }

        else if( key > cur->key){//만약 입력값이 현재노드값보다 크면
            back = cur;//뒤노드를 현재노드로
            cur = cur->right;//현재노드를 왼쪽 자식 노드로
             if(cur->key > key){ printf("일치값 없음\n\n"); return 0;}//만약 일치값이 없으면 출력하고 함수종료
        }

        else if( key == cur->key) break; //입력값과 현재노드값 일치시 반복종료
    }

    if(cur->left != NULL || cur->right != NULL) printf("[%d]는 리프노드가 아닙니다.", key); //현재노드가 리프노드 아닐시 출력


    //현재노드가 뒷노드의 왼쪽 자식인지 오른쪽 자식인지 판별후 현재 노드 할당해제 하고, 뒷노드의 좌 혹은 우 자식 포인터에 NULL
    else if(back->left == cur){
        free(cur);
        back->left = NULL;
    }
    else if( back->right == cur){
        free(cur);
        back->right = NULL;
    }


    return 0;
}

Node* searchRecursive(Node* ptr, int key)
{

    Node * temp = NULL;//노드 포인터
    
    if(key < ptr->key) temp = searchRecursive(ptr->left, key);//입력값이 현재 노드값보다 작으면 왼쪽 자식으로 재귀호출 해서 temp에
    else if (key > ptr->key) temp = searchRecursive(ptr->right, key);//입력값이 현재 노드값보다 크면 오른쪽 자식으로 재귀호출 해서 temp에
    else if(key == ptr->key) temp = ptr;//일치하면 temp에 현재 위치
    
    return temp;//temp 반환

}

Node* searchIterative(Node* head, int key)
{
    
    Node* cur = head->left;//현재 노드에 루트노드 주소


     while(cur != NULL){//현재노드가 NULL이 아닐 동안 반복

        if(cur->key == key) return cur;//만약 현재노드값과 입력값 일치시 현재 노드 반환

        if(key < cur->key){//입력값이 현재노드값보다 작으면
            cur = cur->left;        //현재노드를 왼쪽 자식 노드로
            if(cur->key < key) return NULL;//만약 옮긴 현재 노드값이 입력값보다 작으면 NULL반환 = 일치 노드 없음
        }

        else if( key > cur->key){//입력값이 현재노드값보다 크면
            cur = cur->right;//현재노드를 오른쪽 자식 노드로
             if(cur->key > key) return NULL;//만약 옮긴 현재 노드값이 입력값보다 크면 NULL반환 = 일치 노드 없음
       }
    }


    return NULL;

}


int deleteBothSide(Node * ptr){
    Node* left;//왼쪽
    Node * right;//오른쪽

    if(ptr == NULL) return 0;

    left = ptr->left;//왼쪽에 ptr의 왼쪽 자식
    right = ptr->right;//오른쪽에 ptr의 오른쪽 자식

    free(ptr);//ptr 할당해제

    if(left == NULL && right == NULL) return 1;//만약 ptr이 리프노드였다면 함수 종료

    deleteBothSide(left);//왼쪽 자식으로 재귀호출
    deleteBothSide(right);//오른쪽 자식으로 재귀호출


}




int freeBST(Node* head)
{
    deleteBothSide(head->left);//양쪽 삭제 함수에 루트노드 전달
    head = NULL;//헤드노드에 널
}
