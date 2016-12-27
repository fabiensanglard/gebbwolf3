//
// Created by fabien sanglard on 2016-11-12.
//

#include "ByteStream.h"

ByteStream::ByteStream(uint8_t* cursor){
    this->cursor = cursor;
}

ByteStream::ByteStream(ByteStream& stream){
    this->cursor = stream.cursor;
}

ByteStream::ByteStream() :cursor(NULL)
{

}

ByteStream::~ByteStream(){

}