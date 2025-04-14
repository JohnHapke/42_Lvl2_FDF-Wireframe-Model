# FDF - Wireframe Model

## Purpose

> The purpose of the FDF project is to create a C program that renders a 3D wireframe model of a landscape from a `.fdf` file. It transforms 2D coordinates with altitude data into a 3D isometric projection, connecting points with line segments to visualize terrain.

## Explanation of Behavior

FDF mimics a basic 3D graphics renderer. It takes a `.fdf` file as input, where numbers represent points in space (x, y, z), and displays them as a wireframe in a window using the MiniLibX library. The program:

- Parses the `.fdf` file to extract coordinates and altitudes.
- Projects the points isometrically in 3D space.
- Draws lines between adjacent points to form the wireframe.
- Handles window events like closing via ESC or the window’s cross.

If the input file is malformed or an error occurs, the program exits cleanly with an error message.

## How It Works

**Initialization:** Receives a `.fdf` file as an argument (e.g., `./fdf 42.fdf`).<br>
**File Parsing:** Reads the file line by line (using `get_next_line()` and `ft_split()` from libft) to build a 2D array of points with x, y positions and z altitudes.<br>
**Projection:** Converts coordinates into an isometric view using mathematical transformations (via the `-lm` math library).<br>
**Rendering:**
- Opens a window with MiniLibX.
- Plots points and connects them with lines to form the wireframe.
- Displays the image in the window.

**Event Handling:** Listens for ESC key or window close events to exit gracefully.<br>
**Cleanup:** Frees all allocated memory and closes the window.

## Allowed Functions

- `open`, `close`, `read`, `write`
- `malloc`, `free`
- `perror`, `strerror`, `exit`
- Math library functions (`-lm`)
- MiniLibX functions (e.g., `mlx_init` , `mlx_new_window`, `mlx_pixel_put`)
- Libft functions (e.g., `ft_printf`, `get_next_line`, `ft_split`)

## Compilation and Usage

**Compile:** Run make to build the program.<br>
**Execution:** `./fdf <filename>.fdf`<br>
**Example:** `./fdf 42.fdf` renders the sample landscape.<br>
**Requirements:** A valid `.fdf` file with space-separated integers (e.g., 0 1 2 for altitudes).<br>

## Memory Leaks Test

To check for memory leaks, run:

`valgrind --leak-check=full ./fdf 42.fdf`

This ensures all heap memory is freed properly.

## Bonus Features

The bonus part extends the mandatory functionality with optional enhancements:

**Extra Projection:** Adds a parallel or conic projection alongside isometric.<br>
**Zoom:** Allows zooming in and out of the model.<br>
**Translation:** Moves the wireframe across the window.<br>
**Rotation:** Rotates the model for different viewpoints.<br>
**Custom Bonus:** Implements an additional feature of your choice (e.g., color gradients based on altitude).<br>
**Compile Bonus:** Use `make bonus` to include these features.<br>
**Usage:** Same as the mandatory part, with controls (e.g., keys or mouse) for bonus interactions.<br>

Note: Bonuses are only evaluated if the mandatory part is fully functional and error-free.

## Key Concepts

**File Parsing:** Efficiently reads and processes structured data from a .fdf file (mandatory).<br>
**Graphics Basics:** Uses MiniLibX to manage windows and draw pixels (mandatory).<br>
**3D Projection:** Applies isometric math to simulate depth (mandatory), with optional parallel/conic projections (bonus).<br>
**Memory Management:** Handles dynamic allocation without leaks (mandatory).<br>
**Event Handling:** Manages keyboard (ESC) and window close events for clean exits (mandatory), extended with zoom/rotation controls (bonus).<br>
**Coordinate Transformation:** Converts 2D points to 3D space with altitude (mandatory), enhanced by translation and rotation (bonus).<br>
**Line Drawing:** Connects points with segments to form the wireframe (mandatory).<br>
**User Interaction:** Enables dynamic model manipulation like zooming and rotating (bonus).<br>
**Customization:** Adds optional features like color gradients for visual enhancement (bonus).<br>

## Grade

115 / 100
