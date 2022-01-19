/*
    Trabalho da cadeira de CG

    Isaac Guibson
    Eliaquim Pimentel
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <GL/glut.h>

#define LARGURA  500
#define ALTURA   650

//Controle da Camera
float ex = 50.0;    //olho x
float ey = -49.0;   //olho y
float ez = 20.0;    //olho z
float lx = 50.0;    //look x
float ly = 500.0;   //look y
float lz = 0.0;     //look z
float ux = 0.0;
float uy = 0.0;
float uz = 1.0;
int tras = 1;   //parametro de controle para mudar a posição da camera

//Controle de iluminacao
float vr = 0.5;     //Valor R
float vg = 0.5;     //Valor G
float vb = 0.5;     //Valor B

//Array de posicao dos carros inimigos
/*
Pega um valor aleatorio e translada o carro na pista
*/
int positions[6] = {0, -10, -20, -30, -40, -50};
int random_number1 = 0;
int random_number2 = -10;
int random_number3 = -20;
int random_number_powerUP = -30;

//Game Speed
int FPS = 60;
int dificuldade = 1;
//Game Track
int start=0;
int gv=0;

//Track Score
int score = 0;

//Controle de movimentacao da pista
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

//Controle de translacao do carro do jogador
int lrIndex = 0 ;
int control = 0;

//Controle de rotacao do powerUP
float rotate_value = 0.0;

//Controle de batida do PowerUP
int gotPower = 0;
int scaled_once = 0;
int score_count = 0;

//Controle de translacao dos carros inimigos
int car1 = 0;
int lrIndex1=0;
int car2 = +35;
int lrIndex2=0;
int car3 = +70;
int lrIndex3=0;

//Controle de translacao do powerUP
int power_posx=0;

//Parametros de Texto
const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18 ;
const int font3=(int)GLUT_BITMAP_8_BY_13;

