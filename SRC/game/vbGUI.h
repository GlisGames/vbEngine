#ifndef VBGUI_H
#define VBGUI_H
#include "basetypes.h"
#include <vbCanvas.h>
#include <vector>

//class betMeter : public vbCanvas
//{
//public:
//    betMeter(WORD posx, WORD posy, Color color, BYTE fontIndex)
//    {
//
//    }
//    void startLoadingAnimation();
//    void stopLoadingAnimation();
//    void update()
//    {
//
//    }
//};

class vbGUI : public vbCanvas //singleton class
{
private:
    static vbGUI* instance;
    //std::vector<vbTextbox> paytable;
    //vbCanvas buttons;
    vbGUI();

public:
    //winMeter winningBox = winningBox();
    //vbButton cmdChangeBet;
    //vbButton cmdResetSession = vbButton(hwButton::BUTTON_GAME1, { 800, 360, 400, 50 });
    static vbGUI* getInstance() //singleton
    {
        if (vbGUI::instance == NULL)
            vbGUI::instance = new vbGUI();
        return vbGUI::instance;
    }

    void update();
    void render();

    //singleton protection stuff.. MAYBE?
    //vbGUI(vbGUI& other) = delete;
    //void operator=(const vbGUI&) = delete;
};

#endif