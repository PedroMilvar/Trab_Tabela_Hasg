struct termo{
  char port[30];
  char engl[30];
};

typedef struct termo Termo;

struct tabelaHs {
    int tamanho;
  int qtde;
    Termo **tab;
};


typedef struct tabelaHs TabelaHs;

TabelaHs *criar (int tam);
void inserir(TabelaHs *tabTermos, char *ptChave, char *enValor);
char *buscar(TabelaHs *hashtable, char *key);
void percursoTh(TabelaHs *tabTermos);
void liberaTh(TabelaHs *tabTermos);
int getColisao();
int getIguais();