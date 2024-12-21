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

int main()
{
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


    }
}
