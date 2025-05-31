#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace DialControl
{
   class CameraStudio
   {
   private:
      AllegroFlare::Camera3D* camera;
      std::vector<AllegroFlare::Camera3D> cameras;

   protected:


   public:
      CameraStudio();
      ~CameraStudio();

      void set_camera(AllegroFlare::Camera3D* camera);
      void set_cameras(std::vector<AllegroFlare::Camera3D> cameras);
      AllegroFlare::Camera3D* get_camera() const;
      std::vector<AllegroFlare::Camera3D> get_cameras() const;
      std::vector<AllegroFlare::Camera3D> &get_cameras_ref();
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
   };
}



