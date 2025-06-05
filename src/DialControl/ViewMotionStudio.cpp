

#include <DialControl/ViewMotionStudio.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <DialControl/CameraInfoOverlay.hpp>
#include <Timeline/ParameterMappings/AllegroFlare/Camera3D.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace DialControl
{


ViewMotionStudio::ViewMotionStudio()
   : font_bin(nullptr)
   , camera_studio({})
   , motion_studio({})
   , control_state(STATE_UNDEF)
   , control_state_is_busy(false)
   , control_state_changed_at(0.0f)
   , initialized(false)
{
}


ViewMotionStudio::~ViewMotionStudio()
{
}


void ViewMotionStudio::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[ViewMotionStudio::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


uint32_t ViewMotionStudio::get_control_state() const
{
   return control_state;
}


bool ViewMotionStudio::get_initialized() const
{
   return initialized;
}


DialControl::CameraStudio &ViewMotionStudio::get_camera_studio_ref()
{
   return camera_studio;
}


Timeline::MotionStudio &ViewMotionStudio::get_motion_studio_ref()
{
   return motion_studio;
}


void ViewMotionStudio::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::initialize]: error: guard \"font_bin\" not met");
   }
   camera_studio.set_font_bin(font_bin);
   camera_studio.initialize();

   // Camera A, for now
   build_parameters_for_camera_1();


   // Set the position of the timeline
   AllegroFlare::Placement2D &timeline_placement = motion_studio.get_timeline_placement_ref();
   timeline_placement.position.x = 400;
   timeline_placement.position.y = 900;

   set_control_state(STATE_CAMERA_STUDIO_CONTROL);


   //AllegroFlare::Placement3D placement;
   //Timeline::MotionStudio motion_studio;
   //AllegroFlare::Placement2D &timeline_placement = motion_studio.get_timeline_placement_ref();
   //timeline_placement.position.x = 300;
   //timeline_placement.position.y = 700;

   //MusicElements music_elements;
   //motion_studio.set_parameters(build_parameters_for_music_elements(music_elements));
   //motion_studio.set_parameters(build_parameters_for_placement3D(placement));
   //motion_studio.set_parameter_views(
         //build_parameter_views_for_parameters(
            //&get_font_bin_ref(),
            //&motion_studio.get_parameters_ref()
         //)
      //);
   initialized = true;
   return;
}

void ViewMotionStudio::build_parameters_for_camera_1()
{
   // TODO: Check if this is safe?

   AllegroFlare::Camera3D &camera_1 = *camera_studio.get_current_camera();

   //motion_studio.set_font_bin(font_bin);
   // HERE
   motion_studio.set_parameters(
      //build_parameters_for_placement3D(placement)
      Timeline::ParameterMappings::AllegroFlare::Camera3D::build_parameters(&camera_1)
   );
   //setup_parameter_views_for_parameters();
   motion_studio.set_parameter_views(
         motion_studio.build_parameter_views_for_parameters(
            font_bin,
            &motion_studio.get_parameters_ref(),
            12
         )
      );
   //motion_studio.set_parameter_views(
         //motion_studio.build_parameter_views_for_parameters(
            //font_bin,
            //&motion_studio.get_parameters_ref(),
            //12
         //)
      //);
   return;
}

void ViewMotionStudio::link_camera_1_to_parameters()
{
   AllegroFlare::Camera3D &camera_1 = *camera_studio.get_current_camera();

   for (auto &p : motion_studio.get_parameters_ref())
   {
      if (p.name.empty()) throw std::runtime_error("unrecognized param \"" + p.name + "\"");

      else if (p.name == "near plane") p.parameter = &camera_1.near_plane;
      else if (p.name == "far plane") p.parameter = &camera_1.far_plane;

      else if (p.name == "position.x") p.parameter = &camera_1.position.x;
      else if (p.name == "position.y") p.parameter = &camera_1.position.y;
      else if (p.name == "position.z") p.parameter = &camera_1.position.z;

      else if (p.name == "stepout.x") p.parameter = &camera_1.stepout.x;
      else if (p.name == "stepout.y") p.parameter = &camera_1.stepout.y;
      else if (p.name == "stepout.z") p.parameter = &camera_1.stepout.z;

      else if (p.name == "shift.x") p.parameter = &camera_1.shift.x;
      else if (p.name == "shift.y") p.parameter = &camera_1.shift.y;

      else if (p.name == "spin") p.parameter = &camera_1.spin;
      else if (p.name == "tilt") p.parameter = &camera_1.tilt;
      else if (p.name == "roll") p.parameter = &camera_1.roll;

      else if (p.name == "zoom") p.parameter = &camera_1.zoom;

      else throw std::runtime_error("unaccounted for param \"" + p.name + "\"");
   }

   //setup_parameter_views_for_parameters();
   motion_studio.set_parameter_views(
         motion_studio.build_parameter_views_for_parameters(
            font_bin,
            &motion_studio.get_parameters_ref(),
            12
         )
      );

   return;
}

std::vector<Timeline::ParameterView> ViewMotionStudio::xxbuild_parameter_views_for_parameters(AllegroFlare::FontBin* font_bin, std::vector<Timeline::Parameter>* p, float height)
{
   std::vector<Timeline::ParameterView> result;
   int x = 400;
   int y = 100;
   //int yd = 100;
   int i = 0;
   //float height = Timeline::ParameterView::DEFAULT_HEIGHT;
   //int yd = height;
   for (auto &pp : *p)
   {
      result.push_back(Timeline::ParameterView(font_bin, pp.name, &pp)); // HERE
      result.back().set_height(height);
      i++;
   }
   return result;
}

void ViewMotionStudio::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::update]: error: guard \"initialized\" not met");
   }
   motion_studio.update_playback();
   camera_studio.update();
   return;
}

