
#include <gtest/gtest.h>

#include <DialControl/CameraStudio.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/JSONLoaders/AllegroFlare/Camera3D.hpp>


class DialControl_CameraStudioTest : public ::testing::Test {};
class DialControl_CameraStudioTest_WithInteractionFixture : public AllegroFlare::Testing::WithInteractionFixture {};


const std::string cameras_json_string = R"({
  "cameras": [
    {
      "far_plane": 100.0,
      "near_plane": 0.10000000149011612,
      "position": {
        "x": -2.25,
        "y": 0.0,
        "z": 0.5
      },
      "roll": 0.0,
      "spin": 0.625,
      "stepout": {
        "x": 0.75,
        "y": 0.75,
        "z": 7.0
      },
      "tilt": 0.5,
      "zoom": 1.625
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.10000000149011612,
      "position": {
        "x": -1.5,
        "y": 0.0,
        "z": -0.25
      },
      "roll": 0.0,
      "spin": 0.0,
      "stepout": {
        "x": 1.5,
        "y": 0.75,
        "z": 14.0
      },
      "tilt": 0.0,
      "zoom": 3.25
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.10000000149011612,
      "position": {
        "x": -1.5,
        "y": 0.0,
        "z": 0.5
      },
      "roll": 0.0,
      "spin": 0.0,
      "stepout": {
        "x": 1.5,
        "y": 0.75,
        "z": 92.0
      },
      "tilt": 0.5,
      "zoom": 22.75
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.10000000149011612,
      "position": {
        "x": 0.0,
        "y": 0.0,
        "z": 0.0
      },
      "roll": 0.0,
      "spin": 0.5,
      "stepout": {
        "x": 1.25,
        "y": 0.75,
        "z": 3.0
      },
      "tilt": 0.25,
      "zoom": 1.875
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.10000000149011612,
      "position": {
        "x": -1.25,
        "y": 0.0,
        "z": 0.0
      },
      "roll": 0.0,
      "spin": -0.625,
      "stepout": {
        "x": 1.25,
        "y": 0.25,
        "z": 3.0
      },
      "tilt": 0.125,
      "zoom": 2.75
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.10000000149011612,
      "position": {
        "x": -2.0,
        "y": 0.0,
        "z": 0.5
      },
      "roll": 0.0,
      "spin": 0.875,
      "stepout": {
        "x": 0.25,
        "y": 1.5,
        "z": 51.0
      },
      "tilt": 0.625,
      "zoom": 8.75
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
   AllegroFlare::Model3D *model = model_bin.auto_get("simple_scene-02.obj");
   model->texture = get_bitmap_bin_ref().auto_get("simple_scene-02.png");

   DialControl::CameraStudio camera_studio;
   camera_studio.initialize();

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            // Update the camera_studio
            camera_studio.update();

            // == Draw ==
            clear();

            // Draw the 3D scene
            camera_studio.setup_projection_on_live_camera();
            model->draw();

            // Draw the HUD
            camera_studio.setup_projection_on_hud_camera();

            // Draw the interactive render
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
               case ALLEGRO_KEY_X: // X for "export"?
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


