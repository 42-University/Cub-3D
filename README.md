*This project was created as part of the 42 curriculum by tkenji-u and liferrei.*

# cub3D

## Description
The **cub3D** project is a 3D graphical adventure inspired by the world-famous Wolfenstein 3D, often cited as the first FPS (First-Person Shooter) ever created. The goal of this project is to explore the "ray-casting" technique to create a dynamic first-person view inside a maze. Using the **miniLibX** library, the program parses a map file and renders a "realistic" 3D representation of the environment, where the user can navigate in real-time.

## Instructions

### Compilation
The project must be compiled using the provided Makefile. It includes the mandatory rules: `all`, `clean`, `fclean`, `re`, and `bonus`.

```bash
make
```

### Execution
The program takes a scene description file with the `.cub` extension as its only argument.

```bash
./cub3D maps/map.cub
```

### Controls
* **W, A, S, D**: Move the point of view through the maze.
* **Left/Right Arrows**: Rotate the camera view.
* **ESC**: Close the window and exit the program cleanly.
* **Red [X]**: Close the window and exit the program cleanly.

## Resources

### References
* **Lodev's Raycasting Tutorial**: A fundamental guide for the DDA (Digital Differential Analyzer) algorithm used in ray-casting.
* **miniLibX Documentation**: Essential for window management, pixel manipulation, and event handling.
* **Wolfenstein 3D (1992)**: Reference for the original game design and mechanics.

### AI Usage
In accordance with the 42 curriculum guidelines, Artificial Intelligence (AI) was used as a pedagogical tool during this project:
* **Parsing Logic**: AI assisted in designing a robust map parser, specifically for handling edge cases in the `.cub` file format and validating the maze boundaries.
* **Error Handling**: Used to refine the "Error\n" messages and ensure the program exits cleanly without memory leaks.
* **Code Review**: AI was used to explain complex ray-casting mathematical formulas and to simulate peer-review scenarios to identify potential logical gaps before the final evaluation.
All AI-generated suggestions were thoroughly reviewed, tested, and understood before being integrated into the project.