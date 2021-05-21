/**
******************************************************
* UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL          *
*                                                    *
* CURSO: CIENCIA DA COMPUTACAO                       *
* DICIPLINA: INF01202 - ALGORITMOS E PROGRAMACAO     *
* SEMESTRE: 2020/1                                   *
*                                                    *
* NOME DO PROGRAMA: BREAKOUT                         *
* OBJETIVO: EXECUTAR UMA VARIACAO DO JOGO "BREAKOUT" *
* NOME DO PROGRAMADORES: ARTHUR TONIAL DA SILVEIRA   *
*                        CARLOS EDUARDO WESTERMANN   *
* DATA DE CRIACAO: NOVEMBRO/2020                     *
******************************************************
**/


#include "poder.h"
#include "arquivos_bin.h"
#include "placar.h"


//PROTOTIPOS
void gameloop (JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PAUSAJOGO *pausa, PODER *pod);
void menu (JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod, PAUSAJOGO *p_jogo, char *tecla);
void muda_fase(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod);
int testa_fim_jogo (JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod, char *tecla);
int fim_tijolos(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod);
int fim_vidas(JOGADOR *jog);
int fim_esc(char *tecla, JOGADOR *jog);


int main()
{
    //declaracao de variaveis
    JOGADOR jog;
    PALHETA pal;
    BOLA bol;
    TIJOLO listatijolos[MAXTIJ];
    FASE fases[NUMFASES];
    PODER pod;
    PAUSAJOGO p_jogo;
    JOG_PLACAR listaplacar[N_PLACAR];

    hidecursor(); // esconde cursor

    preenche_dados(&jog, &pal, &bol, listatijolos, fases, &pod); // preenche dados das estruturas
    preenche_tijolos(jog, listatijolos, fases); // le tijolos de um aruivo .bin

    escreve_instrucoes(); // escreve as instrucoes para o usuario
    desenha_tela(jog, pal, bol, listatijolos, fases); // desenha todas as informacoes da tela

    gameloop(&jog, &pal, &bol, listatijolos, fases, &p_jogo, &pod); // entra no loop do jogo

    mostra_placar(&jog, listaplacar); // mostra o placar do jogo e depois encerra programa

    clrscr();
    gotoxy(1, 1);

    return 0;
}


// funcao para o loop do jogo, que mantém o jogo interagivel até que se pressione ESC ou o jogo termine
void gameloop(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PAUSAJOGO *p_jogo, PODER *pod)
{
    char tecla = '0'; // tecla de interacoes do usuario
    int i; // indice de loops

    // mensagem para comeco de jogo
    cputsxy(XINI, YFIM+1, "Mova a palheta com as SETAS e aperte ESPACO para comecar");

    // aguarda gatilho de comeco
    posicao_partida(pal, bol);

    // apaga as instrucoes e deseja um bom jogo :)
    apaga_instrucoes();

    // limpa mensagem de comeco
    gotoxy(XINI, YFIM+1);
    clreol();

    // loop do jogo (ate fim do jogo ou tecla esc)
    while(!testa_fim_jogo(jog, pal, bol, listatijolos, fases, pod, &tecla))
    {
        // leitura de teclado
        if(kbhit())
        {
            tecla = getch();

            if(tecla != ESPECIAL) // se nao for seta
            {
                // vai para menu ver se e um comando valido
                menu(jog, pal, bol, listatijolos, fases, pod, p_jogo, &tecla);
            }
            else // se for seta
            {
                // le segunda parte do codigo da seta e movimenta palheta
                tecla = getch();
                move_palheta(pal, tecla);
            }
        }

        // velocidade da bolinha definida pela fase
        // move bolinha a cada n ciclos
        if(i%fases[jog->fase].vel_bol == 0)
        {
            move_bola(jog, pal, bol, listatijolos, fases, pod);
        }

        // velocidade do poder definida tambem pela fase
        // move poder na metade da velocidade da bolinha (se o poder existir)
        if(pod->flag_pod != 0)
        {
            if(i%((fases[jog->fase].vel_bol)*2) == 0)
            {
                move_poder(jog, pal, listatijolos, fases, pod);
                // reseta i para evitar estouro
                i = 0;
            }
        }
        Sleep(10);
        i++;
    }
}

// funcao para coletar e encaminhar comandos do usuario
void menu(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod, PAUSAJOGO *p_jogo, char *tecla)
{
    // switch para opcoes de comandos
    switch(toupper(*tecla))
    {
        // codigo de pausa (cria save do momento do jogo)
        case 'P':
            pausa(*pal, *bol, listatijolos, jog, p_jogo, pod, tecla);
            break;
        // codigo de carregamento (carrega algum save previamente feito)
        case 'C':
            instancia_jogo(pal, bol, listatijolos, jog, fases, pod, *p_jogo);
            break;
        // codigo de passar fase
        case 'N':
            if(jog->fase < 2)
                muda_fase(jog, pal, bol, listatijolos, fases, pod);
            break;
    }
}