char s[30];
void renderBitmapString(float x, float y, float z, void *font,const char *string){
    const char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void ParametrosIluminacao()
{
	GLfloat luzAmbiente[4]={vr, vg, vb, 1.0};	/* cor branca */

	/* Define os parâmetros da luz de número 0 (Luz Pontual) */
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

	/* Ativa o uso de uma fonte de luz ambiente */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	/* Características do material */
	GLfloat ka[4]={0.9, 0.9, 0.9, 1.0};		/* Reflete porcentagens da cor ambiente */

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
}

void desenhaPowerUp(){

    //desenha o powerUP
    glColor3f(0.651, 0.337, 0.362);
    glPushMatrix();
    glTranslatef(70, 40, 8.5);
    glRotatef(rotate_value, 1.0, 0.0, 0.0);
    glutSolidCube(4);
    glPopMatrix();

    //Funcao de rotacao
    rotate_value++;
    if(rotate_value >= 360){
        rotate_value = 0;
    }
}

void desenhaCarro(){

    //Meio do carro
    glPushMatrix();
    glTranslatef(70, 40, 8.5);
    glutSolidCube(8);
    glPopMatrix();

    //Traseira esq
    glPushMatrix();
    glTranslatef(68, 34, 6.5);
    glutSolidCube(4);
    glPopMatrix();

    //Traseira dir
    glPushMatrix();
    glTranslatef(72, 34, 6.5);
    glutSolidCube(4);
    glPopMatrix();

    //Frente esq
    glPushMatrix();
    glTranslatef(68, 46, 6.5);
    glutSolidCube(4);
    glPopMatrix();

    //Frente dir
    glPushMatrix();
    glTranslatef(72, 46, 6.5);
    glutSolidCube(4);
    glPopMatrix();

    //Roda traseira esquerda
    glColor3f(0.000, 0.000, 0.000);
    glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glTranslatef(-4.0, 35.5, 65.5);
        glutSolidTorus(0.5, 3, 6, 20);
    glPopMatrix();

    //Roda traseira direita
    glColor3f(0.000, 0.000, 0.000);
    glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glTranslatef(-4.0, 35.5, 74.5);
        glutSolidTorus(0.5, 3, 6, 20);
    glPopMatrix();

    //Roda dianteira esquerda
    glColor3f(0.000, 0.000, 0.000);
    glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glTranslatef(-4.0, 44.0, 65.5);
        glutSolidTorus(0.5, 3, 6, 20);
    glPopMatrix();

    //Roda dianteira direita
    glColor3f(0.000, 0.000, 0.000);
    glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        glTranslatef(-4.0, 44.0, 74.5);
        glutSolidTorus(0.5, 3, 6, 20);
    glPopMatrix();
}

void desenhaPlano(){

    //Desenha o ceu
    glColor3f(0.000, 0.749, 1.000);
    glBegin(GL_QUADS);
        glVertex3i(-300, 800, 300);
        glVertex3i(400, 800, 300);
        glColor3f(0.686, 0.933, 0.933);
        glVertex3i(400, 800, 0);
        glVertex3i(-300, 800, 0);
    glEnd();

    //Montanha 1
    glColor3f(0.000, 0.502, 0.000);
    glBegin(GL_TRIANGLES);
        glVertex3f(-10, 799.9, 100);
        glVertex3f(-120, 799.9, 0);
        glVertex3f(50, 799.9, 0);
    glEnd();

    //Montanha 2
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
        glVertex3f(-120, 799.9, 100);
        glVertex3f(-80, 799.9, 0);
        glVertex3f(-200, 799.9, 0);
    glEnd();

    //Montanha 3
    glColor3f(0.000, 0.502, 0.000);
    glBegin(GL_TRIANGLES);
        glVertex3f(130, 799.8, 200);
        glVertex3f(200, 799.8, 0);
        glVertex3f(0, 799.8, 0);
    glEnd();

    //Montanha 4
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
        glVertex3f(240, 799.9, 100);
        glVertex3f(300, 799.9, 0);
        glVertex3f(150, 799.9, 0);
    glEnd();

    //desenha a estrada
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_QUADS);
        glVertex3i(0, 800, 0);
        glVertex3i(100, 800, 0);
        glVertex3i(100, 0, 0);
        glVertex3i(0, 0, 0);
    glEnd();

    //Faixa lateral esq
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_QUADS);
        glVertex3f(-10, 800, 0);
        glVertex3f(0, 800, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(-10, 0, 0);
    glEnd();

    //faixa lateral dir
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_QUADS);
        glVertex3f(100, 800, 0);
        glVertex3f(110, 800, 0);
        glVertex3f(110, 0, 0);
        glVertex3f(100, 0, 0);
    glEnd();

    //Desenha faixa central 1
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_QUADS);
        glVertex3f(48, roadDivTop+800, 0.1);
        glVertex3f(52, roadDivTop+800, 0.1);
        glVertex3f(52, roadDivTop+700, 0.1);
        glVertex3f(48, roadDivTop+700, 0.1);
    glEnd();
    roadDivTop--;
    if(roadDivTop<-900){
        roadDivTop = 100;
        score=score+5;
        dificuldade++;
    }

    //Desenha faixa central 2
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex3f(48, roadDivMdl+200, 0.1);
        glVertex3f(52, roadDivMdl+200, 0.1);
        glVertex3f(52, roadDivMdl+100, 0.1);
        glVertex3f(48, roadDivMdl+100, 0.1);
    glEnd();
    roadDivMdl--;
    if(roadDivMdl<-300){
        roadDivMdl = 700;
        score=score+5;
    }

    //CHAMANDO POWERUP
    glPushMatrix();
    glTranslatef(random_number_powerUP, power_posx+6500, 0);
    desenhaPowerUp();
    glPopMatrix();
    power_posx--;
    //Pegando o powerUP
    if((power_posx+6500 <= 10) && (random_number_powerUP == lrIndex1)){
        if(!(power_posx+6500 <= 0)){
            gotPower = 1;
            power_posx = 0;
            score_count = score;
        }
    }
    //Transladando o powerUP
    if(power_posx < -6600){
        power_posx = 0;
        random_number_powerUP = positions[rand() % 6];
    }

    //Carro do Jogador
    glColor3f(0.678, 0.020, 0.134);
    glPushMatrix();
    glTranslatef(lrIndex1, 0, 0);
    //Se pegar o powerUp escala
    if(gotPower == 1){
        glScalef(2, 2, 2);
        scaled_once = 1;
    }
    //Se tiver escalonado translade para o local correto
    if(scaled_once == 1){
        glTranslatef(-35, -15, 0);
    }
    //apos acumular alguns pontos, volte ao normal
    if(score > (score_count + 15) && gotPower == 1){
        gotPower = 0;
        scaled_once = 0;
        glScalef(-1, -1, -1);
        score_count = 0;
    }
    desenhaCarro();
    glPopMatrix();

    //Carro inimigo
    glColor3f(0.800, 0.500, 0.000);
    glPushMatrix();
    glTranslatef(random_number1, car1+700, 0);
    desenhaCarro();
    glPopMatrix();
    car1 = car1 - dificuldade;
    if((car1+700 <= 10) && (random_number1 == lrIndex1)){
        if(!(car1+700 <= 0) && scaled_once == 0){
            start = 0;
            gv=1;
            tras = 1;
        }
    }
    //Fazer o carro vir pra tras
    if(car1 < -800){
        car1 = 0;
        random_number1 = positions[rand() % 6];
    }

    //Carro inimigo 2
    glColor3f(0.200, 0.500, 0.600);
    glPushMatrix();
    glTranslatef(random_number2, car2+900, 0);
    desenhaCarro();
    glPopMatrix();
    car2 = car2 - dificuldade;
    //Batida dos carros
    if((car2+900 <= 10) && (random_number2 == lrIndex1)){
        if(!(car2+900 <= 0) && scaled_once == 0){
            start = 0;
            gv=1;
            tras = 1;
        }
    }
    //Fazer o carro vir pra tras
    if(car2 < -1000){
        car2 = 0;
        random_number2 = positions[rand() % 6];
    }

    //Carro inimigo 3
    glColor3f(0.325, 0.186, 0.237);
    glPushMatrix();
    glTranslatef(random_number3, car3+1100, 0);
    desenhaCarro();
    glPopMatrix();
    car3 = car3 - dificuldade;
    //Batida dos carros
    if((car3+1100 <= 10) && (random_number3 == lrIndex1)){
        if(!(car3+1100 <= 0) && scaled_once == 0){
            start = 0;
            gv=1;
            tras = 1;
        }
    }
    //Fazer o carro vir pra tras
    if(car3 < -1200){
        car3 = 0;
        random_number3 = positions[rand() % 6];
    }

    //Tela de pontuacao tras
    glColor3f(0.000, 0.000, 0.000);
        glBegin(GL_QUADS);
        glVertex3f(100,200,100);
        glVertex3f(140,200,100);
        glVertex3f(140,200,80);
        glVertex3f(100,200,80);
    glEnd();
    //Speed Print
    char buffer1 [50];
    sprintf (buffer1, "Level %d", dificuldade);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(102, 199.9, 96,(void *)font3,buffer1);
    //Score Print
    char buffer [50];
    sprintf (buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(102, 199.9, 93,(void *)font3,buffer);

    //Tela de pontuacao cima
    glColor3f(0.000, 0.000, 0.000);
        glBegin(GL_QUADS);
        glVertex3f(75,113,80);
        glVertex3f(93,113,80);
        glVertex3f(93,123,80);
        glVertex3f(75,123,80);
    glEnd();
    //Speed Print
    char buffer2 [50];
    sprintf (buffer2, "Level %d", dificuldade);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(75, 120, 82,(void *)font3,buffer2);
    //Score Print
    char buffer3 [50];
    sprintf (buffer3, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(75, 118, 82,(void *)font3,buffer3);
}

//z = ponta da arvore
//x = canto inferior esquerdo do tronco
//y = profundidade
void tree(int x, int y, int z){
    //Arvore
    //Tronco
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_TRIANGLES);
        glVertex3f(x+5,y,z);
        glVertex3f(x+10,y,z-20);
        glVertex3f(x,y,z-20);
    glEnd();

    //Folhas
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
        glVertex3f(x+5,y-0.1,z);
        glVertex3f(x+15,y-0.1,z-10);
        glVertex3f(x-5,y-0.1,z-10);
    glEnd();
}

