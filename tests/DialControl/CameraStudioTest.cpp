
#include <gtest/gtest.h>

#include <DialControl/CameraStudio.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera3D.hpp>


class DialControl_CameraStudioTest : public ::testing::Test {};
class DialControl_CameraStudioTest_WithInteractionFixture : public AllegroFlare::Testing::WithInteractionFixture {};


const std::string cameras_json_string = R"({
  "cameras": [
    {
      "position": { "x": 0.0, "y": 0.0, "z": 0.0 },
      "stepout": { "x": 0.0, "y": 1.0, "z": 10.0 },
      "spin": 1.5,
      "tilt": 0.0,
      "zoom": 1.0
    },
    {
      "position": { "x": 1.0, "y": 0.0, "z": 0.0 },
      "stepout": { "x": 0.5, "y": 0.0, "z": 4.5 },
      "spin": 2.5,
      "tilt": 1.0,
      "zoom": 2.0
    },
    {
      "position": { "x": 1.0, "y": 0.0, "z": 0.0 },
      "stepout": { "x": 1.0, "y": 1.0, "z": 8.0 },
      "spin": 3.5,
      "tilt": 2.0,
      "zoom": 3.0
    },
    {
      "position": { "x": 1.0, "y": 0.0, "z": 0.0 },
      "stepout": { "x": 1.0, "y": 1.0, "z": 20.0 },
      "spin": 4.5,
      "tilt": 3.0,
      "zoom": 2.5
    },
    {
      "position": { "x": 1.0, "y": 0.0, "z": 0.0 },
      "stepout": { "x": 2.0, "y": 2.0, "z": 24.0 },
      "spin": 5.5,
      "tilt": 4.0,
      "zoom": 1.0
    },
    {
      "position": { "x": 1.0, "y": 0.0, "z": 0.0 },
      "stepout": { "x": 2.0, "y": 2.0, "z": 20.0 },
      "spin": 0.5,
      "tilt": 5.0,
      "zoom": 2.0
    }
  ]
})";


TEST(DialControl_CameraStudioTest, can_be_created_without_blowing_up)
{
   DialControl::CameraStudio camera_studio;
}


TEST_F(DialControl_CameraStudioTest_WithInteractionFixture, INTERACTIVE__will_work_as_expected)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_data_path() + "models");
   AllegroFlare::Model3D *model = model_bin.auto_get("centered_unit_cube-02.obj");

   DialControl::CameraStudio camera_studio;
   camera_studio.initialize();

   AllegroFlare::Camera2D &hud_camera = camera_studio.get_hud_camera_ref();

   std::vector<AllegroFlare::Camera3D> &cameras = camera_studio.get_cameras_ref();
   //std::map<std::string, AllegroFlare::Camera3D> cameras;

   //AllegroFlare::Camera3D baseline_camera;
   //baseline_camera.stepout = { 0, 0, 16 };
   //baseline_camera.zoom = 1.0; //1.62;
   //baseline_camera.tilt = 0.0; //ALLEGRO_PI * 0.25;
   //baseline_camera.spin = 0.125;
   //baseline_camera.position = { 0, 0, 0 };

   AllegroFlare::Camera3D *current_camera = nullptr;
   AllegroFlare::Camera3D &live_camera = camera_studio.get_live_camera_ref();
   //live_camera = baseline_camera;

   //cameras.resize(6);
   int &current_camera_idx = camera_studio.get_current_camera_idx_ref();
   //for (int i=0; i<cameras.size(); i++)
   //{
      //cameras[i] = baseline_camera;
   //}
   //current_camera = &cameras[current_camera_idx];

   //DialControl::CameraStudio camera_studio;
   //camera_studio.set_current_camera(current_camera);

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear();

            // Draw the 3D scene
            camera_studio.update();
            //live_camera.blend(current_camera, 0.1);

            live_camera.setup_projection_on(al_get_target_bitmap());
            model->draw();

            // Draw the HUD
            hud_camera.setup_dimensional_projection(al_get_target_bitmap());
            interactive_test_render_status();
            al_flip_display();
         }
         break;

         case ALLEGRO_EVENT_KEY_DOWN:
         {
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_N:
               {
                  camera_studio.set_current_camera_to_next_camera();
               } break;
               case ALLEGRO_KEY_P:
               {
                  camera_studio.set_current_camera_to_previous_camera();
               } break;
               case ALLEGRO_KEY_D:
               {
                  std::cout << camera_studio.build_json_dump() << std::endl;
               } break;
               case ALLEGRO_KEY_L:
               {
                  camera_studio.load_json(cameras_json_string); // BROKEN. TODO: Fix
               } break;
               default:
               {
                  camera_studio.on_key_down(&current_event);
               } break;
            }
            //else
            //camera_control.on_key_down(&current_event);
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            //switch(current_event.keyboard.keycode)
            //{
               //case ALLEGRO_KEY_ENTER:
                  // Do something
               //break;
            //}
         }
         break;
      }
   }
}


