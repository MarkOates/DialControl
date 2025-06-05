
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class Timeline_ParameterViewTest : public ::testing::Test {};
class Timeline_ParameterViewTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


//#include <Timeline/Parameter.hpp>
#include <Timeline/ParameterView.hpp>


TEST_F(Timeline_ParameterViewTest, can_be_created_without_blowing_up)
{
   Timeline::ParameterView parameter;
}


TEST_F(Timeline_ParameterViewTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_track_as_expected)
{
   Timeline::Parameter parameter;
   Timeline::ParameterView parameter_view(&get_font_bin_ref(), "position.x", &parameter);
   AllegroFlare::Placement2D place = build_centered_placement(parameter_view.get_width(), parameter_view.get_height());
   parameter.keyframes = {
      Timeline::Keyframe::construct(2.0, 0.4),
      Timeline::Keyframe::construct(4.0, 0.6),
      Timeline::Keyframe::construct(5.0, 0.2),
      Timeline::Keyframe::construct(5.5, 0.3),
   };

   clear();
   place.start_transform();
   parameter_view.render();
   place.restore_transform();
   al_flip_display();
   sleep_for(1);
}


TEST_F(Timeline_ParameterViewTestWithAllegroRenderingFixture,
   CAPTURE__render__when_the_parameter_has_either_or_min_or_max_bounds__will_render_the_track_as_expected)
{
   Timeline::Parameter parameter;
   Timeline::ParameterView parameter_view(&get_font_bin_ref(), "position.x", &parameter);
   AllegroFlare::Placement2D place = build_centered_placement(parameter_view.get_width(), parameter_view.get_height());
   parameter.keyframes = {
      Timeline::Keyframe::construct(2.0, 0.4),
      Timeline::Keyframe::construct(4.0, 0.6),
      Timeline::Keyframe::construct(5.0, 0.2),
      Timeline::Keyframe::construct(5.5, 0.3),
   };
   parameter.has_max_value = false;
   parameter.has_min_value = false;

   clear();
   place.start_transform();
   parameter_view.render();
   place.restore_transform();
   al_flip_display();
   sleep_for(1);
}


TEST_F(Timeline_ParameterViewTestWithAllegroRenderingFixture,
   CAPTURE__render__with_start_x_at_non_zero__will_render_the_keyframes_offset_from_the_left)
{
   Timeline::Parameter parameter;
   Timeline::ParameterView parameter_view(&get_font_bin_ref(), "position.x", &parameter);
   AllegroFlare::Placement2D place = build_centered_placement(parameter_view.get_width(), parameter_view.get_height());
   parameter.keyframes = {
      Timeline::Keyframe::construct(2.0, 0.4),
      Timeline::Keyframe::construct(4.0, 0.6),
      Timeline::Keyframe::construct(5.0, 0.2),
      Timeline::Keyframe::construct(5.5, 0.3),
      Timeline::Keyframe::construct(10.5, 0.2),

      Timeline::Keyframe::construct(12.0, 0.2), // should not appear
   };
   parameter.has_max_value = false;
   parameter.has_min_value = false;

   // Customize the parameter view
   parameter_view.set_start_x(1.0);
   parameter_view.set_time_scale(2.0);

   clear();
   place.start_transform();
   parameter_view.render();
   place.restore_transform();
   al_flip_display();
   sleep_for(1);
}


