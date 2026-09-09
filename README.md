# PSE em Ação

## Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola

O **PSE em Ação** é uma aplicação desenvolvida em linguagem C para auxiliar no planejamento, registro e acompanhamento de ações coletivas do Programa Saúde na Escola (PSE).

O projeto foi desenvolvido como parte da **AEP — 2º semestre de 2026**, pelos alunos do curso de Engenharia de Software da UniCesumar.

## 🎯 Objetivo

Desenvolver uma aplicação simples, executada em ambiente de terminal, capaz de organizar informações sobre ações de **vacinação e saúde bucal**, permitindo seu cadastro, consulta, atualização e acompanhamento.

## ⚙️ Funcionalidades

O sistema possui as seguintes funcionalidades:

* Cadastro de ações;
* Listagem de ações cadastradas;
* Pesquisa por código, escola ou tema;
* Atualização da situação da ação;
* Registro da quantidade efetiva de participantes;
* Geração de resumo geral das ações;
* Validação das entradas do usuário;
* Verificação de códigos duplicados;
* Controle de quantidades inválidas.

## 💻 Tecnologias utilizadas

* Linguagem C
* Aplicação executada em terminal
* Estruturas condicionais e de repetição
* Vetores
* `struct`
* Funções

## 👥 Integrantes

* Daniel Matuzawa dos Santos
* Gabriel Ferreira Matos
* Henry Jun Sasakura

## 📁 Estrutura do projeto

```text
PSE-EM-ACAO/
│
├── README.md
│
├── src/
│   └── pse_em_acao.c
│
└── docs/
    ├── AEP_PSE_em_Acao.pdf
    ├── Fluxograma_Geral.png
    ├── Fluxograma_Cadastro.png
    └── Pseudocodigos.pdf
```

## ▶️ Como executar

### Pré-requisitos

É necessário possuir um compilador da linguagem C instalado, como o GCC.

### Compilação

```bash
gcc src/pse_em_acao.c -o pse_em_acao
```

### Execução

No Windows:

```bash
pse_em_acao.exe
```

No Linux:

```bash
./pse_em_acao
```

## 📚 Documentação

A documentação do projeto está disponível na pasta `docs`, contendo:

* Documento da AEP;
* Fluxograma geral do sistema;
* Fluxograma detalhado do cadastro;
* Pseudocódigos;
* Outros materiais relacionados ao desenvolvimento.

## 📌 Escopo

O sistema trabalha exclusivamente com **dados fictícios e informações coletivas**. Não são armazenados nomes, diagnósticos, prontuários ou informações clínicas individuais de estudantes.

O projeto possui caráter acadêmico e não realiza diagnóstico, triagem médica, prescrição ou recomendação de tratamentos.
