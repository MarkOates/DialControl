
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


