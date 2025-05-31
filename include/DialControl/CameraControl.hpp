#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <allegro5/allegro.h>


namespace DialControl
{
   class CameraControl
   {
   private:
      AllegroFlare::Camera3D* camera;

   protected:


   public:
      CameraControl();
      ~CameraControl();

      void set_camera(AllegroFlare::Camera3D* camera);
      AllegroFlare::Camera3D* get_camera() const;
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
   };
}



