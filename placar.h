#include "dados.h"


//PROTOTIPOS
void abre_arq_txt(FILE **arqtxt);
short le_arq_txt (FILE **arqtxt, JOG_PLACAR listaplacar[]);
void mostra_placar (JOGADOR *jog, JOG_PLACAR listaplacar[]);
short insere_jogador_placar (JOGADOR *jog, JOG_PLACAR listaplacar[], int *cont_placar);
void ordena_placar (JOG_PLACAR listaplacar[], int i);
void salva_placar (FILE *arq, JOG_PLACAR listaplacar[], int cont_placar);
void printa_placar (JOG_PLACAR listaplacar[], int cont_placar);
