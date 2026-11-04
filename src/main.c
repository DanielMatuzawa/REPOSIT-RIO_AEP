
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACOES 100
#define TAM_TEXTO 50
#define TAM_DATA 11

#define PLANEJADA 0
#define REALIZADA 1
#define CANCELADA 2

typedef struct {
    int codigo;
    char escola[TAM_TEXTO];
    char tema[TAM_TEXTO];
    char dataPrevista[TAM_DATA];
    char publicoAlvo[TAM_TEXTO];
    char responsavel[TAM_TEXTO];
    int qtdPrevista;
    int qtdEfetiva;
    int situacao;
} Acao;

/* ---------- Entrada e utilitarios ---------- */

void aparar(char *texto) {
    int inicio = 0;
    int fim = (int)strlen(texto) - 1;

    while (texto[inicio] != '\0' && isspace((unsigned char)texto[inicio])) {
        inicio++;
    }
    while (fim >= inicio && isspace((unsigned char)texto[fim])) {
        fim--;
    }
    memmove(texto, texto + inicio, fim - inicio + 1);
    texto[fim - inicio + 1] = '\0';
}


int lerTexto(const char *rotulo, char *destino, int tamanho) {
    char buffer[256];

    printf("%s", rotulo);
    destino[0] = '\0';
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    aparar(buffer);
    if ((int)strlen(buffer) >= tamanho) {
        return 0;
    }
    strcpy(destino, buffer);
    return 1;
}


int lerInteiro(const char *rotulo, int *valor) {
    char buffer[64];
    char *fim;
    long numero;

    printf("%s", rotulo);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    aparar(buffer);
    if (buffer[0] == '\0') {
        return 0;
    }
    numero = strtol(buffer, &fim, 10);
    if (*fim != '\0' || numero > 1000000 || numero < -1000000) {
        return 0;
    }
    *valor = (int)numero;
    return 1;
}

int dataValida(const char *data) {
    int i, dia, mes;

    if (strlen(data) != 10) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (data[i] != '/') {
                return 0;
            }
        } else if (!isdigit((unsigned char)data[i])) {
            return 0;
        }
    }
    dia = (data[0] - '0') * 10 + (data[1] - '0');
    mes = (data[3] - '0') * 10 + (data[4] - '0');
    return dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12;
}

int contemIgnorandoCaixa(const char *texto, const char *busca) {
    char t[TAM_TEXTO];
    char b[TAM_TEXTO];
    int i;

    strncpy(t, texto, TAM_TEXTO - 1);
    t[TAM_TEXTO - 1] = '\0';
    strncpy(b, busca, TAM_TEXTO - 1);
    b[TAM_TEXTO - 1] = '\0';
    for (i = 0; t[i] != '\0'; i++) {
        t[i] = (char)tolower((unsigned char)t[i]);
    }
    for (i = 0; b[i] != '\0'; i++) {
        b[i] = (char)tolower((unsigned char)b[i]);
    }
    return strstr(t, b) != NULL;
}

const char *nomeSituacao(int situacao) {
    if (situacao == REALIZADA) {
        return "Realizada";
    }
    if (situacao == CANCELADA) {
        return "Cancelada";
    }
    return "Planejada";
}

