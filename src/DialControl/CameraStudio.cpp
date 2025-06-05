

#include <DialControl/CameraStudio.hpp>

#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <DialControl/CameraInfoOverlay.hpp>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace DialControl
{


CameraStudio::CameraStudio()
   : font_bin(nullptr)
   , cameras({})
   , cameras_({})
   , current_camera_idx(0)
   , current_camera(nullptr)
   , live_camera({})
   , hud_camera({})
   , camera_info_overlay_visible(true)
   , initialized(false)
{
}


CameraStudio::~CameraStudio()
{
}


void CameraStudio::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[CameraStudio::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void CameraStudio::set_cameras(std::vector<AllegroFlare::Camera3D> cameras)
{
   this->cameras = cameras;
}


void CameraStudio::set_cameras_(std::vector<DialControl::CameraInfo> cameras_)
{
   this->cameras_ = cameras_;
}


void CameraStudio::set_current_camera(AllegroFlare::Camera3D* current_camera)
{
   this->current_camera = current_camera;
}


std::vector<AllegroFlare::Camera3D> CameraStudio::get_cameras() const
{
   return cameras;
}


std::vector<DialControl::CameraInfo> CameraStudio::get_cameras_() const
{
   return cameras_;
}


AllegroFlare::Camera3D* CameraStudio::get_current_camera() const
{
   return current_camera;
}


bool CameraStudio::get_initialized() const
{
   return initialized;
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
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraStudio::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraStudio::initialize]: error: guard \"font_bin\" not met");
   }
   AllegroFlare::Camera3D baseline_camera;
   baseline_camera.stepout = { 0, 0, 16 };
   baseline_camera.zoom = 1.0; //1.62;
   baseline_camera.tilt = 0.0; //ALLEGRO_PI * 0.25;
   baseline_camera.spin = 0.0; //125;
   baseline_camera.position = { 0, 0, 0 };
   baseline_camera.use_unit_values(); // Use unit values for rotation

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

void CameraStudio::setup_projection_on_live_camera()
{
   live_camera.setup_projection_on(al_get_target_bitmap());
   return;
}

void CameraStudio::setup_projection_on_hud_camera()
{
   hud_camera.setup_dimensional_projection(al_get_target_bitmap());
   al_clear_depth_buffer(1);
   al_set_render_state(ALLEGRO_DEPTH_TEST, 0);
   return;
}

void CameraStudio::toggle_camera_info_overlay_visibility()
{
   camera_info_overlay_visible = !camera_info_overlay_visible;
}

void CameraStudio::show_camera_info_overlay()
{
   camera_info_overlay_visible = true;
}

void CameraStudio::hide_camera_info_overlay()
{
   camera_info_overlay_visible = false;
}

void CameraStudio::draw_camera_info_overlay()
{
   if (!camera_info_overlay_visible) return;

   DialControl::CameraInfoOverlay camera_info_overlay(font_bin, current_camera);
   camera_info_overlay.set_camera_name("Camera Unnamed");
   camera_info_overlay.render();

   return;
}

void CameraStudio::set_current_camera_to_next_camera()
{
   int total_cameras = cameras.size();
   current_camera_idx = (current_camera_idx + 1) % total_cameras;
   current_camera = &cameras[current_camera_idx];
   return;
}

