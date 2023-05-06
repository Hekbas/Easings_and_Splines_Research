---
layout: default
title: The Easing Class
nav_order: 4
---

# The Easing Class

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
{: .note }
> __'dt'__ needs to be divided by 1000 since totalTime is expressed in seconds.

#### Example

The code below ilustrates how to implement an animation into a rectangle.
```c++
double t = easingPause->TrackTime(dt);
double easedY = easing->EasingAnimation(a, b, t, easing);
SDL_Rect rectangle = { x, easedY, w, h };
app->render->DrawRectangle(rectangle, r, g, b, a, false);
```
