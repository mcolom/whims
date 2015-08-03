// http://www.oocities.org/valcoey/intropengl.html
//
// g++ main_oocities.cpp -lGL -lGLU -lglut -o oocities

/* Este programa utiliza proyeccion ortografica para
 * visualizar una "Tetera", este objeto esta definido
 * en GLUT, se crea una fuente de luz, y un material */

//Incluimos las librerias
#include <GL/glut.h>
#include <stdlib.h>

void init(void)
{
 // Ubicamos la fuente de luz en el punto (1.0, 1.0, 1.0)
 GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

 // Activamos la fuente de luz
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glDepthFunc(GL_LESS);
 glEnable(GL_DEPTH_TEST);
 // Queremos que se dibujen las caras frontales
 // y con un color solido de relleno. 
 glPolygonMode(GL_FRONT, GL_FILL); 
}

void reshape(int w, int h)
{
 if (!h)
	return;
 glViewport(0, 0,  (GLsizei) w, (GLsizei) h);
 // Activamos la matriz de proyeccion.
 glMatrixMode(GL_PROJECTION);
 // "limpiamos" esta con la matriz identidad.
 glLoadIdentity();
 // Usamos proyeccion ortogonal
  glOrtho(-200, 200, -200, 200, -200, 200);
 // Activamos la matriz de modelado/visionado. 
 glMatrixMode(GL_MODELVIEW);
 // "Limpiamos" la matriz
 glLoadIdentity();
}

// Aqui ponemos lo que queremos dibujar.
void display(void)
{ 
 // Propiedades del material
 GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
 GLfloat mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
 GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
 GLfloat mat_shininess[] = { 100.0f };

 // "Limpiamos" el frame buffer con el color de "Clear", en este 
 // caso negro. 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glMatrixMode( GL_MODELVIEW_MATRIX );
 glLoadIdentity();
 
 // Rotacion de 30 grados en torno al eje x
 glRotated(25.0, 1.0, 0.0, 0.0);
 // Rotacion de -30 grados en torno al eje y
 glRotated(-30.0, 0.0, 1.0, 0.0);
 // Dibujamos una "Tetera" y le aplico el material

 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
 glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
 glutSolidTeapot(125.0);

 glFlush();
} 

// Termina la ejecucion del programa cuando se presiona ESC
void keyboard(unsigned char key, int x, int y)
{
 switch (key) 
   {
   case 27: exit(0);
             break;
   }
}    

// Main del programa.
int main(int argc, char **argv)
{ 
 // Inicializo OpenGL
 glutInit(&argc, argv);
 
 // Activamos buffer simple y colores del tipo RGB  
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

 // Definimos una ventana de medidas 300 x 300 como ventana 
 // de visualizacion en pixels
 glutInitWindowSize (300, 300);
 
 // Posicionamos la ventana en la esquina superior izquierda de 
 // la pantalla.
 glutInitWindowPosition (0, 0);

 // Creamos literalmente la ventana y le adjudicamos el nombre que se
 // observara en su barra de titulo.
 glutCreateWindow ("Teapot");

 // Inicializamos el sistema 
 init();

 glutDisplayFunc(display); 
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 glutMainLoop();
 
 // ANSI C requiere que main retorne un valor entero.
 return 0;
}
