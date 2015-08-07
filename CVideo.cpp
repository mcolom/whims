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

//#include <GL/gl.h>
//#include <GL/glu.h>
//
//#include <GL/glut.h>
#include <GL/freeglut.h> // To use glutLeaveMainLoop

#include "CVideo.h"

void do_cvideo_display() {
	cvideo_instance->display();
}

void do_cvideo_reshape(int w, int h) {
	cvideo_instance->reshape(w, h);
}

void do_cvideo_keyboard(unsigned char key, int x, int y) {
	cvideo_instance->keyboard(key, x, y);
}

void do_cvideo_mouse(int button, int state, int x, int y) {
	cvideo_instance->mouse(button, state, x, y);
}

void do_cvideo_mouse_motion(int x, int y) {
	cvideo_instance->mouse_motion(x, y);
}


void joystick_callback(unsigned int buttonMask, int x, int y, int z) {
	cvideo_instance->set_joystick_data(buttonMask, x, y, z);
}

void CVideo::set_joystick_data(unsigned int buttonMask, int x, int y, int z) {
	//printf("JS; B: %d, x=%d, y=%d, z=%d\n", buttonMask, x, y, z);	
	this->js_x = x;
	this->js_y = y;
	this->js_z = z;
	this->js_button = (buttonMask != 0);
	glutPostRedisplay();
}

CVideo::CVideo(int window_Nx, int window_Ny, int argc, char **argv) {
    cvideo_instance	= this;

    this->window_Nx = window_Nx;
    this->window_Ny = window_Ny;
	
	this->anglex = 0;
	this->angley = 0;
	
	this->camera_x = 0;
	this->camera_y = 0;
	this->camera_z = -5.0;
	
	this->camera_angle_x = 0;
	this->camera_angle_y = 0;
	this->camera_angle_z = 0;
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(window_Nx, window_Ny);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Whimps");
	
	glutJoystickFunc(joystick_callback, 1000/24);

	glClearColor(0.01, 0.01, 0.2, 0.0);
	glShadeModel(GL_FLAT);

	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	
	// We want to draw frontal faces with a solid color
	glPolygonMode(GL_FRONT, GL_FILL);	
	

	glutDisplayFunc(do_cvideo_display);
	glutReshapeFunc(do_cvideo_reshape);

	// To use glutLeaveMainLoop and continue
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
	              GLUT_ACTION_CONTINUE_EXECUTION);
	glutKeyboardFunc(do_cvideo_keyboard);
	glutMouseFunc(do_cvideo_mouse);
	//glutMotionFunc(mouse_motion);
	glutPassiveMotionFunc(do_cvideo_mouse_motion);
	
	gluLookAt(camera_y, 0.0, camera_z,   // eye (camera position)
	          0.0, 0.0, camera_z+10.0,   // center (where the camera looks at)
	          0.0, 1.0, 0.0);  // up
	
	glutMainLoop();

	printf("CVideo exiting MainLoop...\n");
}

CVideo::~CVideo() {
	printf("CVideo destroyed\n");
}

