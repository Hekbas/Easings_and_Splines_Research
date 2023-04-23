
This project is a collection of C++ functions for creating and manipulating easings and splines. It includes 30 easing functions that can be used to animate user interfaces or create smooth animations.
It also includes examples in different scenes for testing.

## Easings

The concept of easing was first introduced in the 1930s by Disney animators, who were looking for ways to make their animated characters move more fluidly. However, it wasn't until the rise of computer graphics in the 1980s that easings became a common technique in animation software.

Easing techniques are used in a wide variety of applications, and have a significant impact on the gameplay experience in video games, especially in games that require precision control and quick reflexes. One of the most common applications of easing in video games is to create smooth movement animations for characters and objects.

For example, when a character jumps, easing can be used to make the jump animation appear more natural by gradually accelerating the character's movement upward and then gradually slowing down their descent. It can also be used to create more responsive controls and to smooth camera transitions between different game areas or angles.

Easing functions can be classified into several categories based on their behavior and the way they interpolate values over time. I have classified the ones used in this project into the following:

**Sine**
Curved path, similar to the shape of a sine wave, gradual acceleration and deceleration.
**Quadratic**
Accelerate or decelerate the motion at a constant rate.
**Cubic**
Accelerate or decelerate the motion more aggressively than quadratic easing functions.
**Quartic**
More aggressive than Cubic.
**Quintic**
More aggressive than Quartic.
**Exponential**
Accelerate or decelerate the motion exponentially.
**Circular**
Create a motion that follows a circular path, gradual acceleration and deceleration.
**Back**
Create a motion that overshoots its target and then returns to it.
**Elastic**
Simulate a spring-like motion where the animation overshoots its target and then bounces back.
**Bounce**
Simulate a bouncing ball by adding a series of small, quick bounces.

Each category includes three functions:

- Ease In: Starts the animation slowly and gradually accelerates towards the end.
- Ease Out: Starts the animation at full speed and gradually slows down towards the end.
- Ease InOut: Starts the animation slowly, accelerates towards the middle, and then gradually slows down towards the end.

 Each of the 30 functions can be called directly or by using EasingAnimation and passing the appropriate EasingType.

## Controls

- Camera Movement (W, A, S, D)
- Limit FPS (F10)

## Contributing
Contributions to the project are welcome! If you find a bug or have an idea for a new feature, please open an issue or submit a pull request.

## License
The project is licensed under the MIT License.
