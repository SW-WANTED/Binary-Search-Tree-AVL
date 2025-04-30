typedef struct avl AVL;

void inserirNo(AVL **raiz, int chave);
void removerNo(AVL **raiz, int chave);
void imprimirNivel(AVL *raiz, int nivel);
AVL *pesquisarNo(AVL *raiz, int chave);
int somarSubarvoreEsquerda(AVL *raiz);
int encontrarMaior(AVL *raiz, int n, int *encontrado);