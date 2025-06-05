
#include <gtest/gtest.h>

#include <Timeline/MotionStudio.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/Placement3D.hpp>


class Timeline_MotionStudioTestWithInteractionFixture : public AllegroFlare::Testing::WithInteractionFixture {};




std::vector<Timeline::Parameter> build_parameters_for_placement3D(AllegroFlare::Placement3D &p)
{
   std::vector<Timeline::Parameter> result = {
      Timeline::Parameter::build("position.x", &p.position.x, {
         Timeline::Keyframe::construct(2.0, 0.4),
         Timeline::Keyframe::construct(4.0, 0.6),
         Timeline::Keyframe::construct(5.0, 0.2),
         Timeline::Keyframe::construct(5.5, 0.3),
      }),
      Timeline::Parameter::build("position.y", &p.position.y, {
         Timeline::Keyframe::construct(2.0, 0.4),
         Timeline::Keyframe::construct(4.0, 0.6),
         Timeline::Keyframe::construct(5.0, 0.2),
         Timeline::Keyframe::construct(5.5, 0.3),
      }),
      Timeline::Parameter::build("position.z", &p.position.z, {
         Timeline::Keyframe::construct(2.0, 0.4),
         Timeline::Keyframe::construct(4.0, 0.6),
         Timeline::Keyframe::construct(5.0, 0.2),
         Timeline::Keyframe::construct(5.5, 0.3),
      }),
      Timeline::Parameter::build("rotation.x", &p.position.y, {
      }),
      Timeline::Parameter::build("rotation.y", &p.position.z, {
      }),
      Timeline::Parameter::build("rotation.z", &p.position.y, {
      }),
   };

   return result;
}



static struct MusicElements
{
   float volume = 0.8f;
   float mod = 0.8f;
};


std::vector<Timeline::Parameter> build_parameters_for_music_elements(MusicElements &p)
{
   std::vector<Timeline::Parameter> result = {
      Timeline::Parameter::build("volume", &p.volume, {
         Timeline::Keyframe::construct(2.0, 0.4),
         Timeline::Keyframe::construct(4.0, 0.6),
         Timeline::Keyframe::construct(5.0, 0.2),
         Timeline::Keyframe::construct(5.5, 0.3),
      }),
      Timeline::Parameter::build("mod", &p.mod, {
         Timeline::Keyframe::construct(2.0, 0.4),
         Timeline::Keyframe::construct(4.0, 0.6),
         Timeline::Keyframe::construct(5.0, 0.2),
         Timeline::Keyframe::construct(5.5, 0.3),
      }),
   };

   return result;
}



/*
std::vector<Timeline::ParameterView> build_parameter_views_for_parameters(
   AllegroFlare::FontBin *font_bin, 
   std::vector<Timeline::Parameter> *p,
   float height=Timeline::ParameterView::DEFAULT_HEIGHT
)
{
   std::vector<Timeline::ParameterView> result;
   int x = 400;
   int y = 100;
   //int yd = 100;
   int i = 0;
   //float height = Timeline::ParameterView::DEFAULT_HEIGHT;
   //int yd = height;
   for (auto &pp : *p)
   {
      result.push_back(Timeline::ParameterView(font_bin, pp.name, &pp));
      result.back().set_height(height);
      i++;
   }
   return result;
}
*/




void build_scenario(Timeline::MotionStudio &motion_studio, AllegroFlare::FontBin *font_bin, AllegroFlare::Placement3D &p)
{
   //Timeline::ParameterView parameter_view(font_bin, "position.x", &parameter);

   //Timeline::Parameter parameter = Timeline::Parameter::build();
   //motion_studio.set_parameter_views({
      //Timeline::Parameter::build()
   //});
   //Timeline::Parameter parameter;
}


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
         motion_studio.build_parameter_views_for_parameters(
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


TEST_F(Timeline_MotionStudioTestWithInteractionFixture,
   CAPTURE__will_work_with_the_expected_context_for_MusicElements)
{
   AllegroFlare::Placement3D placement;
   Timeline::MotionStudio motion_studio;
   AllegroFlare::Placement2D &timeline_placement = motion_studio.get_timeline_placement_ref();
   timeline_placement.position.x = 300;
   timeline_placement.position.y = 700;

   MusicElements music_elements;

   motion_studio.set_parameters(build_parameters_for_music_elements(music_elements));
   //motion_studio.set_parameters(build_parameters_for_placement3D(placement));
   motion_studio.set_parameter_views(
         motion_studio.build_parameter_views_for_parameters(
            &get_font_bin_ref(),
            &motion_studio.get_parameters_ref(),
            120
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


