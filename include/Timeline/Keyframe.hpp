#pragma once


#include <Timeline/Keyframe.hpp>
#include <functional>


namespace Timeline
{
   class Keyframe
   {
   private:

   protected:


   public:
      std::function<float(float)> interpolator_func;
      float value;
      double time;
      bool focused;
      Keyframe(std::function<float(float)> interpolator_func={}, float value=0.0f, double time=0.0, bool focused=false);
      ~Keyframe();

      void set_focused(bool focused=false);
      void set_as_focused();
      void set_as_unfocused();
      static Timeline::Keyframe construct(double time=0.0, float value=0.0f, std::function<float(float)> interpolator_func={});
   };
}



