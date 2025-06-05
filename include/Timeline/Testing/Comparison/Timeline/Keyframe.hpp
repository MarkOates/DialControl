#pragma once


#include <Timeline/Keyframe.hpp>
#include <ostream>


namespace Timeline
{
   bool operator==(const Keyframe& object, const Keyframe& other_object);
   void PrintTo(const Keyframe& object, ::std::ostream* os);
}


