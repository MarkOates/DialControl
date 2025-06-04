
#include <gtest/gtest.h>

#include <Timeline/Testing/Comparison/Timeline/Keyframe.hpp>


TEST(Timeline_Testing_Comparison_Timeline_KeyframeTest,
   PrintTo__with_an_AllegroFlare_Keyframe__will_output_as_expected)
{
   std::stringstream ss;
   Timeline::Keyframe object;
   object.time = 0.1;
   object.value = 0.2;

   PrintTo(object, &ss);

   std::string expected_output =
R"(Keyframe(
   time: 0.1,
   value: 0.2,
   focused: 0,
))";

   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(Timeline_Testing_Comparison_Timeline_KeyframeTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   Timeline::Keyframe object;
   Timeline::Keyframe other_object;

   EXPECT_EQ(object, other_object);
}


