

#include <DialControl/CameraStudio.hpp>

#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace DialControl
{


CameraStudio::CameraStudio()
   : cameras({})
   , current_camera_idx(0)
   , current_camera(nullptr)
   , live_camera({})
   , hud_camera({})
   , initialized(false)
{
}


CameraStudio::~CameraStudio()
{
}


void CameraStudio::set_cameras(std::vector<AllegroFlare::Camera3D> cameras)
{
   this->cameras = cameras;
}


void CameraStudio::set_current_camera(AllegroFlare::Camera3D* current_camera)
{
   this->current_camera = current_camera;
}


std::vector<AllegroFlare::Camera3D> CameraStudio::get_cameras() const
{
   return cameras;
}


AllegroFlare::Camera3D* CameraStudio::get_current_camera() const
{
   return current_camera;
}


bool CameraStudio::get_initialized() const
{
   return initialized;
}


std::vector<AllegroFlare::Camera3D> &CameraStudio::get_cameras_ref()
{
   return cameras;
}


int &CameraStudio::get_current_camera_idx_ref()
{
   return current_camera_idx;
}


AllegroFlare::Camera3D &CameraStudio::get_live_camera_ref()
{
   return live_camera;
}


AllegroFlare::Camera2D &CameraStudio::get_hud_camera_ref()
{
   return hud_camera;
}


void CameraStudio::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraStudio::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraStudio::initialize]: error: guard \"(!initialized)\" not met");
   }
   AllegroFlare::Camera3D baseline_camera;
   baseline_camera.stepout = { 0, 0, 16 };
   baseline_camera.zoom = 1.0; //1.62;
   baseline_camera.tilt = 0.0; //ALLEGRO_PI * 0.25;
   baseline_camera.spin = 0.125;
   baseline_camera.position = { 0, 0, 0 };

   // Set the live_camera to the baseline_camera
   live_camera = baseline_camera;

   // Set the number of cameras to 6 (for now)
   cameras.resize(6);
   //current_camera_idx = 0;
   for (int i=0; i<cameras.size(); i++)
   {
      cameras[i] = baseline_camera;
   }
   current_camera = &cameras[current_camera_idx];

   initialized = true;
   return;
}

void CameraStudio::update()
{
   live_camera.blend(current_camera, 0.1);
   return;
}

void CameraStudio::on_key_down(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraStudio::on_key_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraStudio::on_key_down]: error: guard \"initialized\" not met");
   }
   if (!(current_camera))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraStudio::on_key_down]: error: guard \"current_camera\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraStudio::on_key_down]: error: guard \"current_camera\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraStudio::on_key_down]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraStudio::on_key_down]: error: guard \"event\" not met");
   }
   if (!((event->type == ALLEGRO_EVENT_KEY_DOWN)))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraStudio::on_key_down]: error: guard \"(event->type == ALLEGRO_EVENT_KEY_DOWN)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraStudio::on_key_down]: error: guard \"(event->type == ALLEGRO_EVENT_KEY_DOWN)\" not met");
   }
   bool shift = event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   bool ctrl = event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
   bool alt = event->keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
   bool command = event->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;

   constexpr auto SHIFT = AllegroFlare::KeyboardCommandMapper::SHIFT;
   constexpr auto CTRL = AllegroFlare::KeyboardCommandMapper::CTRL;
   constexpr auto COMMAND = AllegroFlare::KeyboardCommandMapper::COMMAND;
   constexpr auto OPTION = AllegroFlare::KeyboardCommandMapper::OPTION;

   AllegroFlare::KeyboardCommandMapper mapper;

   mapper.set_mapping(ALLEGRO_KEY_UP, 0, { "up" });
   mapper.set_mapping(ALLEGRO_KEY_DOWN, 0, { "down" });
   mapper.set_mapping(ALLEGRO_KEY_LEFT, 0, { "left" });
   mapper.set_mapping(ALLEGRO_KEY_RIGHT, 0, { "right" });

   mapper.set_mapping(ALLEGRO_KEY_1, COMMAND, { "dial_1_left" });
   mapper.set_mapping(ALLEGRO_KEY_2, COMMAND, { "dial_1_right" });
   mapper.set_mapping(ALLEGRO_KEY_3, COMMAND, { "dial_2_left" });
   mapper.set_mapping(ALLEGRO_KEY_4, COMMAND, { "dial_2_right" });
   mapper.set_mapping(ALLEGRO_KEY_5, COMMAND, { "dial_3_left" });
   mapper.set_mapping(ALLEGRO_KEY_6, COMMAND, { "dial_3_right" });
   mapper.set_mapping(ALLEGRO_KEY_7, COMMAND, { "dial_4_left" });
   mapper.set_mapping(ALLEGRO_KEY_8, COMMAND, { "dial_4_right" });


   std::vector<std::string> commands = mapper.get_mapping(event->keyboard.keycode, shift, ctrl, alt, command);


   for (auto &command : commands)
   {
      if (command.empty()) continue;

      else if (command == "right") current_camera->stepout.x += 0.25;
      else if (command == "left") current_camera->stepout.x -= 0.25;
      else if (command == "up") current_camera->stepout.y += 0.25;
      else if (command == "down") current_camera->stepout.y -= 0.25;

      else if (command == "dial_1_left") current_camera->tilt -= 0.125;
      else if (command == "dial_1_right") current_camera->tilt += 0.125;
      else if (command == "dial_2_left") current_camera->spin -= 0.125;
      else if (command == "dial_2_right") current_camera->spin += 0.125;
      else if (command == "dial_3_left") current_camera->zoom -= 0.125;
      else if (command == "dial_3_right") current_camera->zoom += 0.125;
      else if (command == "dial_4_left") current_camera->stepout.z -= 1.0;
      else if (command == "dial_4_right") current_camera->stepout.z += 1.0;
   }


   return;
}


} // namespace DialControl


