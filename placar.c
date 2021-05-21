#include "dados.h"


//PROTOTIPOS
void abre_arq_txt(FILE **arqtxt);
short le_arq_txt (FILE **arqtxt, JOG_PLACAR listaplacar[]);
void mostra_placar (JOGADOR *jog, JOG_PLACAR listaplacar[]);
short insere_jogador_placar (JOGADOR *jog, JOG_PLACAR listaplacar[], short *cont_placar);
void ordena_placar (JOG_PLACAR listaplacar[], int i);
void salva_placar (FILE *arq, JOG_PLACAR listaplacar[], int cont_placar);
void printa_placar (JOG_PLACAR listaplacar[], int cont_placar);


// funcao que abre arquivo .txt do ranking
void abre_arq_txt(FILE **arqtxt)
{
    *arqtxt = fopen("BreakoutJog.txt", "r");
}

// funcao que le o conteudo de arquivo .txt do ranking, e passa para array de JOG_PLACAR
short le_arq_txt(FILE **arqtxt, JOG_PLACAR listaplacar[])
{
    char linha[MAX]; // linha lida do documento .txt
    int cont_placar = 0; // contador de linhas

    // abre o arquivo .txt
    abre_arq_txt(arqtxt);

    // se nao conseguiu abrir o arquivo, encerra com 0
    if(*arqtxt == NULL)
    {
        printa_aviso(VERMELHO, "Erro ao abrir arquivo!");
        return 0;
    }
    // caso contrario
    else
    {
        // converte cada linha do documento txt em um elemento de um array JOG_PLACAR
        // recebe primeira linha
        fgets(linha, MAX, *arqtxt)

        // enquanto nao encontrar o fim do arquivo
        while(!feof(*arqtxt))
        {
            // pega o nome do jogador do placar
            strcpy(listaplacar[cont_placar].nome, strtok(linha, "#"));
            // pega a pontuacao do jogador do placar
            listaplacar[cont_placar].pontos = atoi(strtok(NULL, "#"));

            // soma em 1 a quantidade de linhas
            cont_placar++;
            // e le a proxima linha
            fgets(linha, MAX, *arqtxt);
        }
        //fecha arquivo
        fclose(*arqtxt);
        //retorna o numero de jogadores lidos
        return cont_placar;
    }
}

// funcao que insere, ordena e printa o ranking de melhores jogadores no fim do jogo
void mostra_placar(JOGADOR *jog, JOG_PLACAR listaplacar[])
{
    FILE* arqtxt; // arquivo que será aberto
    short cont_placar = le_arq_txt(&arqtxt, listaplacar); // numero de pessoas salvas
    char tecla =  '0'; // tecla para interacoes do usuario
    int i; // i para ordenar placar

    // se o jogador acabou o jogo sem pressionar ESC
    if(jog->termino)
    {
        // pega nome do ojgador para ranking
        pega_nome(jog);

        // verifica se jogador entra no placar e
        // coloca o indice i para ordenacao na posicao correta
        i = insere_jogador_placar(jog, listaplacar, &cont_placar);

        // ordena placar apos mudancas
        ordena_placar(listaplacar, i);

        // salva placar atualizado
        salva_placar(arqtxt, listaplacar, cont_placar);

        // mostra placar na tela
        printa_placar(listaplacar, cont_placar);
    }

    // mensagem de encerrar jogo
    gotoxy(XINI, YFIM+1);
    clreol();
    printf("Aperte ENTER para encerrar...");

    // espera por ENTER para encerrar
    do{
        fflush(stdin);
        tecla = getch();
    }while(tecla != ENTER);
}

// funcao para inserir jogador na lista do placar,
// caso tenha atingido uma pontuacao alta o suficiente
short insere_jogador_placar (JOGADOR *jog, JOG_PLACAR listaplacar[], short *cont_placar)
{
    int i = 0; // indice para for

    // procura se nome do jogador ja esta no placar
    while(i < *cont_placar && strcmp(jog->nome, listaplacar[i].nome))
        i++;

    // caso em que jogador ja esta no placar
    if(i < *cont_placar)
    {
        // mantem a pontuacao mais alta
        if(jog->pontos > listaplacar[i].pontos)
        {
            listaplacar[i].pontos = jog->pontos;
        }
    }
    // caso o placar esteja cheio
    else if(i == N_PLACAR)
    {
        // verifica se pontuacao do jogador e maior que ultimo colocado
        if(jog->pontos >= listaplacar[i-1].pontos)
        {
            // caso sim, muda o ultimo colocado para o jogador
            strcpy(listaplacar[i-1].nome, jog->nome);
            listaplacar[i-1].pontos = jog->pontos;
        }
        // diminui i em 1 para manter no tamanho do arranjo
        i--;
    }
    // caso em que o placar nao esteja cheio
    else
    {
        // adiciona jogador em nova posicao
        strcpy(listaplacar[i].nome, jog->nome);
        listaplacar[i].pontos = jog->pontos;
        // e aumenta numero de jogadores no placar em 1
        (*cont_placar)++;
    }
    return i;
}

// funcao para ordenar placar de melhores jogadores
void ordena_placar (JOG_PLACAR listaplacar[], int i)
{
    JOG_PLACAR auxiliar; // JOG_PLACAR auxiliar para trocas

    // enquanto i for menor que o indice da primeira posicao (0),
    // e o placar estiver desordenado, o ordena
    while(i > 0 && listaplacar[i].pontos > listaplacar[i-1].pontos)
    {
        strcpy(auxiliar.nome, listaplacar[i].nome);
        auxiliar.pontos = listaplacar[i].pontos;

        strcpy(listaplacar[i].nome, listaplacar[i-1].nome);
        listaplacar[i].pontos = listaplacar[i-1].pontos;

        strcpy(listaplacar[i-1].nome, auxiliar.nome);
        listaplacar[i-1].pontos = auxiliar.pontos;

        i--;
    }
}

// funcao que salva o array de melhores jogadores em um arquivo .txt
void salva_placar(FILE *arqtxt, JOG_PLACAR listaplacar[], int cont_placar)
{
    int i; // indice de for

    arqtxt = fopen("BreakoutJog.txt", "w"); // arquivo aberto para escrita

    // se deu erro na abertura do arquivo, retornar 0
    if(!arqtxt)
    {
        printa_aviso(VERMELHO, "Erro ao abrir arquivo do placar!");
    }
    // senao, escrever no arquivo
    else
    {
        // preenche ate atingir numero de pessoas no placar
        for(i = 0; i < cont_placar && i < N_PLACAR; i++)
            fprintf(arqtxt, "%s#%d\n", listaplacar[i].nome, listaplacar[i].pontos);

        // fecha arquivo
        fclose(arqtxt);
    }
}

// funcao que printa na tela o placar de melhores jogadores
void printa_placar(JOG_PLACAR listaplacar[], int cont_placar)
{
    int i; // indice de for

    // desenha topo da tabela
    textcolor(LIGHTCYAN);
    cputsxy(XINF, YRANK-2, "       MELHORES JOGADORES");
    cputsxy(XINF, YRANK-1, "--------------------------------");
    textcolor(WHITE);

    // printa jogadores do ranking, com posicao, nome e pontuacao
    for(i = 0; i < cont_placar && i < N_PLACAR; i++)
    {
        gotoxy(XINF, YRANK+i);
        printf("%d | %-20s | %5d", i+1, listaplacar[i].nome, listaplacar[i].pontos);
    }
}
