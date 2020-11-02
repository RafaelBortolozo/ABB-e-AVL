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
void printSearch(Nodo*);		     //imprime pesquisa

main(){
	Nodo* root= createRoot();
	Nodo* aux;
	int data;
	int op=0;
	
	while(op==0){
		printf("\n\t*****Sistema de biblioteca*****\n\n\n");
        printf("\t1)Inserir\n");
        printf("\t2)Excluir\n");
        printf("\t3)Buscar\n");
        printf("\t4)Sair\n");
        
        scanf("%d",&op);
        switch (op){
            case 1: system("clear||cls");
					data= requestData();
					system("clear||cls");
					insert(root, data);
					
					printf("%d", root->data);
					getch();
					printf("\tLivro cadastrado com sucesso!\n\n");
					op=0;
                    break;
			
			case 2: system("clear||cls");
					data= requestData();
					system("clear||cls");
					del(search(root, data), data);
					printf("\tLivro removido com sucesso!\n\n");
                    op=0;
					break;
                    
			case 3: system("clear||cls");
					data= requestData();
					system("clear||cls");
					aux= search(root, data);
					printSearch(aux);
					op=0;
					break;
					
			case 4: break;
               
            default:system("clear||cls");
					op=0;
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
	Nodo* new_nodo= createRoot();
	new_nodo->data=data;
	
	//insercao do primeiro elemento da arvore
	if(root->data==NULL){
		root=new_nodo;
		return;
	}
	
	//se existir elemento(s) na arvore, percorre ela
	//ate achar um local para adicionar o new_nodo
	else{
		for(;;){
			if(data <= root->data){
				if(root->left==NULL){
					root->left=new_nodo;
					return;
				}else{
					root= root->left;
				}
			}else{
				if(root->right==NULL){
					root->right=new_nodo;
					return;
				}else{
					root= root->right;
				}
			}
		}
	}
	
}

void del(Nodo* root, int data){
	
}

Nodo* search(Nodo* root, int data){
	
	//se nao encontrar o livro, retorna NULL
	if(root->data==NULL) return NULL;
	
	//se encontrou, vai retornar o elemento no final do codigo
	if(root->data == data);
	
	//percorre a arvore usando recursividade
	else if(data <= root->data){
		root->left= search(root->left, data);
	}else{
		root->right= search(root->right, data);
	}
	
	return root;
}

int requestData(){
	int data;
	printf("Digite o codigo do livro\n");
	scanf("%d", &data);
	return data;
}

void printSearch(Nodo* nodo){
	if(nodo!=NULL){
		printf("\tLivro codigo: %d, encontrado!\n\n", nodo->data);
	}else{
		printf("\tLivro inexistente!\n\n");
	}
}
