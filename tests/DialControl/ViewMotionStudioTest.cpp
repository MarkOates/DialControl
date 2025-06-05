
#include <gtest/gtest.h>

#include <DialControl/ViewMotionStudio.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/ModelBin.hpp>


class DialControl_ViewMotionStudioTestWithInteractionFixture : public AllegroFlare::Testing::WithInteractionFixture {};


TEST(DialControl_ViewMotionStudioTest, can_be_created_without_blowing_up)
{
   DialControl::ViewMotionStudio view_motion_studio;
}





const std::string cameras_json_string = R"({
  "cameras": [
    {
      "far_plane": 100.0,
      "near_plane": 1.0,
      "position": {
        "x": 0.0,
        "y": 0.0,
        "z": 0.0
      },
      "roll": 0.0,
      "roll_in_unit_values": true,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": true,
      "stepout": {
        "x": 0.0,
        "y": 0.0,
        "z": 16.0
      },
      "tilt": 0.0,
      "tilt_in_unit_values": true,
      "zoom": 1.0
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
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.5,
        "y": 0.75,
        "z": 14.0
      },
      "tilt": 0.0,
      "tilt_in_unit_values": false,
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
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.5,
        "y": 0.75,
        "z": 92.0
      },
      "tilt": 0.5,
      "tilt_in_unit_values": false,
      "zoom": 22.75
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.125,
      "position": {
        "x": 0.0,
        "y": 0.0,
        "z": 0.0
      },
      "roll": 0.0,
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.5,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.25,
        "y": 0.75,
        "z": 3.0
      },
      "tilt": 0.25,
      "tilt_in_unit_values": false,
      "zoom": 1.875
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.125,
      "position": {
        "x": -1.25,
        "y": 0.0,
        "z": 0.0
      },
      "roll": 0.0,
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": -0.625,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.25,
        "y": 0.25,
        "z": 3.0
      },
      "tilt": 0.125,
      "tilt_in_unit_values": false,
      "zoom": 2.75
    },
    {
      "far_plane": 100.0,
      "near_plane": 1.0,
      "position": {
        "x": 0.0,
        "y": 0.0,
        "z": -1.0
      },
      "roll": 0.0,
      "roll_in_unit_values": true,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": true,
      "stepout": {
        "x": 0.0,
        "y": 0.0,
        "z": 20.0
      },
      "tilt": 0.09375,
      "tilt_in_unit_values": true,
      "zoom": 4.0
    }
  ],
  "parameters": [
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "position.x"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "position.y"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "position.z"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "stepout.x"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "stepout.y"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 16.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "stepout.z"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [
        {
          "focused": false,
          "time": 1.0833332538604736,
          "value": -0.20000001788139343
        },
        {
          "focused": false,
          "time": 2.51666522026062,
          "value": 0.0
        }
      ],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "spin"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [
        {
          "focused": false,
          "time": 1.0166652202606201,
          "value": 0.10000000149011612
        },
        {
          "focused": false,
          "time": 3.149996519088745,
          "value": 0.0
        }
      ],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "tilt"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "roll"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 1.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "zoom"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "shift.x"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "shift.y"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 1.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "near plane"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 100.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "far plane"
    }
  ]
})";





const std::string cameras_json_string_x = R"({
  "cameras": [
    {
      "far_plane": 200.0,
      "near_plane": 0.01,
      "position": {
        "x": -2.25,
        "y": 0.0,
        "z": 0.5
      },
      "roll": 0.0,
      "roll_in_unit_values": true,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.125,
      "spin_in_unit_values": true,
      "stepout": {
        "x": 0.75,
        "y": 0.75,
        "z": 7.0
      },
      "tilt": 0.125,
      "tilt_in_unit_values": true,
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
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.5,
        "y": 0.75,
        "z": 14.0
      },
      "tilt": 0.0,
      "tilt_in_unit_values": false,
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
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.5,
        "y": 0.75,
        "z": 92.0
      },
      "tilt": 0.5,
      "tilt_in_unit_values": false,
      "zoom": 22.75
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.125,
      "position": {
        "x": 0.0,
        "y": 0.0,
        "z": 0.0
      },
      "roll": 0.0,
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.5,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.25,
        "y": 0.75,
        "z": 3.0
      },
      "tilt": 0.25,
      "tilt_in_unit_values": false,
      "zoom": 1.875
    },
    {
      "far_plane": 100.0,
      "near_plane": 0.125,
      "position": {
        "x": -1.25,
        "y": 0.0,
        "z": 0.0
      },
      "roll": 0.0,
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": -0.625,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.25,
        "y": 0.25,
        "z": 3.0
      },
      "tilt": 0.125,
      "tilt_in_unit_values": false,
      "zoom": 2.75
    },
    {
      "far_plane": 100.0,
      "near_plane": 1.0,
      "position": {
        "x": 0.0,
        "y": 0.0,
        "z": -1.0
      },
      "roll": 0.0,
      "roll_in_unit_values": true,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": true,
      "stepout": {
        "x": 0.0,
        "y": 0.0,
        "z": 20.0
      },
      "tilt": 0.09375,
      "tilt_in_unit_values": true,
      "zoom": 4.0
    }
  ],
  "parameters": [
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "position.x"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "position.y"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "position.z"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "stepout.x"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "stepout.y"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 16.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "stepout.z"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "spin"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "tilt"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "roll"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 1.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "zoom"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "shift.x"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 0.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "shift.y"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 1.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "near plane"
    },
    {
      "has_max_value": false,
      "has_min_value": false,
      "initial_value": 100.0,
      "keyframes": [],
      "max_value": 1.0,
      "min_value": 0.0,
      "name": "far plane"
    }
  ]
})";





