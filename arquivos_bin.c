#include "desenha.h"


//PROTOTIPOS
void pausa (PALHETA pal, BOLA bol, TIJOLO listatijolos[], JOGADOR *jog, PAUSAJOGO *p_jogo, PODER *pod, char *tecla);
int salva(PAUSAJOGO p_jogo, char nome[]);
int le_jogo(PAUSAJOGO *p_jogo, char nome[]);
void instancia_jogo (PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], JOGADOR *jog, FASE fases[], PODER *pod, PAUSAJOGO pausa);


// funcao para pausar o jogo e criar um save do instante pausado em um arquivo .bin
void pausa(PALHETA pal, BOLA bol, TIJOLO *listatijolos, JOGADOR *jog, PAUSAJOGO *p_jogo, PODER *pod, char *tecla)
{
    int i; // indice for

    *tecla = '0';

    // pega nome do jogador
    pega_nome(jog);

    // p_jogo é atualisado com dados do jogo do instante pausado (pal, bol, jogador, poder e tijolos)
    p_jogo->pal = pal;
    p_jogo->bol = bol;
    p_jogo->jog = *jog;
    p_jogo->pod = *pod;
    for(i = 0; i < MAXTIJ; i++)
        p_jogo->listatijolos[i] = listatijolos[i];

    // salva o p_jogo em um arquivo .bin
    salva(*p_jogo, jog->nome);

    // mensagem de encerrar pausa
    cputsxy(XINI, YFIM+1, "Pressione 'P' se deseja voltar ao jogo ou 'ESC' caso queira encerrar");

    // espera por 'p' para seguir; ou ESC para encerrar
    do{
        if (*tecla == ESPECIAL)
            *tecla = getch();
        *tecla = getch();
    }while(toupper(*tecla) != 'P' && *tecla != ESC);

    // limpa mensagem de encerrar pausa
    gotoxy(XINI, YFIM+1);
    clreol();
}

// funcao para salvar estrutura PAUSAJOGO em um arquivo .bin
// retorna 1 em caso de erro e 0 caso contrario
int salva(PAUSAJOGO p_jogo, char nome[])
{
    char nome_aux[MAX_NOME]; // nome auxiliar para não concatenar ".bin" no jogador
    FILE *save; // arquivo

    // copia nome do jogador para string auxiliar
    strcpy(nome_aux, nome);

    // abre o arquivo
    if((save  = fopen(strcat(nome_aux, ".bin"), "wb")) == NULL)
    {
        // mensagem de erro ao abrir
        printa_aviso(VERMELHO, "Erro ao abrir arquivo!");
        return 1;
    }

    // escrever no arquivo
    if(fwrite(&p_jogo, sizeof(PAUSAJOGO), 1, save) != 1)
    {
        // mensagem de erro ao escrever
        printa_aviso(VERMELHO, "Erro ao escrever no arquivo!");
        return 1;
    }

    // Fecha o arquivo
    fclose(save);
    return 0;
}

// funcao para preencher estrutura PAUSAJOGO a partir de um arquivo .bin
// retorna 1 em caso de erro e 0 caso contrario
int le_jogo(PAUSAJOGO *p_jogo, char nome[])
{
    FILE *save; // arquivo
    char nome_bin[MAX_NOME]; // nome auxiliar para não concatenar ".bin" no jogador

    // copia nome do jogador para string auxiliar
    strcpy(nome_bin, nome);

    // abre arquivo
    if((save = fopen(strcat(nome_bin, ".bin"), "rb")) == NULL)
    {
        // mensagem de erro ao abrir arquivo
        printa_aviso(VERMELHO, "Erro ao abrir arquivo!");
        return 0;
    }

    // le o arquivo
    if(fread(p_jogo, sizeof(PAUSAJOGO), 1, save) != 1)
    {
        // mensagem de erro ao ler arquivo
        printa_aviso(VERMELHO, "Erro ao ler arquivo!");
        return 0;
    }

    // fecha arquivo
    fclose(save);
    return 1;
}

// Desenha informações do jogo e manda pro gameloop
void instancia_jogo(PALHETA *pal, BOLA *bol, TIJOLO listatijolos[], JOGADOR *jog, FASE fases[], PODER *pod, PAUSAJOGO p_jogo)
{
    char nome[MAX_NOME+1]; // nome do arquivo a ser buscado
    int i; //indice de for

    // pede o nome do save
    gotoxy(XINI, YFIM+1);
    clreol();
    cputsxy(XINI, YFIM+1, "Nome do save: ");
    gets(nome);

    // ve se o arquivo foi aberto
    if(le_jogo(&p_jogo, nome))
    {
        // se sim, atualiza os dados do jogo com os dados do save e printa tela nova
        *pal = p_jogo.pal;
        *bol = p_jogo.bol;
        *jog = p_jogo.jog;
        *pod = p_jogo.pod;
        for(i = 0; i < MAXTIJ; i++)
            listatijolos[i] = p_jogo.listatijolos[i];

        // atualiza a tela
        system("cls");
        desenha_tela(*jog, *pal, *bol, listatijolos, fases);

        // mensagem de sucesso
        printa_aviso(VERDE, "Arquivo carregado com sucesso!");
    }
    // senao
    else
    {
        // mensagem de erro
        printa_aviso(VERMELHO, "Nao ha um save disponivel");
    }
}
