#include <iostream>
#include "headers/Algorithm.h"

using namespace std;

int PlayWithWaveBuffer(vector<char>& buffer, string& msg, string& inputExt)
{
    char* modulusBytes = new char[4] {0}; // Max number of modulus in bytes
    char* customHeader = new char[MY_HEADER] {0}; // Custom header
    string fileExtension = "";

    string end = "@<;;";
    msg += end;

    // How many times the buffer is bigger than the message
    long modulus = ((buffer.size() - WAV_HEADER - START_SPACE) / (msg.size() + MY_HEADER));

    cout << "[\033[0;92m+\033[0;0m] Spreading level: " << "\033[0;92m" << modulus << "\033[0;0m" << endl;

    // Verify if it is safe to hide the message. Must me at must half the size of the space avaible
    if(modulus <= 3)
    {
        cout << "[\033[0;91m-\033m[0;0m] [\033[0;91mThe message might be to big for the audio file\033m[0;0m" << endl;
        return ERROR;
    }

    CreateHeader(modulus, modulusBytes, customHeader, fileExtension, false);

    int n = 0;
    int pos = 0;

    // Write my custom header first (Spread)
    for (vector<char>::iterator it = buffer.begin() + WAV_HEADER + START_SPACE;
         it != buffer.end(); ++it)
    {
        if (n % MY_HEADER_MODULE == 0)
        {
            *it = customHeader[pos];
            pos++;
            //cout << "Header -> " << *it << endl; // Uncomment this to see the message being written

            if (pos == MY_HEADER)
            {
                cout << "[\033[0;92m+\033[0;0m] \033[0;92mHeader Written Successfully...\033[0;0m" << endl;
                break;
            }
        }
        n++;
    }

    // Delete arrays we are not using it anymore
    modulusBytes = new char[1]; // Relocate memory
    delete[] modulusBytes;
    delete[] customHeader;

    int j = 0;
    pos = 0;
    // Since the actual data of the wav starts at byte 44. Everything above is just header things that we don't care atm
    for (vector<char>::iterator it = buffer.begin() + WAV_HEADER + n + MY_HEADER_MODULE + START_SPACE;
         it != buffer.end(); ++it)
    {
        if (j % modulus == 0)
        {
            *it = msg.at(pos);
            pos++;
            //cout << *it << endl; // Uncomment this to see the message being written

            if (pos >= msg.size())
                break;
        }
        j++;
    }

    if (pos < msg.size())
    {
        cout << "[\033[0;91m*\033[0;0m] \033[0;91mMaybe the whole file was not written in\033[0;0m" << endl;
    }

    return OutputBindedData(buffer, inputExt);
}

int PlayWithWaveBuffer(vector<char>& buffer, vector<char>& msgBuffer, string& fileExtension, string& inputExt)
{
    char* modulusBytes = new char[4] {0}; // Max number of modulus in bytes
    char* customHeader = new char[MY_HEADER] {0}; // Custom header

    if (buffer.size()/4 <= msgBuffer.size())
    {
        cout << "[\033[0;91m-\033m[0;0m] [\033[0;91mThe message might be to big for the audio file\033m[0;0m" << endl;
        return ERROR;
    }

    msgBuffer.push_back('@');
    msgBuffer.push_back('<');
    msgBuffer.push_back(';');
    msgBuffer.push_back(';');

    // How many times the buffer is bigger than the message
    // buffer.size() - (HEADER SIZE = 44 bytes) - (My own tags to de hidden file = 3 bytes)
    long modulus = ((buffer.size() - WAV_HEADER - START_SPACE) / (msgBuffer.size() + MY_HEADER));

    cout << "[\033[0;92m+\033[0;0m] Spreading level: " << "\033[0;92m" << modulus << "\033[0;0m" << endl;

    // Verify if it is safe to hide the message. Must me at must half the size of the space avaible
    if(modulus <= 3)
    {
        cout << "[\033[0;91m-\033m[0;0m] [\033[0;91mThe message might be to big for the audio file\033m[0;0m" << endl;
        return ERROR;
    }

    CreateHeader(modulus, modulusBytes, customHeader, fileExtension, true);

    int n = 0;
    int pos = 0;

    // Write my custom header first (Spread)
    for (vector<char>::iterator it = buffer.begin() + WAV_HEADER + START_SPACE;
         it != buffer.end(); ++it)
    {
        if (n % MY_HEADER_MODULE == 0)
        {
            *it = customHeader[pos];
            pos++;
            //cout << "Header -> " << *it << endl; // Uncomment this to see the message being written

            if (pos == MY_HEADER)
            {
                cout << "[\033[0;92m+\033[0;0m] \033[0;92mHeader Written Successfully...\033[0;0m" << endl;
                break;
            }
        }
        n++;
    }

    // Delete arrays we are not using it anymore
    modulusBytes = new char[1]; // Relocate memory
    delete[] modulusBytes;
    delete[] customHeader;

    int j = 0;
    pos = 0;
    for (vector<char>::iterator it = buffer.begin() + WAV_HEADER + n + MY_HEADER_MODULE + START_SPACE;
         it != buffer.end(); ++it)
    {
        if (j % modulus == 0)
        {
            *it = msgBuffer.at(pos);
            pos++;
            //cout << *it << endl; // Uncomment this to see the message being written

            if (pos >= msgBuffer.size())
                break;
        }
        j++;
    }

    if (pos < msgBuffer.size())
    {
        cout << "[\033[0;91m*\033[0;0m] \033[0;91mMaybe the whole file was not written in\033[0;0m" << endl;
    }

    return OutputBindedData(buffer, inputExt);
}

