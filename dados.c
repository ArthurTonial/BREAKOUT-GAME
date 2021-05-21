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
    AMARELO = 14,
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


// funcao para preencher dados das estruturas
void preenche_dados(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod)
{
    srand(time(NULL));

    // zera flag de poder
     pod->flag_pod = 0;

    // preenche o arranjo de fases
    fases[0] = (FASE){NUMTIJ   , VEL_1, PONTOS_1,        AZUL,  AZUL_CLARO};
    fases[1] = (FASE){NUMTIJ+10, VEL_2, PONTOS_2, VERDE_CLARO,       CINZA};
    fases[2] = (FASE){NUMTIJ+20, VEL_3, PONTOS_3,      MARROM,     AMARELO};

    // preenche as informacoes do jogador, palheta e bola
    *jog = (JOGADOR){"Guest", VIDAS_INICIAL, 0, 0, 0};
    *pal = (PALHETA){{VEL_PALX,0}, {XPAL1, YPAL}, {XPAL2, YPAL}, CHAR_PAL};
    *bol = (BOLA){{pow(-1, random(0, 1)),-1}, {XBOL, YBOL}, CHAR_BOL};
}

// funcao para preencher arranjo de tijolos com os adequados da fase
void preenche_tijolos(JOGADOR jog, TIJOLO listatijolos[], FASE fases[])
{
    // arranjos de tijolos de cada fase
    TIJOLO fase1[NUMTIJ] =  {{'#', { 9, 7}, {13, 8},  0,       BLUE}, {'#', {16, 7}, {20, 8},  1, LIGHTBLUE},
                             {'#', {23, 7}, {27, 8},  1,  LIGHTBLUE}, {'#', {30, 7}, {34, 8},  1, LIGHTBLUE},
                             {'#', {37, 7}, {41, 8}, -1,  LIGHTCYAN}, {'#', {44, 7}, {48, 8}, -1, LIGHTCYAN},
                             {'#', {51, 7}, {55, 8},  1,  LIGHTBLUE}, {'#', {58, 7}, {62, 8},  1, LIGHTBLUE},
                             {'#', {65, 7}, {69, 8},  1,  LIGHTBLUE}, {'#', {72, 7}, {76, 8},  0,      BLUE},
                             {'#', { 9,13}, {13,14},  0,       BLUE}, {'#', {16,13}, {20,14},  1, LIGHTBLUE},
                             {'#', {23,13}, {27,14},  1,  LIGHTBLUE}, {'#', {30,13}, {34,14},  1, LIGHTBLUE},
                             {'#', {37,13}, {41,14}, -1,  LIGHTCYAN}, {'#', {44,13}, {48,14}, -1, LIGHTCYAN},
                             {'#', {51,13}, {55,14},  1,  LIGHTBLUE}, {'#', {58,13}, {62,14},  1, LIGHTBLUE},
                             {'#', {65,13}, {69,14},  1,  LIGHTBLUE}, {'#', {72,13}, {76,14},  0,      BLUE},};

    TIJOLO fase2[NUMTIJ+10]={{'#', { 7, 5}, {11, 6},  0, LIGHTGREEN}, {'#', {75, 5}, {79, 6},  0, LIGHTGREEN},
                             {'#', {12, 6}, {16, 7},  1,  LIGHTGRAY}, {'#', {70, 6}, {74, 7},  1,  LIGHTGRAY},
                             {'#', {17, 7}, {21, 8},  1,  LIGHTGRAY}, {'#', {65, 7}, {69, 8},  1,  LIGHTGRAY},
                             {'#', {22, 8}, {26, 9},  1,  LIGHTGRAY}, {'#', {60, 8}, {64, 9},  1,  LIGHTGRAY},
                             {'#', {27, 9}, {31,10},  1,  LIGHTGRAY}, {'#', {55, 9}, {59,10},  1,  LIGHTGRAY},
                             {'#', {32,10}, {36,11},  0, LIGHTGREEN}, {'#', {50,10}, {54,11},  0, LIGHTGREEN},
                             {'#', {37,11}, {41,12}, -1,      GREEN}, {'#', {45,11}, {49,12}, -1,      GREEN},
                             {'#', { 7,17}, {11,18},  0, LIGHTGREEN}, {'#', {75,17}, {79,18},  0, LIGHTGREEN},
                             {'#', {12,16}, {16,17},  1,  LIGHTGRAY}, {'#', {70,16}, {74,17},  1,  LIGHTGRAY},
                             {'#', {17,15}, {21,16},  1,  LIGHTGRAY}, {'#', {65,15}, {69,16},  1,  LIGHTGRAY},
                             {'#', {22,14}, {26,15},  1,  LIGHTGRAY}, {'#', {60,14}, {64,15},  1,  LIGHTGRAY},
                             {'#', {27,13}, {31,14},  1,  LIGHTGRAY}, {'#', {55,13}, {59,14},  1,  LIGHTGRAY},
                             {'#', {32,12}, {36,13},  0, LIGHTGREEN}, {'#', {50,12}, {54,13},  0, LIGHTGREEN},
                             {'#', {41, 5}, {45, 6}, -1,      GREEN}, {'#', {41,17}, {45,18}, -1,      GREEN},
                             {'#', { 7,11}, {11,12}, -1,      GREEN}, {'#', {75,11}, {79,12}, -1,      GREEN},};

    TIJOLO fase3[NUMTIJ+20]={{'#', { 5, 5}, { 9, 6}, -1,        RED}, {'#', {17, 5}, {21, 6},  0,      BROWN},
                             {'#', {29, 5}, {33, 6}, -1,        RED}, {'#', {41, 5}, {45, 6},  0,      BROWN},
                             {'#', {53, 5}, {57, 6}, -1,        RED}, {'#', {65, 5}, {69, 6},  0,      BROWN},
                             {'#', {77, 5}, {81, 6}, -1,        RED}, {'#', {12, 7}, {16, 8},  1,     YELLOW},
                             {'#', {22, 7}, {26, 8},  1,     YELLOW}, {'#', {36, 7}, {40, 8},  1,     YELLOW},
                             {'#', {46, 7}, {50, 8},  1,     YELLOW}, {'#', {60, 7}, {64, 8},  1,     YELLOW},
                             {'#', {70, 7}, {74, 8},  1,     YELLOW}, {'#', { 5, 9}, { 9,10}, -1,        RED},
                             {'#', {17, 9}, {21,10},  0,      BROWN}, {'#', {29, 9}, {33,10}, -1,        RED},
                             {'#', {41, 9}, {45,10},  0,      BROWN}, {'#', {53, 9}, {57,10}, -1,        RED},
                             {'#', {65, 9}, {69,10},  0,      BROWN}, {'#', {77, 9}, {81,10}, -1,        RED},
                             {'#', { 5,13}, { 9,14}, -1,        RED}, {'#', {17,13}, {21,14},  0,      BROWN},
                             {'#', {29,13}, {33,14}, -1,        RED}, {'#', {41,13}, {45,14},  0,      BROWN},
                             {'#', {53,13}, {57,14}, -1,        RED}, {'#', {65,13}, {69,14},  0,      BROWN},
                             {'#', {77,13}, {81,14}, -1,        RED}, {'#', {12,15}, {16,16},  1,     YELLOW},
                             {'#', {22,15}, {26,16},  1,     YELLOW}, {'#', {36,15}, {40,16},  1,     YELLOW},
                             {'#', {46,15}, {50,16},  1,     YELLOW}, {'#', {60,15}, {64,16},  1,     YELLOW},
                             {'#', {70,15}, {74,16},  1,     YELLOW}, {'#', { 5,17}, { 9,18}, -1,        RED},
                             {'#', {17,17}, {21,18},  0,      BROWN}, {'#', {29,17}, {33,18}, -1,        RED},
                             {'#', {41,17}, {45,18},  0,      BROWN}, {'#', {53,17}, {57,18}, -1,        RED},
                             {'#', {65,17}, {69,18},  0,      BROWN}, {'#', {77,17}, {81,18}, -1,        RED},};
    int i; //iterador de for

    // switch pra ver qual array copiar
    switch(jog.fase)
    {
    case 0:
        for(i = 0; i < MAXTIJ; i++)
            listatijolos[i] = fase1[i];
        break;
    case 1:
        for(i = 0; i < MAXTIJ; i++)
            listatijolos[i] = fase2[i];
        break;
    case 2:
        for(i = 0; i < MAXTIJ; i++)
            listatijolos[i] = fase3[i];
        break;
    }



}

