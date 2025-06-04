#pragma once


#include <AllegroFlare/Camera3D.hpp>
#include <Timeline/Parameter.hpp>
#include <vector>


namespace Timeline
{
   namespace ParameterMappings
   {
      namespace AllegroFlare
      {
         class Camera3D
         {
         private:

         protected:


         public:
            Camera3D();
            ~Camera3D();

            static std::vector<Timeline::Parameter> build_parameters(::AllegroFlare::Camera3D* camera=nullptr);
         };
      }
   }
}



