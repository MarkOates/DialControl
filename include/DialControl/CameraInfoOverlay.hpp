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
      std::string camera_name;
      bool camera_is_tracking_object;
      ALLEGRO_FONT* obtain_font();
      ALLEGRO_FONT* obtain_bold_font();

   protected:


   public:
      CameraInfoOverlay(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Camera3D* camera=nullptr, std::string camera_name="[unset-camera_name]", bool camera_is_tracking_object=true);
      ~CameraInfoOverlay();

      void set_camera(AllegroFlare::Camera3D* camera);
      void set_camera_name(std::string camera_name);
      void set_camera_is_tracking_object(bool camera_is_tracking_object);
      AllegroFlare::Camera3D* get_camera() const;
      std::string get_camera_name() const;
      bool get_camera_is_tracking_object() const;
      std::string tos(float f=0.0f);
      std::string tosv(AllegroFlare::Vec3D v={});
      float hfov_degrees();
      void render();
      void draw_pill(float x=0.0f, float y=0.0f, float w=300.0f, float h=50.0f, float column_divider_pos=100.0f, float column_divider_padding=6.0f, std::string label="[unset-label]", ALLEGRO_COLOR label_color=ALLEGRO_COLOR{1, 1, 1, 1}, std::string value="[unset-value]", ALLEGRO_COLOR value_color=ALLEGRO_COLOR{1, 1, 1, 1});
   };
}



