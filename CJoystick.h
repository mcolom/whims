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
 
#include <pthread.h>

#ifndef _CJOYSTICK_H_
#define _CJOYSTICK_H_

class CJoystick {
	private:

	pthread_t tid;
	bool run_thread;

	int fd;

    char num_axes;
    char num_buttons;
    int driver_version;
    char *name;
    
    bool button;
    float angle[4];
        
	public:

	CJoystick();
	~CJoystick();
	
	int get_fd();	
	
	bool get_button();	
	void set_button(bool state);
	float get_angle(int axis);	
	void set_angle(float angle, int axis);
	
	bool thread_active();
};

static CJoystick *cjoystick_instance = NULL;

#endif
