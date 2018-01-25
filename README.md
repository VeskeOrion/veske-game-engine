# veske-game-engine

Hooray! As of 2017 Jan 15, it works! Entities can be added and will be rendered on the screen, and their logic will be updated according to their current state.

---

A work-in-progress game engine I am hoping to build from the ground up. It's currently growing to fast for all my commits to be self-explanatory.

This game engine is a personal goal/study of mine and I hope to build a fully functional game out of it some day, something 2-dimensional and desktop based, pixel art in style. I am more intersted in the work behind programming game objects to move and interact with each other in the game world than I am with directly programming the operating system, so instead of writing with solely the Windows API, I am using a fantastic library called [Simple DirectMedia Layer](https://www.libsdl.org/).

While I doubt anyone will ever see this page, if you do happen accross my code, internet wanderer, feel free to use it in any way you wish.

---

Things to do (not in order):

1. Create the 'Level' class, which will contain tons of information about world objects (Entities) that exist within it. These could be player characters, NPCs, items on the floor, buildings, etc.

2. Create the 'UI' classes, which will help create a start menu instead of just jumping right into the game, and a way to manage settings and items (when they are introduced)

3. Create the level loading and storing procedure, which will read (binary or text) files that contain information about a level, and will place them into the world to be played in

4. Create the 'Audio' class, which will play audio files using SDL subroutines

5. In the future, once plain pixel art is displayed and animated on screen and manipulable via keyboard and mouse input, I hope to utilize more in depth graphical effects such as lighting.
