# Game Programming Assignments

## Assignment 1 - Building a Three Dimensional World

Due. January 24, 2020

---

### World Building

---

Create a three dimensional world using the `world[][][]` array.

Create a flat surface which will be the ground on which the game will be
played. It should be 100 units in the x and z dimension. It should be at
least 5 units deep in the y dimension. Make the top layer of the ground a
green colour. Make the layers below the top layer a brown colour.
You can use the setUserColour() function to create the colours. You can
also use the default colours but they are very bright. Do not make the
ground too high (don't use a large y value) as you will need to put
objects in the sky and the player will move above the ground so there
needs to be enough world space for the sky.

Randomly place several hills and valleys in the world. These should
be approximately 10 units in both x and z dimensions. They should be
two or three units in height. Place enough of these around the world
make the ground look interesting. Use green for the hill colour.

The edges should not be steep on the hills or valleys. Each step should
move up one unit for each unit forward. For example, the following is an
example of a hill and a valley seen from the side. The slope on the edges
is gradual and there are no places where there are two stacked cubes
on the edge.

       XXXXXXX
      XXXXXXXXX
     XXXXXXXXXXX

     XXXXX       XXXXXX
          X     X
           XXXXX

The following is an example of a hill and valley that has edges which are
too steep.

     XXXXXXXXXX
     XXXXXXXXXX
     XXXXXXXXXX

     XXXXXXXX     XXXXXXXX
            X     X
            XXXXXXX

We will eventually create players in the game which can climb up one
cube but will not be able to climb two stacked cubes. The intention
of the sloping hills and valleys is to create surfaces that the players
will be able to move over without getting stuck.

The position of the hills and valleys should be random. Each time the
game is started they should appear in different locations. Use the rand()
function to find locations for them. They should not run into the edge
of the world.

---

### Collision Detection

---

Add collision detection so the viewpoint cannot pass into a space
which is occupied by a cube. Any world space that is not set equal to 0
is occupied.

Test for collisions by checking if the position the viewpoint will move
into is an occupied space in the world. Write the collision detection so
that the viewpoint does not pass inside a cube.

The simplest method for collision detection is to test if the next move
of the viewpoint will enter an occupied cube. If the cube is occupied
then prevent the movement. This can be done using the get and set viewposition
functions.

Responding to a collision when it is just about to occur
may not always be sufficient. It is possible in some cases
for the viewpoint to pass into the edge of a cube and not register as
being inside the cube. This allows the user to see inside the cube
when they should not be able to do so. You may need to take into consideration
the direction which the viewpoint is moving and predict when it is getting
near to the cube instead of it being inside the cube. In this case you
are actually looking for the viewpoint being close to an occupied space
instead of inside that space.

Add collision detection so the viewpoint cannot move outside the
space defined by the world array. The viewpoint should not move to
a position less than 0 in any direction. It should not move to a position
greater than 99 in the x and z direction, and not greater than 49 in the y
direction.

Since the game will be played from above you should limit the
maximum elevation of the viewpoint. This will prevent the viewer
from getting too high in the air. Pick a maximum elevation and
do not allow the viewpoint to move above this range. The viewpoint
should be at least 15 units above the ground.

---

### Clouds and Timing

---

Clouds will be animated objects which move through the upper part
of the world space. You will need to keep track of the cloud's locations
and update the world array as they move. The movement of the clouds
should be easily visible. Pick speed and shape for clouds which clearly
demonstrate the motion. Make clouds larger than one or two cubes in size.
Clouds can be flat (one layer deep) but they should be wide and long
enough to be easily seen.

Add the clouds in the world array as white or light gray cubes. Move the
clouds by changing the location for the cubes. When the clouds move past the
edge of the world they should move back to the opposite side of the world.
For example, if a cloud at position x == 99 and it will next move to
x == 100 (which would be outside the world space) it should move to location
x == 0. You can use modulus to calculate the cloud x and z positions.

Put the clouds at an elevation that is higher than the maximum player
elevation. The player's viewpoint should not be able to enter a cloud.

The update() function is called by OpenGL. This is used for
the animations. If the updates to the screen are allowed to run
freely then the speed of the animation will depend on how often
the function is called. Faster computers will have faster animations.

To avoid this you need to use real time to schedule updates to the
animated objects. Use real time to update the cloud animations on a
fixed time schedule. You should check the current time with each
call to update() and only change the animation if enough time has
passed since the previous change. Do not use sleep() for this operation.

---

### Player Bases

---

Create two player bases. These will be five units along each edge and three
units tall. Pick two different colours and place them on the ground
so they are not too close to each other. Bases should not appear in a
valley or on top of a hill. It could be useful to place the bases first
and then make sure the hills and valleys do not collide with them.

You can make the bases look more interesting than simple boxes if you
wish. You can make them multiple colours and you can add windows or
towers.

## Assignment 2 - Projectiles, Meteors, and Maps

Due. February 7, 2020

---

### Meteors

---

The resources that will be collected in the game are meteors. They should appear in the sky and land on the ground. Animate them using black or dark coloured cubes in the world array. They should have coloured cubes that look like fire trails following them as they drop to the ground. The fire trails should disappear once they land on the ground.

The meteors should move diagonally while they drop from the sky. Once they contact the ground or any occupied cube in the world array they should stop descending. Meteors should not land on clouds. They should be treated like any other object in the world array once they have reached the ground.

The meteors should drop randomly in the world. They should not repeatedly fall in the same location.

Since the meteors will drop diagonally they should move in both the x and z direction while falling. This means they may need to start in a location outside the maximum world dimensions (100x50x100). While they are falling you should store their location in a data structure. This will allow you to position them outside the world array. Once they stop falling you can clear the data structure to store their location while falling.

Use the timing schedular you developed in assignment 1 to control the speed of the meteors as they drop to the ground. Make them drop in a reasonable speed so the player can see them fall.

Initially there should be 30 meteors that fall at the start of the game. Every 30 seconds another 10 meteors should fall.

---

### Launching a Projectile

---

Launch a projectile from the viewpoint. It should travel in the direction which the viewpoint was facing when it is launched. The player should be able to control the angle the projectile when it is fired. After that it should move in a straight line. When the projectile strikes a cube in the world array both the projectile and the cube should be removed from the game.

The projectile should travel in a straight line from the viewpoint. You will likely want to use the getViewPosition() and getViewOrientation() functions to find the starting location of the viewpoint and the angle that the viewpoint is facing. It is a good idea to examine the values these functions return, particularly the orientation, to understand the values they return.

The mouse() function allows you to respond to button press and release events on the mouse. Remove the existing printf's from the mouse() function in your final submission. They are there to help understand the function and are not meant to be part of the final system. Launch the projectile when the left mouse button is pressed.

If a projectile impacts the side of the world space then it should be removed (when 0>x>99 or 0>z>99 or y>49).

Use the mob functions to create and control the projectile. There are examples of these functions in a1.c. Opponents will be added in later assignments which can collide with the projectiles and be removed from the game. For now all the projectile can do is remove cubes from the world array.

---

### Displaying a Two Dimensional World Map

---

Use the `draw2D()` function draw two dimensional maps on the screen. The map should show the boundary of the world, the player's current location, the landed meteor locations, and the location of the bases, The maps should display the x and z coordinates of the world. They do not need to show elevation in the y axis.

The int displayMap variable will be used to indicate what type of map will be displayed. When:

    displayMap == 0, no map is displayed
    displayMap == 1, a small world map in the upper right corner is drawn
    displayMap == 2, a large world map is displayed in the middle of the screen is drawn

The value of displayMap is cycled through using the m key.

You can use the `draw2D\*()` functions to drawn lines, boxes, and triangles. The `set2Dcolour()` function lets you set the colour of the shapes. These are described in the readme.txt file.

Draw lines to indicate the boundary of the map and draw a square to indicate the players location on the map.

You should use the screenWidth and screenHeight variables to scale the size of the maps when the window size is changed.

## Assignment 3 - Enemy AI and Animation

Due. March 6, 2020

---

### AI Vehicles and Animation

---

Create vehicles and animate them in the game. Draw them by placing values in the world array. You can animate their motion and make them move by updating the values in the world array.

The vehicles will search the world for fallen meteors, pick them up, and bring them back to the base. The vehicle should follow a randomly created path until it comes within ten spaces of a meteor on the ground. Once it is near a meteor the vehicle should drive in a straight line towards it.
When the vehicle is near the meteor it should stop and the meteor should be removed from the ground and placed on top of the vehicle.

Once a meteor has been loaded onto the vehicle it should be removed from the game world. You can animate the meteor moving onto the vehicle if you wish.

The vehicle will need to be drawn with multiple blocks simultaneously. It should not appear as a single cube and it should occupy several squares at one time. The vehicle is in essence a truck that will go and pick up a meteor so make the vehicle appear truck-like. It would be difficult to make a convincing vehicle in a 2x2x2 or less space.

---

### AI Agents - Searching and Picking up Meteors

---

The vehicles will follow a random path while searching for meteors. Pick a random destination that the vehicle will move towards. As it moves towards this destination it should check if it is within ten units of a fallen meteor. When the vehicle is within 10 units to the meteor it should change its destination to be the meteor's location.

If a vehicle picks up a meteor which other vehicles are moving towards then the other vehicles should pick a new random destination and
start searching for another meteor.

The vehicles will only move towards meteors that are on the ground.
Those that are still in the sky can be ignored.

The vehicles all start near their base. Each base should have five vehicles
that start searching for meteors when the game starts. All vehicles are
independent of each other and should search and retrieve meteors
without interacting with each other.

The starting state for each vehicle is to pick a random destination
and to start moving towards that location in the world. The initial
state is searching.

Have the agents move at a reasonable speed. Pick a speed that makes
the game playable.

Write the AI using a state machine where the agent is either searching
for meteors, moving to pick to pick up a meteor, loading a meteor, or
returning to the base.

The state machine for this AI is:

| Current State  | detect meteor  | don't' detect meteor |    have meteor | close to meteor |
| -------------- | :------------: | -------------------: | -------------: | --------------: |
| searching      |  move towards  |            searching | return to base |         loading |
| moving towards |  move towards  |            searching | return to base |         loading |
| loading meteor |    loading     |              loading | return to base |         loading |
| return to base | return to base |       return to base | return to base |  return to base |

The inputs to the state machine are:

- detect meteor
  - the vehicle is within ten spaces of the meteor
- don't detect meteor
  - there is no meteor within ten spaces of the vehicle
- have meteor
  - the vehicle has loaded a meteor which can be returned to the base
- close to meteor
  - the vehicle is near enough to load the meteor

The states in the state machine are:

- searching
  - following a random path until a meteor is found
- moving towards a meteor
  - once a meteor is found (within 10 units from the vehicle, change destination to the meteor
- loading meteor
  - once the vehicle is near to the meteor it should load the meteor onto the vehicle
- return to base
  - once the vehicle has a meteor loaded it should follow a straight line back to its base

The vehicles should be a colour similar to that of their base.

Pick a reasonable time for the vehicle to load the meteor. Once a vehicle has started loading a meteor then it will finish loading and return to the base without being interrupted.

Allow the vehicles to climb walls of more than one cube in height.

---

### Shooting the Vehicles

---

Place five towers randomly around the world space for each base. The towers should have a similar colour to the base and the vehicles. If a vehicle from the other base comes too close to a tower then the tower should shoot a ball at the vehicle. Use the same method of shooting you used for the player to shoot in assignment 2 but with the ball starting at the tower.

If the vehicle is shot by a tower then it should return to the base, lose a meteor if it is carrying one, and begin searching again. The tower should have to hit the vehicle at least twice for the vehicle to be sent back to the base.

When the vehicle is destroyed and sent back to the base, make a crater in the ground from the last location of the vehicle.

---

### Counting Meteors

When a vehicle brings a meteor back the its base, remove the meteor from the vehicle and place it beside the base. The goal is to create a 3x3 cube of meteors. Once the vehicle has dropped off the meteor it should begin searching for another meteor to retrieve.

---

## Details

---

### Choosing Parameters

It is important to pick values for parameters such as colours, speed of objects, the effect of gravity so they are easy for the marker to see. If the effect of a parameter it isn't obvious or is difficult to see then it will be marked as missing or incomplete.

Make sure colours are bright and distinct. Choose velocities that are fast enough to be seen.

### Coding Practices

Write the code using standard stylistic practices. Use functions, reasonable variable names, and consistent indentation. If the code is difficult for the TA to understand then you will lose marks.

As usual, keep backups of your work using source control software.

### Starting Code

The starting code is available on the Courselink site.
You can untar the file using tar xvf filename.
All of the changes to the code should be made in the a1.c file.

Note that the graphics code may be modified for later assignment. If you make changes to the graphics code (in graphics.c or visible.c) then you may have to recode the changes in later assignments.

### Submitting the Assignment

Put all of the files in a directory named 4820 so they unpack into this directory.

Submit the assignment using Courselink. Submit only the source code and the makefile. Bundle the code in a tar file.

The assignments will be marked on the Macs in Thorn 2420.
If you develop your code on a different platform then it is a good idea to put the include files in an #ifdef for that system
so they will still compile on the Macs. Test your program on the
Macs before you submit it.

Include the graphics code with your submission. Include a makefile that will compile the executable. Name the executable a1.

The TA will unpack your code and type "make". They will then try to run an executable named "./a1". If the make command or executing a1 does not work then you will lose a substantial number of marks.

Don't name your program with a .exe extension. If the assignment
says name the executable a1 then don't change the name to a1.exe.

It is always a good idea to unpack and test the file you are submitting to be sure that what you submit actually compiles.

Include a readme.txt with your name, student number, and a description of anything that does not work correctly in your assignment.
