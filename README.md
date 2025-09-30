# 🤖 Projeto de Computação Gráfica - Robô Karen 

Repositório do projeto desenvolvido para a disciplina **Introdução à Computação Gráfica** do curso de **Engenharia de Computação - UFPB**.  
O projeto consiste na implementação, em **linguagem C com OpenGL**, de um robô humanoide inspirado na **Karen** (computador do Plankton, do desenho *Bob Esponja*).  

O robô possui movimentos corporais e consegue se deslocar utilizando rodas em seus "pés".  


## 📌 O que o código faz
- Renderiza em 3D a personagem Karen como um robô humanoide.  
- Permite movimentação dos braços.
- Permite troca de rostos para o robô.
- Permite troca de iluminação.
- Possui rodas para locomoção.  
- Movimentos básicos de deslocamento e movimentos coordenados.

## 🎮 Controles  

O robô Karen e a cena podem ser controlados via teclado. Abaixo estão todas as teclas e suas funções:

### 🔹 Movimento do Robô  
- **W / w** : Mover para frente  
- **S / s** : Mover para trás  
- **A / a** : Girar para a esquerda em torno do seu eixo 
- **D / d** : Girar para a direita em torno de seu eixo

### 🔹 Câmera (Órbita ao redor da cena)  
- **I / i** : Orbitar para a esquerda  
- **O / o** : Orbitar para a direita  

### 🔹 Braços e Articulações  
- **Z / z** : Abaixar o braço (ombro)  
- **H / h** : Levantar o braço (ombro)  
- **X / x** : Dobrar o cotovelo  
- **J / j** : Esticar o cotovelo  
- **e** : Girar o robô no sentido anti-horário  
- **E** : Girar o robô no sentido horário  

### 🔹 Inclinação do Corpo  
- **K / k** : Inclinar o corpo para frente (até 25°)  
- **L / l** : Inclinar o corpo para trás (até -25°)  

### 🔹 Aparência e Cena  
- **T / t** : Trocar o rosto da Karen  
- **Q / q** : Alternar iluminação do cenário (entre configurações diferentes)  

### 🔹 Outros  
- **ESC** : Sair do programa  


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
- Problema 1: Linkar os elementos do robô uma vez criados de maneiras separadas. No nosso caso, a criação da cabeça do robô foi uma das primeiras partes a ser criada e depois o corpo junto com a base. Eles desevem se mover todos juntos e isso acabou sendo um problema na hora da implementação. - [Jasom Rocha](https://github.com/JasomRocha)
- Problema 2: Dificuldades de implementação, na lógica de espelhamento dos braços, e colocar as "garras" do robô. - [Jasom Rocha](https://github.com/JasomRocha)
- Problema 3: Dificuldades de implementação de mais objetos na cena, mesmo sendo objetos mais básicos. - [Igor Matheus](https://github.com/Igor-Matheus)


## 🚀 O que pode ser melhorado
- Melhoria 1: Maneira como os braços foram implemnetados e a lógica de movimentação pelo cenário (questões físicas e referenciais) - [Jasom Rocha](https://github.com/JasomRocha)
- Melhoria 2: Texturas mais realistas para serem colocadas no ambiente da cena, bem como acréscimo de mais elementos. - [Igor Matheus](https://github.com/Igor-Matheus)
- Melhoria 3:


## 👨‍💻 Autoria
Projeto desenvolvido por:
- [Gustavo Gomes](https://github.com/IGustaMe) - Desenhos esquemáticos e de textura. Modelagem da cabeça do robô a partir de polígonos utilizando a função glBegin(GL_QUADS) para cada parte da TV. Aplicação das texturas em cada polígono.
- [Igor Matheus](https://github.com/Igor-Matheus) - Toda a estrutura do README.md, bem como a maior parte das coisas escritas e adicionadas nele. Implementação de mais objetos na cena (bolhas, algas, pedras). Adição de iluminação mais parecida com o fundo do mar e botão (tecla Q/q do teclado) para alternar entre a iluminação anterior e a que simula o fundo do mar. Implementaçao da alteração das texturas no rosto do robô Karen, alterações essas que ocorrem ao apertar a tecla T/t do teclado.  
- [Jasom Rocha](https://github.com/JasomRocha) - Desenvolvi o corpo do robô juntamente com a primeira ideia de cenário, basicamente defini como se constrói um cilindro para visualização 3D e depois empilhei um total de 7 cilindros logo abaixo da cabeça (TV) do robô. Criei alguns inputs de movimentação do robô e fiz com que ele se desloque pelo cenário, de maneira que podemos observar sua movimentação olhando para os objetos que foram postos para compor a cena, isso é o inicio da abordagem final, e foi tudo que foi trabalhado por mim na primeira semana de desenvolvimento do projeto fazendo o commit das alterações em (27/09). 
  Em (29/09) fiz o commit dos braços e da movimentação dos braços do robô, tive dificuldades de implementação, na lógica de espelhamento dos braços e colocar as "garras" do robô. 

### evidência 1 (27/09) - [Jasom Rocha](https://github.com/JasomRocha)
<img width="563" height="634" alt="image" src="https://github.com/user-attachments/assets/f69a51b6-f31c-4100-bf64-b51a70c43f9a" />

### evidência 2 (27/09) - [Jasom Rocha](https://github.com/JasomRocha)
<img width="562" height="635" alt="Captura de tela 2025-09-27 132505" src="https://github.com/user-attachments/assets/14092173-8cd3-40dd-a361-6d3327f3e8e6" />

### evidênica 3 (29/09) - [Jasom Rocha](https://github.com/JasomRocha)

<img width="524" height="577" alt="Captura de tela 2025-09-29 111455" src="https://github.com/user-attachments/assets/0a33b8a6-f6e1-40e1-a4ff-08cd5232538e" />



