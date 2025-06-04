
#include <gtest/gtest.h>

#include <Timeline/JSONLoaders/Timeline/Parameter.hpp>
#include <Timeline/Testing/Comparison/Timeline/Parameter.hpp>


TEST(Timeline_JSONLoaders_Timeline_ParameterTest,
   to_json__with_default_values__returns_the_object_as_json_with_the_expected_values)
{
   Timeline::Parameter parameter;
   nlohmann::json j = parameter;

   std::string expected_values =
R"({
  "has_max_value": true,
  "has_min_value": true,
  "initial_value": 0.0,
  "keyframes": [],
  "max_value": 1.0,
  "min_value": 0.0,
  "name": "[unset-name]"
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(Timeline_JSONLoaders_Timeline_ParameterTest,
   to_json__with_non_default_values__returns_the_object_as_json_with_the_expected_values)
{
   Timeline::Parameter parameter;
   parameter.name = "position.x";
   parameter.initial_value = 256.0f;
   parameter.keyframes = {
      Timeline::Keyframe::construct(2.0, 0.25),
      Timeline::Keyframe::construct(4.0, 0.125),
   };

   nlohmann::json j = parameter;

   std::string expected_values =
R"({
  "has_max_value": true,
  "has_min_value": true,
  "initial_value": 256.0,
  "keyframes": [
    {
      "focused": false,
      "time": 2.0,
      "value": 0.25
    },
    {
      "focused": false,
      "time": 4.0,
      "value": 0.125
    }
  ],
  "max_value": 1.0,
  "min_value": 0.0,
  "name": "position.x"
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(Timeline_JSONLoaders_Timeline_ParameterTest,
   from_json__loads_json_data_into_the_object)
{
   Timeline::Parameter parameter;

   std::string json =
R"({
  "initial_value": 256.0,
  "has_max_value": true,
  "has_min_value": true,
  "keyframes": [
    {
      "focused": false,
      "time": 2.0,
      "value": 0.25
    },
    {
      "focused": false,
      "time": 4.0,
      "value": 0.125
    }
  ],
  "max_value": 1.0,
  "min_value": 0.0,
  "name": "position.x"
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(parameter);

   Timeline::Parameter expected;
   expected.name = "position.x";
   expected.initial_value = 256.0f;
   expected.keyframes = {
      Timeline::Keyframe::construct(2.0, 0.25),
      Timeline::Keyframe::construct(4.0, 0.125),
   };

   EXPECT_EQ(expected, parameter);
}



