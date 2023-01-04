#ifndef CATDRepColor_H
#define CATDRepColor_H

// R :: red   [0,255]
// G :: green [0,255]
// B :: blue  [0,255]

// -----------------------------------------------
//    User Color
// -----------------------------------------------

// BoneFillet : yellow -"Edge Fillet"
#define DREPCOLOR_BONEFILLET_R 250
#define DREPCOLOR_BONEFILLET_G 225
#define DREPCOLOR_BONEFILLET_B   0

// Chamfer : blue
#define DREPCOLOR_CHAMFER_R 151
#define DREPCOLOR_CHAMFER_G 255
#define DREPCOLOR_CHAMFER_B 255

// JointFillet : orange - "Corner Fillet"
#define DREPCOLOR_JOINTFILLET_R 238
#define DREPCOLOR_JOINTFILLET_G 118
#define DREPCOLOR_JOINTFILLET_B   0

// JointChamfer : darkorange - "Corner Chamfer"
#define DREPCOLOR_JOINTCHAMFER_R 238
#define DREPCOLOR_JOINTCHAMFER_G 80
#define DREPCOLOR_JOINTCHAMFER_B 0

// Canonic : grey - "Basic"
#define DREPCOLOR_CANONIC_R 205
#define DREPCOLOR_CANONIC_G 192
#define DREPCOLOR_CANONIC_B 176

// Datum : green - "Advanced"
#define DREPCOLOR_DATUM_R   0
#define DREPCOLOR_DATUM_G 205
#define DREPCOLOR_DATUM_B   0

// Pattern : greenblue
#define DREPCOLOR_PATTERN_R  85
#define DREPCOLOR_PATTERN_G 247
#define DREPCOLOR_PATTERN_B 247

// Draft : greenblue
#define DREPCOLOR_DRAFT_R 150
#define DREPCOLOR_DRAFT_G 100
#define DREPCOLOR_DRAFT_B 100

// Button : dark red
#define DREPCOLOR_BUTTON_R 163
#define DREPCOLOR_BUTTON_G  31
#define DREPCOLOR_BUTTON_B  21

// -----------------------------------------------
//    Expert Color
// -----------------------------------------------

// 1 support BoneFillet : red - hue(0)
#define DREPCOLOR_BONEFILLET_ONE_SUPPORT_R 247
#define DREPCOLOR_BONEFILLET_ONE_SUPPORT_G  85
#define DREPCOLOR_BONEFILLET_ONE_SUPPORT_B  85

// 0 support BoneFillet : red - hue(0)
#define DREPCOLOR_BONEFILLET_ZERO_SUPPORT_R 247
#define DREPCOLOR_BONEFILLET_ZERO_SUPPORT_G   0
#define DREPCOLOR_BONEFILLET_ZERO_SUPPORT_B   0

// Variable BoneFillet : purple - hue(270)
#define DREPCOLOR_BONEFILLET_VARIABLE_R 166
#define DREPCOLOR_BONEFILLET_VARIABLE_G  85
#define DREPCOLOR_BONEFILLET_VARIABLE_B 247

// Tritangent BoneFillet : purple - hue()
#define DREPCOLOR_BONEFILLET_TRITANGENT_R 255
#define DREPCOLOR_BONEFILLET_TRITANGENT_G 153
#define DREPCOLOR_BONEFILLET_TRITANGENT_B 204

// +-- 0 support Draft : red - hue(0)
#define DREPCOLOR_DRAFT_ZERO_SUPPORT_R 247
#define DREPCOLOR_DRAFT_ZERO_SUPPORT_G   0
#define DREPCOLOR_DRAFT_ZERO_SUPPORT_B   0


// Subdiv : ? - hue(?)
#define DREPCOLOR_SUBDIV_R 224
#define DREPCOLOR_SUBDIV_G   0
#define DREPCOLOR_SUBDIV_B 128


// -----------------------------------------------
//    Select Color for CGMReplay rgb[0,15]
// -----------------------------------------------
// Light Blue
#define LSO_SELECTCOLOR_R 12
#define LSO_SELECTCOLOR_G 14
#define LSO_SELECTCOLOR_B 15

// Light Yellow : for LiveSelectFace
#define LSO_SELECTEXTENSION1COLOR_R 15
#define LSO_SELECTEXTENSION1COLOR_G 15
#define LSO_SELECTEXTENSION1COLOR_B 10

// Light Green : for LiveSelectFace
#define LSO_SELECTEXTENSION2COLOR_R 5
#define LSO_SELECTEXTENSION2COLOR_G 15
#define LSO_SELECTEXTENSION2COLOR_B 10

#endif
