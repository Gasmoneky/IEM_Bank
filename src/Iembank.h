#pragma once
#include "imgui.h"
#include "iems.h"
#include "dacs.h"
#include <iostream>

class Iemplusdacbank {
private:
    enum choice {
        Default,
        IemPage,
        DacPage,
    };

    choice myChoice = Default;
    

    IemBank myIemBank;
    DacBank myDacBank;

     public:
    void RenderTheUi() {
        
        ImGui::Text("WHICH ONE WOULD YOU EXPLORE TODAY");
        if (ImGui::Button("IEMS",ImVec2(100,50))) {
            myChoice = IemPage;
        }
        ImGui::SameLine();
        if (ImGui::Button("DACS,", ImVec2(100, 50))) {
            myChoice = DacPage;
        }
        
        if (myChoice == IemPage) {
            ImGui::Text("WELCOME TO THE AMAZING WORLD OF IEMS");
            
            
            myIemBank.renderIemPage(); 
        }
        
        if (myChoice == DacPage) {
            ImGui::Text("WELCOME TO THE AMAZING WORLD OF DACS");
            myDacBank.renderDacPage();
        }
    }
};