void CVideo::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity ();

	gluLookAt(camera_x, camera_y, camera_z,   // eye (camera position)
	          camera_x, camera_y, camera_z+10.0,   // center (where the camera looks at)
	          0.0, 1.0, 0.0);  // up

	//glRasterPos2f(0.5, 0.5);
	//glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"some text");
	//glutBitmapCharacter(GLUT_STROKE_ROMAN, 's');
	//glLoadIdentity ();
	
	// clear the matrix
	// viewing transformation
	
	// modeling transformation
	glScalef(1.0, 1.0, 1.0);
	
	// Axes
	float XP[3] = {1,0,0},  XN[3] = {-1,0,0}, YP[3] = {0,1,0},
	      YN[3] = {0,-1,0}, ZP[3] = {0,0,1},  ZN[3] = {0,0,-1},
	      ORG[3] = {0,0,0};
	//
	glBegin(GL_LINES);
	//
	glColor3f(1,0,0);
	glVertex3fv(ORG);
	glVertex3fv(XP);
	//
	glColor3f(0,1,0);
	glVertex3fv(ORG);
	glVertex3fv(YP);
	//
	glColor3f(0,0,1);
	glVertex3fv(ORG);
	glVertex3fv(ZP);
	//
	glEnd();
	

	glColor3f(0.8, 0.2, 0.7);
	glutSolidCube(0.3);
	
	glColor3f(0.3, 0.6, 0.4);
    //	
	//glPushMatrix();
		//glRotatef(anglex, 1, 0, 0);
		//glRotatef(angley, 0, 1, 0);	
		//glutWireTeapot(0.5);

	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 100.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glPushMatrix();
		glColor3f(0.8, 0.3, 0.1);
		glTranslatef(this->camera_x, this->camera_y, this->camera_z+2.0);
		glutSolidSphere(0.05, 50, 50);
	glPopMatrix();
			
	glRotatef(-45.0 * this->js_x / 1000.0 , 0, 0, 1);
	glRotatef(-45.0 * this->js_y / 1000.0 , 1, 0, 0);

	glPushMatrix();
		glTranslatef(-3, -1, 13.0);
		glRotatef(10*this->camera_z, 1, 0, 0);
		glutSolidTeapot(0.56);
	glPopMatrix();

	glutSolidTeapot(0.5);
	
	glPushMatrix();
		glTranslatef(0, 0, 3.0);
		glutSolidTeapot(0.7);
	glPopMatrix();
	//
	glPushMatrix();
		glTranslatef(1, 1, 7.0);
		glutSolidTeapot(0.2);
	glPopMatrix();
	//
	glPushMatrix();
		glTranslatef(1, 1, 4.0);
		glutSolidTorus (0.275, 0.85, 20, 50);
	glPopMatrix();
	//
	glPushMatrix();
		glTranslatef(1, 1, 13.0);
		glutSolidCone (0.575, 0.35, 12, 15);
	glPopMatrix();
	//
	
	//glutWireSphere(0.2, 10, 10);
	
	//glPushMatrix();
		//glTranslatef(this->camera_x, this->camera_y, this->camera_z+10.0);
	//glPopMatrix();
	
		//glutSolidTeapot(0.4);
	//glPopMatrix();


	glFlush ();
	glutSwapBuffers();
}

void CVideo::reshape(int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0,   // fov (field of view) angle y
	               1.0,    // aspect ratio 
	               1.5,    // z near
	               20.0);  // z far
	this->window_Nx = w;
	this->window_Ny = h;
	glMatrixMode (GL_MODELVIEW);
}

void CVideo::keyboard(unsigned char key, int x, int y) {
	float desp = 0.3;
	
	switch (key) {
		case 27:
			glutLeaveMainLoop();
			break;
		case 'o':
			this->camera_x += desp;
			break;
		case 'p':
			this->camera_x -= desp;
			break;
		case 'q':
			this->camera_z += desp;
			break;
		case 'a':
			this->camera_z -= desp;
			break;

		default:
			;
			//printf("%d (%c)\n", key, key);
	}
	glutPostRedisplay();
	printf("Camera: [%.2f, %.2f, %.2f]\n", camera_x, camera_y, camera_z);
}

void CVideo::mouse(int button, int state, int x, int y) {
	if (button == 0)
		this->left_button_pressed = (state == 0);
	else if (button == 2)
		this->right_button_pressed = (state == 0);
	printf("left=%d, right=%d\n", this->left_button_pressed,
	                              this->right_button_pressed);
}

void CVideo::mouse_motion(int x, int y) {
    //anglex = 3*360*y / this->window_Nx;
    //angley = 3*360*x / this->window_Ny;
    camera_z = 10.0*y / this->window_Nx;
    camera_y = 5.0*x / this->window_Ny;
    printf("Camera: [%.2f, %.2f, %.2f]\n", camera_x, camera_y, camera_z);
    glutPostRedisplay();
}
