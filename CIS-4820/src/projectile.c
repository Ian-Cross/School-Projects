#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graphics.h"
#include "projectile.h"
/*
Start
------------------------------------
|   xRot    |   yRot    |   zRot   |
| 0.000000  | 45.000000 | 0.000000 |

even left
359.000000 812.000000 0.000000

even right
359.000000 901.000000 0.000000

straight up
254.000000 901.000000 0.000000

strait down
447.000000 899.000000 0.000000
*/

int totalProjectiles = 0;

void fireMouseProjectile() {
  float x, y, z;
  getViewPosition(&x, &y, &z);

  if (mobVisible[0] == 0) {
    getViewOrientation(&mouseRotX, &mouseRotY, &mouseRotZ);
    createMob(0, -x, -y, -z, 0.0);
  }
}

void fireTowerProjectile(int sourceX, int sourceY, int sourceZ, int targetX,
                         int targetY, int targetZ) {
  float rotX, rotY, rotZ;

  // createMob(0, -x, -y, -z, 0.0);
}
