#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <DialControl/CameraStudio.hpp>
#include <Timeline/MotionStudio.hpp>
#include <Timeline/Parameter.hpp>
#include <Timeline/ParameterView.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace DialControl
{
   class ViewMotionStudio
   {
   private:
      AllegroFlare::FontBin* font_bin;
      DialControl::CameraStudio camera_studio;
      Timeline::MotionStudio motion_studio;
      bool initialized;

   protected:


   public:
      ViewMotionStudio();
      ~ViewMotionStudio();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      bool get_initialized() const;
      DialControl::CameraStudio &get_camera_studio_ref();
      Timeline::MotionStudio &get_motion_studio_ref();
      void initialize();
      std::vector<Timeline::ParameterView> build_parameter_views_for_parameters(AllegroFlare::FontBin* font_bin=nullptr, std::vector<Timeline::Parameter>* p=nullptr, float height=Timeline::ParameterView::DEFAULT_HEIGHT);
      void update();
      void setup_camera_projection_on_live_camera();
      void render_hud();
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
   };
}