void ViewMotionStudio::setup_camera_projection_on_live_camera()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::setup_camera_projection_on_live_camera]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::setup_camera_projection_on_live_camera]: error: guard \"initialized\" not met");
   }
   camera_studio.setup_projection_on_live_camera();
   return;
}

void ViewMotionStudio::toggle_control_state()
{
   if (is_control_state(STATE_CAMERA_STUDIO_CONTROL)) set_control_state(STATE_MOTION_STUDIO_CONTROL);
   else if (is_control_state(STATE_MOTION_STUDIO_CONTROL)) set_control_state(STATE_CAMERA_STUDIO_CONTROL);
   return;
}

void ViewMotionStudio::render_hud()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::render_hud]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::render_hud]: error: guard \"initialized\" not met");
   }
   camera_studio.setup_projection_on_hud_camera();
   camera_studio.draw_camera_info_overlay();
   motion_studio.render();
   DialControl::CameraInfoOverlay::draw_pill(
      1920/2 + 700, // x
      1080 - 80,    // y
      200,          // w
      48,           // h
      80.0,         // column_divider_pos
      8.0,          // column_divider_padding
      "Mode",       // label
      ALLEGRO_COLOR{1, 1, 1, 1}, // label_color
      get_control_state_string(control_state), // value
      ALLEGRO_COLOR{1, 1, 1, 1}, // value_color
      obtain_font(),
      obtain_bold_font()
   );
   return;
}

void ViewMotionStudio::on_key_down(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::on_key_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::on_key_down]: error: guard \"initialized\" not met");
   }
   // TODO: Fix these paths
   std::string filename_load = "tests/fixtures/animations/camera_move_1-0n.txt";
   std::string filename_save = "tests/fixtures/animations/camera_move_1-0n_output.txt";

   if (event->keyboard.keycode == ALLEGRO_KEY_TAB)
   {
      toggle_control_state();
   }
   else if (event->keyboard.keycode == ALLEGRO_KEY_X)
   {
      std::cout << "saving json to " << filename_save << std::endl;
      std::string file_content = build_json_string();
      AllegroFlare::php::file_put_contents(filename_save, file_content);
   }
   else if (event->keyboard.keycode == ALLEGRO_KEY_L)
   {
      std::cout << "loading json" << std::endl;
      std::string file_content = AllegroFlare::php::file_get_contents(filename_load);
      load_json(file_content);
   }
   else
   {
      switch (control_state)
      {
         case STATE_CAMERA_STUDIO_CONTROL: camera_studio.on_key_down(event); break;
         case STATE_MOTION_STUDIO_CONTROL: motion_studio.on_key_down(event); break;
         default: break;
      }
   }
   return;
}

void ViewMotionStudio::load_json(std::string json_string)
{
   // 1) load the camera json
   camera_studio.load_json(json_string);

   motion_studio.load_json(json_string);

   link_camera_1_to_parameters();
   return;
}

std::string ViewMotionStudio::build_json_string()
{
   // 1) load the camera json
   auto cj = camera_studio.build_json();
   auto mj = motion_studio.build_json();
   //motion_studio.load_json(json_string);
   //link_camera_1_to_parameters();
   cj.update(mj);
   return cj.dump(2);
}

void ViewMotionStudio::set_control_state(uint32_t control_state, bool override_if_busy)
{
   if (!(is_valid_control_state(control_state)))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::set_control_state]: error: guard \"is_valid_control_state(control_state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::set_control_state]: error: guard \"is_valid_control_state(control_state)\" not met");
   }
   if (this->control_state == control_state) return;
   if (!override_if_busy && control_state_is_busy) return;
   uint32_t previous_control_state = this->control_state;

   switch (control_state)
   {
      case STATE_CAMERA_STUDIO_CONTROL:
      break;

      case STATE_MOTION_STUDIO_CONTROL:
      break;

      default:
         AllegroFlare::Logger::throw_error(
            THIS_CLASS_AND_METHOD_NAME,
            "Unable to handle case for control_state \"" + std::to_string(control_state) + "\""
         );
      break;
   }

   this->control_state = control_state;
   control_state_changed_at = al_get_time();

   return;
}

std::string ViewMotionStudio::get_control_state_string(uint32_t control_state)
{
   if (!(is_valid_control_state(control_state)))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::get_control_state_string]: error: guard \"is_valid_control_state(control_state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::get_control_state_string]: error: guard \"is_valid_control_state(control_state)\" not met");
   }
   switch (control_state)
   {
      case STATE_CAMERA_STUDIO_CONTROL: return "Camera"; break;
      case STATE_MOTION_STUDIO_CONTROL: return "Motion"; break;

      default:
         AllegroFlare::Logger::throw_error(
            THIS_CLASS_AND_METHOD_NAME,
            "Unable to handle case for control_state \"" + std::to_string(control_state) + "\""
         );
      break;
   }
   return "[error-obtaining-value]";
}

bool ViewMotionStudio::is_valid_control_state(uint32_t control_state)
{
   std::set<uint32_t> valid_control_states =
   {
      STATE_CAMERA_STUDIO_CONTROL,
      STATE_MOTION_STUDIO_CONTROL,
   };
   return (valid_control_states.count(control_state) > 0);
}

bool ViewMotionStudio::is_control_state(uint32_t possible_control_state)
{
   return (control_state == possible_control_state);
}

float ViewMotionStudio::infer_current_control_state_age(float time_now)
{
   return (time_now - control_state_changed_at);
}

ALLEGRO_FONT* ViewMotionStudio::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -26");
}

ALLEGRO_FONT* ViewMotionStudio::obtain_bold_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::obtain_bold_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::obtain_bold_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-bold.ttf -26");
}


} // namespace DialControl


