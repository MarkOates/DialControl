

#include <DialControl/CameraInfoOverlay.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdexcept>


namespace DialControl
{


CameraInfoOverlay::CameraInfoOverlay(AllegroFlare::FontBin* font_bin, AllegroFlare::Camera3D* camera, std::string camera_name, bool camera_is_tracking_object)
   : font_bin(font_bin)
   , camera(camera)
   , camera_name(camera_name)
   , camera_is_tracking_object(camera_is_tracking_object)
{
}


CameraInfoOverlay::~CameraInfoOverlay()
{
}


void CameraInfoOverlay::set_camera(AllegroFlare::Camera3D* camera)
{
   this->camera = camera;
}


void CameraInfoOverlay::set_camera_name(std::string camera_name)
{
   this->camera_name = camera_name;
}


void CameraInfoOverlay::set_camera_is_tracking_object(bool camera_is_tracking_object)
{
   this->camera_is_tracking_object = camera_is_tracking_object;
}


AllegroFlare::Camera3D* CameraInfoOverlay::get_camera() const
{
   return camera;
}


std::string CameraInfoOverlay::get_camera_name() const
{
   return camera_name;
}


bool CameraInfoOverlay::get_camera_is_tracking_object() const
{
   return camera_is_tracking_object;
}


std::string CameraInfoOverlay::tos(float f)
{
   std::stringstream ss;
   ss << f;
   return ss.str();
}

std::string CameraInfoOverlay::tosv(AllegroFlare::Vec3D v)
{
   std::stringstream ss;
   ss << "      " << v.x << "      " << v.y << "      " << v.z;
   return ss.str();
}

std::string CameraInfoOverlay::tosv2(AllegroFlare::Vec2D v)
{
   std::stringstream ss;
   ss << "      " << v.x << "      " << v.y;
   return ss.str();
}

float CameraInfoOverlay::hfov_degrees()
{
   if (camera->zoom <= 0.0f)
   {
      // A zoom value of 0 or less would lead to division by zero in the perspective setup
      // or an undefined/extremely wide FoV.
      // You might want to throw an error or return a specific value.
      // For example, using AllegroFlare::Logger:
      // AllegroFlare::Logger::warn_from(
      //    "AllegroFlare::Camera3D::get_horizontal_fov_degrees",
      //    "Zoom value is non-positive (" + std::to_string(zoom) + "), FoV calculation might be meaningless or invalid."
      // );
      // Returning 180 for zoom -> 0+ as a practical limit, or handle as an error.
      // If zoom is exactly 0, it's a mathematical singularity for 1/zoom.
      // If zoom is negative, the interpretation of 'zoom' might differ.
      // For now, let's assume zoom must be positive.
      if (camera->zoom == 0.0f) return 180.0f; // Effectively infinite FoV tends to 180 degrees
      return 0.0f; // Or some other indicator of an invalid state for negative zoom
   }

   float hfov_rad = 2.0f * std::atan(1.0f / camera->zoom);
   return hfov_rad * (180.0f / ALLEGRO_PI);
}

void CameraInfoOverlay::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::render]: error: guard \"font_bin\" not met");
   }
   if (!(camera))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::render]: error: guard \"camera\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::render]: error: guard \"camera\" not met");
   }
   int y = -400;
   float spac = 80;

   float ry = y+1080/2 - spac - 40;
   auto w = ALLEGRO_COLOR{1, 1, 1, 1};
   auto g = ALLEGRO_COLOR{0.56, 0.93, 0.56, 1};
   auto f = obtain_font();
   auto bf = obtain_bold_font();

   //draw_pill(1920/2 - 130, ry,       280, 48, 90.0, 8.0, "name", w, "Camera A");
   draw_pill(1920/2 - 130, ry,       280, 48, 90.0, 8.0, "name", w, camera_name, w, f, bf);
   //draw_pill(1920/2-60 - 360 + 10, ry,       220, 48, 90.0, 8.0, "zoom", w, "110%");
   draw_pill(1920/2-60 - 360 + 10, ry,       220, 48, 90.0, 8.0, "zoom", w, tos(camera->zoom * 100) + "%", w, f, bf);
   //draw_pill(1920/2 + 200, ry,       240, 48, 80.0, 8.0, "DOF", w, "90deg");
   draw_pill(1920/2 + 200, ry,       240, 48, 80.0, 8.0, "HFoV", w, tos(hfov_degrees()), w, f, bf);
   //draw_pill(1920/2 - 860, ry, 400, 48, 136.0, 8.0, "position", w, "     0.2       10       20");
   draw_pill(1920/2 - 860, ry, 400, 48, 136.0, 8.0, "position", w, tosv(camera->position), w, f, bf);
   //draw_pill(1920/2 + 500, ry, 400, 48, 136.0, 8.0, "stepout", w, "     0.2       10       20");
   draw_pill(1920/2 + 500, ry, 400, 48, 136.0, 8.0, "stepout", w, tosv(camera->stepout), w, f, bf);

   draw_pill(1920/2 + 500 + 130, ry + 56, 270, 48, 136.0-30, 8.0, "shift", w, tosv2(camera->shift), w, f, bf);

   if (camera_is_tracking_object)
   {
      draw_pill(1920/2 - 860, ry+48, 180, 48, 48.0, 8.0, "*", g, "tracking", g, f, bf);
   }

   float n_spin = camera->spin;
   //draw_pill(1920/2 - 885, y+1080/2 + spac*4,       200, 48, 80.0, 8.0, "spin", w, "3 / 32");
   //draw_pill(1920/2 - 885, y+1080/2 + spac*5,       200, 48, 80.0, 8.0, "tilt", w, "8 / 32");
   //draw_pill(1920/2 - 885, y+1080/2 + spac*6,       200, 48, 80.0, 8.0, "roll", w, "0 / 32");
   draw_pill(1920/2 - 885, y+1080/2 + spac*4,       200, 48, 80.0, 8.0, "spin", w, tos(camera->spin), w, f, bf);
   draw_radial_diagram(1920/2 - 885 + 260, y+1080/2 + spac*4 + 48/2, 30, n_spin - 0.25);

   draw_pill(1920/2 - 885, y+1080/2 + spac*5,       200, 48, 80.0, 8.0, "tilt", w, tos(camera->tilt), w, f, bf);
   draw_radial_diagram(1920/2 - 885 + 260, y+1080/2 + spac*5 + 48/2, 30, camera->tilt);

   draw_pill(1920/2 - 885, y+1080/2 + spac*6,       200, 48, 80.0, 8.0, "roll", w, tos(camera->roll), w, f, bf);
   draw_radial_diagram(1920/2 - 885 + 260, y+1080/2 + spac*6 + 48/2, 30, camera->roll, false);




   //draw_pill(1920/2 + 700, y+1080/2 + spac*2,       200, 48, 80.0, 8.0, "far", w, "1000");
   draw_pill(1920/2 + 700, y+1080/2 + spac*2,       200, 48, 80.0, 8.0, "far", w, tos(camera->far_plane), w, f, bf);
   //draw_pill(1920/2 + 700, y+1080/2 + spac*7,       200, 48, 80.0, 8.0, "near", w, "0.125");
   draw_pill(1920/2 + 700, y+1080/2 + spac*7,       200, 48, 80.0, 8.0, "near", w, tos(camera->near_plane), w, f, bf);


   return;
}

