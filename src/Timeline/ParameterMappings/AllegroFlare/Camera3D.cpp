

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

   std::vector<Timeline::Parameter> result = {
      Timeline::Parameter::build("position.x", &p.position.x, {}),
      Timeline::Parameter::build("position.y", &p.position.y, {}),
      Timeline::Parameter::build("position.z", &p.position.z, {}),

      Timeline::Parameter::build("stepout.x", &p.stepout.x, {}),
      Timeline::Parameter::build("stepout.y", &p.stepout.y, {}),
      Timeline::Parameter::build("stepout.z", &p.stepout.z, {}),

      Timeline::Parameter::build("spin", &p.spin, {}),
      Timeline::Parameter::build("tilt", &p.spin, {}),
      Timeline::Parameter::build("roll", &p.spin, {}),

      Timeline::Parameter::build("zoom", &p.spin, {}),

      Timeline::Parameter::build("shift.x", &p.shift.x, {}),
      Timeline::Parameter::build("shift.y", &p.shift.y, {}),

      Timeline::Parameter::build("near plane", &p.near_plane, {}),
      Timeline::Parameter::build("far plane", &p.far_plane, {}),
   };

   return result;
}


} // namespace AllegroFlare
} // namespace ParameterMappings
} // namespace Timeline


