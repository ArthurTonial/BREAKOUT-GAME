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


// funcao para mover a paleta
void move_palheta(PALHETA *pal, char tecla)
{
    int i = 0;  //controlador do while
    int xv = pal->vel_dir.x; //velocidade e direcao da palheta
    int x1 = pal->ponto1.x, x2 = pal->ponto2.x; //coordenadas x limites da palheta
    int y1 = pal->ponto1.y; //coordenada y da palheta

    //switch case pra ver se a seta foi a esquerda ou a direita
    switch(tecla)
    {
        case SETA_ESQ:
            //Verifica até onde o movimento pode ser feito
            while (i < xv && x1-1 > XINI)
            {
                putchxy(x2, y1, ' ');
                x2--;
                x1--;
                i++;
            }
            //atualiza as coordenadas da palheta
            pal->ponto1.x = x1;
            pal->ponto2.x = x2;
            //e desenha a plaheta
            desenha_palheta(*pal);
        break;

        case SETA_DIR:
            //Verifica até onde o movimento pode ser feito
            while (i < xv && x2+1 < XFIM)
            {
                putchxy(x1, y1, ' ');
                x2++;
                x1++;
                i++;
            }
            //atualiza as coordenadas da palheta
            pal->ponto1.x = x1;
            pal->ponto2.x = x2;
            //e desenha a plaheta
            desenha_palheta(*pal);
        break;
    }
}

// funcao para mover a bolinha, testando possiveis colisoes em sua trajetoria
void move_bola(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod)
{
    // testa todas possiveis colisoes da bolinha, mudando a direcao nos prorpios testes
    colisao_bola_esq_tij(jog, bol, listatijolos, fases, pod);
    colisao_bola_dir_tij(jog, bol, listatijolos, fases, pod);
    colisao_bola_paredes(bol);
    colisao_bola_palheta(*pal, bol);
    colisao_bola_paredes(bol);
    colisao_bola_face_tij(jog, bol, listatijolos, fases, pod);
    colisao_bola_teto_chao(jog, pal, bol, pod);

    // depois de todos os testes, move a bolinha de fato
    // apaga a bolinha anterior
    textcolor(BLACK);
    desenha_bolinha(*bol);
    // muda a posicao dela
    bol->posicao.x += bol->vel_dir.x;
    bol->posicao.y += bol->vel_dir.y;
    // desenha ela na nova posicao
    textcolor(WHITE);
    desenha_bolinha(*bol);

    //desenha palheta novamente para evitar furos na mesma
    if(bol->posicao.y == pal->ponto1.y+1)
        desenha_palheta(*pal);
}

// funcao que verifica se ha colisao entre dois envelopes. Retorna 1 se colidiu e 0 caso contrario
short testa_colisao(int x1Obj1, int x2Obj1, int y1Obj1, int y2Obj1, int x1Obj2, int x2Obj2, int y1Obj2, int y2Obj2)
{
    //verifica se ha colisão entre objetos
    if(x1Obj2 <= x2Obj1 && x2Obj2 >= x1Obj1 && y1Obj2 <= y2Obj1 && y2Obj2 >= y1Obj1)
        return 1;
    else
        return 0;
}

// funcao para mover bolinha e palhetaa antes de comecar o jogo de fato
void posicao_partida(PALHETA *pal, BOLA *bol)
{
    char tecla = '0'; // tecla para interacoes

    // loop ate receber um espaco para iniciar jogo
    do{
        // le tecla do usuario
        fflush(stdin);
        tecla = getch();

        // caso seja uma seta
        if(tecla == ESPECIAL)
        {
            // recebe segunda parte do caractere
            tecla = getch();

            // move palheta
            move_palheta(pal, tecla);

            // e move bolinha horizontalmente
            move_bola_horizontal(*pal, bol, tecla);
        }
    }while(tecla != ESPACO);
}

// funcao para testar e executar colisao com palheta
void colisao_bola_palheta(PALHETA pal, BOLA *bol)
{
    int xpal1 = pal.ponto1.x; // coordenada palheta
    int xpal2 = pal.ponto2.x;
    int ypal = pal.ponto1.y;

    int xbol_next = bol->posicao.x + bol->vel_dir.x; // suposicao da posicao x futura da bola
    int ybol_next = bol->posicao.y + bol->vel_dir.y; // suposicao da posicao y futura da bola

    // teste colisão com esquerda da palheta
    if(testa_colisao(xbol_next, xbol_next, ybol_next, ybol_next, xpal1, xpal1+(xpal2-xpal1)/2, ypal, ypal))
    {
        //muda direcao da bolinha
        bol->vel_dir.y *= -1;
        bol->vel_dir.x = -1;
    }
    // teste colisão com direita da palheta
    else if(testa_colisao(xbol_next, xbol_next, ybol_next, ybol_next, xpal1+(xpal2-xpal1)/2-1, xpal2, ypal, ypal))
    {
        //muda direcao da bolinha
        bol->vel_dir.y *= -1;
        bol->vel_dir.x = 1;
    }
}

