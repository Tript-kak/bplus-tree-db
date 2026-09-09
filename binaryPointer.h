#include <bits/stdc++.h>
using namespace std;

class Pointer{
    public:
        static constexpr uint8_t TYPE_DATA = 0x01;
        static constexpr uint8_t TYPE_NODE = 0x02;
        
        static constexpr size_t BYTES = 1 + sizeof(int64_t) + sizeof(int32_t);
    
    private:
        uint8_t type;
        int64_t position;
        int32_t chunk;

    public:
        Pointer(uint8_t type, int64_t position, int32_t chunk):
            type(type),
            position(position),
            chunk(chunk){}
            
            uint8_t getType() const{
                return type;
            }

            int64_t getPosition() const{
                return position;
            }

            int32_t getChunk() const{
                return chunk;
            }

            void setType(uint8_t type){
                this->type = type;
            }

            void setPosition(int64_t position){
                this->position = position;
            }

            void setChunk(int32_t chunk){
                this->chunk = chunk;
            }

            static Pointer empty(){
                return Pointer{
                    0x00,0,0
                };
            }

            bool isDataPointer() const{
                return type == TYPE_DATA;
            }

            bool isNodePointer() const {
                return type == TYPE_NODE;
            }

            vector<uint8_t> toBytes() const{
                vector<uint8_t> bytes(BYTES);

                bytes[0] = type;

                for(int i=0; i < 8; i++){
                    bytes[i+1] = (position >> (56-i*8)) & 0xFF;
                }

                for(int i=0; i < 4; i++){
                    bytes[i+9] = (chunk >> (24-i*8)) & 0xFF;
                }

                return bytes;
            }

            static Pointer fromBytes(const vector<uint8_t>& bytes,size_t position = 0){

                    if(position + BYTES > bytes.size()){
                        throw out_of_range("Not enough bytes");
                    }

                    uint8_t type = bytes[position];
                    int64_t pointerPosition = 0;

                    for(int i=0; i< 8; i++){
                        pointerPosition = (pointerPosition << 8) | bytes[position+1+i]; 
                    }

                    int32_t chunk = 0;

                    for(int i=0; i < 4; i++){
                        chunk = (chunk << 8) | bytes[position+9+i];
                    }

                    return Pointer(type,position,chunk);
            }


            void fillBytes(vector<uint8_t>& source, size_t position) const{
                if(position + BYTES > source.size()){
                    throw out_of_range("Not enough space");             
                }

                source[position] = type;

                for(int i=0; i <8; i++){
                    source[position + 1 + i] = (this->position >> (56-i*8)) & 0xFF;
                }

                for(int i=0; i < 4; i++){
                    source[position + 9 + i] = (chunk >> (24- i*8)) & 0xFF;
                }
            }

            int compareTo(const Pointer& other) const{
                if(chunk < other.chunk) return -1;

                if(chunk > other.chunk) return 1;

                if(position < other.position) return -1;

                if(position > other.position) return 1;

                return 0;
            }

            bool operator == (const Pointer& other) const{
                return type == other.type && position == other.position && chunk == other.chunk;
            }

            bool operator != (const Pointer& other) const {
                return !(*this == other);
            }

            bool operator<(const Pointer& other) const{
               if(chunk != other.chunk) return (chunk < other.chunk);

               return position < other.position;
            }

            friend ostream& operator<<(
                ostream& os,
                const Pointer& pointer
            ){
                os << "Pointer{"
                   << "type=" <<(int)pointer.type
                   << ",position" << pointer.position
                   << ",chunk" << pointer.chunk
                   <<"}";

                   return os;
            }


};