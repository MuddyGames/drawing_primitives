# Practical 05: Drawing Primitives and Sprites

Welcome! In this practical you'll draw shapes, load a sprite, move it around with the keyboard and tidy up after yourself.

By the end you'll understand how a raylib game is put together: **initialise -> game loop -> clean up**.

> Project was generated with [raylib project creator](https://raysan5.itch.io/raylib-project-creator) by raysan5. You can use this tool to start your own raylib projects.

---

## Short version

If you just want to get going, this is the whole thing in a few lines:

**1. Clone**

```bash
mkdir -p ~/Projects
cd ~/Projects
git clone https://github.com/MuddyGames/drawing_primitives
```

**2. Set up raylib**

*Linux:*

```bash
cd ~/Projects/drawing_primitives/setup
bash setup_linux.sh
```

or make the script executable and run it directly:

```bash
cd ~/Projects/drawing_primitives/setup
chmod +x setup_linux.sh
./setup_linux.sh
```

*Windows* (install [raylib](https://raysan5.itch.io/raylib) first, and then use w64devkit terminal):

```bash
cd ~/Projects/drawing_primitives/setup
sh setup_windows.sh
```

**3. Build and run**

```bash
cd ~/Projects/drawing_primitives
make run                            # desktop
```

Rest of this page explains each step, and what to do when the computer says no.

---

## Step 1: Get the project

Keep all your work in a `Projects` folder in your home directory (C: drive or $HOME).

- **Linux:** open a terminal.
- **Windows:** open the **w64devkit** terminal (`C:\raylib\w64devkit\w64devkit.exe`).

Then type the same commands on both:

```bash
mkdir -p ~/Projects
cd ~/Projects
git clone https://github.com/MuddyGames/drawing_primitives
```

Your project now lives in `~/Projects/drawing_primitives`.

---

## Step 2: Install raylib and Emscripten

### Linux (Debian, Ubuntu, Pop!_OS or Arch)

```bash
cd ~/Projects/drawing_primitives/setup
bash setup_linux.sh
```

It will ask for your password to install packages. It takes a few minutes, especially on Lab machines.

### Windows

Install **[raylib installer](https://raysan5.itch.io/raylib):** keep the default location, `C:\raylib`.

Then in the **w64devkit** terminal:

```bash
cd ~/Projects/drawing_primitives/setup
sh setup_windows.sh
```

### When it finishes

**Close the terminal and open a new one.**.

### Manual setup (only if the script didn't work for you)

Prefer doing it by hand, or did the script throw a wobbly? Here's what it does, step by step.

#### Linux: raylib

Install the build tools.

Debian/Ubuntu/Pop!_OS:

```bash
sudo apt install build-essential git python3 libasound2-dev libx11-dev libxrandr-dev \
     libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev \
     libwayland-dev libxkbcommon-dev
```

Arch:

```bash
sudo pacman -S --needed base-devel git python alsa-lib mesa glu libx11 libxrandr \
     libxi libxcursor libxinerama wayland libxkbcommon
```

> Arch has its own `raylib` and `emscripten` packages, but don't use them. The Makefile looks in `~/raylib` and `~/emsdk`.

Build raylib:

```bash
git clone --depth 1 https://github.com/raysan5/raylib.git ~/raylib
cd ~/raylib/src
make PLATFORM=PLATFORM_DESKTOP
```

#### Linux: Emscripten (for web builds)

```bash
git clone https://github.com/emscripten-core/emsdk.git ~/emsdk
cd ~/emsdk
./emsdk install latest
./emsdk activate latest
echo 'source "$HOME/emsdk/emsdk_env.sh" > /dev/null 2>&1' >> ~/.bashrc
source ~/.bashrc
cd ~/raylib/src
make PLATFORM=PLATFORM_WEB -B
```

#### Windows: raylib

The raylib installer has done it all for you. Nothing to do here.

#### Windows: Emscripten (for web builds)

The raylib installer may already include it. Check in w64devkit:

```bash
ls C:/raylib/emsdk/upstream/emscripten/emcc.bat
```

If that file isn't there, install emsdk from a **Command Prompt** (`cmd`). This is the only step that needs it, because the installer is a `.bat` file:

```bat
git clone https://github.com/emscripten-core/emsdk.git C:\raylib\emsdk
cd C:\raylib\emsdk
emsdk install latest
emsdk activate latest
```

Then build raylib for web, back in w64devkit:

```bash
EMSDK=C:/raylib/emsdk
PY=$(ls -d $EMSDK/python/*_64bit)
NODE=$(ls -d $EMSDK/node/*_64bit)/bin
cd C:/raylib/raylib/src
make PLATFORM=PLATFORM_WEB -B EMSDK_PATH=$EMSDK PYTHON_PATH=$PY NODE_PATH=$NODE
```


---

## Step 3: Build and run

Every build command runs from the `./` root folder:

```bash
cd ~/Projects/drawing_primitives/
```

### On your desktop

| | Linux | Windows (w64devkit) |
|---|---|---|
| Build | `make` | `make` |
| Run | `./drawing_primitives` | `./drawing_primitives.exe` |
| Tidy up | `make clean` | `make clean` |

A window should pop up. If it does, take a moment. You've earned it.

### In your browser

```bash
make run_web
```

This builds the web version, starts a small local web server and opens
**<http://127.0.0.1:8000/drawing_primitives.html>** in your browser.

Press **Ctrl+C** in the terminal to stop the server. It won't take offence.

| Command | What it does |
|---|---|
| `make web` | Builds the web version only |
| `make run_web` | Builds it and opens it in your browser |
| `make clean PLATFORM=PLATFORM_WEB` | Removes the web build files |

> **Why the server?** Browsers won't run a game straight from a file on your disk, for security reasons. The little server keeps them happy.

---

## How the project is laid out

```
drawing_primitives/
├── Makefile            build instructions
├── src/
│   ├── main.c          opens the window, runs the game loop
│   └── game.c          YOUR code goes here
├── include/
│   └── game.h          function declarations
├── resources/          your sprites and images
├── build/              everything make creates
├── platform/           icons and web page template; leave these alone
└── setup/              setup scripts (run once)
```

`main.c` runs the show. Your code goes into four functions in `game.c`:

| Function | When it runs | Put this in it |
|---|---|---|
| `InitGame()` | Once, at the start | Load textures, set starting positions |
| `UpdateGame()` | Every frame | Read input, move things |
| `DrawGame()` | Every frame | Draw everything |
| `CloseGame()` | Once, at the end | Unload textures |

---

## Tasks

### Task 1: Explore the template

Find where drawing happens. Notice that every drawing call sits between `BeginDrawing()` and `EndDrawing()`. Drawing outside them is like talking at the back of a lecture: nobody sees it.

### Task 2: Drawing primitives

Draw at least a **circle**, a **rectangle**, a **line** and a **triangle**. Use raylib's built-in colours and **at least one custom RGBA colour** of your own. Forty shades of green, if you like.

### Task 3: Add a sprite

1. Create a `resources` folder inside `./` **project root folder**.
2. Put an image in it, e.g. `player.png`.
3. Load it in `InitGame()` and draw it in `DrawGame()`.
4. Move it with the **arrow keys** in `UpdateGame()`.

### Task 4: An interactive scene

Combine your shapes and sprite into a little scene. Some ideas:

- A rectangle for the ground, with your sprite standing on it.
- Pressing **SPACE** changes a shape's colour.
- Clicking the **mouse** draws a circle at the cursor.

Surprise us. Bonus marks for imagination, not for the number of exclamation marks in your comments.

### Task 5: Clean up after yourself

- Call `UnloadTexture()` for every texture you loaded.
- Make sure `CloseWindow()` is the last thing that runs.

Leave the place as you found it. Your mother would be proud.

---

## Cheat sheet

```c
// Shapes
DrawCircle(200, 200, 50, RED);
DrawRectangle(100, 100, 80, 40, BLUE);
DrawLine(0, 0, 400, 300, GREEN);
DrawTriangle((Vector2){300, 200}, (Vector2){250, 250}, (Vector2){350, 250}, PURPLE);

// Your own colour: red, green, blue, alpha (0–255)
Color myColor = (Color){ 150, 200, 100, 255 };

// Sprites
Texture2D sprite = LoadTexture("resources/player.png");  // after InitWindow()
DrawTexture(sprite, x, y, WHITE);
UnloadTexture(sprite);                                   // before CloseWindow()

// Input
IsKeyDown(KEY_RIGHT);     // true the whole time the key is held
IsKeyPressed(KEY_SPACE);  // true once, the moment it's pressed
GetMousePosition();       // where the mouse is (a Vector2)
```

> **Triangle not showing?** List the three points **anti-clockwise**, or raylib won't draw it.

---

## When things go wrong

Don't panic. Nine times out of ten it's one of these:

| You see… | What's going on | Fix |
|---|---|---|
| `raylib.h: No such file or directory` | make can't find raylib | Run the setup script again (Step 2) |
| `emcc: No such file or directory` or `emcc not found` | Emscripten isn't loaded in this terminal | Close the terminal and open a new one. On Linux you can also run `source ~/emsdk/emsdk_env.sh` |
| `mingw32-make: not found` (Windows) | Your w64devkit isn't the raylib one | Use `make MAKE=make` |
| Sprite is missing; it's just not there | The game can't find the image | Run the game from `./`, and check the file really is in `./resources/` |
| Sprite missing in the browser only | `resources/` is empty or doesn't exist | Put at least one file in `./resources/` and run `make run_web` again |
| `Address already in use` | Something is already using port 8000 | Use `make run_web WEB_PORT=8080` |
| Browser says it can't connect | The page opened before the server was ready | Refresh the page |
| The program still won't build | Old leftover files | `make clean`, then `make` again |

Still stuck? Read the **first** error message, not the last. The first one is usually the real problem; the rest are just complaining about it.

---

## Before you submit

- [ ] It compiles and runs with no errors or warnings
- [ ] Shapes appear in the right places and colours
- [ ] Your sprite appears and moves with the arrow keys
- [ ] Textures are unloaded and the window closes cleanly
- [ ] `./resources/` with at least one sprite is committed
- [ ] Your code is commented and tidy

Commit early and commit often. Deadlines are like buses in Carlow: you'll see one coming, but it won't wait for you.

Best of luck. Now go draw something brilliant.