#include <gl/glut.h>

GLfloat angulo, aspecto;
int X,Y,Z, tela_x, tela_y; 
            
// Fun��o callback chamada para fazer o desenho
void Desenha(void)
{
	// Limpa a janela e o buffer de profundidade
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//frontal
 	glPushMatrix();
 	glScalef(25,1,1); 
	glColor3f(   1.0,  0.0,  0.0 );
	glutSolidCube(1);
	glPopMatrix();
	
	//lateral esquerda
	glPushMatrix();
	glTranslatef(-12,0,-18);
 	glScalef(1,1,35); 
	glColor3f(1.0,  0.0,  0.0);
	glutSolidCube(1);
	glPopMatrix();
	
	//lateral direita
	glPushMatrix();
	glTranslatef(12,0,-18);
 	glScalef(1,1,35); 
	glColor3f(   1.0,  0.0,  0.0 );
	glutSolidCube(1);
	glPopMatrix();
	
	//back
 	glPushMatrix();
 	glTranslatef(0,0,-36);
 	glScalef(25,1,1); 
	glColor3f(1.0,  0.0,  0.0 );
	glutSolidCube(1);
	glPopMatrix();
	
	//trilho Central
	glPushMatrix();
	glTranslatef(0,0,-17.75);
 	glScalef(1.7,1,35.5); 
	glColor3f(   1.0,  0.0,  0.0 );
	glutSolidCube(1);
	glPopMatrix();
	
	//mesa impress�o
 	glPushMatrix();
 	glTranslatef(0,0.9,-16.5);
 	glScalef(18,0.2,18); 
	glColor3f(   1.0,  0.0,  0.0 );
	glutSolidCube(1);
	glPopMatrix();
	
	//bule impresso
	glPushMatrix();
	glTranslatef(0,3.2,-16.5);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidTeapot(3);
	glPopMatrix();
	

	
glutSwapBuffers();}

// Inicializa os par�metros de rendering (luz)
void Inicializa (void)
{ 	
	
	// Posi��o do obbservador
	X = 0, Y = 50, Z = 100;
	angulo = 40;
	
	// Modelo de reflex�o da luz. Percentual de intensidade de cada cor
	// luz refletida no ambiente. Sua origem n�o pode ser determinada. Gera uma ilumina��o constante.
	GLfloat luz_ambiente [4]  = {0.2,0.2,0.2,1};       
	
	// Luz que vem de uma dire��o e � refletida em todas as dire��es quando atinge a superf�cie. 
	// Coloca o efeito degrade.
	GLfloat luz_difusa   [4]  = {0.8,0.8,0.8,1.0};	   
	
	// Luz que vem de uma dire��o e � refletida em uma �nica dire��o (Em geral: cinza ou branca). 
	// Ponto de brilho.
	GLfloat luz_especular[4]  = {1, 1, 1, 1};          
	
	//Posi��o da Luz
	//�ltimo par�metro zero: luz direcional, diferente 0: posi��o (puntual)
	GLfloat posicao_luz  [4]  = {0, 50.0, 50.0, 1}; 

	// Brilho do material
	GLfloat especularidade[4] = {1.0,1.0,1.0,1.0}; 		
	GLint   especularidade_material = 30;    // Trocar o valor de 10 a 200.

 	// Cor de fundo da janela (preta)
	glClearColor(0, 0, 0, 0);

	// Modelos de tonaliza��o:	
	// Modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH); 
	
	// Preenchimento com apenas uma cor.
	//glShadeModel(GL_FLAT); 

	// Define a reflect�ncia do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

	// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS, especularidade_material);

	// Especifica as propriedades do modelo de iluminua��o. 
	// Segundo par�metro define a intensidade da luz ambiente	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);

	// Define os par�metros da luz de n�mero 0. A OpenGL tem at� oito fontes.
	//Par�metros 1: fonte de luz (0 a 7), 2: caracteristica a luz, 3: determina o valor do par�metro especifica
	glLightfv(GL_LIGHT0, GL_AMBIENT,  luz_ambiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  luz_difusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz );

	// Define a cor do material a partir da cor atual
	glEnable(GL_COLOR_MATERIAL);
	
	// Liga a ilumina��o
	glEnable(GL_LIGHTING);  
	
	// Liga a luz n�mero zero
	glEnable(GL_LIGHT0);
	
	// Habilita a bufferiza��o de profundidade
	glEnable(GL_DEPTH_TEST);
}

// Fun��o usada para especificar o volume de visualiza��o
void ParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
	gluPerspective(angulo,aspecto,0.4,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
	gluLookAt(X,Y,Z, 0,0,0, 0,1,0);
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanho(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a corre��o de aspecto
	aspecto = (GLfloat)w/(GLfloat)h;
    
	// Define os par�metros de visualiza��o
	ParametrosVisualizacao();
}

void TeclasEspeciais(int tecla, int x, int y) {
		switch (tecla) {
			case GLUT_KEY_LEFT:  X -=5; break;
			case GLUT_KEY_RIGHT: X +=5; break;
			case GLUT_KEY_UP:  	 Y +=5;	break;
			case GLUT_KEY_DOWN:  Y -=5;	break;

			case GLUT_KEY_HOME:  Z +=5;	break;
			case GLUT_KEY_END :  Z -=5;	break;
		}
		glLoadIdentity();
		gluLookAt(X,Y,Z, 0,0,0, 0,1,0);
        glutPostRedisplay();
    }


// Callback de mouse
void Mouse(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) angulo -= 5;		
	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) angulo += 5;
		
	ParametrosVisualizacao();
	glutPostRedisplay();
}

// Programa Principal
int main(int argc, char** argv)
{
    // Define o tamanho da tela
	int tam_x = 500;
	int tam_y = 500;
	
	// obt�m o tamanho da tela do computador
	tela_x = GetSystemMetrics(SM_CXSCREEN);
	tela_y = GetSystemMetrics(SM_CYSCREEN);
			
	glutInit(&argc, argv);
	glutInitWindowSize(tam_x,tam_y); 	
	glutInitWindowPosition((tela_x-tam_x)/2,(tela_y-tam_y)/2); // posiciona o meio da tela		

	// Indica o modo de visualiza��o da janela. 
	// GLUT_DOUBLE: os desenhos s�o feitos fora da tela, para depois serem inclu�dos na tela. 
	// GLUT_DEPTH: ativa o algoritmo Z Buffer, que permite que novos objetos n�o sobreponham os objetos mais pr�ximos.	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanho);
	glutSpecialFunc(TeclasEspeciais);
	glutMouseFunc(Mouse);
	Inicializa();
	glutMainLoop();
}
