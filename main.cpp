#include <iostream>
#include<fstream>
#include<vector>
#include<windows.h>
#include<cstdint>

using namespace std;
struct NTFSHeader {
uint32_t fileIdent;
uint16_t offsetCor;
uint16_t logFile;
uint64_t logNum;
uint16_t secMft;
uint16_t links;
uint16_t firstOffset;
uint16_t flags;
uint32_t realSize;
uint32_t selectSize;
uint64_t fileLink;
uint32_t nextIdent;
uint32_t numFileRec;
};
struct ATRHeader {
uint32_t type;
uint32_t atrLength;
char flag;
char length;
uint16_t nameOffsetAttr;
uint16_t packFlag;
uint16_t atrIdent;
uint32_t atrSize;
uint16_t conOffset;
char flagIndex;
char atrFill;
};
int main()
{
    setlocale(LC_ALL,"Russian");
    ifstream ntfs_file("File_record.dat",ios::binary);
    if (ntfs_file.is_open()) {
    ntfs_file.seekg(0,ios::end);
    int file_size = ntfs_file.tellg();
    ntfs_file.seekg(0,ios::beg);
    vector<char>ntfs_data(file_size,0);
    ntfs_file.read(ntfs_data.data(),file_size);
    NTFSHeader* p_header = reinterpret_cast<NTFSHeader*>(&ntfs_data[0]);
    cout << hex << int(p_header ->fileIdent) << endl;;
    cout << hex << int(p_header ->firstOffset) << endl;;
    cout << hex << int(p_header ->numFileRec) << endl;
    int offset = int(p_header->firstOffset);
    while(true) {
        ATRHeader* pa_header = reinterpret_cast<ATRHeader*>(&ntfs_data[offset]);
        if ((pa_header->type) == 0xFFFFFFFF) {
            break;
        }
        int TypeAtrib = pa_header->type;
        cout << hex << "Type of attribute: " << TypeAtrib;
        switch(TypeAtrib) {
    case 0x10:
        cout <<" - $STANDART_INFORMATION"<<endl;
        break;
    case 0x20:
        cout <<" - $ATTRIBUTE_LIST"<<endl;
        break;
    case 0x30:
        cout <<" - $FILE_NAME"<<endl;
        break;
    case 0x40:
        cout <<" - $OBJECT_ID"<<endl;
        break;
    case 0x50:
        cout <<" - $SECURITY_DESCRIPTOR"<<endl;
        break;
    case 0x80:
        cout <<" - $DATA"<<endl;
        break;
    case 0x90:
        cout <<" - $INDEX_ROOT"<<endl;
        break;
    case 0xA0:
        cout <<" - $INDEX_ALLOCATION"<<endl;
        break;
    case 0xB0:
        cout <<" - $BITMAP"<<endl;
        break;
    case 0x100:
        cout <<" - $LOGGED_UTILITY_STREAM"<<endl;
        break;
        }
        if (TypeAtrib == 0x30) {
           int sizeOfName = ntfs_data[offset+88];
           wchar_t* data = reinterpret_cast<wchar_t*>(&ntfs_data[offset+90]);
           wstring fileName = wstring(data, sizeOfName);
           wcout << fileName << endl;
        }
        offset +=pa_header->atrLength;
    }


    }
}
