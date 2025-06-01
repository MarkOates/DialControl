#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <string>


namespace DialControl
{
   class CameraInfo
   {
   private:

   protected:


   public:
      std::string name;
      AllegroFlare::Camera3D camera;
      bool position_tracks_a_target;
      void* object_being_tracked;
      CameraInfo();
      ~CameraInfo();

   };
}



