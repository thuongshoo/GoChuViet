//
//  ConvertTool.h
//  GoChuViet
//
//  Created by thuongshoo 31 December 2022.
//  Copyright © 2022 thuongshoo. All rights reserved.
//

#ifndef ConvertTool_h
#define ConvertTool_h

#include "DataType.h"
#include <string>
//using namespace std;

extern bool convertToolDontAlertWhenCompleted;
extern bool convertToolToAllCaps;
extern bool convertToolToAllNonCaps;
extern bool convertToolToCapsFirstLetter;
extern bool convertToolToCapsEachWord;
extern bool convertToolRemoveMark;
extern Uint8 convertToolFromCode;
extern Uint8 convertToolToCode;
extern int convertToolHotKey;

std::string convertUtil(const std::string& sourceString);

#endif /* ConvertTool_h */
