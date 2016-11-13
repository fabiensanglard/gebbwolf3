//
// Created by fabien sanglard on 2016-11-12.
//

#ifndef TOVGAPLANES_BYTESTREAM_H
#define TOVGAPLANES_BYTESTREAM_H


#include <cstdint>
#include <cstdio>

class ByteStream {
public:



    ByteStream(uint8_t* cursor);
    ByteStream(ByteStream& stream);
    ByteStream();
    ~ByteStream();

    inline void Set(uint8_t* cursor){
        this->cursor = cursor;
    }

    inline void MoveForward(size_t bytes){
        this->cursor += bytes;
    }

    inline uint8_t ReadByte(void){
        return *this->cursor++;
    }

    inline uint8_t PeekByte(void){
        return *(this->cursor+1);
    }


    inline uint16_t ReadUShort(void){
        uint16_t* ushortP = (uint16_t*)this->cursor;
        this->cursor+=2;
        return *ushortP;
    }

    inline int16_t ReadShort(void){
        int16_t* shortP = (int16_t*)this->cursor;
        this->cursor+=2;
        return *shortP;
    }

    inline uint8_t* GetPosition(void){
        return this->cursor;
    }

    inline uint32_t ReadUInt32LE(void){
        uint32_t* i = (uint32_t*)cursor;
        cursor+=4;
        return *i;
    }

    inline int32_t ReadInt32LE(void){
        int32_t* i = (int32_t*)cursor;
        cursor+=4;
        return *i;
    }

    inline uint32_t ReadUInt32BE(void){

        uint32_t toLittleEndian = 0;
        toLittleEndian |= *(cursor++)   << 24 ;
        toLittleEndian |= *(cursor++)   << 16 ;
        toLittleEndian |= *(cursor++)   <<  8 ;
        toLittleEndian |= *(cursor++)   <<  0 ;

        return toLittleEndian;
    }




private:
    uint8_t* cursor;
};


#endif //TOVGAPLANES_BYTESTREAM_H
