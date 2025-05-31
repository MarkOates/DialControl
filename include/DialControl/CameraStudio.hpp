#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <allegro5/allegro.h>
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
      std::vector<AllegroFlare::Camera3D> &get_cameras_ref();
      int &get_current_camera_idx_ref();
      AllegroFlare::Camera3D &get_live_camera_ref();
      AllegroFlare::Camera2D &get_hud_camera_ref();
      void initialize();
      void update();
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
   };
}