TEST_F(DialControl_ViewMotionStudioTestWithInteractionFixture,
   CAPTURE__will_work_with_the_expected_context_for_placement3d)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_data_folder_path() + "models");
   AllegroFlare::Model3D *model = model_bin.auto_get("simple_scene-03.obj");
   model->texture = get_bitmap_bin_ref().auto_get("simple_scene-03.png");

   DialControl::ViewMotionStudio view_motion_studio;
   view_motion_studio.set_font_bin(&get_font_bin_ref());
   view_motion_studio.initialize();
   view_motion_studio.load_json(cameras_json_string); // Load some test data
   //view_motion_studio.get_camera_studio_ref().load_json(cameras_json_string); // Load some test data

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            // Update
            view_motion_studio.update();

            // Render
            clear();

            // Render the scene
            view_motion_studio.setup_camera_projection_on_live_camera();
            model->draw();

            // Render the hud
            view_motion_studio.render_hud();

            // Render the test status
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
         case ALLEGRO_EVENT_KEY_DOWN:
         {
            view_motion_studio.on_key_down(&current_event);
         }
         break;
      }
   }
}



/*
TEST_F(Timeline_MotionStudioTestWithInteractionFixture,
   CAPTURE__will_work_with_the_expected_context_for_placement3d)
{
   AllegroFlare::Placement3D placement;
   Timeline::MotionStudio motion_studio;
   AllegroFlare::Placement2D &timeline_placement = motion_studio.get_timeline_placement_ref();
   timeline_placement.position.x = 300;
   timeline_placement.position.y = 700;

   MusicElements music_elements;

   //motion_studio.set_parameters(build_parameters_for_music_elements(music_elements));
   motion_studio.set_parameters(build_parameters_for_placement3D(placement));
   motion_studio.set_parameter_views(
         build_parameter_views_for_parameters(
            &get_font_bin_ref(),
            &motion_studio.get_parameters_ref()
         )
      );


   //build_scenario(motion_studio, &get_font_bin_ref(), placement);
   //Timeline::ParameterView parameter_view(&get_font_bin_ref(), "position.x", &parameter);
   //motion_studio.set_parameter_views({
      //parameter_view
   //});

   while(interactive_test_wait_for_event())
   {
      ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            // Update
            motion_studio.update_playback();

            // Render
            clear();
            motion_studio.render();
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
         case ALLEGRO_EVENT_KEY_DOWN:
         {
            motion_studio.on_key_down(&current_event);
            //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            //switch(current_event.keyboard.keycode)
            //{
               //case ALLEGRO_KEY_ENTER:
                  //// Do something
               //break;
            //}
         }
         break;
      }
   }
}




class DialControl_CameraStudioTest : public ::testing::Test {};
class DialControl_CameraStudioTest_WithInteractionFixture : public AllegroFlare::Testing::WithInteractionFixture {};


const std::string cameras_json_string = R"({
  "cameras": [
    {
      "far_plane": 200.0,
      "near_plane": 0.01,
      "position": {
        "x": -2.25,
        "y": 0.0,
        "z": 0.5
      },
      "roll": 0.0,
      "roll_in_unit_values": true,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.125,
      "spin_in_unit_values": true,
      "stepout": {
        "x": 0.75,
        "y": 0.75,
        "z": 7.0
      },
      "tilt": 0.125,
      "tilt_in_unit_values": true,
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
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.5,
        "y": 0.75,
        "z": 14.0
      },
      "tilt": 0.0,
      "tilt_in_unit_values": false,
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
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.5,
        "y": 0.75,
        "z": 92.0
      },
      "tilt": 0.5,
      "tilt_in_unit_values": false,
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
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.5,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.25,
        "y": 0.75,
        "z": 3.0
      },
      "tilt": 0.25,
      "tilt_in_unit_values": false,
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
      "roll_in_unit_values": false,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": -0.625,
      "spin_in_unit_values": false,
      "stepout": {
        "x": 1.25,
        "y": 0.25,
        "z": 3.0
      },
      "tilt": 0.125,
      "tilt_in_unit_values": false,
      "zoom": 2.75
    },
    {
      "far_plane": 100.0,
      "near_plane": 1.0,
      "position": {
        "x": 0.0,
        "y": 0.0,
        "z": -1.0
      },
      "roll": 0.0,
      "roll_in_unit_values": true,
      "shift": {
        "x": 0.0,
        "y": 0.0
      },
      "spin": 0.0,
      "spin_in_unit_values": true,
      "stepout": {
        "x": 0.0,
        "y": 0.0,
        "z": 20.0
      },
      "tilt": 0.09375,
      "tilt_in_unit_values": true,
      "zoom": 4.0
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
   AllegroFlare::Model3D *model = model_bin.auto_get("simple_scene-03.obj");
   model->texture = get_bitmap_bin_ref().auto_get("simple_scene-03.png");

   DialControl::CameraStudio camera_studio;
   camera_studio.set_font_bin(&get_font_bin_ref());
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
            camera_studio.draw_camera_info_overlay();

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
               //case ALLEGRO_KEY_L:
               //{
                  //camera_studio.load_json(cameras_json_string); // BROKEN. TODO: Fix
               //} break;
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
*/


