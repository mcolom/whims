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

#include "CVideo.h"

class CVideo {
	private:

	int window_Nx;
	int window_Ny;

	float anglex;
	float angley;
	
	bool left_button_pressed;
	bool right_button_pressed;
	
	float camera_x;
	float camera_y;
	float camera_z;
	
	float camera_angle_x;
	float camera_angle_y;
	float camera_angle_z;

	public:

	CVideo(int window_Nx, int window_Ny, int argc, char **argv);
	~CVideo();
	
	void keyboard(unsigned char key, int x, int y);
	void display();
	void reshape(int w, int h);
	void mouse(int button, int state, int x, int y);
	void mouse_motion(int x, int y);	
};

static CVideo *cvideo_instance = NULL;

#endif
