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
#include <pthread.h>
#include "CJoystick.h"

static pthread_t joystick_tid;
static bool run_joystick_thread;

const int buffer_len = 256;

static int fd;

void* joystick_thread(void *arg) {
	struct js_event ev;
	unsigned char num;

	while (run_joystick_thread) {
		do {
			int ret = read(fd,
							&ev,
							sizeof(struct js_event));
			if (ret != sizeof(struct js_event)) {
				return NULL;
			}
		} while (ev.type & JS_EVENT_INIT);

		num = ev.number % 4;
		switch (ev.type) {
			case JS_EVENT_BUTTON:
				button = (ev.value == 1);
				break;
			case JS_EVENT_AXIS: {
				float angle_joy = ev.value * 45.0 / 32767.0;
				angle[num] = angle_joy;
				break;
			}
			default:
				break;
		}
		printf("button: %d, [%f, %f, %f, %f]\n",
		  button,
		  angle[0], angle[1], angle[2], angle[3]);
	}
	printf("Thread exiting\n");
	pthread_exit(NULL);
}

void get_joystick_info() {	
	ioctl(fd, JSIOCGAXES, &num_axes);
	printf("%d axes\n", num_axes);

	ioctl(fd, JSIOCGBUTTONS, &num_buttons);
	printf("%d buttons\n", num_buttons);

	ioctl(fd, JSIOCGVERSION, &driver_version);
	printf("driver version: %d\n", driver_version);
	
	if (ioctl(fd, JSIOCGNAME(buffer_len), name) < 0)
		strncpy(name, "???", 4);

	printf("Joystick name: %s\n", name);
}

void start_joystick() {
	name = new char[buffer_len];

	// open the joystick
	const char *device = "/dev/input/js0";
	struct JS_DATA_TYPE js;
	
	if ((fd = open(device, O_RDONLY)) < 0 ) {
		fprintf(stderr, "Can't open joystick device %s\n", device);
		//
		num_axes = 0;
		num_buttons = 0;
		driver_version = -1;
		return;
	}
	
	get_joystick_info();

	run_joystick_thread = true;
	int err = pthread_create(&joystick_tid, NULL, &joystick_thread, NULL);
	if (err != 0)
		printf("Can't create joystick thread :[%s]", strerror(err));
	else
		printf("Joystick thread created successfully\n");
}

void finish_joystick() {
	printf("CJoystick finishing\n");
	
	printf("Waiting for thread to terminate...\n");
	run_joystick_thread = false;
	pthread_cancel(joystick_tid); 	// [ToDo] use select to prevent thread
							// blocked in read
	pthread_join(joystick_tid, NULL);
	printf("Thread joined\n");

	close(fd);
	
	delete[] name;
}