void CameraStudio::set_current_camera_to_previous_camera()
{
   int total_cameras = cameras.size();
   current_camera_idx = (current_camera_idx - 1 + total_cameras) % total_cameras;
   current_camera = &cameras[current_camera_idx];
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


   // Camera movement controls

   mapper.set_mapping(ALLEGRO_KEY_W, 0, { "position_z_minus" });
   mapper.set_mapping(ALLEGRO_KEY_S, 0, { "position_z_plus" });
   mapper.set_mapping(ALLEGRO_KEY_A, 0, { "position_x_minus" });
   mapper.set_mapping(ALLEGRO_KEY_D, 0, { "position_x_plus" });
   mapper.set_mapping(ALLEGRO_KEY_C, 0, { "position_y_minus" });
   mapper.set_mapping(ALLEGRO_KEY_E, 0, { "position_y_plus" });
   mapper.set_mapping(ALLEGRO_KEY_COMMA, 0, { "shift_left" });
   mapper.set_mapping(ALLEGRO_KEY_FULLSTOP, 0, { "shift_right" });
   mapper.set_mapping(ALLEGRO_KEY_J, 0, { "shift_up" });
   mapper.set_mapping(ALLEGRO_KEY_M, 0, { "shift_down" });

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

   // UI Controls

   mapper.set_mapping(ALLEGRO_KEY_H, 0, { "toggle_camera_info_overlay_visibility" });
   mapper.set_mapping(ALLEGRO_KEY_N, 0, { "set_current_camera_to_next_camera" });
   mapper.set_mapping(ALLEGRO_KEY_P, 0, { "set_current_camera_to_previous_camera" });
   mapper.set_mapping(ALLEGRO_KEY_X, 0, { "dump_json_to_cout" });
   //mapper.set_mapping(ALLEGRO_KEY_L, 0, { "load_json_string" });



   float dial_increment = 1.0 / 32;


   std::vector<std::string> commands = mapper.get_mapping(event->keyboard.keycode, shift, ctrl, alt, command);


   for (auto &command : commands)
   {
      if (command.empty()) continue;

      else if (command == "position_x_plus") current_camera->position.x += 0.25;
      else if (command == "position_x_minus") current_camera->position.x -= 0.25;
      else if (command == "position_y_plus") current_camera->position.y += 0.25;
      else if (command == "position_y_minus") current_camera->position.y -= 0.25;
      else if (command == "position_z_plus") current_camera->position.z += 0.25;
      else if (command == "position_z_minus") current_camera->position.z -= 0.25;
      else if (command == "shift_left") current_camera->shift.x -= 0.0625;
      else if (command == "shift_right") current_camera->shift.x += 0.0625;
      else if (command == "shift_up") current_camera->shift.y += 0.0625;
      else if (command == "shift_down") current_camera->shift.y -= 0.0625;

      else if (command == "right") current_camera->stepout.x += 0.25;
      else if (command == "left") current_camera->stepout.x -= 0.25;
      else if (command == "up") current_camera->stepout.y += 0.25;
      else if (command == "down") current_camera->stepout.y -= 0.25;

      else if (command == "dial_1_left") current_camera->spin -= dial_increment;
      else if (command == "dial_1_right") current_camera->spin += dial_increment;
      else if (command == "dial_2_left") current_camera->tilt -= dial_increment;
      else if (command == "dial_2_right") current_camera->tilt += dial_increment;
      else if (command == "dial_3_left") current_camera->zoom -= 0.125;
      else if (command == "dial_3_right") current_camera->zoom += 0.125;
      else if (command == "dial_4_left") current_camera->stepout.z -= 1.0;
      else if (command == "dial_4_right") current_camera->stepout.z += 1.0;

      else if (command == "toggle_camera_info_overlay_visibility") toggle_camera_info_overlay_visibility();
      else if (command == "set_current_camera_to_next_camera") set_current_camera_to_next_camera();
      else if (command == "set_current_camera_to_previous_camera") set_current_camera_to_previous_camera();
      else if (command == "dump_json_to_cout") std::cout << build_json_dump() << std::endl;

      else
      {
         throw std::runtime_error("missinasdnh89sdh89fhsg");
      }
   }

   return;
}

std::string CameraStudio::build_json_dump()
{
   nlohmann::json j;
   j["cameras"] = cameras;
   return j.dump(2);
}

nlohmann::json CameraStudio::build_json()
{
   nlohmann::json j;
   j["cameras"] = cameras;
   return j;
}

void CameraStudio::load_json(std::string json_string)
{
   nlohmann::json j = nlohmann::json::parse(json_string); // TODO: Consider moving this into a TRY block

   if (j.contains("cameras") && j["cameras"].is_array())
   {
      // Set all the cameras to the camera values in the JSON array
      cameras = j["cameras"].get<std::vector<AllegroFlare::Camera3D>>();

      // Output some debugging info
      bool output_debug_info = false;
      if (output_debug_info)
      {
         std::cout << "- " << std::endl;
         for (int i=0; i<cameras.size(); i++)
         {
            std::cout << " camera " << i << ": " << std::endl;
            std::cout << "       position: { " << cameras[i].position.x
                                               << ", " << cameras[i].position.y
                                               << ", " << cameras[i].position.z
                                               << "}" << std::endl;
            std::cout << "       stepout: { " << cameras[i].stepout.x
                                               << ", " << cameras[i].stepout.y
                                               << ", " << cameras[i].stepout.z
                                               << "}" << std::endl;
            std::cout << "       spin: " << cameras[i].spin << std::endl;
            std::cout << "       tilt: " << cameras[i].tilt << std::endl;
            std::cout << "       zoom: " << cameras[i].zoom << std::endl;
            std::cout << "       near: " << cameras[i].near_plane << std::endl;
            std::cout << "       far: " << cameras[i].far_plane << std::endl;
         }
      }

      // Refresh the *current_camera (since it now points to an invalid camera
      current_camera = &cameras[current_camera_idx];
   }
   else
   {
      throw std::runtime_error("Expected key \"cameras\" with an array value in JSON");
   }

   return;
}


} // namespace DialControl