//funcao para pegar o nome do jogador
void pega_nome(JOGADOR *jog)
{
    int tamanho; //tamanho da string nome

    // mensagem para pegar nome
    gotoxy(XINI, YFIM+1);
    clreol();
    printf("Escreva um nome para o jogador [de 1 a %d caracteres]: ", MAX_NOME);

    // loop para pegar um nome com tamanho certo
    do{
        // le o nome
        gets(jog->nome);
        tamanho = strlen(jog->nome);

        // limpa mensagem para pegar nome
        gotoxy(XINI, YFIM+1);
        clreol();

        // caso seja um tamanho ruim
        if (tamanho > MAX_NOME || tamanho == 0)
        {
            // mensagem de erro
            textcolor(RED);
            printf("ERRO! Tamanho de nome invalido. Digite novamente [de 1 a %d caracteres]: ", MAX_NOME);
            textcolor(WHITE);
        }

    }while (tamanho > MAX_NOME || tamanho == 0);

    // escreve nome do jogador na lateral
    gotoxy(XINF+9, YJOGADOR);
    printf("                       ");
    gotoxy(XINF+9, YJOGADOR);
    puts(jog->nome);
}

// funcao para gerar um numero aleatorio entre o min e max
int random(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

// funcao para escrever mensagens temporarias no rodape da moldura
void printa_aviso(int cor, char erro[])
{
    // vai para linha de rodape e limpa ela
    gotoxy(XINI, YFIM+1);
    clreol();

    // escreve mensagem escolhida com cor escolhida
    textcolor(cor);
    printf("%s", erro);
    textcolor(WHITE);
    Sleep(1250);

    // apos 1,25s, apaga mensagem
    gotoxy(XINI, YFIM+1);
    clreol();
}

#endif /* DADOS_H */