/**
* Look for the custom header and define what type of message is in it
*
* @param buffer: File loaded into a buffer
* */
int FindHiddenMessage(vector<char>& buffer)
{
    char* customHeader = new char[MY_HEADER] {0}; // Custom header

    int n = 0;
    int pos = 0;
    cout << "[\033[0;92m*\033m[0;0m] \033[0;92mLooking for the hidden message...\033m[0;0m" << endl;
    // Since the actual data of the wav starts at byte 44 we start from it. Everything above is just header things that we don't care atm
    for (vector<char>::iterator it = buffer.begin() + WAV_HEADER + START_SPACE;
         it != buffer.end(); ++it)
    {
        if (n % MY_HEADER_MODULE == 0)
        {
            customHeader[pos] = *it;
            //cout << "Custom Header: " << customHeader[pos] << endl; // Uncomment this if you want to see the header being read
            pos++;
            if (pos == MY_HEADER)
            {
                //cout << "Header has been read " << endl;
                break;
            }
        }
        n++;
    }

    CustomHeader cHeader (customHeader);

    // Clean memory
    delete[] customHeader;

    if (cHeader.GetType() == 'b')
    {   
        cout << "[\033[0;92m*\033m[0;0m] \033[0;92mFile detected. Retrieving it...\033m[0;0m" << endl;
        cHeader.SetLastPosition(n);
        return FindHiddenBinaryInWave(buffer, cHeader);
    }
    else if (cHeader.GetType() == 't'){
        cout << "[\033[0;92m*\033m[0;0m] \033[0;92mString detected. Retrieving it...\033m[0;0m" << endl;
        cHeader.SetLastPosition(n);
        return FindHiddenTextInWave(buffer, cHeader);
    }
    else{
        // If it hits here it's because there was no message found in the file
        cout << "[\033m[0;91m-\033m[0;0m] \033m[0;91mFailed to detect a hidden file.\033[0;91m" << endl;
        cout << "[\033m[0;91m-\033m[0;0m] \033m[0;91mNo custom header was found.\033[0;91m" << endl;
        return ERROR;
    }
}

int FindHiddenTextInWave(vector<char>& buffer, CustomHeader& customHeader)
{
    string msgText;

    int modulus = customHeader.GetModulus();
    int lastPos = customHeader.GetLastPosition();

    int n = 0;
    int pos = 0;
    vector<char>::iterator tempIterator;
    // Since the actual data of the wav starts at byte 44. Everything above is just header things that we don't care atm
    for (vector<char>::iterator it = buffer.begin() + WAV_HEADER + lastPos + MY_HEADER_MODULE + START_SPACE;
         it != buffer.end(); ++it)
    {
        if (n % modulus == 0)
        {
            if (*it == 64)
            {
                // @
                //Setting the iterator to the next possible position
                tempIterator = buffer.begin() + n + 44 + MY_HEADER_MODULE + START_SPACE + lastPos + modulus;

                if (*tempIterator == 60) {
                    //<
                    //Setting the iterator to the next possible position
                    tempIterator = buffer.begin() + n + 44 + MY_HEADER_MODULE + START_SPACE + lastPos + (2* modulus);

                    if (*tempIterator == 59) {
                        // ;
                        // Setting the iterator to next possible flag
                        tempIterator = buffer.begin() + n + 44 + MY_HEADER_MODULE + START_SPACE + lastPos + (3 * modulus);

                        if (*tempIterator == 59){
                            // End of message reached
                            cout << "[\033[0;92m+\033[0;0m] Message recovered size: " << "\033[0;92m" << pos << "\033[0;0m" << " bytes" << endl;

                            // Output text
                            cout << "[\033[0;92m+\033[0;0m] Message: " << "\033[0;92m" << msgText.c_str() << "\033[0;0m" << endl;
                            return SUCCESS;
                        }
                    }
                }
            }

            msgText[pos] = *it;
            //cout << msgText[pos] << endl; // Uncomment this if yuo want to see the characters being read
            pos++;

        }
        n++;
    }

    // If it hits here it's because there was no message found in the file
    cout << "[\033[0;91m-\033[0;0m] \033[0;91mNo message found :(\033[0;0m" << endl;
    return ERROR;

}

