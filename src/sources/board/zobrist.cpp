#include "board.h"

zh_t StartZH;
zh_t PawnZH[64];
zh_t RookZH[64];
zh_t BishopZH[64];
zh_t KingZH[64];
zh_t WhiteZH[64];
zh_t BlackZH[64];
zh_t ColorZH;

void zobrist_hashes::init(){
    srand(0);
    StartZH = rand();
    ColorZH = rand();
    for (int i=0; i < 64; i++){
        PawnZH[i] = rand();
        RookZH[i] = rand();
        BishopZH[i] = rand();
        KingZH[i] = rand();
        WhiteZH[i] = rand();
        BlackZH[i] = rand();
    }
}
