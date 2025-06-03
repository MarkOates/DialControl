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
   camera.position = { 20, 5, 16 };
   camera.stepout = { 0, 2, 12 };
   camera.tilt = 0.125;
   camera.spin = 0.0;
   //camera.spin = 0.25;
   camera.roll = 0.0;
   camera.zoom = 1.2;
   camera.near_plane = 0.125;
   camera.far_plane = 2000;

   clear_neutral();
   DialControl::CameraInfoOverlay camera_info_overlay(&get_font_bin_ref(), &camera);
   camera_info_overlay.set_camera_name("Camera A");

   camera_info_overlay.render();
   al_flip_display();
   sleep_for(1);
}



void draw_circular_diagram(float cx, float cy, float d, int t, float l,
                           float line_thickness, bool draw_center_line)
{
   float radius = d / 2.0f;

   // Draw main circle
   al_draw_circle(cx, cy, radius, al_map_rgb(255, 255, 255), line_thickness);

   // Draw ticks
   float tick_alignment = 0.5;
   for (int i = 0; i < t; ++i)
   {
      float angle = ALLEGRO_PI * 2.0f * i / t;
      float x1 = cx + std::cos(angle) * radius;
      float y1 = cy + std::sin(angle) * radius;
      float x2 = cx + std::cos(angle) * (radius - l);
      float y2 = cy + std::sin(angle) * (radius - l);

      al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 255, 255), line_thickness);
   }

   // Draw center horizontal line if requested
   if (draw_center_line)
   {
      float x1 = cx - radius;
      float x2 = cx + radius;
      float y = cy;

      al_draw_line(x1, y, x2, y, al_map_rgb(255, 255, 255), line_thickness);
   }
}


void draw_radial_ticks(float cx, float cy, float r, int t, float l,
                       int s, int o, float line_thickness)
{
   for (int i = 0; i < t; ++i)
   {
      // Determine whether to skip this tick
      if (s > 0 && ((i + o) % s == 0))
      {
         continue;
      }

      float angle = ALLEGRO_PI * 2.0f * i / t;

      float x1 = cx + std::cos(angle) * r;
      float y1 = cy + std::sin(angle) * r;
      float x2 = cx + std::cos(angle) * (r + l);
      float y2 = cy + std::sin(angle) * (r + l);

      al_draw_line(x1, y1, x2, y2, al_map_rgb(255, 255, 255), line_thickness);
   }
}



void draw_clockwise_radial_line(float cx, float cy, float r,
                                float v, float t, ALLEGRO_COLOR c)
{
   // Ensure v is within [0.0, 1.0]
   float normalized_v = fmodf(v, 1.0f);
   if (normalized_v < 0.0f)
   {
      normalized_v += 1.0f;
   }

   // Convert to clockwise angle (Allegro uses counter-clockwise by default)
   float angle = ALLEGRO_PI * 2.0f * normalized_v;

   float x2 = cx + std::cos(angle) * r;
   float y2 = cy + std::sin(angle) * r;

   al_draw_line(cx, cy, x2, y2, c, t);
}



void draw_circular_rotation_diagram_notched(float x, float y, float radius, float value)
{
   draw_radial_ticks(x, y, radius, 32, 3, 4, 0, 2.0);

   // midminor ticks (8)
   draw_radial_ticks(x, y, radius, 8, 10, 2, 0, 2.0);


   draw_radial_ticks(x, y, radius, 4, 10, 0, 0, 2.0);


   draw_clockwise_radial_line(x, y, radius - 3, value, 6.0, ALLEGRO_COLOR{1, 1, 1, 1});

}



float get_leftmost_position(
      int n,
      float spacing
){
   float total_width = (n - 1) * spacing;
   float leftmost_x = (total_width / 2);
   return leftmost_x;
}



