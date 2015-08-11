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
#include <unistd.h> // [sleep]
#include <string.h>
#include <pthread.h>

#include "CVideo.h"

static pthread_t tid_main;

void* main_thread(void *arg) {
	int counter = 0;
	while (counter < 10) {
		printf("Main running (%d)\n", counter);	
		sleep(10);
		counter++;
	}
	
	pthread_exit(NULL);
}

bool check_joystick(const char *device) {
	FILE *f = fopen(device, "r");
	bool joystick_detected = (f != NULL);
	if (joystick_detected)
		fclose(f);
	return joystick_detected;
	
}

int main(int argc, char **argv) {
	// Check if the joystick is available
	// If not, just leave!
	const char *joystick_device = "/dev/input/js0";
	if (!check_joystick(joystick_device)) {
		fprintf(stderr, "Can't open joystick device %s!\n",
		  joystick_device);
		return EXIT_FAILURE;
	}
	
	
	int err = pthread_create(&tid_main, NULL, &main_thread, NULL);
	if (err != 0)
		printf("Can't create main thread :[%s]", strerror(err));
	else
		printf("Main thread created successfully\n");

	CVideo *video = new CVideo(600, 600, argc, argv);
	
	// ...
	
	delete video;
	return EXIT_SUCCESS;
}
