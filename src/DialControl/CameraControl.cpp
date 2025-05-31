

#include <DialControl/CameraControl.hpp>

#include <AllegroFlare/KeyboardCommandMapper.hpp>
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
   bool ctrl = event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
   bool alt = event->keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
   bool command = event->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
   //bool command = event->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
   //ALLEGRO_KEYMOD_SHIFT
   //ALLEGRO_KEYMOD_CTRL
   //ALLEGRO_KEYMOD_ALT
   //ALLEGRO_KEYMOD_LWIN
   //ALLEGRO_KEYMOD_RWIN
   //ALLEGRO_KEYMOD_MENU
   //ALLEGRO_KEYMOD_ALTGR
   //ALLEGRO_KEYMOD_COMMAND

   constexpr auto SHIFT = AllegroFlare::KeyboardCommandMapper::SHIFT;
   constexpr auto CTRL = AllegroFlare::KeyboardCommandMapper::CTRL;
   //constexpr auto ALT = AllegroFlare::KeyboardCommandMapper::ALT;
   constexpr auto COMMAND = AllegroFlare::KeyboardCommandMapper::COMMAND;
   constexpr auto OPTION = AllegroFlare::KeyboardCommandMapper::OPTION;

   AllegroFlare::KeyboardCommandMapper mapper;

   //std::vector<std::string> commands = { "dial_4_right" };
   //mapper.set_mapping(ALLEGRO_KEY_RIGHT, SHIFT | CTRL | COMMAND | OPTION, { "dial_4_right" });
   //mapper.set_mapping(ALLEGRO_KEY_LEFT, SHIFT | CTRL | COMMAND | OPTION, { "dial_4_left" });
   mapper.set_mapping(ALLEGRO_KEY_1, COMMAND, { "dial_1_left" });
   mapper.set_mapping(ALLEGRO_KEY_2, COMMAND, { "dial_1_right" });
   mapper.set_mapping(ALLEGRO_KEY_3, COMMAND, { "dial_2_left" });
   mapper.set_mapping(ALLEGRO_KEY_4, COMMAND, { "dial_2_right" });
   mapper.set_mapping(ALLEGRO_KEY_5, COMMAND, { "dial_3_left" });
   mapper.set_mapping(ALLEGRO_KEY_6, COMMAND, { "dial_3_right" });
   mapper.set_mapping(ALLEGRO_KEY_7, COMMAND, { "dial_4_left" });
   mapper.set_mapping(ALLEGRO_KEY_8, COMMAND, { "dial_4_right" });
   //mapper.set_mapping(ALLEGRO_KEY_RIGHT, SHIFT, { "dial_4_right" });
   //mapper.set_mapping(ALLEGRO_KEY_LEFT, SHIFT, { "dial_4_left" });
   //mapper.set_mapping(ALLEGRO_KEY_1, COMMAND, { "dial_1_left" });
   //mapper.set_mapping(ALLEGRO_KEY_2, COMMAND, { "dial_1_right" });



   std::vector<std::string> commands = mapper.get_mapping(event->keyboard.keycode, shift, ctrl, alt, command);


   for (auto &command : commands)
   {
      if (command.empty()) continue;
      else if (command == "dial_1_left") camera->tilt -= 0.125;
      else if (command == "dial_1_right") camera->tilt += 0.125;
      else if (command == "dial_2_left") camera->zoom -= 0.125;
      else if (command == "dial_2_right") camera->zoom += 0.125;
      else if (command == "dial_3_left") camera->stepout.z -= 1.0;
      else if (command == "dial_3_right") camera->stepout.z += 1.0;
      else if (command == "dial_4_left") camera->spin -= 0.125;
      else if (command == "dial_4_right") camera->spin += 0.125;
   }


   return;
}


} // namespace DialControl


