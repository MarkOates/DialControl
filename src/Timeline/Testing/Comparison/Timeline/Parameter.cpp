

#include <Timeline/Testing/Comparison/Timeline/Parameter.hpp>
#include <Timeline/Testing/Comparison/Timeline/Keyframe.hpp>


namespace Timeline
{


bool operator==(const Parameter& object, const Parameter& other_object)
{
   if (object.name != other_object.name) return false;
   if (object.parameter != other_object.parameter) return false;
   if (object.initial_value != other_object.initial_value) return false;
   if (object.keyframes != other_object.keyframes) return false;
   if (object.has_min_value != other_object.has_min_value) return false;
   if (object.has_max_value != other_object.has_max_value) return false;
   if (object.min_value != other_object.min_value) return false;
   if (object.max_value != other_object.max_value) return false;
   return true;
}


void PrintTo(const Parameter& object, ::std::ostream* os)
{
   *os << "Parameter(\n"
       << "   name: \"" << object.name << "\",\n"
       << "   has_min_value: " << object.has_min_value << ",\n"
       << "   has_max_value: " << object.has_max_value << ",\n"
       << "   min_value: " << object.min_value << ",\n"
       << "   max_value: " << object.max_value << ",\n"
       << "   parameter: " << object.parameter << ",\n"
       << "   initial_value: " << object.initial_value << ",\n"
       << "   keyframes: ";

   if (object.keyframes.empty())
   {
      *os << "[]\n";
   }
   else
   {
      *os << "[\n";
      for (const auto& keyframe : object.keyframes)
      {
         *os << "      ";
         Timeline::PrintTo(keyframe, os);
         *os << ",\n";
      }
      *os << "   ]\n";
   }

   *os << ")";
}


}


