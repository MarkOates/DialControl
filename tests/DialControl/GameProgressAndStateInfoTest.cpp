
#include <gtest/gtest.h>

#include <DialControl/GameProgressAndStateInfo.hpp>


TEST(DialControl_GameProgressAndStateInfoTest, can_be_created_without_blowing_up)
{
   DialControl::GameProgressAndStateInfo game_progress_and_state_info;
}


TEST(DialControl_GameProgressAndStateInfoTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "DialControl/GameProgressAndStateInfo",
     DialControl::GameProgressAndStateInfo::TYPE
   );
}


TEST(DialControl_GameProgressAndStateInfoTest, type__has_the_expected_value_matching_TYPE)
{
   DialControl::GameProgressAndStateInfo game_progress_and_state_info;
   EXPECT_EQ(DialControl::GameProgressAndStateInfo::TYPE, game_progress_and_state_info.get_type());
}


