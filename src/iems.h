#pragma once
#include <vector>
#include <string>
#include "imgui.h"
#include "database.h"

class IemBank {
private:
    std::vector<std::string> IemName;
    char iemdbName[128]{};
    std::vector<std::string> searchResults;

public:
    Database db;


    IemBank() {
        searchResults.clear();
    }

    void renderIemPage() {
        ImGui::Text("HELLO TO THE IEM SECTION ");
        ImGui::Separator();
        ImGui::Text("WHAT IEM WOULD YOU LIKE TO LOOK FOR TODAY???");


        if (ImGui::InputText("NAME OF IEM", iemdbName, IM_ARRAYSIZE(iemdbName))) {

            searchResults = db.SearchGear(iemdbName);
        }
        ImGui::SameLine();
        if (ImGui::Button("X")) {
            memset(iemdbName, 0, sizeof(iemdbName));
            searchResults.clear();
        }
        if (!searchResults.empty()) {
            ImGui::Separator();
            ImGui::Text("LAST SEARCH RESULTS (%d):", (int)searchResults.size());
            int id = 0;
            for (const auto& iem : searchResults) {
                ImGui::PushID(id++);
                if (ImGui::Selectable(iem.c_str())) {
                    std::cout << "SELECTED" << iem << std::endl;
                }
                ImGui::SameLine(ImGui::GetWindowWidth() - 65);
                if (ImGui::Button("DEL")) {
                    db.deleteIem(iem.c_str());
                    searchResults = db.SearchGear(iemdbName); 
                }
                ImGui::PopID();
            }
        }

        if (strlen(iemdbName) > 0) {
            ImGui::Text("SEARCHING FOR %s ", iemdbName);
        }
        ImGui::Separator();

        if (searchResults.empty()) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "NO GEAR FOUND IN THE DATABASE");
            if (ImGui::Button("SAVE NEW IEM TO DATABASE")) {
                db.AddIem(iemdbName);
            }
        }
        else {
            ImGui::Text("FOUND %d MATCHES ", static_cast<int>(searchResults.size()));
        }

        for (const auto& iem : searchResults) {
            if (ImGui::Selectable(iem.c_str())) {
                std::cout << "YOU CLICKED ON :" << iem << std::endl;
            }
        }
    }

};