// funcao para testar e executar colisao com paredes
void colisao_bola_paredes(BOLA *bol)
{
    int xbol_next = bol->posicao.x + bol->vel_dir.x; // suposicao da posicao x futura da bola
    int ybol_next = bol->posicao.y + bol->vel_dir.y; // suposicao da posicao y futura da bola

    // teste colisao com parede esquerda
    if(testa_colisao(xbol_next, xbol_next, ybol_next, ybol_next, XINI, XINI, YINI, YFIM))
    {
        //muda direcao da bolinha
        bol->vel_dir.x *= -1;
    }
    // teste colisao com parede direita
    else if(testa_colisao(xbol_next, xbol_next, ybol_next, ybol_next, XFIM, XFIM, YINI, YFIM))
    {
        //muda direcao da bolinha
        bol->vel_dir.x *= -1;
    }
}

// funcao para testar e executar colisao com faces dos tijolos
void colisao_bola_face_tij(JOGADOR *jog, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod)
{
    int i = 0; // indice para loop
    int xbol_next = bol->posicao.x + bol->vel_dir.x; // suposicao da posicao x futura da bola
    int ybol_next = bol->posicao.y + bol->vel_dir.y; // suposicao da posicao y futura da bola
    int num_tij = fases[jog->fase].numTijolos; //numero de tijolos da fase

    // teste colisao com face de tijolos
    // procura possivel tijolo a ser colidido
    while(!testa_colisao(xbol_next, xbol_next, ybol_next, ybol_next, listatijolos[i].ponto1.x, listatijolos[i].ponto2.x, listatijolos[i].ponto1.y, listatijolos[i].ponto2.y) && i < num_tij)
        i++;

    // caso tenha encontrado
    if(i < num_tij && listatijolos[i].estado <= 1)
    {
        //resolve o tijolo e
            resolve_tijolo(jog, listatijolos,fases,pod, i);

        //muda direcao da bolinha
        bol->vel_dir.y *= -1;
    }
}

// funcao para testar e executar colisao com lateral direita dos tijolos
void colisao_bola_dir_tij(JOGADOR *jog, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod)
{
    int i = 0; // indice para loop
    int xbol = bol->posicao.x; // posicao x da bola
    int ybol = bol->posicao.y; // posicao y da bola
    int num_tij = fases[jog->fase].numTijolos; //numero de tijolos da fase

    // teste colisao com lateral direita dos tijolos
    // se estiver vindo de uma direcao adequada
    if(bol->vel_dir.x == -1)
    {
        // procura possivel lateral direita de tijolo a ser colidido
        while(!testa_colisao(xbol, xbol, ybol, ybol, listatijolos[i].ponto2.x+1, listatijolos[i].ponto2.x+1, listatijolos[i].ponto1.y, listatijolos[i].ponto2.y) && i < num_tij)
            i++;

        // se encontrou
        if(i < num_tij && listatijolos[i].estado <= 1)
        {
            //resolve o tijolo e
            resolve_tijolo(jog, listatijolos,fases,pod, i);

            //muda direcao da bolinha
            bol->vel_dir.x *= -1;
        }
    }
}

// funcao para testar e executar colisao com lateras esquerda dos tijolos
void colisao_bola_esq_tij(JOGADOR *jog, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod)
{
    int i = 0; // indice para loop
    int xbol = bol->posicao.x; // posicao x da bola
    int ybol = bol->posicao.y; // posicao y da bola
    int num_tij = fases[jog->fase].numTijolos; //numero de tijolos da fase


    //teste colisao com lateral esquerda dos tijolos
    if(bol->vel_dir.x == 1)
    {
        //procura possivel lateral esquerda de tijolo a ser colidido
        while(!testa_colisao(xbol, xbol, ybol, ybol, listatijolos[i].ponto1.x-1, listatijolos[i].ponto1.x-1, listatijolos[i].ponto1.y, listatijolos[i].ponto2.y) && i < num_tij)
            i++;

        // se encontrou
        if(i < num_tij && listatijolos[i].estado <= 1)
        {
            //resolve o tijolo e
            resolve_tijolo(jog, listatijolos,fases,pod, i);

            //muda direcao da bolinha
            bol->vel_dir.x *= -1;
        }
    }
}

