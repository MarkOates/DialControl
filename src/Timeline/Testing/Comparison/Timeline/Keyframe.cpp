

#include <Timeline/Testing/Comparison/Timeline/Keyframe.hpp>


namespace Timeline
{


bool operator==(const Keyframe& object, const Keyframe& other_object)
{
   if (object.time != other_object.time) return false;
   if (object.value != other_object.value) return false;
   if (object.focused != other_object.focused) return false;
   return true;
}


void PrintTo(const Keyframe& object, ::std::ostream* os)
{
   *os << "Keyframe(\n"
       << "   time: " << object.time << ",\n"
       << "   value: " << object.value << ",\n"
       << "   focused: " << object.focused << ",\n"
       << ")";
}


}


