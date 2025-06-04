
#include <gtest/gtest.h>

#include <Timeline/Testing/Comparison/Timeline/Parameter.hpp>


TEST(Timeline_Testing_Comparison_Timeline_ParameterTest,
   PrintTo__with_an_AllegroFlare_Parameter__with_default_values__will_output_as_expected)
{
   std::stringstream ss;
   Timeline::Parameter parameter;

   PrintTo(parameter, &ss);

   std::string expected_output =
R"(Parameter(
   name: "[unset-name]",
   has_min_value: 1,
   has_max_value: 1,
   min_value: 0,
   max_value: 1,
   parameter: 0x0,
   initial_value: 0,
   keyframes: []
))";
   //std::string expected_output = "Parameter(0.1, 0.2)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(Timeline_Testing_Comparison_Timeline_ParameterTest,
   PrintTo__with_an_AllegroFlare_Parameter__with_non_default_values__will_output_as_expected)
{
   std::stringstream ss;
   Timeline::Parameter parameter; //= {0.1, 0.2};
   parameter.name = "position.x";
   parameter.initial_value = 256.0f;
   parameter.keyframes = {
      Timeline::Keyframe::construct(2.0, 0.4),
      Timeline::Keyframe::construct(4.0, 0.8),
   };

   PrintTo(parameter, &ss);

   std::string expected_output =
R"(Parameter(
   name: "position.x",
   has_min_value: 1,
   has_max_value: 1,
   min_value: 0,
   max_value: 1,
   parameter: 0x0,
   initial_value: 256,
   keyframes: [
      Keyframe(
   time: 2,
   value: 0.4,
   focused: 0,
),
      Keyframe(
   time: 4,
   value: 0.8,
   focused: 0,
),
   ]
))";
   //std::string expected_output = "Parameter(0.1, 0.2)";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(Timeline_Testing_Comparison_Timeline_ParameterTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   Timeline::Parameter object;
   Timeline::Parameter other_object;

   EXPECT_EQ(object, other_object);
}


