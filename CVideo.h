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

#ifndef _CVIDEO_H_
#define _CVIDEO_H_


#include <vector>

#include <GL/gl.h>


using namespace std;

class CRectangle {
	private:

	float x, y, z; 		// Position
	float rx, ry, rz; 	// Rotation
	float sx, sy, sz; 	// Scaling
	
	public:
	
	CRectangle(float x, float y, float z,
			   float rx, float ry, float rz,
			   float sx, float sy, float sz) {
	}
};

class CVideo {
	private:

	int window_Nx, window_Ny; // Window size
	float fov; // Field of view of the camera
	
	bool left_button_pressed, right_button_pressed; // Mouse buttons
	
	float ball_x, ball_y, ball_z; // Ball position
		
	int js_x, js_y, js_z; // Joystick axes
	bool js_button_left, js_button_right; // Joystick buttons
	
	vector<CRectangle> rectangles; // All rectangles in the scenario

	GLuint scenario_list_id; // GLUT list to draw the scenario
	
	void rotate_ball_from_origin(float desp);
	GLuint create_scenario();

	void put_rectangle(float x,  float y,  float z,
					   float rx, float ry, float rz,
					   float sx, float sy, float sz);

	void add_rectangle(float x,  float y,  float z,
					   float rx, float ry, float rz,
					   float sx, float sy, float sz);

	public:

	CVideo(int window_Nx, int window_Ny, int argc, char **argv);
	~CVideo();
	
	void keyboard(unsigned char key, int x, int y);
	void display();
	void reshape(int w, int h);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x, int y);
	void set_joystick_data(unsigned int buttonMask, int x, int y, int z);
	void draw_scenario();
};

static CVideo *cvideo_instance = NULL;

#endif