// funcao para testar e executar colisao com teto ou chao
void colisao_bola_teto_chao(JOGADOR *jog, PALHETA *pal, BOLA *bol, PODER *pod)
{
    int xbol_next = bol->posicao.x + bol->vel_dir.x; // suposicao da posicao x futura da bola
    int ybol_next = bol->posicao.y + bol->vel_dir.y; // suposicao da posicao y futura da bola

    // teste colisao com teto
    if(testa_colisao(xbol_next, xbol_next, ybol_next, ybol_next, XINI, XFIM, YINI, YINI))
    {
        //muda direcao da bolinha
        bol->vel_dir.y *= -1;
    }
    // teste colisao com chao
    else if(testa_colisao(xbol_next, xbol_next, ybol_next, ybol_next, XINI, XFIM, YFIM, YFIM))
    {
        // diminui o numero de vidas em 1
        (jog->vidas)--;
        vidas_jogador(*jog);

        // animacao de que perdeu vida
        textcolor(RED);
        desenha_bolinha(*bol);
        Sleep(1000);

        // apaga palheta, bolinha e poder
        textcolor(BLACK);
        desenha_bolinha(*bol);
        desenha_palheta(*pal);
        if(pod->flag_pod)
            desenha_poder(*pod);
        textcolor(WHITE);

        //atualiza dados de palheta, bolinha e poder
        pod->flag_pod = 0;

        bol->posicao.x = XBOL;
        bol->posicao.y = YBOL;
        bol->vel_dir.x = pow(-1, random(0, 1));
        //muda direcao da bolinha
        bol->vel_dir.y = -1;

        pal->ponto1.x = XPAL1+jog->fase;
        pal->ponto2.x = XPAL2-jog->fase;

        // desenha palheta e bolinha na posicao central
        desenha_palheta(*pal);
        desenha_bolinha(*bol);

        // e se continuar vivo, aguarda comando para seguir
        if(jog->vidas > 0)
        {
            cputsxy(XINI, YFIM+1, "Mova a palheta com as SETAS e aperte ESPACO para jogar");
            // aguarda gatilho de comeco
            posicao_partida(pal, bol);
            // limpa mensagem
            gotoxy(XINI, YFIM+1);
            clreol();
        }
        else
        {
            bol->vel_dir = (COORDENADA){0,0};
        }
    }
}

// funcao para mover a bola horizontalmente
void move_bola_horizontal(PALHETA pal, BOLA *bol, char tecla)
{
    int largura_pal = pal.ponto2.x - pal.ponto1.x + 1; // largura da palheta

    if(tecla == SETA_DIR)
            {
                // caso a bolinha nao esteja numa posicao limite a direita
                // move ela
                if(bol->posicao.x + largura_pal/2 + 1 < XFIM)
                {
                    textcolor(BLACK);
                    desenha_bolinha(*bol);

                    bol->posicao.x += pal.vel_dir.x;

                    textcolor(WHITE);
                    desenha_bolinha(*bol);
                }
            }
            // ou move bolinha para esquerda
            else if(tecla == SETA_ESQ)
            {
                // caso a bolinha nao esteja numa posicao limite a esquerda
                // move ela
                if(bol->posicao.x - largura_pal/2 - 1 > XINI)
                {
                    textcolor(BLACK);
                    desenha_bolinha(*bol);

                    bol->posicao.x -= pal.vel_dir.x;

                    textcolor(WHITE);
                    desenha_bolinha(*bol);
                }
            }
}

// funcao para definir o que fazer com tijolo
void resolve_tijolo(JOGADOR *jog, TIJOLO listatijolos[], FASE fases[], PODER *pod, int i)
{
    // incrementa em 1 o estado do tijolo
    listatijolos[i].estado++;

    // se tijolo quebrou, apagar ele
    if(listatijolos[i].estado == 2)
    {
        destroi_tijolo(jog, listatijolos, fases, pod, i);
    }
    // se ainda falta um hit, mudar para a cor adequada
    else if(listatijolos[i].estado == 1)
    {
        listatijolos[i].cor = fases[jog->fase].cor1;
        desenha_tijolo(listatijolos[i]);
    }
    // se ainda faltam dois hits, mudar para a cor adequada
    else if(listatijolos[i].estado == 0)
    {
        listatijolos[i].cor = fases[jog->fase].cor0;
        desenha_tijolo(listatijolos[i]);
    }
}
