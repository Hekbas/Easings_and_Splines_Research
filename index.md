
This project is a collection of C++ functions for creating and manipulating easings and splines. It includes 30 easing functions that can be used to animate user interfaces or create smooth animations.
It also includes examples in different scenes for testing.

## About Easings

The concept of easing was first introduced in the 1930s by Disney animators, who were looking for ways to make their animated characters move more fluidly. However, it wasn't until the rise of computer graphics in the 1980s that easings became a common technique in animation software.

Easing techniques are used in a wide variety of applications, and have a significant impact on the gameplay experience in video games, especially in games that require precision control and quick reflexes. One of the most common applications of easing in video games is to create smooth movement animations for characters and objects.

For example, when a character jumps, easing can be used to make the jump animation appear more natural by gradually accelerating the character's movement upward and then gradually slowing down their descent. It can also be used to create more responsive controls and to smooth camera transitions between different game areas or angles.

## Clasification

Easing functions can be classified into several categories based on their behavior and the way they interpolate values over time. I have classified the ones used in this project into the following:

- **Sine:** Curved path, similar to the shape of a sine wave, gradual acceleration and deceleration.
They are often used for animations that require a fluid and organic movement, such as the movement of waves or the motion of a pendulum.

- **Quadratic:** Accelerate or decelerate the motion at a constant rate.
They can be used to create a sense of momentum or inertia in an animation.

- **Cubic:** Accelerate or decelerate the motion more aggressively than quadratic easing functions.
They can be used to create a more pronounced sense of momentum or to simulate natural movements like bouncing.

- **Quartic:** More aggressive than Cubic.

- **Quintic:** More aggressive than Quartic.

- **Exponential:** Accelerate or decelerate the motion exponentially.
They can be used to create an exaggerated sense of momentum or to simulate movements like a rocket taking off.

- **Circular:** Create a motion that follows a circular path, gradual acceleration and deceleration.
Circular easing functions are often used for animations that involve rotation or circular movement.

- **Back:** Create a motion that overshoots its target and then returns to it.

- **Elastic:** Simulate a spring-like motion where the animation overshoots its target and then bounces back.
They can be used to create a playful or whimsical effect in animations.

- **Bounce:** Simulate a bouncing ball by adding a series of small, quick bounces.

Each category includes three types of functions:

- **Ease In:** Starts the animation slowly and gradually accelerates towards the end.
- **Ease Out:** Starts the animation at full speed and gradually slows down towards the end.
- **Ease InOut:** Starts the animation slowly, accelerates towards the middle, and then gradually slows down towards the end.

## The Easing Class

For this project I've included 30 easing functions for you to mess around with. All of them accept __'t'__ as a parameter and returns a double value.
The class also includes 'EasingAnimation(int start, int end, double time, EasingType easingType)'
- **start:** initial position of the object.
- **end:** final position.
- **time:** value 0 - 1.
- **easingType:** the type of easing to use.

__'EasingAnimation()'__ uses the function specified by __'easingType'__ to calculate the interpolated position at the time given by __'t'__.

```c++
double Easing::EasingAnimation(int start, int end, double time, EasingType easingType)
{
    // Lambda function:
    // [capture list](parameters) -> return type {function body}
    // Captures current object and easingType by value,
    // making them accessible within the function's scope.
    auto easing = [this, easingType](double t) -> double
    {
        switch (easingType)
        {
        case EasingType::EASE_IN_SIN:           return EaseInSin(t);
        case EasingType::EASE_OUT_SIN:          return EaseOutSin(t);    
        case EasingType::EASE_INOUT_SIN:        return EaseInOutSin(t);
        // All other Easing Types...
        }
    };

    double t = easing(time);
    return start + (end - start) * t;
}
```

All the parameters requiered by the function seem pretty straightforward asides from __'t'__. How do we know what value we need to pass to the function?

We'll need to keep track of the following:
- Time passed since the start of the animation.
- Total duration of the animation.
- Status of the animation (has it finished?).

And for this purpose, I've added this variables into the Easings Class:

```c++
double elapsedTime = 0;
double totalTime = 0;
bool bFinished = true;
```

Next, __'TrackTime(double dt)'__ will be used to calculate the time passed since the beginning of the animation and returning a value from 0-1, it does so by adding __'dt'__ to __'elapsedTime'__ and dividing by __'totalTime'__. It also checks if the animation has finished.

```c++
double Easing::TrackTime(double dt)
{
    if (elapsedTime < totalTime)
    {
        elapsedTime += (dt / 1000);
        return elapsedTime / totalTime;
    }
    else
    {
        bFinished = true;
        elapsedTime = 0;
        return 1;
    }
}
```
> Note that __'dt'__ needs to be divided by 1000 since totalTime is expressed in seconds.

#### Example

The code below ilustrates how to implement an animation into a rectangle.
```c++
double t = easingPause->TrackTime(dt);
double easedY = easing->EasingAnimation(a, b, t, easing);
SDL_Rect rectangle = { x, easedY, w, h };
app->render->DrawRectangle(rectangle, r, g, b, a, false);
```



## Improvements
Implement saving spline points in .xml for quickly saving points after editing the spline. 

## Bibliography
[The Continuity of Splines](https://www.youtube.com/watch?v=jvPPXbo87ds)

[An In-Depth look at Lerp, Smoothstep, and Shaping Functions](https://www.youtube.com/watch?v=YJB1QnEmlTs)

[javidx9](https://www.youtube.com/@javidx9)

[Easing functions](https://github.com/nicolausYes/easing-functions)