//Desenho da tela inicial
void fristDesign(){

        //Parametros de iluminacao (dia)
        vr = 0.5;
        vg = 0.5;
        vb = 0.5;

        //Triangulo preto (pista)
        glColor3f(0, 0, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f(50, 800, 0);
            glVertex3f(100, 0, 0);
            glVertex3f(0, 0, 0);
        glEnd();


        //Triangulo branco (listra da pista)
         glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLES);
            glVertex3f(50,800,0.01);
            glVertex3f(55,0,0.01);
            glVertex3f(45,0,0.01);
        glEnd();

         //Ceu (degrade azul)
        glColor3f(0.000, 0.749, 1.000);
        glBegin(GL_QUADS);
            glVertex3f(-300,800,300);
            glVertex3f(400,800,300);
            glColor3f(0.686, 0.933, 0.933);
            glVertex3f(400,800,0);
            glVertex3f(-300,800,0);
        glEnd();

        //Montanha 1
        glColor3f(0.235, 0.702, 0.443);
        glBegin(GL_TRIANGLES);
            glVertex3f(-150, 799.9, 150);
            glVertex3f(-50, 799.9, 0);
            glVertex3f(-250, 799.9, 0);
        glEnd();

        //Montanha 2
        glColor3f(0.000, 0.502, 0.000);
        glBegin(GL_TRIANGLES);
            glVertex3f(-30,799.8,170);
            glVertex3f(50,799.8,0);
            glVertex3f(-200,799.8,0);
        glEnd();

        //Montanha 3
        glColor3f(0.000, 0.502, 0.000);
        glBegin(GL_TRIANGLES);
            glVertex3f(130,799.8,200);
            glVertex3f(200,799.8,0);
            glVertex3f(0,799.8,0);
        glEnd();

        //Montanha 4
        glColor3f(0.235, 0.702, 0.443);
        glBegin(GL_TRIANGLES);
            glVertex3f(200, 799.9, 100);
            glVertex3f(350, 799.9, 0);
            glVertex3f(150, 799.9, 0);
        glEnd();

        //Arvores do lado esquerdo
        tree(-10,100,20);
        tree(-10,200,20);
        tree(-10,500,20);
        tree(-100,400,20);

        //Arvores do lado direito
        tree(100,100,20);
        tree(100,200,20);
        tree(100,500,20);
        tree(180,400,20);


        //Menu
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_QUADS);
            glVertex3f(15,100,45);
            glVertex3f(85,100,45);
            glVertex3f(85,100,10);
            glVertex3f(15,100,10);
        glEnd();


        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_QUADS);
            glVertex3f(17,99.9,43);
            glVertex3f(83,99.9,43);
            glVertex3f(83,99.9,12);
            glVertex3f(17,99.9,12);
        glEnd();


        //Desenha na cor amarela o texto
        glColor3f(1.000, 1.000, 0.000);
        renderBitmapString(25,100,60,(void *)font1,"O Carro Desgovernado");

        //Informacao de GAME OVER
        if(gv==1){
            glColor3f(1.000, 0.000, 0.000);
            renderBitmapString(30,99.8,51,(void *)font1,"GAME OVER");
            glColor3f(1.000, 0.000, 0.000);
            char buffer2 [50];
            sprintf (buffer2, "Seu Score foi : %d", score);
            renderBitmapString(30,99.8,46,(void *)font1,buffer2);

        }

        //Informacoes do jogo
        glColor3f(0.000, 1.000, 0.000);
        renderBitmapString(18,99.8,40,(void *)font2,"Aperte ESPACO para COMECAR");
        renderBitmapString(18,99.8,36,(void *)font2,"Aperte ESC para SAIR");

        glColor3f(1.000, 1.000, 1.000);
        renderBitmapString(18,99.8,29, (void *)font3,"Aperte CIMA para acelerar");
        renderBitmapString(18,99.8,26, (void *)font3,"Aperte BAIXO para freiar");
        renderBitmapString(18,99.8,23, (void *)font3,"Aperte DIREITA para virar a direita");
        renderBitmapString(18,99.8,20, (void *)font3,"Aperte ESQUERDA para virar a esquerda");
        renderBitmapString(18,99.8,17, (void *)font3,"Aperte F1 para alterar camera");
        renderBitmapString(18,99.8,14, (void *)font3,"BOTAO DIREITO para pausar e opcoes");

        //Informacoes Integrantes
        glColor3f(0.000, 1.000, 1.000);
        renderBitmapString(30,20,7, (void *)font3,"Integrantes:");
        renderBitmapString(30,20,5, (void *)font3,"Isaac Guibson");
        renderBitmapString(30,20,3, (void *)font3,"Eliaquim Pimentel");

}