int buscarIndicePorCodigo(const Acao acoes[], int total, int codigo) {
    int i;

    for (i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}


void exibirMenu(void) {
    printf("\n=========== PSE EM ACAO ===========\n");
    printf("1 - Cadastrar acao\n");
    printf("2 - Listar acoes\n");
    printf("3 - Pesquisar acao\n");
    printf("4 - Atualizar situacao da acao\n");
    printf("5 - Gerar resumo geral\n");
    printf("6 - Sair\n");
    printf("===================================\n");
}

void exibirAcao(const Acao *a) {
    printf("\nCodigo.............: %d\n", a->codigo);
    printf("Escola.............: %s\n", a->escola);
    printf("Tema...............: %s\n", a->tema);
    printf("Data prevista......: %s\n", a->dataPrevista);
    printf("Publico-alvo.......: %s\n", a->publicoAlvo);
    printf("Responsavel........: %s\n", a->responsavel);
    printf("Participantes prev.: %d\n", a->qtdPrevista);
    printf("Participantes efet.: %d\n", a->qtdEfetiva);
    printf("Situacao...........: %s\n", nomeSituacao(a->situacao));
}



void cadastrarAcao(Acao acoes[], int *total) {
    Acao nova;
    int codigoOk;
    int quantidadeOk;
    int textosOk = 1;

    printf("\n--- CADASTRAR ACAO ---\n");
    codigoOk = lerInteiro("Codigo: ", &nova.codigo);
    textosOk &= lerTexto("Escola: ", nova.escola, TAM_TEXTO);
    textosOk &= lerTexto("Tema (ex: Vacinacao, Saude Bucal): ", nova.tema, TAM_TEXTO);
    textosOk &= lerTexto("Data prevista (dd/mm/aaaa): ", nova.dataPrevista, TAM_DATA);
    textosOk &= lerTexto("Publico-alvo: ", nova.publicoAlvo, TAM_TEXTO);
    textosOk &= lerTexto("Responsavel: ", nova.responsavel, TAM_TEXTO);
    quantidadeOk = lerInteiro("Quantidade prevista de participantes: ", &nova.qtdPrevista);

    if (!codigoOk || !quantidadeOk || !textosOk
        || nova.escola[0] == '\0' || nova.tema[0] == '\0'
        || nova.dataPrevista[0] == '\0' || nova.publicoAlvo[0] == '\0'
        || nova.responsavel[0] == '\0') {
        printf("Erro: campo obrigatorio vazio ou invalido.\n");
        return;
    }
    if (nova.codigo <= 0) {
        printf("Erro: o codigo deve ser maior que zero.\n");
        return;
    }
    if (!dataValida(nova.dataPrevista)) {
        printf("Erro: data invalida. Use o formato dd/mm/aaaa.\n");
        return;
    }
    if (buscarIndicePorCodigo(acoes, *total, nova.codigo) != -1) {
        printf("Erro: ja existe uma acao com o codigo %d.\n", nova.codigo);
        return;
    }
    if (nova.qtdPrevista < 0) {
        printf("Erro: a quantidade prevista nao pode ser negativa.\n");
        return;
    }
    if (*total >= MAX_ACOES) {
        printf("Erro: limite de %d acoes atingido.\n", MAX_ACOES);
        return;
    }

    nova.qtdEfetiva = 0;
    nova.situacao = PLANEJADA;
    acoes[*total] = nova;
    (*total)++;
    printf("Acao %d cadastrada com sucesso (situacao: Planejada).\n", nova.codigo);
}

void listarAcoes(const Acao acoes[], int total) {
    int i;

    printf("\n--- ACOES CADASTRADAS ---\n");
    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }
    printf("%-5s %-20s %-16s %-10s %-6s %-6s %-10s\n",
           "Cod", "Escola", "Tema", "Data", "Prev.", "Efet.", "Situacao");
    for (i = 0; i < total; i++) {
        printf("%-5d %-20.20s %-16.16s %-10s %-6d %-6d %-10s\n",
               acoes[i].codigo, acoes[i].escola, acoes[i].tema,
               acoes[i].dataPrevista, acoes[i].qtdPrevista,
               acoes[i].qtdEfetiva, nomeSituacao(acoes[i].situacao));
    }
    printf("Total: %d acao(oes).\n", total);
}

void pesquisarAcao(const Acao acoes[], int total) {
    int criterio, codigo, i, encontradas = 0;
    char termo[TAM_TEXTO];

    printf("\n--- PESQUISAR ACAO ---\n");
    printf("1 - Por codigo\n2 - Por escola\n3 - Por tema\n");
    if (!lerInteiro("Criterio: ", &criterio) || criterio < 1 || criterio > 3) {
        printf("Erro: criterio de pesquisa invalido.\n");
        return;
    }

    if (criterio == 1) {
        if (!lerInteiro("Codigo: ", &codigo)) {
            printf("Erro: codigo invalido.\n");
            return;
        }
        i = buscarIndicePorCodigo(acoes, total, codigo);
        if (i == -1) {
            printf("Nenhuma acao encontrada com o codigo %d.\n", codigo);
            return;
        }
        exibirAcao(&acoes[i]);
        return;
    }

    lerTexto(criterio == 2 ? "Escola (ou parte do nome): " : "Tema (ou parte do nome): ",
             termo, TAM_TEXTO);
    if (termo[0] == '\0') {
        printf("Erro: o termo de pesquisa nao pode ser vazio.\n");
        return;
    }
    for (i = 0; i < total; i++) {
        const char *campo = (criterio == 2) ? acoes[i].escola : acoes[i].tema;
        if (contemIgnorandoCaixa(campo, termo)) {
            exibirAcao(&acoes[i]);
            encontradas++;
        }
    }
    if (encontradas == 0) {
        printf("Nenhuma acao encontrada para \"%s\".\n", termo);
    } else {
        printf("\n%d acao(oes) encontrada(s).\n", encontradas);
    }
}

