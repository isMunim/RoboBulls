#include "color_palettes.h"


#include "model/constants.h"




// =============== FIELD COLORS ===========================
// ========================================================

#define LINE_THICKNESS 40
const QPen blueLinePen(QColor::fromRgb(0,0,255,255), LINE_THICKNESS, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
const QPen yellowLinePen(Qt::yellow, LINE_THICKNESS, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
const QPen blackLinePen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);


const QMap<QString, FieldPallete> field_pallete_maps = {
    {"Default",   {QBrush(Qt::darkGreen, Qt::SolidPattern),
                   QPen(QColor::fromRgb(245,245,245,255), LINE_THICKNESS, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(Qt::white, 50, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(Qt::lightGray, 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin)}},
    {"Ice Rink",  {QBrush(QColor::fromRgb(200,255,255,255), Qt::SolidPattern),
                   QPen(Qt::red, 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(Qt::red, 50, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(Qt::darkRed, 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin)}},
    {"Air Hockey",{QBrush(QColor::fromRgb(50,50,200,255), Qt::SolidPattern),
                   QPen(Qt::white, 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(Qt::white, 50, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(QColor::fromRgb(56,56,56,255), 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin)}},
    {"Basketball",{QBrush(QColor::fromRgb(205,133,63,255), Qt::SolidPattern),
                   QPen(Qt::white, 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(Qt::white, 50, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(QColor::fromRgb(152,0,0,255), 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin)}},
    {"Basketball",{QBrush(Qt::white, Qt::SolidPattern),
                   QPen(Qt::darkGray, 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(Qt::darkGray, 50, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(QColor::fromRgb(32,32,32,255), 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin)}},
    {"Basketball",{QBrush(QColor::fromRgb(152,251,152,255), Qt::SolidPattern),
                   QPen(QColor::fromRgb(85,107,47,255), 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(QColor::fromRgb(85,107,47,255), 50, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin),
                   QPen(QColor::fromRgb(37,57,0,255), 40, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin)}},
};


// ====== PANEL SELECTED ROBOT COLORS & ROBOT FRAMES ======
// ========================================================

#define SIGN(X) (X<0 ? 0 : X==0 ? 1 : 2)
const ColorsDial colors_dial_sign[3] = {
    {
        "background-color: rgb(200, 0, 0);",
        "background-color: rgb(100, 0, 0);"
    },
    {
        "background-color: rgb(150, 150, 150);",
        "background-color: rgb(100, 100, 100);"
    },
    {
        "background-color: rgb(0, 200, 0);",
        "background-color: rgb(0, 100, 0);"
    }
};

// Colors of dial according to percentage
// of max-min value (split into 0.2 intervals, and starting less than minimum)
int PERCENTAGE_INDEX(float val, float min, float max){
    float percentage = (val-min)/(max-min);
    int i =  percentage / 0.2;
    return i < 0 ? 0 : i > 5 ? 5 : i;
}
const ColorsDial colors_dial_value[6] = {
    {
        "background-color: rgb(150, 150, 150);",
        "background-color: rgb(100, 100, 100);"
    },
    {
        "background-color: rgb(0, 191, 255);",
        "background-color: rgb(0, 140, 200);"
    },
    {
        "background-color: rgb(0, 0, 255);",
        "background-color: rgb(0, 0, 200);"
    },
    {
        "background-color: rgb(160, 32, 240);",
        "background-color: rgb(100, 0, 190);"
    },
    {
        "background-color: rgb(208, 32, 144);",
        "background-color: rgb(150, 0, 90);"
    },
    {
        "background-color: rgb(255, 20, 147);",
        "background-color: rgb(200, 0, 90);"
    }
};


// ==================== TEAM COLORS =======================
// ========================================================

// OBS: BLUE = 0 , YELLOW = 1
const TeamColors team_colors[2] = {
    {
        "background-color: rgb(250, 250, 220);",
        "background-color: rgb(225, 225, 0);",
        "background-color: rgb(0, 0, 100);"
    },
    {
        "background-color: rgb(225, 225, 255);",
        "background-color: rgb(255, 255, 0);",
        "background-color: rgb(100, 100, 0);"
    }
};