void Desenha_Eixos_Coordenados()
{
	/* Desenha Eixo +Y */
	glColor3f(1.0, 0.0, 0.0); /* RED */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, ALTURA/2, 0);
	glEnd();

	/* Desenha Eixo -Y */
	glColor3f(1.0, 0.8, 0.8); /* RED claro */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, -ALTURA/2, 0);
	glEnd();

	/* Desenha Eixo +X */
	glColor3f(0.0, 0.0, 1.0); /* BLUE */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(LARGURA/2, 0, 0);
	glEnd();

	/* Desenha Eixo -X */
	glColor3f(0.8, 0.8, 1.0); /* BLUE claro */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(-LARGURA/2, 0, 0);
	glEnd();

	/* Desenha Eixo +Z */
	glColor3f(0.0, 1.0, 0.0); /* GREEN */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, LARGURA/2);
	glEnd();

	/* Desenha Eixo -Z */
	glColor3f(0.8, 1.0, 0.8); /* GREEN claro */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, -LARGURA/2);
	glEnd();

}

/* Função callback chamada para fazer o desenho */
void Desenha(void)
{
	glEnable(GL_DEPTH_TEST);

	/* Limpa a janela de visualização com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    /*
    //vista de tras
	gluLookAt(50.0, -49.0, 20.0,	// eye
              50.0, 500.0, 0.0,		// look
    		  0.0, 0.0, 1.0);		// up


    //vista de cima
    gluLookAt(50.0, 80.0, 200.0,	// eye
              50.0, 80.0, 0.0,		// look
    		  0.0, 1.0, 0.0);		// up
    */

    //Se tras = 1, paremetros de camera para tras
    if(tras == 1){
        ex = 50.0;
        ey = -49.0;
        ez = 20.0;
        lx = 50.0;
        ly = 500.0;
        lz = 0.0;
        ux = 0.0;
        uy = 0.0;
        uz = 1.0;
    //Se nao, parametros de camera para cima
    } else {
        ex = 50.0;
        ey = 80.0;
        ez = 200.0;
        lx = 50.0;
        ly = 80.0;
        lz = 0.0;
        ux = 0.0;
        uy = 1.0;
        uz = 0.0;
    }

    gluLookAt(ex, ey, ez,	// eye
              lx, ly, lz,		// look
    		  ux, uy, uz);		// up

    ParametrosIluminacao();

	//Desenha_Eixos_Coordenados();

	//Se comeca o jogo
	if(start==1){
        desenhaPlano();
    //Volta para tela inicial
    } else{
        fristDesign();
    }

	/* Executa os comandos OpenGL */
	glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);
}