void atualizarSituacao(Acao acoes[], int total) {
    int codigo, indice, opcao, efetiva;

    printf("\n--- ATUALIZAR SITUACAO ---\n");
    if (!lerInteiro("Codigo da acao: ", &codigo)) {
        printf("Erro: codigo invalido.\n");
        return;
    }
    indice = buscarIndicePorCodigo(acoes, total, codigo);
    if (indice == -1) {
        printf("Erro: nao existe acao com o codigo %d.\n", codigo);
        return;
    }

    printf("Situacao atual: %s\n", nomeSituacao(acoes[indice].situacao));
    printf("1 - Planejada\n2 - Realizada\n3 - Cancelada\n");
    if (!lerInteiro("Nova situacao: ", &opcao) || opcao < 1 || opcao > 3) {
        printf("Erro: opcao de situacao invalida.\n");
        return;
    }

    if (opcao == 2) {
        if (!lerInteiro("Quantidade efetiva de participantes: ", &efetiva)) {
            printf("Erro: quantidade invalida. Situacao nao alterada.\n");
            return;
        }
        if (efetiva < 0) {
            printf("Erro: a quantidade nao pode ser negativa. Situacao nao alterada.\n");
            return;
        }
        acoes[indice].situacao = REALIZADA;
        acoes[indice].qtdEfetiva = efetiva;
    } else {
        acoes[indice].situacao = (opcao == 1) ? PLANEJADA : CANCELADA;
        acoes[indice].qtdEfetiva = 0;
    }
    printf("Situacao da acao %d atualizada para %s.\n",
           codigo, nomeSituacao(acoes[indice].situacao));
}

void gerarResumo(const Acao acoes[], int total) {
    int i;
    int planejadas = 0, realizadas = 0, canceladas = 0;
    int totalParticipantes = 0, previstoRealizadas = 0;
    double percentual = 0.0;

    for (i = 0; i < total; i++) {
        if (acoes[i].situacao == PLANEJADA) {
            planejadas++;
        } else if (acoes[i].situacao == REALIZADA) {
            realizadas++;
            totalParticipantes += acoes[i].qtdEfetiva;
            previstoRealizadas += acoes[i].qtdPrevista;
        } else {
            canceladas++;
        }
    }
    if (previstoRealizadas > 0) {
        percentual = (double)totalParticipantes / previstoRealizadas * 100.0;
    }

    printf("\n--- RESUMO GERAL ---\n");
    printf("Acoes cadastradas..............: %d\n", total);
    printf("Acoes planejadas...............: %d\n", planejadas);
    printf("Acoes realizadas...............: %d\n", realizadas);
    printf("Acoes canceladas...............: %d\n", canceladas);
    printf("Total de participantes.........: %d\n", totalParticipantes);
    printf("Previsto nas acoes realizadas..: %d\n", previstoRealizadas);
    printf("Percentual de participacao.....: %.1f%%\n", percentual);
}

int main(void) {
    Acao acoes[MAX_ACOES];
    int total = 0;
    int opcao;

    do {
        exibirMenu();
        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            if (feof(stdin)) {
                break;
            }
            opcao = -1;
        }

        switch (opcao) {
            case 1: cadastrarAcao(acoes, &total); break;
            case 2: listarAcoes(acoes, total); break;
            case 3: pesquisarAcao(acoes, total); break;
            case 4: atualizarSituacao(acoes, total); break;
            case 5: gerarResumo(acoes, total); break;
            case 6: printf("\nEncerrando o programa. Ate logo!\n"); break;
            default: printf("Opcao invalida. Escolha de 1 a 6.\n");
        }
    } while (opcao != 6);

    return 0;
}
