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
- Problema 1:
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
- [Jasom Rocha](https://github.com/JasomRocha) - (Descrição da parte feita: )


