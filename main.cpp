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

void init(void) {
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

void display(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
	glLoadIdentity ();
	/* clear the matrix */
	/* viewing transformation */
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef (1.0, 2.0, 1.0);
	/* modeling transformation */
	glutWireCube (1.0);
	
	glutWireTeapot(1.0);

	glFlush ();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
 switch (key) {
   case 27:
     glutLeaveMainLoop();
     break;
   }
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	// To use glutLeaveMainLoop and continue
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
	              GLUT_ACTION_CONTINUE_EXECUTION);
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();

	printf("Exiting...\n");
	return EXIT_SUCCESS;
}
