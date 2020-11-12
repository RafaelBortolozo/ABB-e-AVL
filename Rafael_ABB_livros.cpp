#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> //necessario para limpar o terminal
#include <conio.h> //biblioteca de desenvolvimento


/* Aluno: Rafael Bortolozo 
   Arvore binaria de busca
*/


typedef struct sNodo{
	struct sNodo* left;
	struct sNodo* right;
	int data;
}Nodo;

Nodo* createRoot();					 //cria raiz da arvore
Nodo* insert(Nodo* root, int data);  //insere livro
int requestData();					 //solicita codigo do livro
Nodo* del(Nodo* root, int data);	 //delete livro
Nodo* search(Nodo* root, int data);  //pesquisa livro
void printSearch(Nodo*);		     //imprime pesquisa
Nodo* searchMax(Nodo* root);		 //Procura maior elemento
void pre_ordem (Nodo* root);		 //Pre-ordem
void em_ordem (Nodo* root);			 //Em-ordem
void pos_ordem (Nodo* root);		 //Pos-ordem
Nodo* test(Nodo* root);				 //carrega teste

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
        printf("\t4)Pre-ordem\n");
        printf("\t5)Em-ordem\n");
        printf("\t6)Pos-ordem\n");
        printf("\t7)TEST\n");
        printf("\t8)Sair\n");
        
        scanf("%d",&op);
        switch (op){
            case 1: system("clear||cls");
					data= requestData();
					system("clear||cls");
					root= insert(root, data);
					printf("\tLivro cadastrado com sucesso!\n\n");
					printf("\tRaiz da arvore: %d \n\n", root->data);
					op=0;
                    break;
			
			case 2: system("clear||cls");
					data= requestData();
					system("clear||cls");
					root= del(root, data);
					if(root!=NULL){
						printf("\tLivro \"%d\" removido com sucesso!\n\n", data);
					}else{
						printf("delete Error", data);
					}
                    op=0;
					break;
                    
			case 3: system("clear||cls");
					data= requestData();
					system("clear||cls");
					aux= search(root, data);
					printSearch(aux);
					op=0;
					break;
			
			case 4: system("clear||cls");
					printf("Pre-ordem: \n\n");
					pre_ordem(root);
					op=0;
					break;
			
			case 5: system("clear||cls");
					printf("Em-ordem: \n\n");
					em_ordem(root);
					op=0;
					break;
					
			case 6: system("clear||cls");
					printf("Pos-ordem: \n\n");
					pos_ordem(root);
					op=0;
					break;
					
			case 7: system("clear||cls");
					printf("Teste carregado! \n\n");
					root= test(root);
					op=0;
					break;		
			
			case 8: break;
               
            default:system("clear||cls");
					op=0;
                    break;
        }
    }
}

Nodo* createRoot(){	
	return NULL;
}

Nodo* insert(Nodo *root, int data){
    
	//Caso encontrar um espa�o vazio, o nodo � inserido e finaliza o codigo
	if(root == NULL){
        root=(Nodo*)malloc(sizeof(Nodo));
        root->data = data;
        root->left = NULL;
        root->right = NULL;
    }
    
    //caso nao foi encontrado um espa�o vazio, continua a percorrer a arvore atrav�s da recursividade
    else if(data <= root->data){
        root->left = insert(root->left, data); //percorre a arvore atraves do insert, at� encontrar um ponteiro LEFT ou RIGHT que seja NULL
    }
    
	else{
        root->right = insert(root->right, data);
    }
    
	return root;
}

Nodo* del(Nodo* root, int data){
	
	if(root != NULL){
		if(data > root->data){
			root->right = del(root, data);
		}else if(data < root->data){
			root->left = del(root, data);
		}else{
			//elemento encontrado
			//nodo com 0 filho
			if(root->left==NULL && root->right==NULL){
				free(root);
				return NULL;
			}
			
			//nodo com 1 filho
			else if(root->left==NULL){
				Nodo* aux= root->right;
				free(root);
				return aux;
			}else if(root->right==NULL){
				Nodo* aux= root->left;
				free(root);
				return aux;
			}
			
			//nodo com 2 filhos
			else{
				Nodo* aux= searchMax(root->left);
				root->data= aux->data;
				root->left= del(root->left, aux->data);
			}
		}
		return root;
	}
	return NULL;
}

Nodo* search(Nodo* root, int data){
	
	//se nao encontrar o livro, retorna NULL
	if(root==NULL){
		return NULL;
	} 
	
	if(root->data == data){
		return root; //se encontrou, vai retornar o elemento
	} 
	
	//se nao, percorre a arvore usando recursividade
	else if(data <= root->data){
		root=search(root->left, data);
	}else{
		root=search(root->right, data);
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
	if(nodo==NULL){
		printf("\tLivro inexistente!\n\n");
	}else{
		printf("\tLivro \"%d\" encontrado!\n\n", nodo->data);
	}
}

Nodo* searchMax(Nodo* root){
    if(root != NULL){
        Nodo* aux = root;
        while(aux->right != NULL){
            aux = aux->right;
        }
        return aux;
    }
	return NULL;  
}

void pre_ordem (Nodo* root){
 	if(root != NULL){
	    printf("%d ",root->data);
		pre_ordem(root->left);
		pre_ordem(root->right);	    
 	}
}

void em_ordem (Nodo* root){
 	if(root != NULL){
	    em_ordem(root->left);
	    printf("%d ",root->data);
		em_ordem(root->right);	    
 	}
}

void pos_ordem (Nodo* root){
 	if(root != NULL){
	    pos_ordem(root->left);
	    pos_ordem(root->right);
	    printf("%d ",root->data);
 	}
}

Nodo* test(Nodo* root){
	//insere 5,12,2,7,3,1,10,8,9,4,6,11
	//remove 11,8,12,5
	
	root= insert(root, 5);
	root= insert(root, 12);
	root= insert(root, 2);
	root= insert(root, 7);
	root= insert(root, 3);
	root= insert(root, 1);
	root= insert(root, 10);
	root= insert(root, 8);
	root= insert(root, 9);
	root= insert(root, 4);
	root= insert(root, 6);
	root= insert(root, 11);
	
	root= del(root, 11);
	root= del(root, 8);
	root= del(root, 12);
	root= del(root, 5);
	
	return root;
}
