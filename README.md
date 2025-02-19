# Jogo da Forca - Trabalho Final de Algoritmos II

Este repositório contém o código-fonte do **Jogo da Forca**, desenvolvido em linguagem C, como Trabalho Final da disciplina **Algoritmos II** do curso de **Engenharia de Software** da **UTFPR Dois Vizinhos**.

## Descrição

O projeto implementa um jogo da forca que permite ao usuário:
- **Cadastrar, atualizar, apagar e listar palavras**: todas as palavras são armazenadas em um arquivo binário.
- **Jogar a forca**: o jogo seleciona uma palavra aleatória (desde que haja no mínimo 10 palavras cadastradas) e permite que o jogador tente adivinhá-la. Durante o jogo, o sistema exibe underscores para as letras não reveladas, registra as letras já utilizadas e controla o número de tentativas.
- **Controle de pontuação**: pontos são atribuídos para letras acertadas e descontados para tentativas erradas.
- **Menu pós-jogo**: ao término do jogo, é exibido um menu com as opções “Novo Jogo”, “Menu Inicial” e “Sair”.

## Funcionalidades

- **Validação de entrada**: as palavras devem ter no mínimo 5 letras.
- **Evita duplicidade**: não permite o cadastro de palavras repetidas.
- **Gestão de arquivo binário**: as palavras são armazenadas, atualizadas e removidas de um arquivo binário.
- **Interatividade**: menu principal e menu pós-jogo para navegação intuitiva pelo sistema.
- **Pontuação dinâmica**: incremento e desconto de pontos conforme o desempenho do jogador.

## Tecnologias Utilizadas

- **Linguagem C**
- **Manipulação de Arquivos Binários**
- **Funções e Estruturas (struct)**
- **Geração de Números Aleatórios**

## Estrutura do Repositório

- `src/main.c`: Código-fonte principal do jogo.
- `README.md`: Este arquivo, contendo a descrição, instruções e informações sobre o projeto.

## Como Compilar e Executar

1. **Clone o repositório:**

   ```bash
   git clone https://seu-repositorio-url.git
   cd Trabalho_Final_Algoritmos2_UTFPR_Dois_Vizinhos/src
   ```

2. **Compile o código:**

   ```bash
   gcc -o jogo main.c
   ```

3. **Execute o programa:**

   ```bash
   ./jogo
   ```

## Considerações Finais

Este projeto foi desenvolvido com o objetivo de demonstrar conhecimentos em algoritmos, manipulação de arquivos, estruturas de dados e programação modular em C. Foi projetado e implementado para atender aos requisitos do Trabalho Final da disciplina **Algoritmos II** da **UTFPR Dois Vizinhos**, no curso de **Engenharia de Software**.

## Autor

[Eduardo Miola Ceron, Gabriel Colombo]  
[eduardoceron@alunos.utfpr.edu.br]

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE) – veja o arquivo LICENSE para mais detalhes.

