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
#include <cmath>
#include <vector>

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

// Rotate 10 degrees
void CVideo::rotate_ball_from_origin(float desp) {
	float angle = atan2(this->ball_z, this->ball_x);
	
	printf("Angle == %f, (x,z) == (%f, %f)\n", angle, this->ball_x, this->ball_z);
	angle += desp;

	float radius = sqrtf(this->ball_x * this->ball_x +
						 this->ball_z * this->ball_z);
	//printf("DDD %f %f %f %f %f %f\n", this->ball_x, this->ball_x*this->ball_x, this->ball_z, this->ball_z*this->ball_z, this->ball_x * this->ball_x + this->ball_z * this->ball_z, sqrtf(this->ball_x * this->ball_x + this->ball_z * this->ball_z));
	
	this->ball_z = radius * sin(angle);
	this->ball_x = radius * cos(angle);
	
	printf("radius == %f, (x,z) == (%f, %f)\n", radius, this->ball_x, this->ball_z);
}

void CVideo::set_joystick_data(unsigned int buttonMask, int x, int y, int z) {
	//printf("JS; B: %d, x=%d, y=%d, z=%d\n", buttonMask, x, y, z);	
	this->js_x = x;
	this->js_y = y;
	this->js_z = z;
	
	// left:64
	// right: 128
	
	this->js_button_left = (buttonMask == 64);
	this->js_button_right = (buttonMask == 128);
	
	if (this->js_button_left)
		//this->ball_x += 0.5;
		this->rotate_ball_from_origin(0.1);
	//
	if (this->js_button_right)
		//this->ball_x -= 0.5;
		this->rotate_ball_from_origin(-0.1);
		
	
	glutPostRedisplay();
}

GLuint CVideo::create_scenario() {
	// Empty the list of rectangles in the scenario
	this->rectangles.clear();	
	
	GLuint scenario_list_id = glGenLists(1);
	glNewList(scenario_list_id, GL_COMPILE);

	/*this->put_rectangle(0, 0, 0,
						0, 45, -20,
						2, 0.1, 2);

	this->put_rectangle(0, 0, 3,
						30, 0, 0,
						2, 0.1, 2);

	//glEndList(); return scenario_list_id;


    for (int i = 0; i < 90; i += 10)
		this->put_rectangle(0, 0, 6,
							i, 0, 0,
							2, 0.1, 2);

    for (int i = 0; i < 90; i += 10)
		this->put_rectangle(0, 6, 0,
							0, i, 0,
							2, 0.1, 2);

    for (int i = 0; i < 90; i += 10)
		this->put_rectangle(6, 0, 0,
							0, 0, i,
							2, 0.1, 2);*/

	
	/*glPushMatrix();
		glBegin(GL_QUADS);
			glVertex3f(-1, 0, 1);
			glVertex3f(-1, 0, -1);
			glVertex3f(1, 0, 1);
			glVertex3f(1, 0, -1);
		glEnd();
	glPopMatrix();*/	
	
    //
	this->put_rectangle(-3, -1, 3,
						0, 0, 10,
						2, 0.1, 2);	
    //
	this->put_rectangle(4, -3, 4.0,
						0, 0, 5,
						2, 0.1, 2);
    //
	this->put_rectangle(3, -4, 4.0,
						0, 0, 2,
						3, 0.1, 2);
    //
	this->put_rectangle(3, 4, 6.0,
						0, 0, -5,
						2, 0.1, 2);
    //
	this->put_rectangle(-2, 3, 0,
						0, 6, 0,
						2, 0.1, 2);
  
	/*glPushMatrix();
		glTranslatef(-3, -1, 13.0);
		glRotatef(10*this->ball_z, 1, 0, 0);
		glutSolidTeapot(0.56);
	glPopMatrix();

	glutSolidTeapot(0.5);*/

	glEndList();
	
	printf("Scenario created, %d rectangles\n", this->rectangles.size());
	
	return scenario_list_id;
}

CVideo::CVideo(int window_Nx, int window_Ny, int argc, char **argv) {
    cvideo_instance	= this;

    this->window_Nx = window_Nx;
    this->window_Ny = window_Ny;
    
    this->fov = 70.0;
	
	this->ball_x = 0;
	this->ball_y = 0;
	this->ball_z = -5.0;
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(window_Nx, window_Ny);
	glutInitWindowPosition(700, 100);
	glutCreateWindow("Whims");
	
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

	// Light
	GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 100.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	// Create an OpenGL list for the scenario
	this->scenario_list_id = this->create_scenario();
	
	// Run forever!
	glutMainLoop();
}

