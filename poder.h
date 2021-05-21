#include "desenha.h"


#define MULT_PONTOS 5


// PROTOTIPOS
void move_poder(JOGADOR *jog, PALHETA *pal, TIJOLO listatijolos[], FASE fases[], PODER *pod);
void sorteio_poder(PODER *pod, int x, int y);
void poder_vida(JOGADOR *jog);
void poder_pontos(JOGADOR *jog, FASE fase[]);
void poder_palheta(PALHETA *pal);
void colisao_poder_palheta(JOGADOR *jog, PALHETA *pal, FASE fases[], PODER *pod);
void colisao_poder_tijolo(JOGADOR jog, TIJOLO listatijolos[], FASE fases[], PODER pod);
void colisao_poder_chao(PODER *pod);
