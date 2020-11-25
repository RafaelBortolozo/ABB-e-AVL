#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> //necessario para limpar o terminal
#include <conio.h> //biblioteca de desenvolvimento
#include <string.h> //necessario para usar string
#define QTDCARACTERES 60

/* Aluno: Rafael Bortolozo 
   Arvore AVL
*/

typedef struct sBook{
	char name[QTDCARACTERES];
	int issn;
}Book;

typedef struct sNodo{
	struct sNodo* left;
	struct sNodo* right;
	Book* book;
	int height;
}Nodo;

Nodo* createNodo();					 			//cria nodo
Book* createBook();					 			//cria livro
Nodo* insert(Nodo* root, char* name, int issn); //insere livro
char* requestName();				 			//solicita nome do livro
int requestIssn();					 			//solicita ISSN do livro
Nodo* del(Nodo* root, int issn);	 			//delete livro
Nodo* search(Nodo* root, int issn);  			//pesquisa livro
void printSearch(Nodo* nodo);		 			//imprime pesquisa
Nodo* searchMax(Nodo* root);		 			//Procura maior elemento
void preOrder (Nodo* root);			 			//Pre-ordem
void inOrder (Nodo* root);			 			//Em-ordem
void posOrder (Nodo* root);		 	 			//Pos-ordem
Nodo* test(Nodo* root);				 			//carrega teste
Nodo* free_tree(Nodo* root);		 			//libera memoria
Nodo* rightRotate(Nodo* root);		 			//rotacao para a direita
Nodo* leftRotate(Nodo* root);		 			//rotacao para a esquerda
int max(int a, int b);				 			//retorna o maior numero
int height(Nodo* N);         		 			//retorna a altura da arvore
int getBalance(Nodo* root);			 			//retorna o fator de balanceamento
Nodo* leftRotate(Nodo* root);		 			//rotacao esquerda
Nodo* rightRotate(Nodo* root);		 			//rotacao direita

main(){
	Nodo* root= NULL;
	Nodo* aux;
	char name[QTDCARACTERES];
	int issn;
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
					strcpy(name, requestName());
					issn= requestIssn();
					system("clear||cls");
					root= insert(root, name, issn);
					printf("\tLivro cadastrado com sucesso!\n\n");
					op=0;
                    break;
			
			case 2: system("clear||cls");
					issn= requestIssn();
					system("clear||cls");
					aux=search(root, issn);
					if(aux!=NULL){
						root= del(root, issn);
						printf("\tLivro \"%d\" removido!", issn);
					}else{
						printf("\tLivro \"%d\" nao encontrado!", issn);
					}
                    op=0;
                    printf("\n\n");
					break;
                    
			case 3: system("clear||cls");
					issn= requestIssn();
					system("clear||cls");
					aux= search(root, issn);
					printSearch(aux);
					op=0;
					break;
			
			case 4: system("clear||cls");
					printf("\tPre-ordem: \n");
					preOrder(root);
					printf("\n\n");
					op=0;
					break;
			
			case 5: system("clear||cls");
					printf("\tEm-ordem: \n");
					inOrder(root);
					printf("\n\n");
					op=0;
					break;
					
			case 6: system("clear||cls");
					printf("\tPos-ordem: \n");
					posOrder(root);
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
    nodo->book = createBook();
    nodo->height=1;
    return nodo;
}

Book* createBook(){
	Book* book=(Book*)malloc(sizeof(Book));
	book->issn= NULL;
	return book;
}

Nodo* insert(Nodo *root, char* name, int issn){
    
	//Caso encontrar um espaço vazio, o nodo é inserido e finaliza o codigo
	if(root == NULL){
        Nodo* aux= createNodo();
        strcpy(aux->book->name, name);
		aux->book->issn = issn;
        return aux;
    }
    
    //caso nao foi encontrado um espaço vazio, continua a percorrer a arvore através da recursividade
    if(issn <= root->book->issn){
        root->left = insert(root->left, name, issn); //percorre a arvore atraves do insert, até encontrar um ponteiro LEFT ou RIGHT que seja NULL
    }
    
	else if(issn > root->book->issn){
	    root->right = insert(root->right, name, issn);
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
    if (balance > 1 && issn < root->left->book->issn) 
        return rightRotate(root); 
  
    // Right Right Case 
    if (balance < -1 && issn > root->right->book->issn) 
        return leftRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && issn > root->left->book->issn){ 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Left Case 
    if (balance < -1 && issn < root->right->book->issn){ 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    }
	
	return root;
}

char* requestName(){
	char name[QTDCARACTERES];
	printf("Digite o nome do livro: ");
	scanf(" %[^\n]", &name);
	return name;
}

int requestIssn(){
	int issn;
	printf("Digite o ISSN do livro: ");
	scanf("%d", &issn);
	return issn;
}

Nodo* del(Nodo* root, int issn){
	
    //procurando o elemento
    
	//avanca para a subarvore da direita 
    if (issn < root->book->issn) 
        root->left = del(root->left, issn); 
  
    //avanca para a subarvore da esquerda 
    else if(issn > root->book->issn ) 
        root->right = del(root->right, issn); 
  	
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
            root->book->issn = temp->book->issn;
			strcpy(temp->book->name, root->book->name); 
  
            //delete o dado procurado
            root->left = del(root->left, temp->book->issn); 
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

Nodo* search(Nodo* root, int issn){
	
	//se nao encontrar o livro, retorna NULL
	if(root==NULL){
		return NULL;
	} 
	
	if(root->book->issn == issn){
		return root; //se encontrou, vai retornar o elemento
	} 
	
	//se nao, percorre a arvore usando recursividade
	else if(issn <= root->book->issn){
		root=search(root->left, issn);
	}else{
		root=search(root->right, issn);
	}
	
	return root;
}

void printSearch(Nodo* nodo){
	if(nodo==NULL){
		printf("\tLivro inexistente!\n\n");
	}else{
		printf("\tLivro encontrado!\n");
		printf("\t%d- \"%s\" \n\n",nodo->book->issn, nodo->book->name);
	}
}

Nodo* searchMax(Nodo* root){
    Nodo* aux = root;
    while(aux->right != NULL){
        aux = aux->right;
    }
    return aux;
}

void preOrder (Nodo* root){
 	if(root != NULL){
	    printf("\n\t%d- \"%s\" ",root->book->issn, root->book->name);
		preOrder(root->left);
		preOrder(root->right);	    
 	}
}

void inOrder (Nodo* root){
 	if(root != NULL){
	    inOrder(root->left);
	    printf("\n\t%d- \"%s\" ",root->book->issn, root->book->name);
		inOrder(root->right);	    
 	}
}

void posOrder (Nodo* root){
 	if(root != NULL){
	    posOrder(root->left);
	    posOrder(root->right);
	    printf("\n\t%d- \"%s\" ",root->book->issn, root->book->name);
 	}
}

Nodo* test(Nodo* root){
	/*root= insert(root, 10);
	root= insert(root, 20);
	root= insert(root, 30);
	root= insert(root, 40);
	root= insert(root, 50);
	root= insert(root, 25);*/
	
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

int getBalance(Nodo* root){ 
    if (root == NULL){
    	return 0;
	}
    return height(root->left) - height(root->right); 
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
