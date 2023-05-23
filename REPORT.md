# Relatório: Métodos de Ordenação

**Componentes:**
 - Igor Almeida Guedes          202176007
 - Rhuan Nascimento Ferreira    202176033

## Análise de desempenho:

# Descreva aqui como foi feita a analise de desemenho. 
# Qual metodologia empregada? Usaram alguma técnica para melhorar o desempenho de alguns dos métodos?
- A análise de desempenho foi realizada para avaliar o desempenho das árvores AVL, B e vermelho-preto em diferentes cenários de uso. A metodologia empregada envolveu a implementação e execução de testes de desempenho em cada tipo de árvore, comparando métricas como tempo de execução e número de operações realizadas.

- Para cada tipo de árvore, foram realizados testes de inserção, busca e remoção de elementos em diferentes tamanhos de entrada, variando de pequenas quantidades de elementos até cenários com milhares de elementos. Os testes foram executados múltiplas vezes para obter uma média dos resultados e reduzir possíveis flutuações.

# Qual o método mais rápido e o mais lento? Qual configuração da máquinas onde o teste de desempenho  foi realizado?
- com o minimo de valores(100) a arvore RB possui menor tempo de insercao que as demais arvores, tanto com valores ordenados e valores aleatorios. 
- Ja com o maximo de valores(1000000) a arvore B com ordem 16 se torna mais rapida que as demais arvores, tanto para valores aleatorios quantos valores ordenados.

- Configurações da maquina: Ryzen 5 5600x, 16Gb RAM, 30Gb HD, Gtx 970.
# Quantas execuções foram feitas? 
- foram feitas 5 execuções.
## Conclusões

# Descreva aqui suas conclusões pessoals sobre esta atividade e os resultados obtidos
Após realizar essa atividade e analisar os resultados obtidos na análise de desempenho das árvores AVL, B e vermelho-preto, algumas conclusões podem ser destacadas:

1. Cada tipo de árvore tem suas vantagens e desvantagens: A árvore AVL apresentou um bom desempenho em operações de busca, garantindo um balanceamento adequado da árvore. A árvore B mostrou-se eficiente em cenários com grande volume de dados e operações de inserção e remoção frequentes. A árvore vermelho-preto apresentou um equilíbrio entre as outras duas, sendo uma opção versátil em diferentes cenários.

2. A escolha da estrutura de dados depende do contexto de uso: É importante considerar as características do problema em questão e as operações que serão mais frequentes. Cada tipo de árvore possui um trade-off entre tempo de execução, uso de memória e complexidade de implementação, o que torna necessário avaliar qual é a melhor opção para cada situação.

3. O balanceamento é essencial para um bom desempenho: As árvores AVL e vermelho-preto têm mecanismos de balanceamento que garantem uma altura limitada e operações mais eficientes. Essa propriedade é especialmente importante em cenários onde a árvore está sujeita a muitas operações de inserção e remoção.

4. A análise de desempenho é fundamental para a otimização de soluções: Ao realizar testes e medir métricas de desempenho, é possível identificar gargalos e pontos de melhoria em uma implementação. Isso permite tomar decisões embasadas para otimizar o código e escolher a estrutura de dados mais adequada.

Em suma, essa atividade proporcionou uma compreensão mais aprofundada sobre as árvores AVL, B e vermelho-preto, bem como suas características e desempenho em diferentes cenários. A análise de desempenho é uma ferramenta valiosa para orientar a escolha da estrutura de dados e otimizar soluções, levando em consideração as necessidades específicas de cada problema.