int FindHiddenBinaryInWave(vector<char>& buffer, CustomHeader& customHeader)
{
    vector<char> msgBuffer;

    int modulus = customHeader.GetModulus();
    int lastPos = customHeader.GetLastPosition();

    int n = 0;
    int pos = 0;
    vector<char>::iterator tempIterator;
    // Since the actual data of the wav starts at byte 44. Everything above is just header things that we don't care atm
    for (vector<char>::iterator it = buffer.begin() + + WAV_HEADER + lastPos + MY_HEADER_MODULE + START_SPACE;
         it != buffer.end(); ++it)
    {
        if (n % modulus == 0)
        {
            if (*it == 64)
            {
                // @
                //Setting the iterator to the next possible position
                tempIterator = buffer.begin() + n + 44 + MY_HEADER_MODULE + START_SPACE + lastPos + modulus;

                if (*tempIterator == 60) {
                    //<
                    //Setting the iterator to the next possible position
                    tempIterator = buffer.begin() + n + 44 + MY_HEADER_MODULE + START_SPACE + lastPos + (2* modulus);

                    if (*tempIterator == 59) {
                        // ;
                        // Setting the iterator to next possible flag
                        tempIterator = buffer.begin() + n + 44 + MY_HEADER_MODULE + START_SPACE + lastPos + (3 * modulus);

                        if (*tempIterator == 59){
                            // End of message reached
                            cout << "[\033[0;92m+\033[0;0m] Message recovered size: " << "\033[0;92m" << pos << "\033[0;0m" << " bytes" << endl;
                            return OutputBinFile(msgBuffer, customHeader);
                        }
                    }
                }
            }

            msgBuffer.push_back(*it);
            //cout << "Data recovered: " << msgBuffer[pos] << endl; // Uncomment this if you want to see the characters being read
            pos++;

        }
        n++;
    }

    // If it hits here it's because there was no message found in the file
    cout << "[\033[0;91m-\033m[0;0m] [\033[0;91mCould not find the end tags of the hidden file :(\033m[0;0m" << endl;
    return ERROR;
}

int WriteMessageFromEnd(vector<char>& buffer, string msg)
{
    // Verify if it is safe to hide the message in the buffer
    if ((buffer.size() / 4) < msg.size())
    {
        cout << "[\033[0;91m-\033m[0;0m] [\033[0;91mThe message might be to big for the audio file\033m[0;0m" << endl;
        return ERROR;
    }

    // Inverse iterator runs backwards
    int n = 0;
    int pos = 0;
    for (vector<char>::reverse_iterator i = buffer.rbegin();
         i != buffer.rend(); ++i)
    {
        if (n%1000 == 0)
        {
            *i = msg.at(pos);
            pos++;
            cout << *i << endl;

            if (pos >= msg.size())
                break;
        }
        n++;
    }

    return SUCCESS;
}

int OutputBindedData(vector<char>& buffer, string& fileExtension)
{
    string fileName;
    if (fileExtension == "")
        fileName = "output";
    else
        fileName = "output." + fileExtension;

    ofstream output(fileName, std::ios::binary);
    output.write((const char*)&buffer[0], buffer.size());
    output.close();
    cout << "[\033[0;92m+\033[0;0m] File has been saved as: " << "\033[0;92m" << fileName << "\033[0;0m" << endl;

    return SUCCESS;
}

int OutputBinFile(vector<char>& buffer, CustomHeader& cHeader)
{
    string fileName;
    if (cHeader.GetExtension() == "")
        fileName = "output";
    else
        fileName = "output." + cHeader.GetExtension();

    ofstream output(fileName, std::ios::binary);
    output.write((const char*)&buffer[0], buffer.size());
    output.close();
    cout << "[\033[0;92m+\033[0;0m] File has been saved as: " << "\033[0;92m" << fileName << "\033[0;0m" << endl;

    return SUCCESS;
}

void CreateHeader(long& modulus, char* modulusBytes, char* customHeader, string& fileExtension, bool isBinaryType)
{
    /**
    * Create custom header (9 bytes):
    * Modulus value: 4 bytes
    * File extension: 4 bytes
    * Message type (text or file): 1 byte
    * */

    // If modulus is lesser than the max int value of 4 bytes assign it.
    // Otherwise, set a flag to use DEF_MODULE constant
    if (modulus <= 42946729)
        modulusBytes = reinterpret_cast<char*>(&modulus);
    else
        modulusBytes[0] = DEF_MODULE;

    int y, i;
    // Assign modulus to header
    for (i = 0; i < 4; i++)
        customHeader[i] = modulusBytes[i];

    // Assign the file extension to recover later
    for(y = 0, i = 4; i < 8; i++)
    {
        // Dinamically fill the 4 bytes of the file extension even if its less than 4 characters
        if(fileExtension.size() > y )
            customHeader[i] = fileExtension.at(y);
        else
            customHeader[i] = ' ';
        y++;
    }

    // Assign the type of the message
    if (isBinaryType)
        customHeader[8] = 'b';
    else
        customHeader[8] = 't';
}