void CameraInfoOverlay::draw_pill(float x, float y, float w, float h, float column_divider_pos, float column_divider_padding, std::string label, ALLEGRO_COLOR label_color, std::string value, ALLEGRO_COLOR value_color, ALLEGRO_FONT* font, ALLEGRO_FONT* bold_font)
{
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::draw_pill]: error: guard \"font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::draw_pill]: error: guard \"font\" not met");
   }
   if (!(bold_font))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::draw_pill]: error: guard \"bold_font\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::draw_pill]: error: guard \"bold_font\" not met");
   }
   //float x = 1920/2;
   //float y = 1080/3;
   //ALLEGRO_FONT *font = obtain_font();
   //ALLEGRO_FONT *bold_font = obtain_bold_font();
   //float text_width = al_get_text_width(font, quote.c_str());
   //float text_height = al_get_font_line_height(font);
   float h_text_width = w/2;
   float h_text_height = h/2;
   //AllegroFlare::Vec2D padding = {30, 20};
   float h_line_height = al_get_font_line_height(font) / 2;
   //float h_line_height = 

   al_draw_filled_rounded_rectangle(
      x, // - padding.x,
      y, // - padding.y,
      x+w, // + padding.x,
      y+h, // + padding.y,
      8.0f,
      8.0f,
      ALLEGRO_COLOR{0, 0, 0, 1}
      //2.0f
   );

   /*
   al_draw_rounded_rectangle(
      x-h_text_width - padding.x,
      y-h_text_height - padding.y,
      x+h_text_width + padding.x,
      y+h_text_height + padding.y,
      8.0f,
      8.0f,
      ALLEGRO_COLOR{1, 1, 1, 1},
      2.0f
   );
   */

   al_draw_text(
      bold_font,
      label_color,
      x+column_divider_pos-column_divider_padding, y+h_text_height-h_line_height,
      ALLEGRO_ALIGN_RIGHT,
      label.c_str()
   );

   al_draw_text(
      font,
      value_color, //ALLEGRO_COLOR{1, 1, 1, 1},
      x+column_divider_pos+column_divider_padding, y+h_text_height-h_line_height,
      ALLEGRO_ALIGN_LEFT,
      value.c_str()
   );

   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-h_text_height, ALLEGRO_ALIGN_LEFT, quote.c_str());
   return;
}

void CameraInfoOverlay::draw_radial_diagram(float x, float y, float radius, float value, bool draw_backstep_triangle)
{
   draw_radial_ticks(x, y, radius, 32, 3, 4, 0, 2.0);
   draw_radial_ticks(x, y, radius, 8, 10, 2, 0, 2.0);
   draw_radial_ticks(x, y, radius, 4, 10, 0, 0, 2.0);
   draw_clockwise_radial_line(x, y, radius - 3, value, 6.0, ALLEGRO_COLOR{1, 1, 1, 1});
   if (draw_backstep_triangle)
   {
      draw_rotating_triangle_toward_center(x, y, 14, radius-6, value + 0.5, ALLEGRO_COLOR{1, 1, 1, 1});
   }
   //draw_rotating_triangle_toward_center
   return;
}

void CameraInfoOverlay::draw_radial_ticks(float cx, float cy, float r, int t, float l, int s, int o, float line_thickness)
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

void CameraInfoOverlay::draw_clockwise_radial_line(float cx, float cy, float r, float v, float t, ALLEGRO_COLOR c)
{
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
   return;

   /*
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
   */
}

void CameraInfoOverlay::draw_rotating_triangle_toward_center(float x, float y, float l, float d, float v, ALLEGRO_COLOR c)
{
   //void draw_rotating_triangle_toward_center(float x, float y, float l,
                                             //float d, float v,
                                             //ALLEGRO_COLOR c)
   //{
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
   //}
}

ALLEGRO_FONT* CameraInfoOverlay::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -26");
}

ALLEGRO_FONT* CameraInfoOverlay::obtain_bold_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[DialControl::CameraInfoOverlay::obtain_bold_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[DialControl::CameraInfoOverlay::obtain_bold_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-bold.ttf -26");
}


} // namespace DialControl


