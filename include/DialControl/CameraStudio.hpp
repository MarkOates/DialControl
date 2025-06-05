#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <DialControl/CameraInfo.hpp>
#include <allegro5/allegro.h>
#include <lib/nlohmann/json.hpp>
#include <string>
#include <vector>


namespace DialControl
{
   class CameraStudio
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::vector<AllegroFlare::Camera3D> cameras;
      std::vector<DialControl::CameraInfo> cameras_;
      int current_camera_idx;
      AllegroFlare::Camera3D* current_camera;
      AllegroFlare::Camera3D live_camera;
      AllegroFlare::Camera2D hud_camera;
      bool camera_info_overlay_visible;
      bool initialized;

   protected:


   public:
      CameraStudio();
      ~CameraStudio();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_cameras(std::vector<AllegroFlare::Camera3D> cameras);
      void set_cameras_(std::vector<DialControl::CameraInfo> cameras_);
      void set_current_camera(AllegroFlare::Camera3D* current_camera);
      std::vector<AllegroFlare::Camera3D> get_cameras() const;
      std::vector<DialControl::CameraInfo> get_cameras_() const;
      AllegroFlare::Camera3D* get_current_camera() const;
      bool get_initialized() const;
      void initialize();
      void update();
      void setup_projection_on_live_camera();
      void setup_projection_on_hud_camera();
      void toggle_camera_info_overlay_visibility();
      void show_camera_info_overlay();
      void hide_camera_info_overlay();
      void draw_camera_info_overlay();
      void set_current_camera_to_next_camera();
      void set_current_camera_to_previous_camera();
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
      std::string build_json_dump();
      nlohmann::json build_json();
      void load_json(std::string json_string="[unset-json_string]");
   };
}



