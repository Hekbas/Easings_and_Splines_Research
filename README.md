# Easings and Splines

This project is a collection of C++ functions for creating and manipulating easings and splines. It includes 30 easing functions that can be used to animate user interfaces or create smooth animations.
It also includes examples in different scenes for testing.

You can find the research and documentation for this project on my [webpage](https://hekbas.github.io/Easings_and_Splines_Research).  
View the ppt used in the presentation [here](https://docs.google.com/presentation/d/1q1coJHP-QpBSi6BN0cDEZzHbJv7HHC9ORueyxNqs3_o/edit?usp=sharing).

## Installation

The necessary files can be downloaded directly from the GitHub repository or in the Releases section.

## Documentation

Each of the 30 functions included in the library can be classified into several categories based on their behavior and the way they interpolate values over time:

- Sine: Curved path, similar to the shape of a sine wave, gradual acceleration and deceleration.
- Quadratic: Accelerate or decelerate the motion at a constant rate.
- Cubic: Accelerate or decelerate the motion more aggressively than quadratic easing functions.
- Quartic: More aggressive than Cubic.
- Quintic: More aggressive than Quartic.
- Exponential: Accelerate or decelerate the motion exponentially.
- Circular: Create a motion that follows a circular path, gradual acceleration and deceleration.
- Back: Create a motion that overshoots its target and then returns to it.
- Elastic: Simulate a spring-like motion where the animation overshoots its target and then bounces back.
- Bounce: Simulate a bouncing ball by adding a series of small, quick bounces.

Each category includes three functions:

- Ease In: Starts the animation slowly and gradually accelerates towards the end.
- Ease Out: Starts the animation at full speed and gradually slows down towards the end.
- Ease InOut: Starts the animation slowly, accelerates towards the middle, and then gradually slows down towards the end.

 Each of the 30 functions can be called directly or by using EasingAnimation and passing the appropriate EasingType.

## Controls
- Change Between Scenes (1, 2, 3)
- Start Pause MEnu Animation (P)
- Switch Selected Spline Point (Q, E)
- Move Selected Spline Point (W, A, S, D)
- Start Camera Movement on Spline (C)
- Limit FPS (F10)

## Contributing
Contributions to the project are welcome! If you find a bug or have an idea for a new feature, please open an issue or submit a pull request.

## License
The project is licensed under the MIT License.
