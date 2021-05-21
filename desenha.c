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


// funcao que desenha a paleta do jogo
void desenha_palheta(PALHETA pal)
{
    int i; // indice de dor
    int x1 = pal.ponto1.x, x2 = pal.ponto2.x; // posicoes x da palheta
    int y1 = pal.ponto1.y; // posicao y da palheta
    char c = pal.c; // caractere da palheta

    // desenha palheta
    for(i = 0; i < (x2-x1)+1; i++)
        putchxy(x1+i, y1, c);
}

// funcao que desenha a bolinha
void desenha_bolinha(BOLA bol)
{
    //coloca o caractere da bolinha (bola->c) na posição adequada
    putchxy(bol.posicao.x, bol.posicao.y, bol.c);
}

// funcao que desenha os contornos da área de jogo
void desenha_moldura()
{
    int i; // indice de for

    textcolor(CYAN);
    // coloca caracteres especiais da moldura
    gotoxy(XINI, YINI);
    printf("%c", SUP_ESQ);
    gotoxy(XFIM, YINI);
    printf("%c", SUP_MID);
    gotoxy(XFIM2, YINI);
    printf("%c", SUP_DIR);
    gotoxy(XINI, YFIM);
    printf("%c", INF_ESQ);
    gotoxy(XFIM, YFIM);
    printf("%c", INF_MID);
    gotoxy(XFIM2, YFIM);
    printf("%c", INF_DIR);

    //desenha bordas horizontais da moldura
    for (i = XINI+1; i < XFIM2; i++)
    {
        if(i != XFIM)
        {
            gotoxy(i, YINI);
            printf("%c", HORIZONTAL);
            gotoxy(i, YFIM);
            printf("%c", HORIZONTAL);
        }
    }

    //desenha bordas verticais da moldura
    for (i = YINI+1; i < YFIM; i++)
    {
        gotoxy(XINI, i);
        printf("%c", VERTICAL);
        gotoxy(XFIM, i);
        printf("%c", VERTICAL);
        gotoxy(XFIM2, i);
        printf("%c", VERTICAL);
    }

    textcolor(WHITE);
}

// funcao que coloca na tela opções do menu
void desenha_menu()
{
    textcolor(LIGHTGRAY);

    cputsxy(XPAUSAR, YINI-1,"Pausar(P)");
    cputsxy(XCARREGAR, YINI-1,"Carregar(C)");
    cputsxy(XSAIR, YINI-1,"Sair(ESC)");

    textcolor(WHITE);
}

// funcao que desenha um tijolo
void desenha_tijolo(TIJOLO tij)
{
    //variaveis
    int i, j;
    int x1 = tij.ponto1.x, x2 = tij.ponto2.x;
    int y1 = tij.ponto1.y, y2 = tij.ponto2.y;
    char char_tij = tij.c;

    textcolor(tij.cor);
    //verifica se o tijolo a ser desenhado estaria dentro da moldura
    if(x1 > XINI && x2-1 < XFIM)
        if(y1 > YINI && y2-1 < YFIM)
            for(i = 0; i < (x2-x1)+1; i++)
                for(j = 0; j < (y2-y1)+1; j++)
                    putchxy(x1+i, y1+j, char_tij);
    textcolor(WHITE);
}

// funcao que desenha uma lista de tijolos
void desenha_tijolos(TIJOLO listatijolos[], JOGADOR jog, FASE fases[])
{
    int i; // indice de for
    int n_tij = fases[jog.fase].numTijolos; // quantidade de tijolos na fase

    // desenha os tijolos do arranjo ate alcancar o numero de tijolos da fase
    for(i = 0; i < n_tij; i++)
        if(listatijolos[i].estado != 2)
            desenha_tijolo(listatijolos[i]);
}

// funcao que desenha todas informacoes do jogo que devem aparecer na tela
// (moldura, tijolos, menu, bolinha, palheta e informacoes extras)
void desenha_tela(JOGADOR jog, PALHETA pal, BOLA bol, TIJOLO listatijolos[], FASE fases[])
{
    desenha_menu(); // desenha menu
    desenha_moldura(); // desenha a moldura
    desenha_bolinha(bol); // desenha a bola
    desenha_palheta(pal); // desenha a palheta
    escreve_informacoes(jog);// escreve a identificação dos alunos
    desenha_tijolos(listatijolos, jog, fases); // desenha tijolos
}

