PSE em Ação
Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola
O PSE em Ação é uma aplicação desenvolvida em linguagem C, executada no terminal, para auxiliar no planejamento, registro e acompanhamento de ações coletivas do Programa Saúde na Escola (PSE).
O projeto foi desenvolvido como parte da AEP — 2º semestre de 2026, no curso de Engenharia de Software da UniCesumar.
	
Curso	Engenharia de Software
Série	ESOFT2SMB
Ano	2026

Temas trabalhados	Vacinação e Saúde Bucal

🎯 Objetivo
Auxiliar uma equipe escolar e de saúde no planejamento e acompanhamento de ações de vacinação e saúde bucal, mantendo as informações organizadas e preservando a privacidade dos estudantes.

✅ Funcionalidades
O programa possui um menu com as seguintes opções:
Opção	Função

1	Cadastrar ação

2	Listar ações

3	Pesquisar ação (por código, escola ou tema)

4	Atualizar situação da ação (planejada, realizada ou cancelada) e registrar a quantidade efetiva de participantes

5	Gerar resumo geral (ações por situação, total de participantes e percentual de participação)

6	Sair

O programa também valida as entradas: campos vazios, valores inválidos ou negativos, data fora do formato dd/mm/aaaa, código repetido, código inexistente e limite de 100 ações.

Também é possível abrir o arquivo `src/main.c` em uma IDE com suporte a C, compilar e executar pelo próprio ambiente.
💻 Tecnologia
Linguagem: C (padrão C99), apenas biblioteca padrão
Execução: terminal
Conceitos: estruturas condicionais, estruturas de repetição, vetores, `struct` e funções.
📁 Estrutura do repositório
```
├── docs/     # Documentação da AEP (Etapa 1 e Etapa 2)
├── src/      # Código-fonte em C (main.c)
└── README.md
```
👥 Integrantes
Daniel Matuzawa dos Santos
Gabriel Ferreira Matos
Henry Jun Sasakura
📚 Documentação
A pasta `docs/` reúne os materiais da AEP:
Etapa 1: documento da AEP, fluxogramas e pseudocódigos;
Etapa 2: documento final com casos de uso, requisitos atualizados, testes, manual do usuário, capturas de tela e considerações finais;
Link do vídeo de apresentação: [inserir o link]
🔒 Limitações e privacidade
O projeto utiliza exclusivamente dados fictícios e informações coletivas. O sistema não armazena nomes, diagnósticos, prontuários ou qualquer informação clínica individual dos estudantes, e não realiza diagnósticos, triagens médicas, prescrições ou recomendações de tratamento.
Limitações atuais:
Os dados ficam apenas na memória e são perdidos ao encerrar o programa;
O limite é de 100 ações por execução;
Não é possível editar ou excluir ações já cadastradas;
A validação da data não confere se o dia existe no mês (por exemplo, 31/02).
📌 Situação do projeto
Etapa 1 — Análise e planejamento ✅
Etapa 2 — Implementação e apresentação ✅ código em C, testes e documentação concluídos
