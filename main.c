#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//Definições das constantes
#define MINPALAVRAS 10
#define MINLETRAS 5
#define MAXTAMANHO 100

//Estrutura para armazenar as palavras
typedef struct palavra{
    char palavra[MAXTAMANHO];
    int tamanho;
} Palavra;

int palavracont = 0;

//Protótipo das funções
void cadastrar_palavra();
void listar_palavras();
void apagar_palavra();
void atualizar_palavra();
void jogar();
void menu_inicial();

int main() {
    // Limpar o arquivo ao iniciar o programa
    FILE *arquivo = fopen("palavras.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fclose(arquivo);

    menu_inicial();
    return 0;
}

void menu_inicial() {
    int opcao;
    printf("====================================================================================================\n");
    printf("Bem vindo ao jogo da forca\n");
    printf("Digite a opção desejada:\n");
    printf("1 - Novo Jogo\n");
    printf("2 - Cadastrar palavra\n");
    printf("3 - Atualizar palavra\n");
    printf("4 - Apagar palavra\n");
    printf("5 - Mostrar palavras\n");
    printf("6 - Sair\n");
    printf("====================================================================================================\n");
    scanf("%d", &opcao);
    
    // Switch para escolher a opção
    switch (opcao) {
        case 1:
            if (palavracont < MINPALAVRAS) {
                printf("Você deve cadastrar mais %d palavras para iniciar o jogo\n", MINPALAVRAS - palavracont);
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
            printf("Encerrando o programa.\n");
            exit(0);
        default:
            printf("Opção inválida. Tente novamente.\n");
    }
    menu_inicial(); // Recursão para continuar no menu inicial
}

void cadastrar_palavra() {
    FILE *arquivo;
    Palavra nova_palavra;
    printf("Digite a palavra que deseja cadastrar (mínimo %d letras): ", MINLETRAS);
    scanf("%s", nova_palavra.palavra);

    //Verifica se a palavra tem o mínimo de letras
    if (strlen(nova_palavra.palavra) < MINLETRAS) {
        printf("A palavra deve ter no mínimo %d letras.\n", MINLETRAS);
        return;
    }

    arquivo = fopen("palavras.bin", "ab+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    // Verificar se a palavra já existe
    Palavra palavra_existente;
    while (fread(&palavra_existente, sizeof(Palavra), 1, arquivo) == 1) {
        if (strcmp(palavra_existente.palavra, nova_palavra.palavra) == 0) {
            printf("A palavra já existe no arquivo.\n");
            fclose(arquivo);
            return;
        }
    }

    // Adicionar a nova palavra
    nova_palavra.tamanho = (int)strlen(nova_palavra.palavra) + 1;
    fwrite(&nova_palavra, sizeof(Palavra), 1, arquivo);
    palavracont++;
    fclose(arquivo);
    printf("Palavra cadastrada com sucesso.\n");
}

void listar_palavras() {
    FILE *arquivo;
    Palavra palavra;
    arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    printf("Palavras cadastradas:\n");
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        printf("%s\n", palavra.palavra);
    }
    fclose(arquivo);
}

void apagar_palavra() {
    FILE *arquivo;
    FILE *arquivo_temp;
    Palavra palavra;
    char palavra_para_apagar[MAXTAMANHO];
    printf("Digite a palavra que deseja apagar: ");
    scanf("%s", palavra_para_apagar);

    arquivo = fopen("palavras.bin", "rb");
    arquivo_temp = fopen("temp.bin", "wb");
    if (arquivo == NULL || arquivo_temp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    int encontrou = 0;
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        if (strcmp(palavra.palavra, palavra_para_apagar) != 0) {
            fwrite(&palavra, sizeof(Palavra), 1, arquivo_temp);
        } else {
            encontrou = 1;
        }
    }

    fclose(arquivo);
    fclose(arquivo_temp);
    remove("palavras.bin");
    rename("temp.bin", "palavras.bin");

    if (encontrou) {
        palavracont--;
        printf("Palavra apagada com sucesso.\n");
    } else {
        printf("Palavra não encontrada.\n");
    }
}

void atualizar_palavra() {
    FILE *arquivo;
    FILE *arquivo_temp;
    Palavra palavra;
    char palavra_para_atualizar[MAXTAMANHO];
    Palavra nova_palavra;
    printf("Digite a palavra que deseja atualizar: ");
    scanf("%s", palavra_para_atualizar);
    printf("Digite a nova palavra (mínimo %d letras): ", MINLETRAS);
    scanf("%s", nova_palavra.palavra);

    if (strlen(nova_palavra.palavra) < MINLETRAS) {
        printf("A nova palavra deve ter no mínimo %d letras.\n", MINLETRAS);
        return;
    }

    arquivo = fopen("palavras.bin", "rb");
    arquivo_temp = fopen("temp.bin", "wb");
    if (arquivo == NULL || arquivo_temp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    int encontrou = 0;
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        if (strcmp(palavra.palavra, palavra_para_atualizar) == 0) {
            nova_palavra.tamanho = (int)strlen(nova_palavra.palavra) + 1;
            fwrite(&nova_palavra, sizeof(Palavra), 1, arquivo_temp);
            encontrou = 1;
        } else {
            fwrite(&palavra, sizeof(Palavra), 1, arquivo_temp);
        }
    }

    fclose(arquivo);
    fclose(arquivo_temp);
    remove("palavras.bin");
    rename("temp.bin", "palavras.bin");

    if (encontrou) {
        printf("Palavra atualizada com sucesso.\n");
    } else {
        printf("Palavra não encontrada.\n");
    }
}

void jogar() {
    FILE *arquivo;
    Palavra palavra;
    char tentativa;
    int i, acertos = 0, tentativas = 6;
    int acertou;
    int pontos = 0;
    char letras_tentadas[26] = {0}; // Array para armazenar letras tentadas
    int num_tentadas = 0; // Contador de letras tentadas

    arquivo = fopen("palavras.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    // Contar o número de palavras no arquivo
    int num_palavras = 0;
    while (fread(&palavra, sizeof(Palavra), 1, arquivo) == 1) {
        num_palavras++;
    }

    // Escolher uma palavra aleatória
    srand((unsigned int)time(NULL));
    int palavra_aleatoria = rand() % num_palavras;

    // Voltar ao início do arquivo e ler a palavra escolhida
    rewind(arquivo);
    for (i = 0; i <= palavra_aleatoria; i++) {
        fread(&palavra, sizeof(Palavra), 1, arquivo);
    }
    fclose(arquivo);

    // Remover o '\n' da palavra
    palavra.palavra[strcspn(palavra.palavra, "\n")] = 0;

    // Substituir letras da palavra por '_'
    char palavra_oculta[MAXTAMANHO];
    for (i = 0; i < palavra.tamanho - 1; i++) {
        palavra_oculta[i] = '_';
    }
    palavra_oculta[palavra.tamanho - 1] = '\0';

    // Jogo da forca
    while (tentativas > 0 && acertos < palavra.tamanho - 1) {
        printf("Palavra: %s\n", palavra_oculta);
        printf("Tentativas restantes: %d\n", tentativas);
        printf("Pontos: %d\n", pontos);
        printf("Letras já utilizadas: ");
        for (i = 0; i < num_tentadas; i++) {
            printf("%c ", letras_tentadas[i]);
        }
        printf("\nDigite uma letra: ");
        scanf(" %c", &tentativa);

        // Verificar se a entrada é uma única letra
        if (!isalpha(tentativa)) {
            printf("Por favor, digite apenas uma letra.\n");
            continue;
        }

        // Verificar se a letra já foi tentada
        int ja_tentada = 0;
        for (i = 0; i < num_tentadas; i++) {
            if (letras_tentadas[i] == tentativa) {
                ja_tentada = 1;
                break;
            }
        }
        if (ja_tentada) {
            printf("Você já tentou essa letra. Tente outra.\n");
            continue;
        }

        // Adicionar a letra tentada ao array
        letras_tentadas[num_tentadas++] = tentativa;

        acertou = 0;
        for (i = 0; i < palavra.tamanho - 1; i++) {
            if (palavra.palavra[i] == tentativa && palavra_oculta[i] == '_') {
                palavra_oculta[i] = tentativa;
                acertos++;
                acertou = 1;
                pontos += 10; // Ganha 10 pontos por letra acertada
            }
        }

        if (!acertou) {
            tentativas--;
            pontos -= 5; // Perde 5 pontos por tentativa errada
        }
    }

    if (acertos == palavra.tamanho - 1) {
        printf("Parabens! Voce adivinhou a palavra: %s\n", palavra.palavra);
        printf("Pontuação final: %d\n", pontos);
    } else {
        printf("Você perdeu! A palavra era: %s\n", palavra.palavra);
        printf("Pontos finais: %d\n", pontos);
    }

    // Menu após o término do jogo
    int opcao;
    printf("Digite a opção desejada:\n");
    printf("1 - Novo Jogo\n");
    printf("2 - Menu Inicial\n");
    printf("3 - Sair\n");
    scanf("%d", &opcao);
    switch (opcao) {
        case 1:
            jogar();
            break;
        case 2:
            menu_inicial();
            break;
        case 3:
            printf("Encerrando o programa.\n");
            exit(0);
        default:
            printf("Opção inválida. Retornando ao menu inicial.\n");
            menu_inicial();
    }
}
