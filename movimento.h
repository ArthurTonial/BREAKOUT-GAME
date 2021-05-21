#include "desenha.h"


//PROTOTIPOS
void move_palheta (PALHETA *pal, char tecla);
void posicao_partida(PALHETA *pal, BOLA *bol);
void move_bola (JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod);
short testa_colisao (int x1Obj1, int x2Obj1, int y1Obj1, int y2Obj1, int x1Obj2, int x2Obj2, int y1Obj2, int y2Obj2);
void colisao_bola_palheta(PALHETA pal, BOLA *bol);
void colisao_bola_paredes(BOLA *bol);
void colisao_bola_face_tij(JOGADOR *jog, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod);
void colisao_bola_dir_tij(JOGADOR *jog, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod);
void colisao_bola_esq_tij(JOGADOR *jog, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod);
void colisao_bola_teto_chao(JOGADOR *jog, PALHETA *pal, BOLA *bol, PODER *pod);
void move_bola_horizontal(PALHETA pal, BOLA *bol, char tecla);
void resolve_tijolo(JOGADOR *jog, TIJOLO listatijolos[], FASE fases[], PODER *pod, int i);

