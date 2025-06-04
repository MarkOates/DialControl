

#include <DialControl/ViewMotionStudio.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace DialControl
{


ViewMotionStudio::ViewMotionStudio()
   : font_bin(nullptr)
   , camera_studio({})
   , motion_studio({})
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


bool ViewMotionStudio::get_initialized() const
{
   return initialized;
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

void ViewMotionStudio::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[DialControl::ViewMotionStudio::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::ViewMotionStudio::update]: error: guard \"initialized\" not met");
   }
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
   camera_studio.on_key_down(event);
   return;
}


} // namespace DialControl


