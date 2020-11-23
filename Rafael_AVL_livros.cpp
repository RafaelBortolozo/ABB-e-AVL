#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> //necessario para limpar o terminal
#include <conio.h> //biblioteca de desenvolvimento

/* Aluno: Rafael Bortolozo 
   Arvore AVL
*/

typedef struct sNodo{
	struct sNodo* left;
	struct sNodo* right;
	int data;
	int height;
}Nodo;

Nodo* createNodo();					 //cria nodo
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
Nodo* free_tree(Nodo* root);		 //libera memoria
Nodo* rightRotate(Nodo* root);		 //rotacao para a direita
Nodo* leftRotate(Nodo* root);		 //rotacao para a esquerda
int max(int a, int b);				 //retorna o maior numero
int height(Nodo* N);         		 //retorna a altura da arvore
int getBalance(Nodo* node);			 //retorna o fator de balanceamento
Nodo* leftRotate(Nodo* x);			 //rotacao esquerda
Nodo* rightRotate(Nodo* y);			 //rotacao direita

main(){
	Nodo* root= NULL;
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
        printf("\t7)Limpar sistema\n");
        printf("\t8)TEST\n");
        printf("\t9)Sair\n");
        
        scanf("%d",&op);
        switch (op){
            case 1: system("clear||cls");
					data= requestData();
					system("clear||cls");
					root= insert(root, data);
					printf("\tLivro cadastrado com sucesso!\n\n");
					op=0;
                    break;
			
			case 2: system("clear||cls");
					data= requestData();
					system("clear||cls");
					aux=search(root, data);
					if(aux!=NULL){
						root= del(root, data);
						printf("\tLivro \"%d\" removido!", data);
					}else{
						printf("\tLivro nao encontrado!", data);
					}
                    op=0;
                    printf("\n\n");
					break;
                    
			case 3: system("clear||cls");
					data= requestData();
					system("clear||cls");
					aux= search(root, data);
					printSearch(aux);
					op=0;
					break;
			
			case 4: system("clear||cls");
					printf("\tPre-ordem: ");
					pre_ordem(root);
					printf("\n\n");
					op=0;
					break;
			
			case 5: system("clear||cls");
					printf("\tEm-ordem: ");
					em_ordem(root);
					printf("\n\n");
					op=0;
					break;
					
			case 6: system("clear||cls");
					printf("\tPos-ordem: ");
					pos_ordem(root);
					printf("\n\n");
					op=0;
					break;
					
			case 7: system("clear||cls");
					printf("Tem certeza que deseja excluir todos os livros? (1-SIM, 2-NAO)\n");
					scanf("%d", &op);
					system("clear||cls");
					if(op==1){
						root=free_tree(root);
						printf("\tTodos os livros foram excluidos!\n\n");
					} 
					op=0;
					break;
					
			case 8: system("clear||cls");
					root= test(root);
					printf("\tTeste carregado! \n\n");
					op=0;
					break;		
			
			case 9: root=free_tree(root);
					break;
               
            default:system("clear||cls");
					op=0;
                    break;
        }
    }
}

Nodo* createNodo(){
	Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->left = NULL;
    nodo->right = NULL;
    nodo->data = NULL;
    nodo->height=1;
    return nodo;
}

Nodo* insert(Nodo *root, int data){
    
	//Caso encontrar um espaço vazio, o nodo é inserido e finaliza o codigo
	if(root == NULL){
        Nodo* aux= createNodo();
        aux->data = data;
        return aux;
    }
    
    //caso nao foi encontrado um espaço vazio, continua a percorrer a arvore através da recursividade
    if(data <= root->data){
        root->left = insert(root->left, data); //percorre a arvore atraves do insert, até encontrar um ponteiro LEFT ou RIGHT que seja NULL
    }
    
	else if(data > root->data){
	    root->right = insert(root->right, data);
	}
	
	else{
		return root;
	}
	
	//apos a insercao...
	//atualiza altura dos nodos
	root->height = 1 + max(height(root->left), height(root->right));
	
	//obtem o fator de balanceamento do nodo
	int balance= getBalance(root);
	
	
	//se nao for balanceado, sera aplicado a rotacao adequada
	// Left Left Case 
    if (balance > 1 && data < root->left->data) 
        return rightRotate(root); 
  
    // Right Right Case 
    if (balance < -1 && data > root->right->data) 
        return leftRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && data > root->left->data){ 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Left Case 
    if (balance < -1 && data < root->right->data){ 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    }
	
	return root;
}

