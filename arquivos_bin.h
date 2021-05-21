#include "desenha.h"


//PROTOTIPOS
void pausa (PALHETA pal, BOLA bol, TIJOLO listatijolos[], JOGADOR *jog, PAUSAJOGO *p_jogo, PODER *pod, char *tecla);
int salva(PAUSAJOGO p_jogo, char nome[]);
int le_jogo(PAUSAJOGO *p_jogo, char nome[]);
void instancia_jogo (PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], JOGADOR *jog, FASE fases[], PODER *pod, PAUSAJOGO pausa);

