#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace DialControl
{
   class CameraInfoOverlay
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::string quote;
      ALLEGRO_FONT* obtain_font();
      ALLEGRO_FONT* obtain_bold_font();

   protected:


   public:
      CameraInfoOverlay(AllegroFlare::FontBin* font_bin=nullptr, std::string quote="Hello!");
      ~CameraInfoOverlay();

      void render();
      void draw_pill(float x=0.0f, float y=0.0f, float w=300.0f, float h=50.0f, float column_divider_pos=100.0f, float column_divider_padding=6.0f, std::string label="[unset-label]", ALLEGRO_COLOR label_color=ALLEGRO_COLOR{1, 1, 1, 1}, std::string value="[unset-value]", ALLEGRO_COLOR value_color=ALLEGRO_COLOR{1, 1, 1, 1});
   };
}