int requestData(){
	int data;
	printf("Digite o codigo do livro\n");
	scanf("%d", &data);
	return data;
}

Nodo* del(Nodo* root, int data){
	
    //procurando o elemento
    
	//avanca para a subarvore da direita 
    if (data < root->data) 
        root->left = del(root->left, data); 
  
    //avanca para a subarvore da esquerda 
    else if( data > root->data ) 
        root->right = del(root->right, data); 
  	
  	//elemento encontrado
    else{ 
    	
        //nodo com apenas 1 filho ou nenhum
        if((root->left == NULL) || (root->right == NULL)){ 
            Nodo *temp = root->left ? root->left : root->right; 
  
            //nenhum filho 
            if (temp == NULL){ 
                temp = root; 
                root = NULL; 
            }
			
			//apenas 1 filho
			else{
				*root = *temp;
			} 
			 
            free(temp); 
        } 
        
		else{ 
            //nodo com 2 filhos, procura o maior elemento da subarvore da esquerda 
            Nodo* temp = searchMax(root->left); 
  
            //faz uma copia do dado recem-procurado, passando para o root
            root->data = temp->data; 
  
            //delete o dado procurado
            root->left = del(root->left, temp->data); 
        } 
    } 
  
    //se a arvore ficou vazia, entao retorne 
    if (root == NULL) 
      return root; 
  
    //atualiza altura dos nodos
    root->height = 1 + max(height(root->left), height(root->right)); 
  
    //obtem o fator de balanceamento do nodo
    int balance = getBalance(root); 
  
   	//se nao for balanceado, sera aplicado a rotacao adequada 
    // Left Left Case 
    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && getBalance(root->left) < 0){ 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0){ 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 

    return root; 
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

void printSearch(Nodo* nodo){
	if(nodo==NULL){
		printf("\tLivro inexistente!\n\n");
	}else{
		printf("\tLivro \"%d\" encontrado!\n\n", nodo->data);
	}
}

Nodo* searchMax(Nodo* root){
    Nodo* aux = root;
    while(aux->right != NULL){
        aux = aux->right;
    }
    return aux;
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
	root= insert(root, 10);
	root= insert(root, 20);
	root= insert(root, 30);
	root= insert(root, 40);
	root= insert(root, 50);
	root= insert(root, 25);
	
	/*root= insert(root, 5);
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
	root= del(root, 5);*/
	
	return root;
}

Nodo* free_tree(Nodo* root){
	//algoritmo do pos_ordem
	//free() no lugar de printf()
	if(root != NULL){
	    free_tree(root->left);
	    free_tree(root->right);
	    free(root);
 	}
 	return NULL;
}

int max(int a, int b){
	return (a > b)? a : b;
}

int height(Nodo* node){
	if (node == NULL){
		return 0;
	}  
    return node->height;
} 

int getBalance(Nodo* node){ 
    if (node == NULL){
    	return 0;
	}
    return height(node->left) - height(node->right); 
} 

Nodo* rightRotate(Nodo *root){ 
    Nodo *x = root->left; 
    Nodo *T2 = x->right; 
  
    //rotacao
    x->right = root; 
    root->left = T2; 
  
    //atualiza alturas 
    root->height =1+ max(height(root->left), height(root->right)); 
    x->height =1+ max(height(x->left), height(x->right)); 
  
    //retorna o novo root 
    return x; 
}

Nodo* leftRotate(Nodo *root){ 
    Nodo *y = root->right; 
    Nodo *T2 = y->left; 
  
    //rotacao 
    y->left = root; 
    root->right = T2; 
  
    //atualiza alturas 
    root->height =1+ max(height(root->left), height(root->right)); 
    y->height =1+ max(height(y->left), height(y->right)); 
  
    //retorna o novo root  
    return y; 
} 
