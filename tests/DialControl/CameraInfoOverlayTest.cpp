#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <DialControl/CameraInfoOverlay.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class DialControl_CameraInfoOverlayTest : public ::testing::Test {};
class DialControl_CameraInfoOverlayTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(DialControl_CameraInfoOverlayTest, can_be_created_without_blowing_up)
{
   DialControl::CameraInfoOverlay camera_info_overlay;
}


/*
TEST_F(DialControl_CameraInfoOverlayTest, render__without_allegro_initialized__raises_an_error)
{
   DialControl::CameraInfoOverlay camera_info_overlay;
   std::string expected_error_message =
      "CameraInfoOverlay::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(camera_info_overlay.render(), std::runtime_error, expected_error_message);
}


TEST_F(DialControl_CameraInfoOverlayTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   DialControl::CameraInfoOverlay camera_info_overlay;
   std::string expected_error_message =
      "CameraInfoOverlay::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(camera_info_overlay.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(DialControl_CameraInfoOverlayTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   DialControl::CameraInfoOverlay camera_info_overlay;
   std::string expected_error_message =
      "CameraInfoOverlay::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(camera_info_overlay.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(DialControl_CameraInfoOverlayTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   DialControl::CameraInfoOverlay camera_info_overlay;
   std::string expected_error_message =
      "CameraInfoOverlay::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(camera_info_overlay.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   
*/


TEST_F(DialControl_CameraInfoOverlayTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Camera3D camera;
   clear_neutral();
   DialControl::CameraInfoOverlay camera_info_overlay(&get_font_bin_ref(), &camera);
   camera_info_overlay.render();
   al_flip_display();
   sleep_for(1);
}


