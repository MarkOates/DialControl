#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <DialControl/CameraStudio.hpp>
#include <Timeline/MotionStudio.hpp>
#include <allegro5/allegro.h>


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
      void initialize();
      void update();
      void setup_camera_projection_on_live_camera();
      void render_hud();
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
   };
}



