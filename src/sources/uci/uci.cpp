#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <thread>
#include <assert.h>

#include "board.h"
#include "uci.h"

using namespace std;


void do_work(){
    cerr << "work, work" << endl;
}


int uci_loop(istream &input_stream, ostream &output_stream){
    string line;
    string word;
    thread engine_thread;
    bool engine_started = false;
    Board board;

    while (true) {
        getline(input_stream, line);
        istringstream ss(line);

        ss >> word;
        if (word == "uci"){
            output_stream << "id name JACE" << endl;
            output_stream << "id author Espen Haugsdal & Ludvig Killingberg" << endl;
            // TODO send option
            output_stream << "uciok" << endl;
        }
        else if (word == "debug"){
            // TODO
        }
        else if (word == "isready"){
            output_stream << "readyok" << endl;
        }
        else if (word == "setoption"){
            // TODO
        }
        else if (word == "register"){
            // TODO
        }
        else if (word == "ucinewgame"){
            // TODO
        }
        else if (word == "position"){
            ss >> word;
            if (word == "startpos"){
                board = Board();
            } else {
                // assume FEN
                ostringstream fen_ss;

                fen_ss << word;
                for (int i = 0; i < 5; i++) {
                    string tmp;
                    ss >> tmp;
                    fen_ss << " " << tmp;
                }

                board = Board(fen_ss.str());
            }

            ss >> word;
            assert(word == "moves");
            while(ss >> word) {
                // TODO apply moves
            }
            board.print();
        }
        else if (word == "go"){
            assert(!engine_started);
            engine_thread = thread{do_work};
            engine_started = true;
            // TODO
        }
        else if (word == "stop"){
            // TODO
        }
        else if (word == "ponderhit"){
            // TODO
        }
        else if (word == "quit"){
            if (engine_started){
                engine_thread.join();
            }
            return 0;
        }
    };
}