// funcao que desenha poder
void desenha_poder(PODER pod)
{
    // bota caratere do poder na posicao adequada
    putchxy(pod.pos.x, pod.pos.y, pod.c);
}

// funcao que escreve a identificação dos alunos ao lado da moldura
void escreve_informacoes(JOGADOR jog)
{
    //printa detalhes do jogador
    gotoxy(XINF, YJOGADOR);
    printf("JOGADOR: %s", jog.nome);
    pontos_jogador(jog);
    vidas_jogador(jog);
    gotoxy(XINF, YFASE);
    printf("FASE: %d", jog.fase+1);

    //printa detalhes dos programadores
    textcolor(DARKGRAY);
    cputsxy(XINF, YDISCIPLINA, "Disciplina INF01202 - Algoritmos");
    cputsxy(XINF, YSEMESTRE, "Semestre: 2020/1");
    cputsxy(XINF, YNOMES, "Programadores:");
    cputsxy(XINF, YNOMES+1," - Arthur Tonial da Silveira");
    cputsxy(XINF, YNOMES+2," - Carlos Eduardo Westermann");

    textcolor(WHITE);
}

// funcao para nao deixar o cursor visivel
void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// funcao que apaga um tijolo da tela, limpa os valores da coordenada equivalente do mesmo e soma
// a pontuação do tijolo para o jogador. Tambem sorteia um numero para possivel poder.
void destroi_tijolo(JOGADOR *jog, TIJOLO listatijolos[], FASE fases[],  PODER *pod, int indicetijolo)
{
    int i, j; // indices de for

    TIJOLO tij = listatijolos[indicetijolo]; // tijolo a ser apagado

    int x1 = tij.ponto1.x, x2 = tij.ponto2.x; // envelope do tijolo
    int y1 = tij.ponto1.y, y2 = tij.ponto2.y;

    // adiciona a pontuacao do tijolo destruido
    jog->pontos += fases[jog->fase].pontos;
    pontos_jogador(*jog);

    // apaga todo o tijolo destruido
    for(i = 0; i < (x2-x1)+1; i++)
    {
        for(j = 0; j < (y2-y1)+1; j++)
        {
            putchxy(x1+i, y1+j, ' ');
        }
    }

    // verifica se o tijolo liberara algum poder
    sorteio_poder(pod, x1, y2);
}

// funcao que escreve pontos do jogador
void pontos_jogador(JOGADOR jog)
{
    gotoxy(XINF, YPONTOS);
    printf("PONTOS: %d", jog.pontos);
}

// funcao que escreve vidas do jogador
void vidas_jogador(JOGADOR jog)
{
    gotoxy(XINF, YVIDAS);
    printf("VIDAS: %d", jog.vidas);
}

// funcao para colocar instrucoes na tela
void escreve_instrucoes()
{
    textcolor(LIGHTGRAY);

    cputsxy(XINF,    YINST, "-----------INSTRUCOES-----------");
    cputsxy(XINF,  YINST+2, " Mova a palheta com as setinhas ");
    cputsxy(XINF,  YINST+3, "      [<-] ========== [->]      ");

    cputsxy(XINF,  YINST+5, "     Destrua todo os tijolos    ");
    cputsxy(XINF,  YINST+6, "      para avançar de fase      ");

    cputsxy(XINF,  YINST+8, "     Alguns tijolos sao mais    ");
    cputsxy(XINF,  YINST+9, "       dificeis de quebrar      ");

    cputsxy(XINF, YINST+11, "Pegue powerups para uma ajudinha");

    cputsxy(XINF, YINST+13, " Vidas restantes tambem pontuam ");

    textcolor(WHITE);
}

// funcoes para apagr instrucoes da tela e desejar bom jogo
void apaga_instrucoes()
{
    int i; // iterador do for

    // apaga o que estiver nas instrucoes
    for(i = YINST; i < YDISCIPLINA; i++)
        cputsxy(XINF, i  , "                                ");

    textcolor(LIGHTGRAY);
    // imprime mensagem de bom jogo
    cputsxy(XINF, YINST  , "      Tenha um otimo jogo       ");
    cputsxy(XINF, YINST+1, "       e divirta-se! :D         ");
    Sleep(2000);
    textcolor(WHITE);

    // apaga mensagem de bom jogo
    cputsxy(XINF, YINST  , "                                ");
    cputsxy(XINF, YINST+1, "                                ");

}


#endif /* DESENHA_H */
