/*
 *
 * This file is part of the Whims videogame
 *
 * Copyright(c) 2015 Miguel Colom.
 * http://mcolom.info
 *
 * This file may be licensed under the terms of of the
 * GNU General Public License Version 2 (the ``GPL'').
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the GPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the GPL along with this
 * program. If not, go to http://www.gnu.org/licenses/gpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>

#include <GL/gl.h>
#include <GL/glu.h>
//
//#include <GL/glut.h>
#include <GL/freeglut.h> // To use glutLeaveMainLoop


int window_Nx = 600;
int window_Ny = 600;

float anglex = 0.0;
float angley = 0.0;


void init(void) {
	glClearColor (0.01, 0.01, 0.2, 0.0);
	glShadeModel (GL_FLAT);
}

void display(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 0.0, 0.0);

	glLoadIdentity ();
	
	//glRasterPos2f(0.5, 0.5);
	//glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"some text");
	//glutBitmapCharacter(GLUT_STROKE_ROMAN, 's');
	//glLoadIdentity ();
	
	// clear the matrix
	// viewing transformation
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	// modeling transformation
	glScalef (1.0, 1.0, 1.0);

	glutWireCube (2.0);
	
	glColor3f (1.0, 1.0, 1.0);
    //	
	glPushMatrix();
		glRotatef(anglex, 1, 0, 0);
		glRotatef(angley, 0, 1, 0);	
		glutWireTeapot(1.0);
		glutSolidTeapot(0.4);
	glPopMatrix();	

	glutSwapBuffers();
	glFlush ();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, 1.0, 1.5, 20.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			glutLeaveMainLoop();
			break;
		case 'o':
			angley -= 15.0;
			glutPostRedisplay();
			break;
		case 'p':
			angley += 15.0;
			glutPostRedisplay();
			break;
		case 'q':
			anglex -= 15.0;
			glutPostRedisplay();
			break;
		case 'a':
			anglex += 15.0;
			glutPostRedisplay();
			break;

		default:
			;
			//printf("%d (%c)\n", key, key);
	}
}

void mouse (int button, int state, int x, int y) {
	printf("[%d,%d]\n", x, y);
}

void mouse_motion(int x, int y) {
    anglex = 3*360*y / window_Nx;
    angley = 3*360*x / window_Ny;
    glutPostRedisplay();

	//printf("M[%d,%d]\n", x, y);
	//printf("%f,%f \n", anglex, angley);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (window_Nx, window_Ny);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Whimps");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	// To use glutLeaveMainLoop and continue
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
	              GLUT_ACTION_CONTINUE_EXECUTION);
	glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);
	//glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(mouse_motion);
	
	glutMainLoop();

	printf("Exiting...\n");
	return EXIT_SUCCESS;
}
