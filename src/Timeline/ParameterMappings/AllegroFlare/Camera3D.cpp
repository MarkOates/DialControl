

#include <Timeline/ParameterMappings/AllegroFlare/Camera3D.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Timeline
{
namespace ParameterMappings
{
namespace AllegroFlare
{


Camera3D::Camera3D()
{
}


Camera3D::~Camera3D()
{
}


std::vector<Timeline::Parameter> Camera3D::build_parameters(::AllegroFlare::Camera3D* camera)
{
   if (!(camera))
   {
      std::stringstream error_message;
      error_message << "[Timeline::ParameterMappings::AllegroFlare::Camera3D::build_parameters]: error: guard \"camera\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::ParameterMappings::AllegroFlare::Camera3D::build_parameters]: error: guard \"camera\" not met");
   }
   auto &p = *camera;
   static const bool F = false;
   static const bool T = true;

   std::vector<Timeline::Parameter> result = {
      Timeline::Parameter::build("position.x", &p.position.x, {}, p.position.x, F, F),
      Timeline::Parameter::build("position.y", &p.position.y, {}, p.position.y, F, F),
      Timeline::Parameter::build("position.z", &p.position.z, {}, p.position.z, F, F),

      Timeline::Parameter::build("stepout.x", &p.stepout.x, {}, p.stepout.x, F, F),
      Timeline::Parameter::build("stepout.y", &p.stepout.y, {}, p.stepout.y, F, F),
      Timeline::Parameter::build("stepout.z", &p.stepout.z, {}, p.stepout.z, F, F),

      Timeline::Parameter::build("spin", &p.spin, {}, p.spin, F, F),
      Timeline::Parameter::build("tilt", &p.tilt, {}, p.tilt, F, F),
      Timeline::Parameter::build("roll", &p.roll, {}, p.roll, F, F),

      Timeline::Parameter::build("zoom", &p.zoom, {}, p.zoom, F, F),

      Timeline::Parameter::build("shift.x", &p.shift.x, {}, p.shift.x, F, F),
      Timeline::Parameter::build("shift.y", &p.shift.y, {}, p.shift.y, F, F),

      Timeline::Parameter::build("near plane", &p.near_plane, {}, p.near_plane, F, F),
      Timeline::Parameter::build("far plane", &p.far_plane, {}, p.far_plane, F, F),
   };

   return result;
}


} // namespace AllegroFlare
} // namespace ParameterMappings
} // namespace Timeline


