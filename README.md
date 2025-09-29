# 🤖 Projeto de Computação Gráfica - Robô Karen 

Repositório do projeto desenvolvido para a disciplina **Introdução à Computação Gráfica** do curso de **Engenharia de Computação - UFPB**.  
O projeto consiste na implementação, em **linguagem C com OpenGL**, de um robô humanoide inspirado na **Karen** (computador do Plankton, do desenho *Bob Esponja*).  

O robô possui movimentos corporais e consegue se deslocar utilizando rodas em seus "pés".  


## 📌 O que o código faz
- Renderiza em 3D a personagem Karen como um robô humanoide.  
- Permite movimentação de partes do corpo (braços, cabeça, tronco etc.).  
- Possui rodas para locomoção.  
- Animações básicas de deslocamento e movimentos coordenados.  


## 🎨 Desenho esquemático do robô
Um esquema em desenho das partes que compõem o robô:  

![Esquema do robô Karen](./images/karen_robot_scheme.jpeg)  


## 🖼️ Imagens do programa
Imagens e/ou GIF's do programa em execução:  

![Exemplo do robô Karen](./images/karen_robot.png)  


## ⚙️ Como compilar e executar

### Dependências
- Compilador **GCC** (ou compatível).  
- **OpenGL** e **GLUT** instalados na máquina.  

No Linux (Ubuntu/Debian), instale com:
```bash
sudo apt-get update
sudo apt-get install freeglut3-dev
```
No Windows, recomenda-se usar o MinGW ou outro compilador C com suporte a OpenGL e GLUT.

### Compilação
No Linux:
```bash
g++ geometry.cpp robot.cpp -o robot -lGL -lGLU -lglut
```
No Windows (exemplo com MinGW):
```bash
g++ geometry.cpp robot.cpp -o robot -lopengl32 -lglu32 -lfreeglut
```

### Execução
```bash
./robot
```


## ⚠️ Principais problemas encontrados
- Problema 1: Linkar os elementos do robô uma vez criados de maneiras separadas. No nosso caso, a criação da cabeça do robô foi uma das primeiras partes a ser criada e depois o corpo junto com a base. Eles desevem se mover todos juntos e isso acabou sendo um problema na hora da implementação.
- Problema 2:
- Problema 3:


## 🚀 O que pode ser melhorado
- Melhoria 1:
- Melhoria 2:
- Melhoria 3:


## 👨‍💻 Autoria
Projeto desenvolvido por:
- [Gustavo Gomez]() - (Descrição da parte feita: )
- [Igor Matheus](https://github.com/Igor-Matheus) - (Descrição da parte feita: )
- [Jasom Rocha](https://github.com/JasomRocha) - Descrição da parte feita: Desenvolvi o corpo do robô juntamente com a primeira ideia de cenário, basicamente defini como se constrói um cilindro para visualização 3D e depois empilhei um total de 7 cilindros logo abaixo da cabeça (TV) do robô. Criei alguns inputs de movimentação do robô e fiz com que ele se desloque pelo cenário, de maneira que podemos observar sua movimentação olhando para os objetos que foram postos para compor a cena, isso é o inicio da abordagem final, e foi tudo que foi trabalhado por mim na primeira semana de desenvolvimento do projeto fazendo o commit das alterações hoje (27/09).

-- evidência 1
<img width="563" height="634" alt="image" src="https://github.com/user-attachments/assets/f69a51b6-f31c-4100-bf64-b51a70c43f9a" />

-- evidência 2 
<img width="562" height="635" alt="Captura de tela 2025-09-27 132505" src="https://github.com/user-attachments/assets/14092173-8cd3-40dd-a361-6d3327f3e8e6" />


Estado do projeto em 29/09/2025

<img width="524" height="577" alt="Captura de tela 2025-09-29 111455" src="https://github.com/user-attachments/assets/0a33b8a6-f6e1-40e1-a4ff-08cd5232538e" />
