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
Nodo* insert(Nodo* root, int data);  //insere livro
int requestData();					 //solicita codigo do livro
Nodo* del(Nodo* root, int data);	 //delete livro
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
						printf("\tERRO, o livro \"%d\" nao existe!\n\n", data);
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
					
			case 4: break;
               
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
    
	//Caso encontrar um espaço vazio, o nodo é inserido e finaliza o codigo
	if(root == NULL){
        root=(Nodo*)malloc(sizeof(Nodo));
        root->data = data;
        root->left = NULL;
        root->right = NULL;
    }
    
    //caso nao foi encontrado um espaço vazio, continua a percorrer a arvore através da recursividade
    else if(data <= root->data){
        root->left = insert(root->left, data); //percorre a arvore atraves do insert, até encontrar um ponteiro LEFT ou RIGHT que seja NULL
    }
    
	else{
        root->right = insert(root->right, data);
    }
    
	return root;
}

Nodo* del(Nodo* root, int data){
	
	/*Nodo* nodo= search(root, data);
	Nodo* aux;
	
	if((root==NULL) || (nodo==NULL)){
		return NULL;
	}
	
	//se o nodo nao tem filhos, entao ele eh removido e termina o codigo
	if((nodo->left == NULL) && (nodo->right == NULL)){
		free(nodo);
    }else{
    	
		//se houver algum filho, o nodo eh deletado e o filho passa a ocupar o lugar dele 
		if(nodo->right == NULL){
	        aux = nodo;
	        printf("%d ", aux->data);
	        nodo = nodo->left;
	        printf("%d ", nodo->data);
	        free(aux);
	        printf("%d ", aux->data);
	        getch();
    	}
    	
		else if(nodo->left == NULL){
		    aux = nodo;
		    nodo = nodo->right;
		    free(aux);
    	}
		
		//se tiver os 2 filhos, procura-se o elemento mais a direita, na sub-arvore da esquerda
		else{
		    aux = nodo->left;
		    while(aux->right != NULL){
		        aux=aux->right;
        	}
        	
        	//troca de valores
        	nodo->data = aux->data;
        	aux->data=data;
        	nodo->left= del(nodo->left, data);
    	}
	}
	return root;*/
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
