# Descrição do Trabalho - Tema 2

Em um fenômeno da natureza, os deslocamentos $d1, d2, ..., dn$ são determinados pela solução do sistema de equações lineares $Ad = b$, onde $A$ é a matriz das propriedades, $d$ é o vetor das incógnitas e $b$ é o vetor dos termos independentes (vetor constante). Se um desses deslocamentos exceder $0.4 cm$ em módulo, sérios danos e problemas significativos podem ocorrer.

Uma abordagem possível para encontrar o vetor $d$ é através da inversa de $A$ $(d = A^{-1}b)$. Se $A$ é uma matriz $n x n$ que possui uma matriz inversa $A^{-1}$, então $AA^{-1} = I$, onde $I$ é a matriz identidade. Uma maneira de encontrar $A^{-1}$ é determinar as colunas de $A^{-1}$ uma por vez, através das equações:<br>

$$A(A^{-1})1 = \begin{bmatrix}1 \\ 0 \\ \vdots \\ 0\end{bmatrix}, \, A(A^{-1})_2 = \begin{bmatrix}0 \\ 1 \\ \vdots \\ 0\end{bmatrix}, \, \ldots, \, A(A^{-1})\ n = \begin{bmatrix}0 \\ 0 \\ \vdots \\ 1\end{bmatrix}$$


O desenvolvimento de um sistema para calcular os deslocamentos $d_i$ com os requisitos abaixo é proposto:

a) Implementar algoritmo para calcular $A^{-1}$ e, em seguida, $d$ pelo método de Gauss-Jacobi.  
b) Implementar algoritmo para calcular $A^{-1}$ e, em seguida, $d$ pelo método de Gauss-Seidel.  
c) Calibrar o sistema usando como padrão a matriz $A$ e o vetor $b$ fornecidos abaixo.  
d) Fornecer um quadro resposta para cada método, variando os valores de $A$ e de $b$.  
e) Analisar as consequências desse fenômeno para o sistema mencionado abaixo.

## Dados de Entrada

- $n$ (número de deslocamentos)
- Termos de $A_{n x n}$ e de $b_{n x 1}$
- $ε$ (precisão)

## Dados de Saída

- $A^{-1}$
- Os termos de $d_{n x 1}$ que representam os $n$ deslocamentos $d1, d2, ..., dn$.
