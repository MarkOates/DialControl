
#include <gtest/gtest.h>

#include <DialControl/CameraControl.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera3D.hpp>


class DialControl_CameraControlTest : public ::testing::Test {};
class DialControl_CameraControlTest_WithInteractionFixture : public AllegroFlare::Testing::WithInteractionFixture {};


TEST(DialControl_CameraControlTest, can_be_created_without_blowing_up)
{
   DialControl::CameraControl camera_control;
}


TEST_F(DialControl_CameraControlTest_WithInteractionFixture, INTERACTIVE__will_work_as_expected)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_data_path() + "models");
   AllegroFlare::Model3D *model = model_bin.auto_get("centered_unit_cube-02.obj");

   AllegroFlare::Camera2D hud_camera;

   std::vector<AllegroFlare::Camera3D> cameras;
   //std::map<std::string, AllegroFlare::Camera3D> cameras;

   AllegroFlare::Camera3D baseline_camera;
   baseline_camera.stepout = { 0, 0, 16 };
   baseline_camera.zoom = 1.0; //1.62;
   baseline_camera.tilt = 0.0; //ALLEGRO_PI * 0.25;
   baseline_camera.spin = 0.125;
   baseline_camera.position = { 0, 0, 0 };

   AllegroFlare::Camera3D *current_camera = nullptr;
   AllegroFlare::Camera3D live_camera = baseline_camera;

   cameras.resize(6);
   int current_camera_idx = 0;
   for (int i=0; i<cameras.size(); i++)
   {
      cameras[i] = baseline_camera;
   }
   current_camera = &cameras[current_camera_idx];

   DialControl::CameraControl camera_control;
   camera_control.set_camera(current_camera);

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear();

            // Draw the 3D scene
            live_camera.blend(current_camera, 0.1);

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
                  // Next camera
                  int total_cameras = cameras.size();
                  current_camera_idx = (current_camera_idx + 1) % total_cameras;
                  current_camera = &cameras[current_camera_idx];
                  camera_control.set_camera(current_camera);
               } break;
               case ALLEGRO_KEY_P:
               {
                  // Previous camera
                  int total_cameras = cameras.size();
                  current_camera_idx = (current_camera_idx - 1 + total_cameras) % total_cameras;
                  current_camera = &cameras[current_camera_idx];
                  camera_control.set_camera(current_camera);
               } break;
               case ALLEGRO_KEY_D:
               {
                  // Dump cameras to JSON (just to terminal in this example)
                  nlohmann::json j;
                  j["cameras"] = cameras;
                  std::cout << j.dump(2) << std::endl;
               } break;
               default:
               {
                  camera_control.on_key_down(&current_event);
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


/*
TEST_F(TestClassFor_AllegroFlare_Testing_WithInteractionFixture, will_work_with_the_expected_context)
{
   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear();
            interactive_test_render_status();
            al_flip_display();
         }
         break;

         //// For example:
         //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
         //{
            //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                      //<< "Play sound effect event was emitted. "
                      //<< std::endl;
         //}
         //break;

         //// For example:
         //case ALLEGRO_EVENT_KEY_DOWN:
         //{
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            //switch(current_event.keyboard.keycode)
            //{
               //case ALLEGRO_KEY_ENTER:
                  //// Do something
               //break;
            //}
         //}
         //break;
      }
   }
}
*/


