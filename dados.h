#ifndef DADOS_H
#define DADOS_H
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>


#define MAX_NOME 20 // tamanho maximo do nome
#define NUMTIJ 20 // numero minimo de tijolos
#define MAXTIJ 40 // numero maximo de tijolos
#define NUMFASES 3 // numero de fases
#define N_PLACAR 5 // numero de jogadores no placar de maiores pontuacoes
#define MAX 255 // tamanho da linha
#define VIDAS_INICIAL 3//numero de vidas inciais
#define VIDAS_MAX 9//numero maximo de vidas


typedef enum  // textura moldura
{
    HORIZONTAL = 205,
    VERTICAL = 186,

    SUP_ESQ = 201,
    SUP_MID = 203,
    SUP_DIR = 187,

    INF_ESQ = 200,
    INF_MID = 202,
    INF_DIR = 188,
} ASCII_MOLD;

typedef enum  // int das cores na conio
{
    VERMELHO = 4,
    VERDE = 2,
    VERDE_CLARO = 10,
    AZUL = 1,
    AZUL_CLARO = 9,
    CINZA = 7,
    MARROM = 6,
    AMARELO = 14
} CORES;

typedef enum  // poderes
{
    VIDA = 1,
    PONTOS = 2,
    PAL_MAIOR = 3,
    MAX_SORTEIO = 15,

} PODERES;

typedef enum  // teclas
{
    ESPECIAL = -32,
    SETA_ESQ = 75,
    SETA_DIR = 77,
    ESPACO   = 32,
    ENTER    = 13,
    ESC      = 27
} TECLAS;

typedef enum  // moldura
{
    XINI  = 1,
    XFIM  = 85,
    YINI  = 2,
    YFIM  = 28,
    XFIM2 = 120
} MOLDURA;

typedef enum // coords. inf. tela
{
    XPAUSAR   = 23,
    XCARREGAR = 54,
    XSAIR     = 87,

    XINF = 87,

    YPONTOS   = 4,
    YVIDAS    = 5,
    YFASE     = 6,
    YINST     = 8,

    YFIM_JOGO = 9,
    YRANK     = 15
} COORD_INF;

typedef enum // identificacao
{
    YJOGADOR = 3,
    YDISCIPLINA = 23,
    YSEMESTRE = 24,
    YNOMES = 25
} IDENTIFICACAO;

typedef enum  // valores da fase
{
    VEL_1 = 7,
    VEL_2 = 6,
    VEL_3 = 5,
    PONTOS_1 = 100,
    PONTOS_2 = 200,
    PONTOS_3 = 400,
} DADOS_FASE;

typedef enum  // valores da palheta
{
    XPAL1 = 38,
    XPAL2 = 47,
    YPAL = 25,
    VEL_PALX = 2,
    CHAR_PAL = '='
} DADOS_PALHETA;

typedef enum  // valores da bola
{
    XBOL = 43,
    YBOL = 24,
    CHAR_BOL = 'o'
} DADOS_BOLA;


typedef struct // fase
{
    int numTijolos; // quantidade de tijolos da fase
    int vel_bol; // indice para velocidade da bolinha
    int pontos; // pontos de cada tijolo da fase
    int cor0; // cor do tijolo duro intermedario
    int cor1; // cor do tijolo nao duro
} FASE;

typedef struct // coordenada
{
    int x;
    int y;
} COORDENADA;

typedef struct // bola
{
    COORDENADA vel_dir; // direcao e velocidade de deslocamento
    COORDENADA posicao; // posicao da bola no jogo
    char c; // caractere da bola
} BOLA;

typedef struct // palheta
{
    COORDENADA vel_dir; // direcao e velocidade do deslocamento
    COORDENADA ponto1; // envelope da palheta
    COORDENADA ponto2; // coordenada do canto inferior dir do envelope
    char c; // caractere da palheta
} PALHETA;

typedef struct // jogador
{
    char nome[MAX_NOME+1]; // nome do jogador
    int vidas; // vidas do jogador
    int fase; // fase que o jogador esta
    int pontos; // pontos do jogador
    short termino; // forma que acabou o jogo (1 - normal | 0 - ESC)
} JOGADOR;

typedef struct // tijolo
{
    int c; // char do tijolo
    COORDENADA ponto1; // envelope do tijolo
    COORDENADA ponto2;
    int estado; // estado do tijolo (de -1 a 1 inteiro | 2 quebrado)
    int cor; // cor do tijolo
} TIJOLO;

typedef struct // poder
{
    char c; // char do poder
    COORDENADA pos; // coordenada do poder
    short flag_pod; // flag poder (0 - nao tem | outro - sim)
} PODER;

typedef struct // pausa jogo
{
    PALHETA pal; // palheta
    BOLA bol; // bola
    TIJOLO listatijolos[MAXTIJ]; // tijolos
    JOGADOR jog; // jogador
    PODER pod; // poder
} PAUSAJOGO;

typedef struct // jogador placar
{
    char nome[MAX_NOME+1]; // nome do jogador
    int pontos; // pontos do jogador
} JOG_PLACAR;


//PROTOTIPOS
void preenche_dados (JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod);
void preenche_tijolos(JOGADOR jog, TIJOLO listatijolos[], FASE fases[]);
void pega_nome(JOGADOR *jog);
int random(int max, int min);
void printa_aviso(int cor, char erro[]);


#endif /* DADOS_H */
