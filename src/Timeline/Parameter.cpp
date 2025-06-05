

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
   , interpolate_initial_value_to_1st_keyframe(false)
{
}


Parameter::~Parameter()
{
}


Timeline::Parameter Parameter::build(std::string name, float* parameter, std::vector<Timeline::Keyframe> keyframes, float initial_value, bool has_min_value, bool has_max_value, float min_value, float max_value)
{
   Timeline::Parameter result;
   result.name = name;
   result.parameter = parameter;
   result.keyframes = keyframes;
   result.initial_value = initial_value;
   result.has_min_value = has_min_value;
   result.has_max_value = has_max_value;
   result.min_value = min_value;
   result.max_value = max_value;
   return result;
}

void Parameter::add_keyframe(double time, float value, std::function<float(float)> interpolator_func)
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

bool Parameter::remove_keyframe_at_index(std::size_t index)
{
   if (index < keyframes.size()) {
       keyframes.erase(keyframes.begin() + index);
       return true;
   }
   return false;
}

void Parameter::assign_to_time(double position)
{
   if (!(parameter))
   {
      std::stringstream error_message;
      error_message << "[Timeline::Parameter::assign_to_time]: error: guard \"parameter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::Parameter::assign_to_time]: error: guard \"parameter\" not met");
   }
   *parameter = calculate_value_at(position);
   return;
}

float Parameter::calculate_value_at(double position)
{
   if (!(parameter))
   {
      std::stringstream error_message;
      error_message << "[Timeline::Parameter::calculate_value_at]: error: guard \"parameter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::Parameter::calculate_value_at]: error: guard \"parameter\" not met");
   }
   float result_value;

   if (keyframes.empty()) {
       result_value = initial_value;
   } else {
       // At least one keyframe exists
       const Timeline::Keyframe& kf0 = keyframes[0]; // The first keyframe

       if (position < kf0.time) {
           // Behavior when position is before the very first keyframe
           if (interpolate_initial_value_to_1st_keyframe) {
               // TRUE: initial_value acts like a keyframe at t=0, interpolate to kf0
               if (kf0.time <= 0.0) { // If kf0 is at or before t=0, it defines the value at t=0
                   result_value = kf0.value;
               } else {
                   // Interpolate from initial_value (at t=0.0) to kf0 (at kf0.time)
                   double t_norm_double = position / kf0.time; // position is < kf0.time, kf0.time > 0
                   t_norm_double = std::max(0.0, std::min(1.0, t_norm_double)); // Clamp to [0,1]

                   if (kf0.interpolator_func) {
                       float factor = kf0.interpolator_func(static_cast<float>(t_norm_double));
                       result_value = initial_value + factor * (kf0.value - initial_value);
                   } else { // Linear interpolation
                       result_value = initial_value + static_cast<float>(t_norm_double) * (kf0.value - initial_value);
                   }
               }
           } else {
               // FALSE: initial_value is discarded, use the value of the 1st keyframe
               result_value = kf0.value;
           }
       } else { // position >= kf0.time
           // Standard keyframe logic applies from kf0 onwards.
           // initial_value is not used in this path if keyframes exist.

           if (keyframes.size() == 1) {
               // Only one keyframe, and position is at or after it.
               result_value = kf0.value;
           } else {
               // Two or more keyframes, and position is at or after the first one.
               const Timeline::Keyframe& last_kf = keyframes.back();
               if (position >= last_kf.time) {
                   // Position is at or after the last keyframe.
                   result_value = last_kf.value;
               } else {
                   // Position is between two keyframes (or exactly on a keyframe other than the last one).
                   // kf0.time <= position < last_kf.time
                   
                   auto it_next = std::upper_bound(keyframes.begin(), keyframes.end(), position,
                       [](double pos_val, const Timeline::Keyframe& kf) {
                           return pos_val < kf.time; // kf.time is double
                       });

                   // it_next points to the keyframe after 'position'.
                   // (it_next - 1) points to the keyframe before or at 'position'.
                   // This is safe because:
                   //  - keyframes.size() >= 2
                   //  - position >= kf0.time (so it_next != keyframes.begin() unless kf0.time == kf1.time etc.)
                   //  - position < last_kf.time (so it_next != keyframes.end())
                   const Timeline::Keyframe& kf_next = *it_next;
                   const Timeline::Keyframe& kf_prev = *(it_next - 1);

                   if (kf_prev.time == kf_next.time) { // Should not happen with distinct times
                       result_value = kf_next.value;
                   } else {
                       double t_norm_double = (position - kf_prev.time) / (kf_next.time - kf_prev.time);
                       t_norm_double = std::max(0.0, std::min(1.0, t_norm_double)); // Clamp for safety

                       if (kf_next.interpolator_func) {
                           float factor = kf_next.interpolator_func(static_cast<float>(t_norm_double));
                           result_value = kf_prev.value + factor * (kf_next.value - kf_prev.value);
                       } else { // Linear interpolation
                           result_value = kf_prev.value + static_cast<float>(t_norm_double) * (kf_next.value - kf_prev.value);
                       }
                   }
               }
           }
       }
   }

   // Final clamping (values are float, min_value/max_value are float)
   if (has_min_value) {
       result_value = std::max(min_value, result_value);
   }
   if (has_max_value) {
       result_value = std::min(max_value, result_value);
   }

   return result_value;
}


} // namespace Timeline


