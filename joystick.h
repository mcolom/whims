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

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

struct JoystickData {
	bool button;
	float angle[4];

	char num_axes;
	char num_buttons;
	int driver_version;
	char *name;
};

static JoystickData js;

void start_joystick();
void finish_joystick();

#endif