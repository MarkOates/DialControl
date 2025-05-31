#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace DialControl
{
   class CameraStudio
   {
   private:
      std::vector<AllegroFlare::Camera3D> cameras;
      int current_camera_idx;
      AllegroFlare::Camera3D* current_camera;
      AllegroFlare::Camera3D live_camera;
      AllegroFlare::Camera2D hud_camera;
      bool initialized;

   protected:


   public:
      CameraStudio();
      ~CameraStudio();

      void set_cameras(std::vector<AllegroFlare::Camera3D> cameras);
      void set_current_camera(AllegroFlare::Camera3D* current_camera);
      std::vector<AllegroFlare::Camera3D> get_cameras() const;
      AllegroFlare::Camera3D* get_current_camera() const;
      bool get_initialized() const;
      void initialize();
      void update();
      void setup_projection_on_live_camera();
      void setup_projection_on_hud_camera();
      void set_current_camera_to_next_camera();
      void set_current_camera_to_previous_camera();
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
      std::string build_json_dump();
      void load_json(std::string json_string="[unset-json_string]");
   };
}