// funcao para passar para fase seguinte
void muda_fase(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod)
{
    char tecla = '0'; // tecla para interacao do usuario

    // tira poderes da tela
    pod->flag_pod = 0;
    // muda a o argumento fase do jogador pra seguinte
    (jog->fase)++;
    // situa as estruturas de acordo com a nova fase
    *pal = (PALHETA){{VEL_PALX,0}, {XPAL1 + jog->fase, YPAL}, {XPAL2 - jog->fase, YPAL}, CHAR_PAL};
    *bol = (BOLA)   {{pow(-1, random(0, 1)),1}, {XBOL,YBOL}, CHAR_BOL};
    jog->vidas = VIDAS_INICIAL;
    preenche_tijolos(*jog, listatijolos, fases);

    // mensagem de fase concluida
    gotoxy(XINF, YFIM_JOGO-1);
    printf("        Fase %d concluida", jog->fase);
    cputsxy(XINI, YFIM+1, "Aperte ENTER para seguir para a proxima fase...");

    //espera por ENTER do usuario
    do{
        fflush(stdin);
        tecla = getch();
    }while(tecla != ENTER);

    // atualiza a tela
    clrscr();
    desenha_tela(*jog, *pal, *bol, listatijolos, fases);

    // mensagens da nova fase
    gotoxy(XINF, YFIM_JOGO-1);
    printf("      Boa sorte na Fase %d!", jog->fase+1);
    gotoxy(XINI, YFIM+1);
    printf("Mova a palheta com as SETAS e aperte ESPACO para comecar a Fase %d", jog->fase + 1);

    // espera o gatilho de inicio da fase
    posicao_partida(pal, bol);

    // limpa as mensagens de troca de fase
    cputsxy(XINF, YFIM_JOGO-1, "                          ");
    gotoxy(XINI, YFIM+1);
    clreol();
}

// funcao para testar se o jogo acabou. Retorna 1 em caso de termino e 0 caso contrario
int testa_fim_jogo(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod, char *tecla)
{
    return fim_esc(tecla, jog) || fim_tijolos(jog, pal, bol, listatijolos, fases, pod) || fim_vidas(jog);
}

// funcao para testar se fase acabou por nao terem mais tijolos
int fim_tijolos(JOGADOR *jog, PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], FASE fases[], PODER *pod)
{
    int tij_fase = fases[jog->fase].numTijolos; //quantidade de tijolos na fase do momento
    int i = 0; //indice para while

    // ve se ainda tem tijolos
    while(listatijolos[i].estado == 2 && i < tij_fase)
        i++;

    // se nao tiverem mais tijolos, vitoria
    if(i == tij_fase)
    {
        // adiciona pontos extras pelas vidas que sobraram
        jog->pontos += jog->vidas * fases[jog->fase].pontos;
        pontos_jogador(*jog);

        // se nao estiver na ultima fase, passar para a seguinte
        if(jog->fase < NUMFASES-1)
        {
            muda_fase(jog, pal, bol, listatijolos, fases, pod);
        }
        // se estiver na ultima fase, vitoria
        else
        {
            // mensagem de vitoria
            cputsxy(XINF, YFIM_JOGO, "          Vitoria! :D");
            cputsxy(XINF, YFIM_JOGO + 1, " Parabens! Voce venceu o jogo!");
            // atualiza argumento do jogador para termino normal (1)
            jog->termino = 1;
            return 1;
        }
    }
    return 0;
}

// funcao para testar se jogo acabou por nao terem mais vidas
int fim_vidas(JOGADOR *jog)
{
    //ve se o jogador nao tem mais vidas
    if(jog->vidas == 0)
    {
        // mensagem de derrota
        cputsxy(XINF, YFIM_JOGO, "          Derrota! :(");
        cputsxy(XINF, YFIM_JOGO + 1, "  Mais sorte da proxima vez...");
        // atualiza argumento do jogador para termino normal (1)
        jog->termino = 1;
        return 1;
    }
    return 0;
}

// funcao para testar se jogo acabou por ter sido pressionado ESC
int fim_esc(char *tecla, JOGADOR *jog)
{
    // ve se o jogador quer encerrar o jogo
    if(*tecla == ESC)
    {
        // pede confirmacao
        cputsxy(XINI, YFIM+1, "Deseja mesmo sair? (1 - Sim | 0 - Nao)");

        // aguarda resposta
        do{
            fflush(stdin);
            *tecla = getch();
        }while(*tecla != '1' && *tecla != '0');

        // limpa mensagem de confirmacao
        gotoxy(XINI, YFIM+1);
        clreol();

        // se resposta positiva, encaminha para o fim
        if(*tecla == '1')
        {
            cputsxy(XINF, YFIM_JOGO, "   Muito obrigado por jogar :)");
            cputsxy(XINF, YFIM_JOGO + 1, "          Volte sempre!");
            // atualiza argumento do jogador para termino por ESC (0)
            jog->termino = 0;
            return 1;
        }
        else
        {
            //sleep para não voltar o jogo imediatamente
            Sleep(1000);
        }
    }
    return 0;
}
