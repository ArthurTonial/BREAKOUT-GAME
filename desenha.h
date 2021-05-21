#ifndef DESENHA_H
#define DESENHA_H
#include "dados.h"
#include "movimento.h"
#include "poder.h"


//PROTOTIPOS
void desenha_palheta (PALHETA pal);
void desenha_bolinha (BOLA bol);
void desenha_moldura ();
void desenha_menu ();
void desenha_tijolo (TIJOLO tij);
void desenha_tijolos (TIJOLO listatijolos[], JOGADOR jog, FASE fases[]);
void desenha_tela (JOGADOR jog, PALHETA pal, BOLA bol, TIJOLO listatijolos[], FASE fases[]);
void desenha_poder (PODER pod);
void escreve_informacoes (JOGADOR jog);
void hidecursor ();
void destroi_tijolo (JOGADOR *jog, TIJOLO listatijolos[], FASE fases[],  PODER *pod, int indicetijolo);
void pontos_jogador(JOGADOR jog);
void vidas_jogador(JOGADOR jog);
void escreve_instrucoes();
void apaga_instrucoes();



#endif /* DESENHA_H */
