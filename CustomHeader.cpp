#include <string>
#include <boost/algorithm/string.hpp>
#include "headers/CustomHeader.h"

CustomHeader::CustomHeader(char* header) {
    // Set Modulus first
    char* bytes = new char[4];
    for (int i = 0; i < 4; i++) {
        bytes[i] = header[i];
    }

    mModulus = *reinterpret_cast<int*>(bytes);

    //Set extension
    char* ext = new char[4];
    for (int y = 0, i = 4; i < 8; i++, y++) {
        ext[y] = header[i];
    }

    mExtension = std::string(ext);
    boost::algorithm::trim(mExtension);

    // Set Type
    mType = header[8];
    delete[] bytes;
    delete[] ext;
}

CustomHeader::CustomHeader() {
    // Initializing the variables
    return;
}

int CustomHeader::GetModulus() {
    return this->mModulus;
}

std::string CustomHeader::GetExtension() {
    return this->mExtension;
}

char CustomHeader::GetType() {
    return this->mType;
}

int CustomHeader::GetLastPosition() {
    return this->mLastPos;
}

void CustomHeader::SetLastPosition(int n) {
    this->mLastPos = n;
}
