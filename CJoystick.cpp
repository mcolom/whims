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


void* joystick_thread(void *arg) {
	struct js_event ev;
	unsigned char num;

	while (cjoystick_instance->thread_active()) {
		do {
			int ret = read(cjoystick_instance->get_fd(),
							&ev,
							sizeof(struct js_event));
			printf("read\n");
			if (ret != sizeof(struct js_event)) {
				return NULL;
			}
		} while (ev.type & JS_EVENT_INIT);

		num = ev.number;
		switch (ev.type) {
			case JS_EVENT_BUTTON:
				cjoystick_instance->set_button(ev.value == 1);
				break;
			case JS_EVENT_AXIS: {
				float angle = ev.value * 45.0 / 32767.0;
				cjoystick_instance->set_angle(angle, num);
				break;
			}
			default:
				break;
		}
		printf("button: %d, [%f, %f, %f, %f]\n",
		  cjoystick_instance->get_button(),
		  cjoystick_instance->get_angle(0), cjoystick_instance->get_angle(1),
		  cjoystick_instance->get_angle(2), cjoystick_instance->get_angle(3));
	}
	printf("Thread exiting\n");
	pthread_exit(NULL);
}

CJoystick::CJoystick() {
	cjoystick_instance = this;
	
	const char *device = "/dev/input/js0";
	struct JS_DATA_TYPE js;

	// open the joystick 
	if ((this->fd = open(device, O_RDONLY)) < 0 ) {
		fprintf(stderr, "Couldn't open joystick device %s\n", device);
		//
		this->num_axes = 0;
		this->num_buttons = 0;
		this->driver_version = -1;
		return;
	}
	
	ioctl(this->fd, JSIOCGAXES, &this->num_axes);
	printf("%d axes\n", this->num_axes);

	ioctl(this->fd, JSIOCGBUTTONS, &this->num_buttons);
	printf("%d buttons\n", this->num_buttons);

	ioctl(this->fd, JSIOCGVERSION, &this->driver_version);
	printf("driver version: %d\n", this->driver_version);
	
	const int buffer_len = 256;
	this->name = new char[buffer_len];
	if (ioctl(this->fd, JSIOCGNAME(buffer_len), this->name) < 0)
		strncpy(this->name, "???", 4);

	printf("Joystick name: %s\n", this->name);
	
	this->run_thread = true;
	int err = pthread_create(&tid, NULL, &joystick_thread, NULL);
	if (err != 0)
		printf("\ncan't create thread :[%s]", strerror(err));
	else
		printf("\n Thread created successfully\n");
	
	//joystick_get_input(fd);
}

CJoystick::~CJoystick() {
	printf("CJoystick destroyed\n");
	
	printf("Waiting for thread to terminate...\n");
	close(this->fd);
	this->run_thread = false;
	pthread_cancel(this->tid); 	// [ToDo] use select to prevent thread
								// blocked in read
	pthread_join(this->tid, NULL);
	printf("Thread joined\n");
	
	delete[] this->name;
}

int CJoystick::get_fd() {
	return this->fd;
}

bool CJoystick::get_button() {
	return this->button;
}

void CJoystick::set_button(bool state) {
	this->button = state;
}

float CJoystick::get_angle(int axis) {
	return this->angle[axis];
}

void CJoystick::set_angle(float angle, int axis) {
	this->angle[axis] = angle;
}

bool CJoystick::thread_active() {
	return this->run_thread;
}