/*
Controle de inicio e sair do jogo
*/
void processKeys(unsigned char key, int x, int y) {

    switch (key){
        case ' ':
            if(start==0){
                start = 1;
                gv = 0;
                FPS = 60;
                gotPower = 0;
                scaled_once = 0;
                score_count = 0;
                roadDivTop = 0;
                roadDivMdl = 0;
                roadDivBtm = 0;
                lrIndex = 0 ;
                car1 = 0;
                lrIndex1=0;
                car2 = +35;
                lrIndex2=0;
                car3 = +70;
                lrIndex3=0;
                power_posx=0;
                score=0;
                control = 0;
                tras = 1;
                dificuldade = 1;
            }
            break;

        case 27:
            exit(0);
            break;
        default:
            break;
        }
}

//Controle em gameplay
void spe_key(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_DOWN:
            if(FPS>10){
                // Fazendo nada por enquanto
                FPS=FPS;
            }
            break;
        case GLUT_KEY_UP:
            if(FPS < 180){
                // Fazendo nada por enquando
                FPS=FPS;
            }
            break;

        case GLUT_KEY_LEFT:
            if(control > -50){
                lrIndex1 = lrIndex1 - 10;
                control-=10;
            }
            break;

        case GLUT_KEY_RIGHT:
            if(control < 10){
                lrIndex1 = lrIndex1 + 10;
                control+=10;
            }
            break;

        case GLUT_KEY_F1:
            if(tras == 1){
                tras = 0;
            } else {
                tras = 1;
            }
            break;
        default:
                break;
    }

}

//Janela do Menu
void Janela(int opcao)
{
	switch(opcao){
	    //dia
		case 0:
			vr = 0.5;
            vg = 0.5;
            vb = 0.5;
		break;
		//noite
		case 1:
			vr = 0.1;
            vg = 0.1;
            vb = 0.1;
		break;
	}

	/* Necessário chamar toda vez que se faz uma alteração ou evento na janela
	 * Indica a funcao glutMainLoop a chamar glutDisplayFunc com as alterações */
	glutPostRedisplay();
}

void CriarMenu()
{
	/* Cria um menu cujas as opções serão gerenciadas pela funcao "Janela" */
	glutCreateMenu(Janela);

	/* Cria entradas nesse menu */
	glutAddMenuEntry("Dia", 0);
	glutAddMenuEntry("Noite", 1);

	/* Indica qual o botao que acionará o menu */
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* Inicializa parâmetros de rendering */
void Inicializa (void)
{
    /* Define a cor de fundo da janela de visualização como branca */
    glClearColor(0.000, 0.392, 0.000,1);
	glClearDepth(1.0f);


    /* Modo de projecao perspectiva */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, 500/500, 10, 1500);

	// Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering para remoção de faces escondidas
	glEnable(GL_DEPTH_TEST);

	// Modelos de Iluminação Defaut
	glShadeModel(GL_SMOOTH); 		// Gouraud
	glEnable(GL_COLOR_MATERIAL);

}

//Funcao de Animacao
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/(FPS * 2),timer,0);
}

/* Programa Principal */
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Trabalho de CG");
	glutDisplayFunc(Desenha);
	glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys);
	Inicializa();
    CriarMenu();

	glutTimerFunc(1000,timer,0);
	glutMainLoop();
}
