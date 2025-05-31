

#include <DialControl/CameraControl.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace DialControl
{


CameraControl::CameraControl()
   : camera(nullptr)
{
}


CameraControl::~CameraControl()
{
}


void CameraControl::set_camera(AllegroFlare::Camera3D* camera)
{
   this->camera = camera;
}


AllegroFlare::Camera3D* CameraControl::get_camera() const
{
   return camera;
}


void CameraControl::on_key_down(ALLEGRO_EVENT* event)
{
   if (!(camera))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraControl::on_key_down]: error: guard \"camera\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraControl::on_key_down]: error: guard \"camera\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraControl::on_key_down]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraControl::on_key_down]: error: guard \"event\" not met");
   }
   if (!((event->type == ALLEGRO_EVENT_KEY_DOWN)))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraControl::on_key_down]: error: guard \"(event->type == ALLEGRO_EVENT_KEY_DOWN)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraControl::on_key_down]: error: guard \"(event->type == ALLEGRO_EVENT_KEY_DOWN)\" not met");
   }
   bool shift = event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   return;
}


} // namespace DialControl