CVideo::~CVideo() {
	printf("CVideo destroyed\n");
}

void CVideo::add_rectangle(float x,  float y,  float z,
                           float rx, float ry, float rz,
                           float sx, float sy, float sz) {
	CRectangle rect(x, y, z,
				    rx, ry, rz,
					sx, sy, sz);
	this->rectangles.push_back(rect);
}

void CVideo::put_rectangle(float x,  float y,  float z,
                           float rx, float ry, float rz,
                           float sx, float sy, float sz) {
							   
	// Add the rectangle to the list of rectangles
	this->add_rectangle(x, y, z,
						rx, ry, rz,
						sx, sy, sz);

	// Add the rectangle to the OpenGL scene
	glPushMatrix();		
		// Put in its position
		glTranslatef(x, y, z);
		//glTranslatef(0, 0, 10);

		// Rotation
	    glRotatef(rx, 1, 0, 0);
	    glRotatef(ry, 0, 1, 0);
	    glRotatef(rz, 0, 0, 1);

		// Change its size.
		// This should be the last to avoid changing the units!
		glScalef(sx, sy, sz);
				
		// Add the rectangle
		//glutSolidTeapot(1.0);
		glutSolidCube(1.0);
		//glutWireCube(1.0);
	glPopMatrix();
}

void CVideo::draw_scenario() {
	glCallList(this->scenario_list_id);
	return;
}

void CVideo::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity ();

    float dist = 5.0;
    //
    float effect_x = 0*0.05*ball_x*ball_x;
    float effect_y = 0*0.05*ball_y*ball_y;
    float effect_z = 0*0.05*ball_z*ball_z;
    
	gluLookAt(ball_x + effect_x, ball_y + 0.5*dist + effect_y, ball_z - dist + effect_z,   // eye (camera position)
	          ball_x, ball_y, ball_z + dist,   // center (where the camera looks at)
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
	
	glColor3f(0.3, 0.6, 0.4);
	
	// Person ball
	glPushMatrix();
		glColor3f(0.8, 0.3, 0.1);
		glTranslatef(this->ball_x, this->ball_y, this->ball_z);
		glutSolidSphere(0.1, 50, 50);
	glPopMatrix();
	
	// Rotate scenario around the ball
	glPushMatrix();
		// Center the world in the ball
		glTranslatef(this->ball_x, this->ball_y, this->ball_z);
		
		// Rotate around the ball
		glRotatef(10.0 * this->js_x / 1000.0 , 0, 0, 1);
		glRotatef(-10.0 * this->js_y / 1000.0 , 1, 0, 0);
		
		// Get back to the original position
		glTranslatef(-this->ball_x, -this->ball_y, -this->ball_z);
		
		this->draw_scenario();
	glPopMatrix();
	
	


	glFlush ();
	glutSwapBuffers();
}

void CVideo::reshape(int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(this->fov,   // fov (field of view) angle y
	               1.0,    		// aspect ratio 
	               1.5,    		// z near
	               20.0);  		// z far
	this->window_Nx = w;
	this->window_Ny = h;
	glMatrixMode(GL_MODELVIEW);
}

void CVideo::keyboard(unsigned char key, int x, int y) {
	float desp = 0.3;
	
	switch (key) {
		case 27:
			glutLeaveMainLoop();
			break;
		case 'o': {
			this->ball_x += desp;
			break;
		}
		case 'p':
			this->ball_x -= desp;
			break;
		case 'q':
			this->ball_z += desp;
			break;
		case 'a':
			this->ball_z -= desp;
			break;
		case 'y':
			this->ball_y += desp;
			break;
		case 'h':
			this->ball_y -= desp;
			break;
		default:
			;
			//printf("%d (%c)\n", key, key);
	}
	glutPostRedisplay();
	printf("Ball: [%.2f, %.2f, %.2f]\n", ball_x, ball_y, ball_z);
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
    ball_z = 10.0*y / this->window_Nx;
    ball_y = 5.0*x / this->window_Ny;
    printf("Ball: [%.2f, %.2f, %.2f]\n", ball_x, ball_y, ball_z);
    glutPostRedisplay();
}
