

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
   } else if (keyframes.size() == 1) {
       const Timeline::Keyframe& kf0 = keyframes[0]; // kf0.time is double, kf0.value is float

       if (interpolate_initial_value_to_1st_keyframe) {
           if (position < kf0.time) { // double < double comparison
               // Interpolate from initial_value (conceptually at t=0.0) to kf0
               if (kf0.time <= 0.0) { // kf0.time is double, 0.0 is a double literal
                   result_value = kf0.value;
               } else {
                   // Normalized time (as double) for interpolation between initial_value (at t=0.0) and kf0
                   double t_norm_double = position / kf0.time; // double / double = double
                   t_norm_double = std::max(0.0, std::min(1.0, t_norm_double)); // Clamp double t_norm to [0.0, 1.0]

                   if (kf0.interpolator_func) { // Use kf0's interpolator
                       // Cast t_norm_double to float for the interpolator function
                       float factor = kf0.interpolator_func(static_cast<float>(t_norm_double));
                       result_value = initial_value + factor * (kf0.value - initial_value);
                   } else { // Linear interpolation
                       // Cast t_norm_double to float for multiplication with float values
                       result_value = initial_value + static_cast<float>(t_norm_double) * (kf0.value - initial_value);
                   }
               }
           } else { // position >= kf0.time
               result_value = kf0.value;
           }
       } else { // Not interpolating to 1st keyframe from initial_value
           if (position < kf0.time) {
               result_value = initial_value;
           } else {
               result_value = kf0.value;
           }
       }
   } else { // 2 or more keyframes
       const Timeline::Keyframe& first_kf = keyframes.front(); // first_kf.time is double
       const Timeline::Keyframe& last_kf = keyframes.back();   // last_kf.time is double

       if (position < first_kf.time) { // double < double
           if (interpolate_initial_value_to_1st_keyframe) {
               // Interpolate from initial_value (conceptually at t=0.0) to first_kf
               if (first_kf.time <= 0.0) { // first_kf.time is double
                   result_value = first_kf.value;
               } else {
                   // Normalized time (as double)
                   double t_norm_double = position / first_kf.time; // double / double = double
                   t_norm_double = std::max(0.0, std::min(1.0, t_norm_double)); // Clamp double t_norm

                   // Use the first keyframe's interpolator
                   if (first_kf.interpolator_func) {
                       float factor = first_kf.interpolator_func(static_cast<float>(t_norm_double)); // Cast to float
                       result_value = initial_value + factor * (first_kf.value - initial_value);
                   } else { // Linear interpolation
                       result_value = initial_value + static_cast<float>(t_norm_double) * (first_kf.value - initial_value); // Cast to float
                   }
               }
           } else {
               result_value = initial_value;
           }
       } else if (position >= last_kf.time) { // double >= double
           result_value = last_kf.value;
       } else {
           // Position is between first_kf.time (inclusive) and last_kf.time (exclusive)
           // Find the keyframe segment [kf_prev, kf_next]
           auto it_next = std::upper_bound(keyframes.begin(), keyframes.end(), position, 
               [](double pos_val, const Timeline::Keyframe& kf) { // pos_val is double
                   return pos_val < kf.time; // kf.time is double
               });

           const Timeline::Keyframe& kf_next = *it_next;       // kf_next.time is double
           const Timeline::Keyframe& kf_prev = *(it_next - 1); // kf_prev.time is double

           if (kf_prev.time == kf_next.time) { // double == double
               result_value = kf_next.value;
           } else {
               // Normalized time (as double) within the segment
               double t_norm_double = (position - kf_prev.time) / (kf_next.time - kf_prev.time); // double arithmetic
               t_norm_double = std::max(0.0, std::min(1.0, t_norm_double)); // Clamp double t_norm

               // Use the *subsequent* keyframe's interpolator_func
               if (kf_next.interpolator_func) {
                   float factor = kf_next.interpolator_func(static_cast<float>(t_norm_double)); // Cast to float
                   result_value = kf_prev.value + factor * (kf_next.value - kf_prev.value);
               } else { // Linear interpolation
                   result_value = kf_prev.value + static_cast<float>(t_norm_double) * (kf_next.value - kf_prev.value); // Cast to float
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


