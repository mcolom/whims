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

// Documentation about the joystick: 
// https://www.kernel.org/doc/Documentation/input/joystick-api.txt

#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

#include "CJoystick.h"

CJoystick::CJoystick() {
	const char *device = "/dev/input/js0";

	int fd;
	struct JS_DATA_TYPE js;

	// open the joystick 
	if ((fd = open(device, O_RDONLY)) < 0 ) {
		fprintf(stderr, "Couldn't open joystick device %s\n", device);

		this->num_axes = 0;
		this->num_buttons = 0;
		this->driver_version = -1;
		this->name = (char*)"-";

		return;
	}
	
	ioctl(fd, JSIOCGAXES, &this->num_axes);
	printf("%d axes\n", this->num_axes);

	ioctl(fd, JSIOCGBUTTONS, &this->num_buttons);
	printf("%d buttons\n", this->num_buttons);

	ioctl(fd, JSIOCGVERSION, &this->driver_version);
	printf("driver version: %d\n", this->driver_version);
	
	const int buffer_len = 256;
	this->name = new char[buffer_len];
	if (ioctl(fd, JSIOCGNAME(buffer_len), this->name) < 0)
		strncpy(this->name, "???", 4);

	printf("Joystick name: %s\n", this->name);
	
	close(fd);
	
}

CJoystick::~CJoystick() {
	printf("CJoystick destroyed\n");
	delete[] this->name;
}

void CJoystick::display() {
}
