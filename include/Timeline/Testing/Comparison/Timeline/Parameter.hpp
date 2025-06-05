#pragma once


#include <Timeline/Parameter.hpp>
#include <ostream>


namespace Timeline
{
   bool operator==(const Parameter& object, const Parameter& other_object);
   void PrintTo(const Parameter& object, ::std::ostream* os);
}


