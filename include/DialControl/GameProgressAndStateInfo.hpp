#pragma once


#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <string>
#include <vector>


namespace DialControl
{
   class GameProgressAndStateInfo : public AllegroFlare::GameProgressAndStateInfos::Base
   {
   public:
      static constexpr char* TYPE = (char*)"DialControl/GameProgressAndStateInfo";

   private:
      int player_num_lives;
      std::vector<std::string> player_inventory_items;

   protected:


   public:
      GameProgressAndStateInfo();
      virtual ~GameProgressAndStateInfo();

      void set_player_num_lives(int player_num_lives);
      void set_player_inventory_items(std::vector<std::string> player_inventory_items);
      int get_player_num_lives() const;
      std::vector<std::string> get_player_inventory_items() const;
      int &get_player_num_lives_ref();
      std::vector<std::string> &get_player_inventory_items_ref();
      void add_player_inventory_item(std::string item_identifier="[unset-item_identifier]");
      virtual std::string export_to_string() override;
      virtual void import_from_string(std::string data_string="[unset-data_string]") override;
   };
}



