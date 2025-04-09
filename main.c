#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Definição de cores para Windows
#ifdef _WIN32
    #include <windows.h>
    #define LIMPAR_TELA "cls"
    #define COR_RESET ""
    #define COR_VERMELHO ""
    #define COR_VERDE ""
    #define COR_AMARELO ""
    #define COR_AZUL ""
    #define COR_MAGENTA ""
    #define COR_CIANO ""
    #define COR_BRANCO ""
#else
    // Definição de cores para sistemas baseados em Unix
    #define LIMPAR_TELA "clear"
    #define COR_RESET "\033[0m"
    #define COR_VERMELHO "\033[1;31m"
    #define COR_VERDE "\033[1;32m"
    #define COR_AMARELO "\033[1;33m"
    #define COR_AZUL "\033[1;34m"
    #define COR_MAGENTA "\033[1;35m"
    #define COR_CIANO "\033[1;36m"
    #define COR_BRANCO "\033[1;37m"
#endif

// Função para configurar as cores no Windows
void configurarCores() {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD atributosAtuais = consoleInfo.wAttributes;
    #endif
}

// Função para aplicar cor no Windows
void aplicarCor(const char* cor) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (strcmp(cor, "vermelho") == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        else if (strcmp(cor, "verde") == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else if (strcmp(cor, "amarelo") == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else if (strcmp(cor, "azul") == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (strcmp(cor, "magenta") == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (strcmp(cor, "ciano") == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (strcmp(cor, "branco") == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (strcmp(cor, "reset") == 0) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    #else
        if (strcmp(cor, "vermelho") == 0) printf(COR_VERMELHO);
        else if (strcmp(cor, "verde") == 0) printf(COR_VERDE);
        else if (strcmp(cor, "amarelo") == 0) printf(COR_AMARELO);
        else if (strcmp(cor, "azul") == 0) printf(COR_AZUL);
        else if (strcmp(cor, "magenta") == 0) printf(COR_MAGENTA);
        else if (strcmp(cor, "ciano") == 0) printf(COR_CIANO);
        else if (strcmp(cor, "branco") == 0) printf(COR_BRANCO);
        else if (strcmp(cor, "reset") == 0) printf(COR_RESET);
    #endif
}

// Função para limpar a tela
void limparTela() {
    system(LIMPAR_TELA);
}

//Definições das constantes
#define MINPALAVRAS 10
#define MINLETRAS 5
#define MAXTAMANHO 100
#define MAX_JOGADORES 10
#define MAX_CATEGORIAS 10
#define MAX_DICA 200

//Estrutura para armazenar as palavras
typedef struct palavra{
    char palavra[MAXTAMANHO];
    int tamanho;
    char categoria[50];
    char dica[MAX_DICA];
} Palavra;

// Estrutura para armazenar pontuações
typedef struct pontuacao {
    char nome[50];
    int pontos;
    char data[20];
    char dificuldade[10];
} Pontuacao;

int palavracont = 0;

// Função para contar palavras no arquivo
void contar_palavras() {
    FILE *arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        // Se o arquivo não existir, cria-o
        arquivo = fopen("palavras.bin", "wb");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo de palavras\n");
            exit(1);
        }
        palavracont = 0;
    } else {
        // Se o arquivo existir, conta as palavras
        Palavra palavra;
        palavracont = 0;
        while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
            palavracont++;
        }
    }
    fclose(arquivo);
}

// Função para limpar o buffer de entrada
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para validar entrada numérica
int ler_opcao() {
    int opcao;
    char entrada[100];
    
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return -1;
    }
    
    // Verifica se a entrada é um número
    for (int i = 0; i < strlen(entrada) - 1; i++) {
        if (!isdigit(entrada[i])) {
            return -1;
        }
    }
    
    sscanf(entrada, "%d", &opcao);
    return opcao;
}

// Função para validar se uma palavra contém apenas letras, hífens e espaços
int validar_palavra(const char *palavra) {
    for (int i = 0; i < strlen(palavra); i++) {
        if (!isalpha(palavra[i]) && palavra[i] != '-' && palavra[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// Função para converter palavra para minúsculas
void converter_para_minusculas(char *palavra) {
    for (int i = 0; i < strlen(palavra); i++) {
        palavra[i] = tolower(palavra[i]);
    }
}

// Função para registrar pontuação
void registrar_pontuacao(int pontos, const char* dificuldade) {
    FILE *arquivo;
    Pontuacao pontuacao;
    time_t tempo_atual;
    struct tm *info_tempo;
    
    // Obter o nome do jogador
    printf("Digite seu nome (máx. 50 caracteres): ");
    fgets(pontuacao.nome, sizeof(pontuacao.nome), stdin);
    pontuacao.nome[strcspn(pontuacao.nome, "\n")] = 0;
    
    // Registrar os pontos
    pontuacao.pontos = pontos;
    
    // Registrar a data atual
    tempo_atual = time(NULL);
    info_tempo = localtime(&tempo_atual);
    strftime(pontuacao.data, sizeof(pontuacao.data), "%d/%m/%Y", info_tempo);
    
    // Registrar a dificuldade
    strcpy(pontuacao.dificuldade, dificuldade);
    
    // Abrir arquivo para adicionar a pontuação
    arquivo = fopen("pontuacoes.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuações\n");
        return;
    }
    
    fwrite(&pontuacao, sizeof(Pontuacao), 1, arquivo);
    fclose(arquivo);
    printf("Pontuação registrada com sucesso!\n");
}

// Função para mostrar pontuações
void mostrar_pontuacoes() {
    FILE *arquivo;
    Pontuacao pontuacao;
    
    limparTela();
    
    aplicarCor("magenta");
    printf("\n");
    printf("  ██████╗  █████╗ ███╗   ██╗██╗  ██╗██╗███╗   ██╗ ██████╗ \n");
    printf("  ██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝██║████╗  ██║██╔════╝ \n");
    printf("  ██████╔╝███████║██╔██╗ ██║█████╔╝ ██║██╔██╗ ██║██║  ███╗\n");
    printf("  ██╔══██╗██╔══██║██║╚██╗██║██╔═██╗ ██║██║╚██╗██║██║   ██║\n");
    printf("  ██║  ██║██║  ██║██║ ╚████║██║  ██╗██║██║ ╚████║╚██████╔╝\n");
    printf("  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ \n");
    printf("\n");
    aplicarCor("reset");
    
    aplicarCor("amarelo");
    printf("===================================================\n");
    printf("              MELHORES PONTUAÇÕES                  \n");
    printf("===================================================\n\n");
    aplicarCor("reset");
    
    arquivo = fopen("pontuacoes.bin", "rb");
    if (arquivo == NULL) {
        aplicarCor("vermelho");
        printf("Nenhuma pontuação registrada ainda.\n");
        aplicarCor("reset");
        printf("\nPressione Enter para voltar ao menu...");
        getchar();
        return;
    }
    
    // Ler pontuações e colocá-las em um array
    Pontuacao pontuacoes[MAX_JOGADORES];
    int num_pontuacoes = 0;
    
    while (fread(&pontuacao, sizeof(Pontuacao), 1, arquivo) == 1 && num_pontuacoes < MAX_JOGADORES) {
        pontuacoes[num_pontuacoes++] = pontuacao;
    }
    
    fclose(arquivo);
    
    // Ordenar as pontuações (bubblesort)
    for (int i = 0; i < num_pontuacoes - 1; i++) {
        for (int j = 0; j < num_pontuacoes - i - 1; j++) {
            if (pontuacoes[j].pontos < pontuacoes[j + 1].pontos) {
                Pontuacao temp = pontuacoes[j];
                pontuacoes[j] = pontuacoes[j + 1];
                pontuacoes[j + 1] = temp;
            }
        }
    }
    
    // Cabeçalho da tabela
    aplicarCor("ciano");
    printf("%-5s %-20s %-10s %-12s %-10s\n", "POS", "NOME", "PONTOS", "DATA", "DIFICULDADE");
    printf("%-5s %-20s %-10s %-12s %-10s\n", "===", "====================", "==========", "============", "==========");
    aplicarCor("reset");
    
    // Mostrar as top pontuações
    for (int i = 0; i < num_pontuacoes; i++) {
        // Definir cor baseada na posição
        if (i == 0) {
            aplicarCor("amarelo"); // Primeiro lugar (ouro)
        } else if (i == 1) {
            aplicarCor("branco");  // Segundo lugar (prata)
        } else if (i == 2) {
            aplicarCor("verde");   // Terceiro lugar (bronze)
        } else {
            aplicarCor("reset");   // Demais posições
        }
        
        // Exibir medalha para os três primeiros
        char posicao[10];
        if (i == 0) {
            strcpy(posicao, "1 🥇");
        } else if (i == 1) {
            strcpy(posicao, "2 🥈");
        } else if (i == 2) {
            strcpy(posicao, "3 🥉");
        } else {
            sprintf(posicao, "%d", i + 1);
        }
        
        // Exibir cor diferente para a dificuldade
        printf("%-5s %-20s %-10d %-12s ", 
               posicao, 
               pontuacoes[i].nome, 
               pontuacoes[i].pontos, 
               pontuacoes[i].data);
        
        // Cor para a dificuldade
        if (strcmp(pontuacoes[i].dificuldade, "facil") == 0) {
            aplicarCor("verde");
        } else if (strcmp(pontuacoes[i].dificuldade, "normal") == 0) {
            aplicarCor("amarelo");
        } else {
            aplicarCor("vermelho");
        }
        
        printf("%-10s\n", pontuacoes[i].dificuldade);
        aplicarCor("reset");
    }
    
    aplicarCor("reset");
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

// Função para listar palavras
void listar_palavras() {
    FILE *arquivo;
    Palavra palavra;
    int contador = 0;
    
    limparTela();
    
    aplicarCor("amarelo");
    printf("\n===== PALAVRAS CADASTRADAS =====\n\n");
    aplicarCor("reset");
    
    arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        aplicarCor("vermelho");
        printf("Não há palavras cadastradas.\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Cabeçalho da tabela
    aplicarCor("ciano");
    printf("%-5s %-30s %-15s %-30s\n", "ID", "PALAVRA", "CATEGORIA", "DICA");
    printf("%-5s %-30s %-15s %-30s\n", "==", "==============================", "===============", "==============================");
    aplicarCor("reset");
    
    // Listar palavras
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        contador++;
        
        // Alternar cores para facilitar a leitura
        if (contador % 2 == 0) {
            aplicarCor("reset");
        } else {
            aplicarCor("azul");
        }
        
        // Limitar o tamanho da dica para exibição
        char dica_exibida[31] = "";
        strncpy(dica_exibida, palavra.dica, 30);
        if (strlen(palavra.dica) > 30) {
            strcat(dica_exibida, "...");
        }
        
        printf("%-5d %-30s %-15s %-30s\n", 
               contador, 
               palavra.palavra, 
               palavra.categoria, 
               dica_exibida);
    }
    
    aplicarCor("reset");
    
    if (contador == 0) {
        aplicarCor("vermelho");
        printf("\nNão há palavras cadastradas.\n");
        aplicarCor("reset");
    } else {
        aplicarCor("verde");
        printf("\nTotal: %d palavras cadastradas.\n", contador);
        aplicarCor("reset");
    }
    
    fclose(arquivo);
    
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

// Função para apagar palavra
void apagar_palavra() {
    FILE *arquivo, *temp;
    Palavra palavra;
    int indice, contador = 0, encontrou = 0;
    
    limparTela();
    
    aplicarCor("amarelo");
    printf("\n===== APAGAR PALAVRA =====\n\n");
    aplicarCor("reset");
    
    arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        aplicarCor("vermelho");
        printf("Não há palavras cadastradas.\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Cabeçalho da tabela
    aplicarCor("ciano");
    printf("%-5s %-30s %-15s\n", "ID", "PALAVRA", "CATEGORIA");
    printf("%-5s %-30s %-15s\n", "==", "==============================", "===============");
    aplicarCor("reset");
    
    // Listar palavras
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        contador++;
        
        // Alternar cores para facilitar a leitura
        if (contador % 2 == 0) {
            aplicarCor("reset");
        } else {
            aplicarCor("azul");
        }
        
        printf("%-5d %-30s %-15s\n", contador, palavra.palavra, palavra.categoria);
    }
    aplicarCor("reset");
    
    fclose(arquivo);
    
    if (contador == 0) {
        aplicarCor("vermelho");
        printf("\nNão há palavras para apagar.\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Verificar se há palavras suficientes para continuar com o jogo
    if (contador <= MINPALAVRAS) {
        aplicarCor("vermelho");
        printf("\nVocê tem apenas %d palavras cadastradas. O mínimo necessário para o jogo é %d.\n", contador, MINPALAVRAS);
        printf("Impossível apagar mais palavras!\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    printf("\nDigite o número da palavra que deseja apagar (1-%d): ", contador);
    indice = ler_opcao();
    
    if (indice < 1 || indice > contador) {
        aplicarCor("vermelho");
        printf("Índice inválido!\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Confirmar a exclusão
    aplicarCor("amarelo");
    printf("\nTem certeza que deseja apagar esta palavra? (s/n): ");
    aplicarCor("reset");
    char confirmacao;
    scanf(" %c", &confirmacao);
    limpar_buffer();
    
    if (tolower(confirmacao) != 's') {
        aplicarCor("verde");
        printf("Operação cancelada pelo usuário.\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Criar um arquivo temporário
    temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        aplicarCor("vermelho");
        printf("Erro ao criar arquivo temporário!\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Abrir arquivo original para leitura
    arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        aplicarCor("vermelho");
        printf("Erro ao abrir o arquivo!\n");
        aplicarCor("reset");
        fclose(temp);
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Copiar palavras, exceto a escolhida para remoção
    contador = 0;
    Palavra palavra_removida;
    
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        contador++;
        
        if (contador != indice) {
            fwrite(&palavra, sizeof(Palavra), 1, temp);
        } else {
            encontrou = 1;
            palavra_removida = palavra;
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    // Substituir o arquivo original pelo temporário
    if (encontrou) {
        remove("palavras.bin");
        rename("temp.bin", "palavras.bin");
        palavracont--; // Atualizar contador global de palavras
        
        aplicarCor("verde");
        printf("\nPalavra ");
        aplicarCor("ciano");
        printf("'%s'", palavra_removida.palavra);
        aplicarCor("verde");
        printf(" apagada com sucesso!\n");
        aplicarCor("reset");
    } else {
        remove("temp.bin");
        aplicarCor("vermelho");
        printf("\nErro ao apagar palavra.\n");
        aplicarCor("reset");
    }
    
    printf("\nPressione Enter para continuar...");
    getchar();
}

// Função para cadastrar palavra
void cadastrar_palavra() {
    Palavra nova_palavra;
    FILE *arquivo;
    char entrada[MAXTAMANHO];
    
    limparTela();
    aplicarCor("amarelo");
    printf("\n===== CADASTRAR NOVA PALAVRA =====\n\n");
    aplicarCor("reset");
    
    printf("Digite a palavra que deseja cadastrar (pode conter letras, hífens e espaços): ");
    fgets(entrada, MAXTAMANHO, stdin);
    
    // Remover a quebra de linha
    entrada[strcspn(entrada, "\n")] = 0;
    
    // Copiar para a estrutura
    strcpy(nova_palavra.palavra, entrada);
    
    // Converter para minúsculas
    converter_para_minusculas(nova_palavra.palavra);
    
    // Validar se contém apenas caracteres permitidos
    if (!validar_palavra(nova_palavra.palavra)) {
        aplicarCor("vermelho");
        printf("A palavra deve conter apenas letras, hífens e espaços.\n");
        aplicarCor("reset");
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Verificar tamanho mínimo da palavra (excluindo espaços e hífens)
    int letras_validas = 0;
    for (int i = 0; i < strlen(nova_palavra.palavra); i++) {
        if (isalpha(nova_palavra.palavra[i])) {
            letras_validas++;
        }
    }
    
    nova_palavra.tamanho = strlen(nova_palavra.palavra);
    if (letras_validas < MINLETRAS) {
        aplicarCor("vermelho");
        printf("A palavra deve ter no mínimo %d letras (excluindo hífens e espaços).\n", MINLETRAS);
        aplicarCor("reset");
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Verificar se a palavra já existe
    FILE *verificacao = fopen("palavras.bin", "rb");
    if (verificacao != NULL) {
        Palavra palavra_existente;
        while (fread(&palavra_existente, sizeof(Palavra), 1, verificacao) == 1) {
            if (strcmp(palavra_existente.palavra, nova_palavra.palavra) == 0) {
                aplicarCor("vermelho");
                printf("Esta palavra já está cadastrada.\n");
                aplicarCor("reset");
                fclose(verificacao);
                printf("Pressione Enter para continuar...");
                getchar();
                return;
            }
        }
        fclose(verificacao);
    }
    
    // Solicitar categoria
    aplicarCor("ciano");
    printf("\nEscolha uma categoria para a palavra:\n");
    printf("1. Animais\n");
    printf("2. Comidas\n");
    printf("3. Países\n");
    printf("4. Esportes\n");
    printf("5. Filmes\n");
    printf("6. Profissões\n");
    printf("7. Frutas\n");
    printf("8. Objetos\n");
    printf("9. Outro (personalizada)\n");
    aplicarCor("reset");
    
    int opcao_categoria = ler_opcao();
    
    switch(opcao_categoria) {
        case 1:
            strcpy(nova_palavra.categoria, "Animais");
            break;
        case 2:
            strcpy(nova_palavra.categoria, "Comidas");
            break;
        case 3:
            strcpy(nova_palavra.categoria, "Países");
            break;
        case 4:
            strcpy(nova_palavra.categoria, "Esportes");
            break;
        case 5:
            strcpy(nova_palavra.categoria, "Filmes");
            break;
        case 6:
            strcpy(nova_palavra.categoria, "Profissões");
            break;
        case 7:
            strcpy(nova_palavra.categoria, "Frutas");
            break;
        case 8:
            strcpy(nova_palavra.categoria, "Objetos");
            break;
        case 9:
            aplicarCor("amarelo");
            printf("Digite a categoria personalizada: ");
            aplicarCor("reset");
            fgets(nova_palavra.categoria, 50, stdin);
            nova_palavra.categoria[strcspn(nova_palavra.categoria, "\n")] = 0;
            break;
        default:
            strcpy(nova_palavra.categoria, "Geral");
            break;
    }
    
    // Solicitar dica
    aplicarCor("amarelo");
    printf("\nDigite uma dica para esta palavra (opcional): ");
    aplicarCor("reset");
    fgets(nova_palavra.dica, MAX_DICA, stdin);
    nova_palavra.dica[strcspn(nova_palavra.dica, "\n")] = 0;
    
    // Cadastrar a nova palavra
    arquivo = fopen("palavras.bin", "ab");
    if (arquivo == NULL) {
        aplicarCor("vermelho");
        printf("Erro ao abrir o arquivo!\n");
        aplicarCor("reset");
        printf("Pressione Enter para continuar...");
        getchar();
        return;
    }
    
    fwrite(&nova_palavra, sizeof(Palavra), 1, arquivo);
    fclose(arquivo);
    
    palavracont++;
    aplicarCor("verde");
    printf("\nPalavra cadastrada com sucesso!\n");
    aplicarCor("reset");
    printf("Pressione Enter para continuar...");
    getchar();
}

// Função para atualizar palavra
void atualizar_palavra() {
    FILE *arquivo;
    Palavra palavra;
    int indice, contador = 0, encontrou = 0;
    char entrada[MAXTAMANHO];
    
    limparTela();
    
    aplicarCor("amarelo");
    printf("\n===== ATUALIZAR PALAVRA =====\n\n");
    aplicarCor("reset");
    
    arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        aplicarCor("vermelho");
        printf("Não há palavras cadastradas.\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Cabeçalho da tabela
    aplicarCor("ciano");
    printf("%-5s %-30s %-15s\n", "ID", "PALAVRA", "CATEGORIA");
    printf("%-5s %-30s %-15s\n", "==", "==============================", "===============");
    aplicarCor("reset");
    
    // Listar palavras
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        contador++;
        
        // Alternar cores para facilitar a leitura
        if (contador % 2 == 0) {
            aplicarCor("reset");
        } else {
            aplicarCor("azul");
        }
        
        printf("%-5d %-30s %-15s\n", contador, palavra.palavra, palavra.categoria);
    }
    aplicarCor("reset");
    
    fclose(arquivo);
    
    if (contador == 0) {
        aplicarCor("vermelho");
        printf("\nNão há palavras para atualizar.\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    printf("\nDigite o número da palavra que deseja atualizar (1-%d): ", contador);
    indice = ler_opcao();
    
    if (indice < 1 || indice > contador) {
        aplicarCor("vermelho");
        printf("Índice inválido!\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Obter a palavra atual para mostrar
    arquivo = fopen("palavras.bin", "rb");
    Palavra palavra_atual;
    fseek(arquivo, (indice-1) * sizeof(Palavra), SEEK_SET);
    fread(&palavra_atual, sizeof(Palavra), 1, arquivo);
    fclose(arquivo);
    
    aplicarCor("verde");
    printf("\nAtualizando a palavra: ");
    aplicarCor("ciano");
    printf("%s\n", palavra_atual.palavra);
    aplicarCor("reset");
    
    // Ler a nova palavra
    Palavra nova_palavra;
    printf("\nDigite a nova palavra (pode conter letras, hífens e espaços)\n");
    printf("ou deixe em branco para manter a palavra atual: ");
    fgets(entrada, MAXTAMANHO, stdin);
    
    // Remover a quebra de linha
    entrada[strcspn(entrada, "\n")] = 0;
    
    // Verificar se o usuário deixou em branco para manter a palavra
    if (strlen(entrada) == 0) {
        strcpy(nova_palavra.palavra, palavra_atual.palavra);
        nova_palavra.tamanho = palavra_atual.tamanho;
    } else {
        // Copiar para a estrutura
        strcpy(nova_palavra.palavra, entrada);
        
        // Converter para minúsculas
        converter_para_minusculas(nova_palavra.palavra);
        
        // Validar se contém apenas caracteres permitidos
        if (!validar_palavra(nova_palavra.palavra)) {
            aplicarCor("vermelho");
            printf("A palavra deve conter apenas letras, hífens e espaços.\n");
            aplicarCor("reset");
            printf("\nPressione Enter para continuar...");
            getchar();
            return;
        }
        
        // Verificar tamanho mínimo da palavra (excluindo espaços e hífens)
        int letras_validas = 0;
        for (int i = 0; i < strlen(nova_palavra.palavra); i++) {
            if (isalpha(nova_palavra.palavra[i])) {
                letras_validas++;
            }
        }
        
        nova_palavra.tamanho = strlen(nova_palavra.palavra);
        if (letras_validas < MINLETRAS) {
            aplicarCor("vermelho");
            printf("A palavra deve ter no mínimo %d letras (excluindo hífens e espaços).\n", MINLETRAS);
            aplicarCor("reset");
            printf("\nPressione Enter para continuar...");
            getchar();
            return;
        }
        
        // Verificar se a palavra já existe (exceto ela mesma)
        arquivo = fopen("palavras.bin", "rb");
        if (arquivo != NULL) {
            Palavra palavra_existente;
            int indice_atual = 0;
            
            while (fread(&palavra_existente, sizeof(Palavra), 1, arquivo) == 1) {
                indice_atual++;
                // Verificar se a palavra é diferente da que está sendo atualizada
                if (indice_atual != indice && 
                    strcmp(palavra_existente.palavra, nova_palavra.palavra) == 0) {
                    aplicarCor("vermelho");
                    printf("Esta palavra já está cadastrada.\n");
                    aplicarCor("reset");
                    fclose(arquivo);
                    printf("\nPressione Enter para continuar...");
                    getchar();
                    return;
                }
            }
            fclose(arquivo);
        }
    }
    
    // Solicitar categoria
    aplicarCor("ciano");
    printf("\nEscolha uma categoria para a palavra:\n");
    printf("1. Animais\n");
    printf("2. Comidas\n");
    printf("3. Países\n");
    printf("4. Esportes\n");
    printf("5. Filmes\n");
    printf("6. Profissões\n");
    printf("7. Frutas\n");
    printf("8. Objetos\n");
    printf("9. Outro (personalizada)\n");
    printf("0. Manter categoria atual (%s)\n", palavra_atual.categoria);
    aplicarCor("reset");
    
    int opcao_categoria = ler_opcao();
    
    switch(opcao_categoria) {
        case 0:
            strcpy(nova_palavra.categoria, palavra_atual.categoria);
            break;
        case 1:
            strcpy(nova_palavra.categoria, "Animais");
            break;
        case 2:
            strcpy(nova_palavra.categoria, "Comidas");
            break;
        case 3:
            strcpy(nova_palavra.categoria, "Países");
            break;
        case 4:
            strcpy(nova_palavra.categoria, "Esportes");
            break;
        case 5:
            strcpy(nova_palavra.categoria, "Filmes");
            break;
        case 6:
            strcpy(nova_palavra.categoria, "Profissões");
            break;
        case 7:
            strcpy(nova_palavra.categoria, "Frutas");
            break;
        case 8:
            strcpy(nova_palavra.categoria, "Objetos");
            break;
        case 9:
            aplicarCor("amarelo");
            printf("Digite a categoria personalizada: ");
            aplicarCor("reset");
            fgets(nova_palavra.categoria, 50, stdin);
            nova_palavra.categoria[strcspn(nova_palavra.categoria, "\n")] = 0;
            break;
        default:
            strcpy(nova_palavra.categoria, "Geral");
            break;
    }
    
    // Solicitar dica
    aplicarCor("amarelo");
    printf("\nDica atual: %s\n", palavra_atual.dica);
    printf("\nDigite uma nova dica para esta palavra (opcional)\n");
    printf("ou deixe em branco para manter a dica atual: ");
    aplicarCor("reset");
    fgets(entrada, MAX_DICA, stdin);
    entrada[strcspn(entrada, "\n")] = 0;
    
    if (strlen(entrada) == 0) {
        strcpy(nova_palavra.dica, palavra_atual.dica);
    } else {
        strcpy(nova_palavra.dica, entrada);
    }
    
    // Confirmar a atualização
    aplicarCor("amarelo");
    printf("\nTem certeza que deseja atualizar esta palavra? (s/n): ");
    aplicarCor("reset");
    char confirmacao;
    scanf(" %c", &confirmacao);
    limpar_buffer();
    
    if (tolower(confirmacao) != 's') {
        aplicarCor("verde");
        printf("Operação cancelada pelo usuário.\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Criar um arquivo temporário
    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        aplicarCor("vermelho");
        printf("Erro ao criar arquivo temporário!\n");
        aplicarCor("reset");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Abrir arquivo original para leitura
    arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        aplicarCor("vermelho");
        printf("Erro ao abrir o arquivo!\n");
        aplicarCor("reset");
        fclose(temp);
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    
    // Copiar palavras, substituindo a escolhida
    contador = 0;
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        contador++;
        
        if (contador == indice) {
            fwrite(&nova_palavra, sizeof(Palavra), 1, temp);
            encontrou = 1;
        } else {
            fwrite(&palavra, sizeof(Palavra), 1, temp);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    // Substituir o arquivo original pelo temporário
    if (encontrou) {
        remove("palavras.bin");
        rename("temp.bin", "palavras.bin");
        aplicarCor("verde");
        printf("\nPalavra atualizada com sucesso!\n");
        aplicarCor("reset");
    } else {
        remove("temp.bin");
        aplicarCor("vermelho");
        printf("\nErro ao atualizar palavra.\n");
        aplicarCor("reset");
    }
    
    printf("\nPressione Enter para continuar...");
    getchar();
}

// Função para mostrar tela de boas-vindas
void mostrar_tela_boas_vindas() {
    limparTela();
    aplicarCor("ciano");
    printf("\n");
    printf("  ███████╗ ██████╗ ██████╗  ██████╗ █████╗ \n");
    printf("  ██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔══██╗\n");
    printf("  █████╗  ██║   ██║██████╔╝██║     ███████║\n");
    printf("  ██╔══╝  ██║   ██║██╔══██╗██║     ██╔══██║\n");
    printf("  ██║     ╚██████╔╝██║  ██║╚██████╗██║  ██║\n");
    printf("  ╚═╝      ╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝\n");
    printf("\n");
    aplicarCor("reset");
    
    aplicarCor("amarelo");
    printf("=====================================================\n");
    printf("           BEM-VINDO AO JOGO DA FORCA               \n");
    printf("=====================================================\n");
    aplicarCor("reset");
    
    aplicarCor("verde");
    printf("\nComo jogar:\n");
    printf("1. Para jogar, você deve ter pelo menos %d palavras cadastradas.\n", MINPALAVRAS);
    printf("2. Você pode escolher a dificuldade do jogo (fácil, normal ou difícil).\n");
    printf("3. Tente adivinhar a palavra secreta sugerindo letras.\n");
    printf("4. Cada erro adiciona uma parte ao boneco da forca.\n");
    printf("5. Quando o boneco estiver completo, você perde.\n");
    printf("6. Suas pontuações são salvas para comparar com outros jogadores.\n\n");
    aplicarCor("reset");
    
    aplicarCor("amarelo");
    printf("Pressione Enter para continuar...");
    aplicarCor("reset");
    getchar();
}

// Função para desenhar a forca
void desenhar_forca(int erros) {
    printf("\n");
    printf("  _______\n");
    printf("  |     |\n");
    printf("  |     %c\n", (erros >= 1) ? 'O' : ' ');
    printf("  |    %c%c%c\n", (erros >= 3) ? '/' : ' ', (erros >= 2) ? '|' : ' ', (erros >= 4) ? '\\' : ' ');
    printf("  |    %c %c\n", (erros >= 5) ? '/' : ' ', (erros >= 6) ? '\\' : ' ');
    printf(" _|_\n");
    printf("|   |_______\n");
    printf("|           |\n");
    printf("|___________|\n");
}

// Função para jogar
void jogar() {
    int palavraind, i, tentativas, acertos = 0;
    char letra;
    char letras_tentadas[26] = {0}; // Para registrar letras já tentadas
    int num_letras_tentadas = 0;
    char dificuldade[10] = "normal";
    Palavra palavra_sorteada;
    char palavra_exibida[MAXTAMANHO];
    FILE *arquivo;
    int dica_usada = 0;
    
    limparTela();
    aplicarCor("amarelo");
    printf("\n===== SELECIONE A DIFICULDADE =====\n\n");
    aplicarCor("reset");
    
    aplicarCor("verde");
    printf("1 - Fácil (10 tentativas)\n");
    aplicarCor("amarelo");
    printf("2 - Normal (6 tentativas)\n");
    aplicarCor("vermelho");
    printf("3 - Difícil (4 tentativas)\n");
    aplicarCor("reset");
    
    printf("\nEscolha a dificuldade: ");
    int opcao_dificuldade = ler_opcao();
    
    // Definir tentativas baseado na dificuldade
    switch(opcao_dificuldade) {
        case 1:
            tentativas = 10;
            strcpy(dificuldade, "facil");
            break;
        case 2:
            tentativas = 6;
            strcpy(dificuldade, "normal");
            break;
        case 3:
            tentativas = 4;
            strcpy(dificuldade, "dificil");
            break;
        default:
            aplicarCor("amarelo");
            printf("Opção inválida, usando dificuldade normal.\n");
            aplicarCor("reset");
            tentativas = 6;
            strcpy(dificuldade, "normal");
    }
    
    // Sortear uma palavra aleatória
    srand(time(NULL));
    palavraind = rand() % palavracont;
    
    arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        aplicarCor("vermelho");
        printf("Erro ao abrir o arquivo!\n");
        aplicarCor("reset");
        return;
    }
    
    // Posicionar no índice sorteado
    fseek(arquivo, palavraind * sizeof(Palavra), SEEK_SET);
    
    // Ler a palavra
    fread(&palavra_sorteada, sizeof(Palavra), 1, arquivo);
    fclose(arquivo);
    
    // Calcular quantas letras precisam ser acertadas (excluindo espaços e hífens)
    int total_letras = 0;
    for (i = 0; i < palavra_sorteada.tamanho; i++) {
        if (isalpha(palavra_sorteada.palavra[i])) {
            total_letras++;
        }
    }
    
    // Inicializar palavra_exibida: mostrar hífens e espaços, ocultar letras
    for (i = 0; i < palavra_sorteada.tamanho; i++) {
        if (palavra_sorteada.palavra[i] == ' ') {
            palavra_exibida[i] = ' ';
        } else if (palavra_sorteada.palavra[i] == '-') {
            palavra_exibida[i] = '-';
        } else {
            palavra_exibida[i] = '_';
        }
    }
    palavra_exibida[i] = '\0';
    
    // Verificar se existem hífens ou espaços e ajustar o contador de acertos
    for (i = 0; i < palavra_sorteada.tamanho; i++) {
        if (palavra_sorteada.palavra[i] == ' ' || palavra_sorteada.palavra[i] == '-') {
            acertos++;
        }
    }
    
    int pontos = 100; // Sistema de pontuação inicial
    
    // Loop principal do jogo
    while (tentativas > 0 && acertos < palavra_sorteada.tamanho) {
        limparTela(); // Limpar a tela
        
        aplicarCor("ciano");
        printf("\n===== JOGO DA FORCA =====\n");
        aplicarCor("reset");
        
        // Exibir informações sobre a partida
        printf("Categoria: ");
        aplicarCor("magenta");
        printf("%s\n", palavra_sorteada.categoria);
        aplicarCor("reset");
        
        printf("Dificuldade: ");
        if (strcmp(dificuldade, "facil") == 0) {
            aplicarCor("verde");
        } else if (strcmp(dificuldade, "normal") == 0) {
            aplicarCor("amarelo");
        } else {
            aplicarCor("vermelho");
        }
        printf("%s\n", dificuldade);
        aplicarCor("reset");
        
        printf("Tentativas restantes: ");
        if (tentativas > 4) {
            aplicarCor("verde");
        } else if (tentativas > 2) {
            aplicarCor("amarelo");
        } else {
            aplicarCor("vermelho");
        }
        printf("%d\n", tentativas);
        aplicarCor("reset");
        
        printf("Pontuação atual: ");
        aplicarCor("verde");
        printf("%d\n\n", pontos);
        aplicarCor("reset");
        
        // Mostrar palavra atual
        printf("Palavra: ");
        aplicarCor("ciano");
        for (i = 0; i < palavra_sorteada.tamanho; i++) {
            printf("%c ", palavra_exibida[i]);
        }
        aplicarCor("reset");
        printf("\n\n");
        
        // Mostrar letras já tentadas
        printf("Letras tentadas: ");
        for (i = 0; i < num_letras_tentadas; i++) {
            aplicarCor("amarelo");
            printf("%c ", letras_tentadas[i]);
            aplicarCor("reset");
        }
        printf("\n\n");
        
        // Desenhar a forca baseado nas tentativas
        if (tentativas <= 2) {
            aplicarCor("vermelho");
        } else if (tentativas <= 4) {
            aplicarCor("amarelo");
        } else {
            aplicarCor("verde");
        }
        desenhar_forca(6 - tentativas);
        aplicarCor("reset");
        
        // Opção de dica, se disponível e ainda não utilizada
        if (!dica_usada && strlen(palavra_sorteada.dica) > 0 && tentativas <= 3) {
            printf("\nDeseja uma dica? Vai custar 15 pontos (s/n): ");
            char opcao_dica;
            scanf(" %c", &opcao_dica);
            limpar_buffer();
            
            if (tolower(opcao_dica) == 's') {
                aplicarCor("amarelo");
                printf("\nDICA: %s\n", palavra_sorteada.dica);
                aplicarCor("reset");
                pontos -= 15;
                if (pontos < 0) pontos = 0;
                dica_usada = 1;
                printf("\nPressione Enter para continuar...");
                getchar();
                continue;
            }
        }
        
        // Pedir uma letra
        printf("\nDigite uma letra (ou '0' para desistir): ");
        scanf(" %c", &letra);
        limpar_buffer();
        
        // Verificar se o jogador quer desistir
        if (letra == '0') {
            aplicarCor("amarelo");
            printf("\nTem certeza que deseja desistir? (s/n): ");
            aplicarCor("reset");
            char confirmacao;
            scanf(" %c", &confirmacao);
            limpar_buffer();
            
            if (tolower(confirmacao) == 's') {
                limparTela();
                aplicarCor("vermelho");
                printf("\nVocê desistiu!\n");
                printf("A palavra era: %s\n", palavra_sorteada.palavra);
                aplicarCor("reset");
                printf("\nPressione Enter para voltar ao menu...");
                getchar();
                return;
            } else {
                continue;
            }
        }
        
        letra = tolower(letra);
        
        // Verificar se a letra já foi tentada
        int ja_tentou = 0;
        for (i = 0; i < num_letras_tentadas; i++) {
            if (letras_tentadas[i] == letra) {
                ja_tentou = 1;
                break;
            }
        }
        
        if (ja_tentou) {
            aplicarCor("vermelho");
            printf("\nVocê já tentou esta letra!\n");
            aplicarCor("reset");
            printf("\nPressione Enter para continuar...");
            getchar();
            continue;
        }
        
        // Registrar a letra tentada
        letras_tentadas[num_letras_tentadas++] = letra;
        
        // Verificar se a letra está na palavra
        int acertou = 0;
        for (i = 0; i < palavra_sorteada.tamanho; i++) {
            if (palavra_sorteada.palavra[i] == letra && palavra_exibida[i] == '_') {
                palavra_exibida[i] = letra;
                acertos++;
                acertou = 1;
            }
        }
        
        // Atualizar pontuação e fornecer feedback
        if (acertou) {
            pontos += 10;
            aplicarCor("verde");
            printf("\nAcertou! +10 pontos\n");
            aplicarCor("reset");
        } else {
            tentativas--;
            pontos -= 5;
            if (pontos < 0) pontos = 0;
            aplicarCor("vermelho");
            printf("\nErrou! -5 pontos\n");
            aplicarCor("reset");
        }
        
        printf("\nPressione Enter para continuar...");
        getchar();
    }
    
    limparTela(); // Limpar a tela uma última vez
    
    // Desenhar o estado final da forca
    if (acertos == palavra_sorteada.tamanho) {
        aplicarCor("verde");
    } else {
        aplicarCor("vermelho");
    }
    desenhar_forca(6 - tentativas);
    aplicarCor("reset");
    
    // Mostrar resultado final
    if (acertos == palavra_sorteada.tamanho) {
        aplicarCor("verde");
        printf("\n\n");
        printf("███████  █████╗ ██████╗  █████╗ ██████╗ ███████╗███╗   ██╗███████╗██╗\n");
        printf("██╔══██ ██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔════╝████╗  ██║██╔════╝██║\n");
        printf("███████ ███████║██████╔╝███████║██████╔╝█████╗  ██╔██╗ ██║███████╗██║\n");
        printf("██╔═══╝ ██╔══██║██╔══██╗██╔══██║██╔══██╗██╔══╝  ██║╚██╗██║╚════██║╚═╝\n");
        printf("██║     ██║  ██║██║  ██║██║  ██║██████╔╝███████╗██║ ╚████║███████║██╗\n");
        printf("╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═══╝╚══════╝╚═╝\n");
        printf("\n");
        printf("Parabéns! Você venceu!\n");
        printf("A palavra era: %s\n", palavra_sorteada.palavra);
        printf("Pontuação final: %d\n\n", pontos);
        aplicarCor("reset");
        
        // Bônus por dificuldade
        if (strcmp(dificuldade, "dificil") == 0) {
            pontos = pontos * 2;
            aplicarCor("amarelo");
            printf("Bônus de dificuldade: pontuação duplicada para %d!\n\n", pontos);
            aplicarCor("reset");
        } else if (strcmp(dificuldade, "facil") == 0) {
            pontos = pontos / 2;
            aplicarCor("amarelo");
            printf("Penalidade de dificuldade: pontuação reduzida para %d!\n\n", pontos);
            aplicarCor("reset");
        }
        
        // Registrar pontuação
        aplicarCor("ciano");
        printf("Vamos registrar sua pontuação!\n\n");
        aplicarCor("reset");
        registrar_pontuacao(pontos, dificuldade);
    } else {
        aplicarCor("vermelho");
        printf("\n\n");
        printf(" ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ \n");
        printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
        printf("██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝\n");
        printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
        printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n");
        printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");
        printf("\n");
        printf("Você perdeu!\n");
        printf("A palavra era: %s\n\n", palavra_sorteada.palavra);
        aplicarCor("reset");
    }
    
    printf("Pressione Enter para voltar ao menu...");
    getchar();
}

//Protótipo das funções
void cadastrar_palavra();
void listar_palavras();
void apagar_palavra();
void atualizar_palavra();
void jogar();
void menu_inicial();
void limpar_buffer();
void desenhar_forca(int erros);
void contar_palavras();
void registrar_pontuacao(int pontos, const char* dificuldade);
void mostrar_pontuacoes();
void converter_para_minusculas(char *palavra);
int validar_palavra(const char *palavra);
int ler_opcao();
void configurarCores();
void aplicarCor(const char* cor);
void limparTela();
void mostrar_tela_boas_vindas();

int main() {
    // Configurar as cores no Windows
    configurarCores();
    
    // Inicializa a contagem de palavras
    contar_palavras();
    
    // Mostrar tela de boas-vindas
    mostrar_tela_boas_vindas();
    
    menu_inicial();
    return 0;
}

void menu_inicial() {
    int opcao;
    int continuar = 1;
    
    while (continuar) {
        limparTela();
        
        aplicarCor("ciano");
        printf("\n");
        printf("  ███████╗ ██████╗ ██████╗  ██████╗ █████╗ \n");
        printf("  ██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔══██╗\n");
        printf("  █████╗  ██║   ██║██████╔╝██║     ███████║\n");
        printf("  ██╔══╝  ██║   ██║██╔══██╗██║     ██╔══██║\n");
        printf("  ██║     ╚██████╔╝██║  ██║╚██████╗██║  ██║\n");
        printf("  ╚═╝      ╚═════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝\n");
        aplicarCor("reset");

        aplicarCor("amarelo");
        printf("\n=====================================================\n");
        printf("                MENU PRINCIPAL                       \n");
        printf("=====================================================\n");
        aplicarCor("reset");
        
        printf("\nTotal de palavras cadastradas: ");
        if (palavracont < MINPALAVRAS) {
            aplicarCor("vermelho");
            printf("%d", palavracont);
            aplicarCor("reset");
            printf(" (Mínimo necessário: %d)\n", MINPALAVRAS);
        } else {
            aplicarCor("verde");
            printf("%d", palavracont);
            aplicarCor("reset");
            printf(" (Suficiente para jogar)\n");
        }
        
        printf("\nEscolha uma opção:\n\n");
        
        aplicarCor("verde");
        printf("1 - Novo Jogo\n");
        aplicarCor("reset");
        
        aplicarCor("azul");
        printf("2 - Cadastrar palavra\n");
        printf("3 - Atualizar palavra\n");
        printf("4 - Apagar palavra\n");
        printf("5 - Mostrar palavras\n");
        aplicarCor("reset");
        
        aplicarCor("magenta");
        printf("6 - Ver melhores pontuações\n");
        aplicarCor("reset");
        
        aplicarCor("vermelho");
        printf("7 - Sair do jogo\n");
        aplicarCor("reset");
        
        printf("\nDigite sua escolha: ");
        opcao = ler_opcao();
        
        // Switch para escolher a opção
        switch (opcao) {
            case 1:
                if (palavracont < MINPALAVRAS) {
                    limparTela();
                    aplicarCor("vermelho");
                    printf("\nVocê precisa cadastrar mais %d palavra(s) antes de jogar!\n", MINPALAVRAS - palavracont);
                    aplicarCor("reset");
                    printf("\nPressione Enter para continuar...");
                    getchar();
                } else {
                    jogar();
                }
                break;
            case 2:
                cadastrar_palavra();
                break;
            case 3:
                atualizar_palavra();
                break;
            case 4:
                apagar_palavra();
                break;
            case 5:
                listar_palavras();
                break;
            case 6:
                mostrar_pontuacoes();
                break;
            case 7:
                limparTela();
                aplicarCor("amarelo");
                printf("\nTem certeza que deseja sair do jogo? (s/n): ");
                aplicarCor("reset");
                char confirmacao;
                scanf(" %c", &confirmacao);
                limpar_buffer();
                if (tolower(confirmacao) == 's') {
                    limparTela();
                    aplicarCor("verde");
                    printf("\nObrigado por jogar! Até a próxima!\n");
                    aplicarCor("reset");
                    continuar = 0;
                }
                break;
            default:
                limparTela();
                aplicarCor("vermelho");
                printf("\nOpção inválida! Por favor, escolha uma opção entre 1 e 7.\n");
                aplicarCor("reset");
                printf("\nPressione Enter para continuar...");
                getchar();
        }
    }
}
