#pragma once


#include <Timeline/Keyframe.hpp>
#include <Timeline/Parameter.hpp>
#include <cstddef>
#include <functional>
#include <string>
#include <vector>


namespace Timeline
{
   class Parameter
   {
   private:

   protected:


   public:
      std::string name;
      float initial_value;
      float* parameter;
      std::vector<Timeline::Keyframe> keyframes;
      bool has_min_value;
      bool has_max_value;
      float min_value;
      float max_value;
      bool interpolate_initial_value_to_1st_keyframe;
      Parameter();
      ~Parameter();

      static Timeline::Parameter build(std::string name="[unset-name]", float* parameter=nullptr, std::vector<Timeline::Keyframe> keyframes={}, float initial_value=0.0f, bool has_min_value=true, bool has_max_value=true, float min_value=0.0f, float max_value=1.0f);
      void add_keyframe(double time=0.0, float value=0.0f, std::function<float(float)> interpolator_func={});
      bool remove_keyframe_at_index(std::size_t index=0);
      void assign_to_time(double position=0.0);
      float calculate_value_at(double position=0.0);
   };
}