/*
      AllegroFlare::KeyboardCommandMapper mapper;
    body_dependency_symbols:
      - AllegroFlare::KeyboardCommandMapper
  - symbol: AllegroFlare::KeyboardCommandMapper
    headers: [ AllegroFlare/KeyboardCommandMapper.hpp ]
*/



/*


      draw_pill(1920/2 - 885, y+1080/2 + spac*4,       200, 48, 80.0, 8.0, "spin", w, tos(camera->spin));
  - name: draw_pill
    type: void
    parameters:
      - name: x
        type: float
        default_argument: 0.0f
      - name: y
        type: float
        default_argument: 0.0f
      - name: w
        type: float
        default_argument: 300.0f
      - name: h
        type: float
        default_argument: 50.0f
      - name: column_divider_pos
        type: float
        default_argument: 100.0f
      - name: column_divider_padding
        type: float
        default_argument: 6.0f
      - name: label
        type: std::string
        default_argument: '"[unset-label]"'
      - name: label_color
        type: ALLEGRO_COLOR
        default_argument: ALLEGRO_COLOR{1, 1, 1, 1}
      - name: value
        type: std::string
        default_argument: '"[unset-value]"'
      - name: value_color
        type: ALLEGRO_COLOR
        default_argument: ALLEGRO_COLOR{1, 1, 1, 1}
    body: |
      //float x = 1920/2;
      //float y = 1080/3;
      ALLEGRO_FONT *font = obtain_font();
      ALLEGRO_FONT *bold_font = obtain_bold_font();
      //float text_width = al_get_text_width(font, quote.c_str());
      //float text_height = al_get_font_line_height(font);
      float h_text_width = w/2;
      float h_text_height = h/2;
      //AllegroFlare::Vec2D padding = {30, 20};
      float h_line_height = al_get_font_line_height(font) / 2;
      //float h_line_height = 

      al_draw_filled_rounded_rectangle(
         x, // - padding.x,
         y, // - padding.y,
         x+w, // + padding.x,
         y+h, // + padding.y,
         8.0f,
         8.0f,
         ALLEGRO_COLOR{0, 0, 0, 1}
         //2.0f
      );

      al_draw_text(
         bold_font,
         label_color,
         x+column_divider_pos-column_divider_padding, y+h_text_height-h_line_height,
         ALLEGRO_ALIGN_RIGHT,
         label.c_str()
      );

      al_draw_text(
         font,
         value_color, //ALLEGRO_COLOR{1, 1, 1, 1},
         x+column_divider_pos+column_divider_padding, y+h_text_height-h_line_height,
         ALLEGRO_ALIGN_LEFT,
         value.c_str()
      );

      //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-h_text_height, ALLEGRO_ALIGN_LEFT, quote.c_str());
      return;
    body_dependency_symbols:
      - AllegroFlare::Vec2D
      - al_draw_rounded_rectangle
      - al_draw_text




*/

