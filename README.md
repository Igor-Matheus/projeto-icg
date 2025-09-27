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
g++ <nome_do_arquivo.c> -o karen -lGL -lGLU -lglut
```
No Windows (exemplo com MinGW):
```bash
g++ <nome_do_arquivo.c> -o karen -lopengl32 -lglu32 -lfreeglut
```

### Execução
```bash
./karen
```


## ⚠️ Principais problemas encontrados
- Problema 1: Linkar os elementos do robo uma vez criados de maneiras separadas, no nosso caso, a criação da cabeça do robô foi uma das primeiras partes a ser criada e depois o corpo junto com a base, eles desevem se mover todos juntos e isso acabou sendo um problema na hora da implementação.
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
- [Jasom Rocha](https://github.com/JasomRocha) - Descrição da parte feita: Desenvolvi o corpo do robo jutamente com a primeira ideia de cenário, basicamente defini como se constrói um cilindro para visualização 3D e depois empilhei um total de 7 cilindros logo abaixo da cabeça (TV) do robo, criei alguns inputs de movimentação do robo e fiz com que ele se movimenta-se pelo cenário de maneira que, podemos observar sua movimentação olhando para os objetos que foram postos para compor o cenário, Isso é o inicio da abordagem final, e foi tudo que foi trabalhado por mim na primeira semana de desenvolvimento do projetoendo o commit das alterações hoje (27/09)



