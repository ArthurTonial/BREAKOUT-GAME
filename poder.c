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


// funcao para fazer movimento de queda do poder
void move_poder(JOGADOR *jog, PALHETA *pal, TIJOLO listatijolos[], FASE fases[], PODER *pod)
{
    colisao_poder_tijolo(*jog, listatijolos, fases, *pod); // testa colisao com tijolo
    colisao_poder_palheta(jog, pal, fases, pod); //testa colisao com palheta
    colisao_poder_chao(pod); //teste colisao com o chao

    // se o poder ainda nao foi resolvido, move ele de fato
    if(pod->flag_pod != 0)
    {
        textcolor(BLACK);
        desenha_poder(*pod);

        pod->pos.y += 1;

        textcolor(WHITE);
        desenha_poder(*pod);
    }
}

// funcao para sortear numero para possivel poder
void sorteio_poder(PODER *pod, int x, int y)
{
    int i; // valor para o sorteio

    // se nao ha nenhum poder na tela, sorteia um numero
    if(pod->flag_pod == 0)
    {
        // gera numero randomico entre 1 e 15
        i = random(1, MAX_SORTEIO);
        //switch case para ver se poder foi sorteado
        switch(i)
        {
            case VIDA: // se numero sorteado e 1, poder de vidas
                pod->flag_pod = VIDA;
                pod->c = '§';
                // coloca o poder na posicao de saida do tijolo
                pod->pos.x = x + 2;
                pod->pos.y = y;
                break;

            case PONTOS: // se numero sorteado e 2, poder de pontos
                pod->flag_pod = PONTOS;
                pod->c = '$';
                // coloca o poder na posicao de saida do tijolo
                pod->pos.x = x + 2;
                pod->pos.y = y;
                break;

            case PAL_MAIOR: // se numero sorteado e 3, poder de palheta
                pod->flag_pod = PAL_MAIOR;
                pod->c = '+';
                // coloca o poder na posicao de saida do tijolo
                pod->pos.x = x + 2;
                pod->pos.y = y;
                break;
        }
    }
}

// funcao para executar acao do poder de vidas (aumentar em 1 as vidas)
void poder_vida(JOGADOR *jog)
{
    // se o numero de vidas for menor que 9 (quantidade maxima)
    if(jog->vidas < VIDAS_MAX)
    {
        // aumenta as vidas em 1
        jog->vidas++;
        vidas_jogador(*jog);
    }
}

// funcao para executar acao do poder de pontos (bonus na pontuacao)
void poder_pontos(JOGADOR *jog, FASE fase[])
{
    // soma para a pontuacao do jogador MULT_PONTOS vezes a pontuacao de um tijolo na fase
    jog->pontos += fase[jog->fase].pontos * MULT_PONTOS;
    pontos_jogador(*jog);
}

// funcao para executar acao do poder de palheta (aumentar palheta)
void poder_palheta(PALHETA *pal)
{
    int x1 = pal->ponto1.x; // coordenadas x do envelope da palheta
    int x2 = pal->ponto2.x;

    // se a palheta for menor que o tamanho maximo, aumenta
    if(x2 - x1 < XPAL2 - XPAL1 + 5)
    {
        // caso a palheta esteja na extrema esquerda
        if(x1 == XINI+1)
        {
            // cresce pra direita
            pal->ponto2.x = pal->ponto2.x + 2;
        }
        //caso a palheta esteja na extrema esquerda
        else if(x2 == XFIM-1)
        {
            // cresce pra esquerda
            pal->ponto1.x = pal->ponto1.x - 2;
        }
        // senao
        else
        {
            // cresce para os dois lados
            pal->ponto1.x--;
            pal->ponto2.x++;
        }
        // desenha palheta com novo tamanho
        desenha_palheta(*pal);
    }
}

// funcao para testar e executar colisao de poder com palheta
void colisao_poder_palheta(JOGADOR *jog, PALHETA *pal, FASE fases[], PODER *pod)
{
    int xpod = pod->pos.x; // posicao poder
    int ypod = pod->pos.y;
    int xpal1 = pal->ponto1.x; // posicao palheta
    int xpal2 = pal->ponto2.x;
    int ypal = pal->ponto1.y;

    if(testa_colisao(xpod, xpod, ypod+1, ypod+1, xpal1, xpal2, ypal, ypal))
    {
        //fazer a acao do poder
        switch(pod->flag_pod)
        {
            // caso poder de vida
            case VIDA:
                poder_vida(jog);
                break;
            // caso poder de pontos
            case PONTOS:
                poder_pontos(jog, fases);
                break;
            // caso poder de palheta
            case PAL_MAIOR:
                poder_palheta(pal);
                break;
        }

        // apaga poder e considera como resolvido (bota a flag = 0)
        textcolor(BLACK);
        desenha_poder(*pod);
        textcolor(WHITE);
        pod->flag_pod = 0;
    }
}

// funcao para testar e executar colisao de poder com tijolo
void colisao_poder_tijolo(JOGADOR jog, TIJOLO listatijolos[], FASE fases[], PODER pod)
{
    int xpod = pod.pos.x; // posicao do poder
    int ypod = pod.pos.y;
    int i = 0; //indice para loop
    int num_tij = fases[jog.fase].numTijolos;//numero de tijolos da fase

    // testa se passou por um tijolo
    while(!testa_colisao(xpod, xpod, ypod-1, ypod-1, listatijolos[i].ponto1.x, listatijolos[i].ponto2.x, listatijolos[i].ponto1.y, listatijolos[i].ponto2.y) && i < num_tij)
        i++;

    // caso tenha passado
    if(i < num_tij && listatijolos[i].estado <= 1)
    {
        // desenha tijolo novamente para fechar buraco
        desenha_tijolo(listatijolos[i]);
    }
}

// funcao para testar e executar colisao de poder com o chao
void colisao_poder_chao(PODER *pod)
{
    int xpod = pod->pos.x; // posicao do poder
    int ypod = pod->pos.y;

    //verifica se poder colidiu com o chao
    if(testa_colisao(xpod, xpod, ypod+1, ypod+1, XINI, XFIM, YFIM, YFIM))
    {
        // apaga poder e considera como resolvido (bota a flag = 0)
        textcolor(BLACK);
        desenha_poder(*pod);
        textcolor(WHITE);
        pod->flag_pod = 0;
    }
}
