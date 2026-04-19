#pragma once
#include <vector>
#include <string>
#include "imgui.h"
#include "database.h"

class DacBank{
    private:
    std::vector<std::string> dacName;
    char dacdbName[128]{};

    std::vector<std::string> searchResults;

    public:
    Database db;

           void renderDacPage(){
        ImGui::Text("WELCOME TO THE DAC SECTION");
        ImGui::Separator();
        ImGui::Text("WHAT DAC WOULD YOU LIKE TO SEARCH FOR TODAY");
        if(ImGui::InputText("NAME OF DAC",dacdbName,IM_ARRAYSIZE(dacdbName))){
            ImGui::SameLine();
            if(ImGui::Button("X")){
                memset(dacdbName,0,sizeof(dacdbName));
                searchResults.clear();
            }
            if(!searchResults.empty()){
                ImGui::Separator();
                ImGui::Text("LAST SEARCH RESULTS (%d) ",(int)searchResults.size());
                int id = 0;
                for(const auto& dac : searchResults){
                    ImGui::PushID(id++);
                        if(ImGui::Selectable(dac.c_str())){
                            std::cout<<"SELECTED"<<std::endl;
                        }
                        ImGui::SameLine(ImGui::GetWindowWidth()-65);
                        if(ImGui::Button("DEL")){
                            //db.deleteDac(dac.c_str());
                            //searchResults = db.SearchDacGear(dacdbName);
                        }
                        ImGui::PopID();
                    }
                    if (strlen(dacdbName) > 0){
                   ImGui::Text("SEARCHING FOR %s",dacdbName);
                    }
                    ImGui::Separator();
                    if(searchResults.empty()){
                        
                    }
                }


            
            
        }


    }


};