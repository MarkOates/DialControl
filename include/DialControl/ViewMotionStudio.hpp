#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <DialControl/CameraStudio.hpp>
#include <Timeline/MotionStudio.hpp>
#include <Timeline/Parameter.hpp>
#include <Timeline/ParameterView.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>
#include <vector>


namespace DialControl
{
   class ViewMotionStudio
   {
   private:
      enum ControlState
      {
         STATE_UNDEF = 0,
         STATE_CAMERA_STUDIO_CONTROL,
         STATE_MOTION_STUDIO_CONTROL,
      };
      AllegroFlare::FontBin* font_bin;
      DialControl::CameraStudio camera_studio;
      Timeline::MotionStudio motion_studio;
      uint32_t control_state;
      bool control_state_is_busy;
      float control_state_changed_at;
      bool initialized;
      ALLEGRO_FONT* obtain_font();
      ALLEGRO_FONT* obtain_bold_font();

   protected:


   public:
      ViewMotionStudio();
      ~ViewMotionStudio();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      uint32_t get_control_state() const;
      bool get_initialized() const;
      DialControl::CameraStudio &get_camera_studio_ref();
      Timeline::MotionStudio &get_motion_studio_ref();
      void initialize();
      void build_parameters_for_camera_1();
      void link_camera_1_to_parameters();
      std::vector<Timeline::ParameterView> xxbuild_parameter_views_for_parameters(AllegroFlare::FontBin* font_bin=nullptr, std::vector<Timeline::Parameter>* p=nullptr, float height=Timeline::ParameterView::DEFAULT_HEIGHT);
      void update();
      void setup_camera_projection_on_live_camera();
      void toggle_control_state();
      void render_hud();
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
      void load_json(std::string json_string="[unset-json_string]");
      std::string build_json_string();
      void set_control_state(uint32_t control_state=STATE_UNDEF, bool override_if_busy=false);
      std::string get_control_state_string(uint32_t control_state=STATE_UNDEF);
      static bool is_valid_control_state(uint32_t control_state=STATE_UNDEF);
      bool is_control_state(uint32_t possible_control_state=STATE_UNDEF);
      float infer_current_control_state_age(float time_now=al_get_time());
   };
}



