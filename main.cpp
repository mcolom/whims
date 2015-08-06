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

#include "CVideo.h"
#include "CJoystick.h"

int main(int argc, char **argv) {
	//CVideo *video = new CVideo(600, 600, argc, argv);
	CJoystick *joystick = new CJoystick();
	
	int counter = 0;
	while (counter < 5) {
		printf("Main running (%d)\n", counter);	
		sleep(3);
		counter++;
	}

    delete joystick;
    //delete video;
	return EXIT_SUCCESS;
}