void draw_rotating_triangle_toward_center(float x, float y, float l,
                                          float d, float v,
                                          ALLEGRO_COLOR c)
{
   // Normalize v to [0.0, 1.0]
   float normalized_v = fmodf(v, 1.0f);
   if (normalized_v < 0.0f)
   {
      normalized_v += 1.0f;
   }

   // Compute angle of the triangle's base center (clockwise)
   float angle = ALLEGRO_PI * 2.0f * normalized_v;

   // Compute triangle center point (apex, pointing toward the center)
   float tx = x + std::cos(angle) * d;
   float ty = y + std::sin(angle) * d;

   // Angle pointing toward the center
   float pointing_angle = angle + ALLEGRO_PI; // flip direction

   // Compute triangle points
   float half_base = l / 2.0f;
   float height = (std::sqrt(3.0f) / 2.0f) * l;

   // Apex (pointing toward center)
   float apex_x = tx + std::cos(pointing_angle) * height;
   float apex_y = ty + std::sin(pointing_angle) * height;

   // Base corners
   float base_angle = pointing_angle + ALLEGRO_PI / 2.0f;

   float base1_x = tx + std::cos(base_angle) * half_base;
   float base1_y = ty + std::sin(base_angle) * half_base;

   float base2_x = tx - std::cos(base_angle) * half_base;
   float base2_y = ty - std::sin(base_angle) * half_base;

   // Draw triangle
   //al_draw_triangle(apex_x, apex_y,
                    //base1_x, base1_y,
                    //base2_x, base2_y,
                    //c, thickness);
   al_draw_filled_triangle(apex_x, apex_y,
                    base1_x, base1_y,
                    base2_x, base2_y,
                    c );
}




TEST_F(DialControl_CameraInfoOverlayTestWithAllegroRenderingFixture, CAPTURE__draw_circle__will_work)
{
   //AllegroFlare::Camera3D camera;
   //camera.position = { 20, 5, 16 };
   //camera.stepout = { 0, 2, 12 };
   //camera.tilt = 0.125;
   //camera.spin = 0.25;
   //camera.roll = 0.0;
   //camera.zoom = 1.2;
   //camera.near_plane = 0.125;
   //camera.far_plane = 2000;

   clear();

   int objects = 5;
   float spacing = 400;
   float r = 150;

   float x = 1920/2 - get_leftmost_position(4, spacing);
   float y = 1080/2;

   int i=0;



   draw_circular_diagram(x+spacing*i++, y, r, 8, 10,
                              2.0, true);


   //void draw_radial_ticks(float cx, float cy, float r, int t, float l,
                          //int s, int o, float line_thickness)



   //draw_radial_ticks(x+spacing*i++, y, r, 16, 20,
                              //4, 0, 2.0);



   //draw_radial_ticks(x+spacing*i++, y, r, 16, 20,
                              //4, 0, 2.0);

   
   //draw_radial_ticks(x+spacing*i++, y, r, 16, 20,
                              //4, 0, 2.0);

   // minor ticks (32)
   //float radius = 30;
/*
   draw_radial_ticks(x+spacing*i, y, radius, 32, 3,
                              4, 0, 2.0);

   // midminor ticks (8)
   draw_radial_ticks(x+spacing*i, y, radius, 8, 10,
                              2, 0, 2.0);


   draw_radial_ticks(x+spacing*i, y, radius, 4, 10,
                              0, 0, 2.0);


   draw_clockwise_radial_line(x+spacing, y, radius - 3,
                                0.125/4, 6.0, ALLEGRO_COLOR{1, 1, 1, 1});

   i++;


   draw_clockwise_radial_line(x+spacing*i++, y, r,
                                0.0, 6.0, ALLEGRO_COLOR{1, 1, 1, 1});
*/



   draw_circular_rotation_diagram_notched(1920/2, 1080/4, 30, 0.125);


   //draw_circular_diagram(x+spacing*i++, y, r, 8, 10,
                              //2.0, true);

   i++;
   draw_rotating_triangle_toward_center(x+spacing*i, y, 30, 130, 0.25, ALLEGRO_COLOR{1, 1, 0.24, 1});
   draw_rotating_triangle_toward_center(x+spacing*i, y, 20, 100, 0.5, ALLEGRO_COLOR{1, 1, 1, 1});


//void draw_rotating_triangle_toward_center(float x, float y, float l,
                                          //float d, float v,
                                          //ALLEGRO_COLOR c, float thickness)


   //draw_radial_ticks(x+spacing*i++, y, 200, 16, 20,
                              //4, 0, 2.0);

   //draw_
   //DialControl::CameraInfoOverlay camera_info_overlay(&get_font_bin_ref(), &camera);
   //camera_info_overlay.set_camera_name("Camera A");

   //camera_info_overlay.render();
   al_flip_display();
   sleep_for(1);
}


