
#include <gtest/gtest.h>

#include <Timeline/JSONLoaders/Timeline/Keyframe.hpp>
#include <Timeline/Testing/Comparison/Timeline/Keyframe.hpp>


TEST(Timeline_JSONLoaders_Timeline_KeyframeTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   Timeline::Keyframe keyframe;
   nlohmann::json j = keyframe;

   std::string expected_values =
R"({
  "focused": false,
  "time": 0.0,
  "value": 0.0
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(Timeline_JSONLoaders_Timeline_KeyframeTest,
   from_json__loads_json_data_into_the_object)
{
   Timeline::Keyframe keyframe;

   std::string json =
R"({
  "focused": false,
  "time": 1.25,
  "value": 0.75
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(keyframe);

   Timeline::Keyframe expected;
   expected.focused = false;
   expected.time = 1.25;
   expected.value = 0.75;

   EXPECT_EQ(expected, keyframe);
}



