#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace DialControl
{
   class CameraInfoOverlay
   {
   private:
      AllegroFlare::FontBin* font_bin;
      AllegroFlare::Camera3D* camera;
      ALLEGRO_FONT* obtain_font();
      ALLEGRO_FONT* obtain_bold_font();

   protected:


   public:
      CameraInfoOverlay(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Camera3D* camera=nullptr);
      ~CameraInfoOverlay();

      void set_camera(AllegroFlare::Camera3D* camera);
      AllegroFlare::Camera3D* get_camera() const;
      std::string tos(float f=0.0f);
      std::string tosv(AllegroFlare::Vec3D v={});
      void render();
      void draw_pill(float x=0.0f, float y=0.0f, float w=300.0f, float h=50.0f, float column_divider_pos=100.0f, float column_divider_padding=6.0f, std::string label="[unset-label]", ALLEGRO_COLOR label_color=ALLEGRO_COLOR{1, 1, 1, 1}, std::string value="[unset-value]", ALLEGRO_COLOR value_color=ALLEGRO_COLOR{1, 1, 1, 1});
   };
}



