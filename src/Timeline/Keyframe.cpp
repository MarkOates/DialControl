

#include <Timeline/Keyframe.hpp>




namespace Timeline
{


Keyframe::Keyframe(std::function<float(float)> interpolator_func, float value, double time, bool focused)
   : interpolator_func(interpolator_func)
   , value(value)
   , time(time)
   , focused(focused)
{
}


Keyframe::~Keyframe()
{
}


void Keyframe::set_focused(bool focused)
{
   this->focused = focused;
   return;
}

void Keyframe::set_as_focused()
{
   focused = true;
   return;
}

void Keyframe::set_as_unfocused()
{
   focused = false;
   return;
}

Timeline::Keyframe Keyframe::construct(double time, float value, std::function<float(float)> interpolator_func)
{
   Timeline::Keyframe result;
   result.time = time;
   result.value = value;
   result.interpolator_func = interpolator_func;
   return result;
}


} // namespace Timeline


