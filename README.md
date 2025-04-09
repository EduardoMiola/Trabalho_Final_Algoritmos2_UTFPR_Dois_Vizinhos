# 🎮 Jogo da Forca - Trabalho Final de Algoritmos II

Este repositório contém o código-fonte do **Jogo da Forca**, desenvolvido em linguagem C, como Trabalho Final da disciplina **Algoritmos II** do curso de **Engenharia de Software** da **UTFPR Dois Vizinhos**.

## 📝 Descrição

O projeto implementa um jogo da forca interativo com as seguintes funcionalidades:

- **Gestão de palavras**: cadastrar, atualizar, apagar e listar palavras com categorias e dicas
- **Palavras com hífens e espaços**: suporte avançado para expressões e palavras compostas
- **Sistema de dificuldades**: três níveis (fácil, normal e difícil) com número de tentativas variado
- **Interface colorida**: experiência visual melhorada com cores e formatação 
- **Sistema de pontuação**: histórico de melhores pontuações com ranking dos jogadores
- **Feedback interativo**: mensagens coloridas e animações em ASCII para melhor experiência

## 💡 Funcionalidades Avançadas

- **Interface amigável**: menus coloridos e interativos para melhor navegação
- **Validação robusta**: impede entradas inválidas em todos os menus e durante o jogo
- **Categorização**: palavras organizadas por temas como Animais, Países, Frutas, etc.
- **Sistema de dicas**: possibilidade de receber dicas durante o jogo (com penalidade de pontos)
- **Ranking de jogadores**: armazena e exibe as melhores pontuações
- **Feedback visual**: estados da forca com cores diferentes conforme a dificuldade
- **Confirmação de ações**: evita ações acidentais com confirmações para operações críticas

## 🛠️ Tecnologias Utilizadas

- **Linguagem C**
- **Manipulação de Arquivos Binários**
- **Estruturas de Dados Avançadas**
- **Interface com Cores (ANSI/Windows)**
- **Geração de Números Aleatórios**
- **ASCII Art para Interfaces**

## 📂 Estrutura do Repositório

- `main.c`: Código-fonte principal do jogo
- `output/`: Diretório de arquivos compilados
- `README.md`: Documentação do projeto
- `LICENSE`: Arquivo de licença do projeto

## 🚀 Como Compilar e Executar

1. **Clone o repositório:**

   ```bash
   git clone https://github.com/EduardoMiola/Trabalho_Final_Algoritmos2_UTFPR_Dois_Vizinhos.git
   cd Trabalho_Final_Algoritmos2_UTFPR_Dois_Vizinhos
   ```

2. **Compile o código:**

   ```bash
   gcc -o output/jogo main.c
   ```

3. **Execute o programa:**

   ```bash
   ./output/jogo
   ```

## 🎯 Requisitos do Sistema

- Compilador GCC ou equivalente
- Terminal com suporte a cores (para melhor experiência visual)
- Mínimo de 1MB de espaço em disco para arquivos de dados

## 🎲 Como Jogar

1. Cadastre pelo menos 10 palavras para começar a jogar
2. Selecione "Novo Jogo" no menu principal
3. Escolha o nível de dificuldade (fácil, normal ou difícil)
4. Tente adivinhar a palavra secreta digitando letras
5. Você pode solicitar uma dica com penalidade de pontos
6. Vença o jogo descobrindo todas as letras antes de completar a forca
7. Registre sua pontuação no ranking ao vencer

## ✨ Melhorias Implementadas

- **Suporte a cores**: interface colorida em sistemas Windows e Unix
- **Categorização de palavras**: organização por temas com filtros
- **Sistema de dicas**: ajuda opcional durante o jogo
- **Pontuações persistentes**: armazenamento das melhores pontuações
- **Palavras compostas**: suporte a hífens e espaços nas palavras
- **Confirmações**: proteção contra ações acidentais

## 👥 Autores

[Eduardo Miola Ceron, Gabriel Colombo]  
[eduardoceron@alunos.utfpr.edu.br]

## 📄 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE) – veja o arquivo LICENSE para mais detalhes.

---

*Última atualização: Abril de 2025*

