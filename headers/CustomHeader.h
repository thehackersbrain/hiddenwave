// guard header

#ifndef __CUSTOMHEADER_H_INCLUDED__
#define __CUSTOMHEADER_H_INCLUDED__

#include <iostream>

class CustomHeader {
    int mModulus;
    std::string mExtension;
    char mType;
    int mLastPos = 0;
public:
    CustomHeader(char* header);
    CustomHeader();
    int GetModulus();
    std::string GetExtension();
    char GetType();
    int GetLastPosition();

    void SetLastPosition(int n);
};

#endif //__CUSTOMHEADER_H_INCLUDED__
