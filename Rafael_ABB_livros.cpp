#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> //necessario para limpar o terminal
#include <conio.h> //biblioteca de desenvolvimento

typedef struct sNodo{
	struct sNodo* left;
	struct sNodo* right;
	int data;
}Nodo;

Nodo* createRoot();					 //cria raiz da arvore
void insert(Nodo* root, int data);   //insere livro
int requestData();					 //solicita codigo do livro
void del(Nodo* root, int data);		 //delete livro
Nodo* search(Nodo* root, int data);  //pesquisa livro
void printSearch(Nodo* root);		 //imprime pesquisa

main(){
	Nodo* root= createRoot();
	Nodo* aux;
	int data;
	int op=0;
	
	while(op==0){
        system("clear||cls");
		printf("\n\t*****Sistema de biblioteca*****\n\n\n");
        printf("\t1)Inserir\n");
        printf("\t2)Excluir\n");
        printf("\t3)Buscar\n");
        printf("\t4)Sair\n");
        
        scanf("%d",&op);
        switch (op){
            case 1: insert(root, data);
					printf("\n\n\n");
					op=0;
                    break;
			
			case 2: system("clear||cls");
					del(root, data);
                    op=0;
					break;
                    
			case 3: system("clear||cls");
					aux= search(root, data);
					op=0;
					break;
					
			case 4: break;
               
            default:op=0;
                    break;
        }
    }
	
}

Nodo* createRoot(){
	Nodo* root= (Nodo*)malloc(sizeof(Nodo));
	root->left=NULL;
	root->right=NULL;
	root->data=NULL;
	
	return root;
}

void insert(Nodo* root, int data){
	
}

void del(Nodo* root, int data){
	
}

Nodo* search(Nodo* root, int data){
	
}
