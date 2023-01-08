//
//  SmartSwitchKey.cpp
//  GoChuViet
//
//  Created by thuongshoo on 31 December 2022.
//  Copyright © 2022 thuongshoo. All rights reserved.
//

#include "SmartSwitchKey.h"
#include <map>
#include <iostream>
#include <memory.h>

//main data, i use `map` because it has O(Log(n))
static std::map<std::string, Int8> _smartSwitchKeyData;
static std::string _cacheKey = ""; //use cache for faster
static Int8 _cacheData = 0; //use cache for faster

void initSmartSwitchKey(const myByte_t* pData, const int& size) {
    _smartSwitchKeyData.clear();
    if (pData == NULL) return;
    Uint16 count = 0;
    Uint32 cursor = 0;
    if (size >= 2) {
        memcpy(&count, pData + cursor, 2);
        cursor+=2;
    }
    Uint8 bundleIdSize;
    Uint8 value;
    for (int i = 0; i < count; i++) {
        bundleIdSize = pData[cursor++];
        std::string bundleId((char*)pData + cursor, bundleIdSize);
        cursor += bundleIdSize;
        value = pData[cursor++];
        _smartSwitchKeyData[bundleId] = value;
    }
}

void getSmartSwitchKeySaveData(std::vector<myByte_t>& outData) {
    outData.clear();
    Uint16 count = (Uint16)_smartSwitchKeyData.size();
    outData.push_back((myByte_t)count);
    outData.push_back((myByte_t)(count>>8));
    
    for (std::map<std::string, Int8>::iterator it = _smartSwitchKeyData.begin(); it != _smartSwitchKeyData.end(); ++it) {
        outData.push_back((myByte_t)it->first.length());
        for (size_t j = 0; j < it->first.length(); j++) {
            outData.push_back(it->first[j]);
        }
        outData.push_back(it->second);
    }
}

int getAppInputMethodStatus(const std::string& bundleId, const int& currentInputMethod) {
    if (_cacheKey.compare(bundleId) == 0) {
        return _cacheData;
    }
    if (_smartSwitchKeyData.find(bundleId) != _smartSwitchKeyData.end()) {
        _cacheKey = bundleId;
        _cacheData = _smartSwitchKeyData[bundleId];
        return _cacheData;
    }
    _cacheKey = bundleId;
    _cacheData = currentInputMethod;
    _smartSwitchKeyData[bundleId] = _cacheData;
    return -1;
}

void setAppInputMethodStatus(const std::string& bundleId, const int& language) {
    _smartSwitchKeyData[bundleId] = language;
    _cacheKey = bundleId;
    _cacheData = language;
}
