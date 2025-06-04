

#include <Timeline/Parameter.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Timeline
{


Parameter::Parameter()
   : name("[unset-name]")
   , initial_value(0.0f)
   , parameter(nullptr)
   , keyframes({})
   , has_min_value(true)
   , has_max_value(true)
   , min_value(0.0f)
   , max_value(1.0f)
{
}


Parameter::~Parameter()
{
}


Timeline::Parameter Parameter::build(std::string name, float* parameter, std::vector<Timeline::Keyframe> keyframes, float initial_value)
{
   Timeline::Parameter result;
   result.name = name;
   result.parameter = parameter;
   result.keyframes = keyframes;
   result.initial_value = initial_value;
   return result;
}

void Parameter::add_keyframe(float time, float value, std::function<float(float)> interpolator_func)
{
   Timeline::Keyframe keyframe = Timeline::Keyframe::construct(time, value, interpolator_func);
   keyframes.push_back(keyframe);

   // Keep keyframes sorted by time
   std::sort(keyframes.begin(), keyframes.end(), [](const Timeline::Keyframe &a, const Timeline::Keyframe &b)
   {
      return a.time < b.time;
   });

   return;
}

float Parameter::value_at(double position)
{
   if (!(parameter))
   {
      std::stringstream error_message;
      error_message << "[Timeline::Parameter::value_at]: error: guard \"parameter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::Parameter::value_at]: error: guard \"parameter\" not met");
   }
   return 0.0f;
}


} // namespace Timeline


