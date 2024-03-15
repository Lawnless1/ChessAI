#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include <sstream>
#include "hash_pair.h"


using namespace std;




class board
{
public:
    unordered_map<pair<int, int>, char> pieces_b;
    unordered_map<pair<int, int>, char> pieces_w;
    unordered_map<char, unordered_map<pair<int, int>, int>> atked_by;
    bool b_king_moved = false;
    bool w_king_moved = false;
    bool a1_rook_moved = false;
    bool h1_rook_moved = false;
    bool a8_rook_moved = false;
    bool h8_rook_moved = false;
    unordered_map<char, unordered_map<pair<int, int>, char>*> color_to_pieces = {{'b',&pieces_b}, {'w', &pieces_w}};;
    int pawn_move_2 = -2;
    unordered_map<char, function<unordered_set<pair<int, int>>(pair<int, int>, char)>> piece_to_possible_move{
        {'p', bind(&board::p_possible_moves, this, placeholders::_1, placeholders::_2)},
        {'r', bind(&board::r_possible_moves, this, placeholders::_1, placeholders::_2)},
        {'n', bind(&board::n_possible_moves, this, placeholders::_1, placeholders::_2)},
        {'b', bind(&board::b_possible_moves, this, placeholders::_1, placeholders::_2)},
        {'q', bind(&board::q_possible_moves, this, placeholders::_1, placeholders::_2)},
        {'k', bind(&board::k_possible_moves, this, placeholders::_1, placeholders::_2)}};
    unordered_map<char, function<unordered_set<pair<int, int>>(pair<int, int>, char)>> piece_to_attacking{
        {'p', bind(&board::p_attacking, this, placeholders::_1, placeholders::_2)},
        {'r', bind(&board::r_attacking, this, placeholders::_1, placeholders::_2)},
        {'n', bind(&board::n_attacking, this, placeholders::_1, placeholders::_2)},
        {'b', bind(&board::b_attacking, this, placeholders::_1, placeholders::_2)},
        {'q', bind(&board::q_attacking, this, placeholders::_1, placeholders::_2)},
        {'k', bind(&board::k_attacking, this, placeholders::_1, placeholders::_2)}};
        
    unordered_map<char, char> opposite = {{'b', 'w'}, {'w', 'b'}};

    board()
    {
        pieces_w = {{make_pair(0, 0), 'r'}, {make_pair(0, 1), 'n'}, {make_pair(0, 2), 'b'}, {make_pair(0, 3), 'q'}, {make_pair(0, 4), 'k'}, {make_pair(0, 5), 'b'}, {make_pair(0, 6), 'n'}, {make_pair(0, 7), 'r'}, {make_pair(1, 0), 'p'}, {make_pair(1, 1), 'p'}, {make_pair(1, 2), 'p'}, {make_pair(1, 3), 'p'}, {make_pair(1, 4), 'p'}, {make_pair(1, 5), 'p'}, {make_pair(1, 6), 'p'}, {make_pair(1, 7), 'p'}, };
        pieces_b = {{make_pair(6, 0), 'p'}, {make_pair(6, 1), 'p'}, {make_pair(6, 2), 'p'}, {make_pair(6, 3), 'p'}, {make_pair(6, 4), 'p'}, {make_pair(6, 5), 'p'}, {make_pair(6, 6), 'p'}, {make_pair(6, 7), 'p'}, {make_pair(7, 0), 'r'}, {make_pair(7, 1), 'n'}, {make_pair(7, 2), 'b'}, {make_pair(7, 3), 'q'}, {make_pair(7, 4), 'k'}, {make_pair(7, 5), 'b'}, {make_pair(7, 6), 'n'}, {make_pair(7, 7), 'r'}, };
        atked_by = {
            {'b', {{make_pair(0, 0), 0}, {make_pair(0, 1), 0}, {make_pair(0, 2), 0}, {make_pair(0, 3), 0}, {make_pair(0, 4), 0}, {make_pair(0, 5), 0}, {make_pair(0, 6), 0}, {make_pair(0, 7), 0}, {make_pair(1, 0), 0}, {make_pair(1, 1), 0}, {make_pair(1, 2), 0}, {make_pair(1, 3), 0}, {make_pair(1, 4), 0}, {make_pair(1, 5), 0}, {make_pair(1, 6), 0}, {make_pair(1, 7), 0}, {make_pair(2, 0), 0}, {make_pair(2, 1), 0}, {make_pair(2, 2), 0}, {make_pair(2, 3), 0}, {make_pair(2, 4), 0}, {make_pair(2, 5), 0}, {make_pair(2, 6), 0}, {make_pair(2, 7), 0}, {make_pair(3, 0), 0}, {make_pair(3, 1), 0}, {make_pair(3, 2), 0}, {make_pair(3, 3), 0}, {make_pair(3, 4), 0}, {make_pair(3, 5), 0}, {make_pair(3, 6), 0}, {make_pair(3, 7), 0}, {make_pair(4, 0), 0}, {make_pair(4, 1), 0}, {make_pair(4, 2), 0}, {make_pair(4, 3), 0}, {make_pair(4, 4), 0}, {make_pair(4, 5), 0}, {make_pair(4, 6), 0}, {make_pair(4, 7), 0}, {make_pair(5, 0), 0}, {make_pair(5, 1), 0}, {make_pair(5, 2), 0}, {make_pair(5, 3), 0}, {make_pair(5, 4), 0}, {make_pair(5, 5), 0}, {make_pair(5, 6), 0}, {make_pair(5, 7), 0}, {make_pair(6, 0), 0}, {make_pair(6, 1), 0}, {make_pair(6, 2), 0}, {make_pair(6, 3), 0}, {make_pair(6, 4), 0}, {make_pair(6, 5), 0}, {make_pair(6, 6), 0}, {make_pair(6, 7), 0}, {make_pair(7, 0), 0}, {make_pair(7, 1), 0}, {make_pair(7, 2), 0}, {make_pair(7, 3), 0}, {make_pair(7, 4), 0}, {make_pair(7, 5), 0}, {make_pair(7, 6), 0}, {make_pair(7, 7), 0}}},
            {'w', {{make_pair(0, 0), 0}, {make_pair(0, 1), 0}, {make_pair(0, 2), 0}, {make_pair(0, 3), 0}, {make_pair(0, 4), 0}, {make_pair(0, 5), 0}, {make_pair(0, 6), 0}, {make_pair(0, 7), 0}, {make_pair(1, 0), 0}, {make_pair(1, 1), 0}, {make_pair(1, 2), 0}, {make_pair(1, 3), 0}, {make_pair(1, 4), 0}, {make_pair(1, 5), 0}, {make_pair(1, 6), 0}, {make_pair(1, 7), 0}, {make_pair(2, 0), 0}, {make_pair(2, 1), 0}, {make_pair(2, 2), 0}, {make_pair(2, 3), 0}, {make_pair(2, 4), 0}, {make_pair(2, 5), 0}, {make_pair(2, 6), 0}, {make_pair(2, 7), 0}, {make_pair(3, 0), 0}, {make_pair(3, 1), 0}, {make_pair(3, 2), 0}, {make_pair(3, 3), 0}, {make_pair(3, 4), 0}, {make_pair(3, 5), 0}, {make_pair(3, 6), 0}, {make_pair(3, 7), 0}, {make_pair(4, 0), 0}, {make_pair(4, 1), 0}, {make_pair(4, 2), 0}, {make_pair(4, 3), 0}, {make_pair(4, 4), 0}, {make_pair(4, 5), 0}, {make_pair(4, 6), 0}, {make_pair(4, 7), 0}, {make_pair(5, 0), 0}, {make_pair(5, 1), 0}, {make_pair(5, 2), 0}, {make_pair(5, 3), 0}, {make_pair(5, 4), 0}, {make_pair(5, 5), 0}, {make_pair(5, 6), 0}, {make_pair(5, 7), 0}, {make_pair(6, 0), 0}, {make_pair(6, 1), 0}, {make_pair(6, 2), 0}, {make_pair(6, 3), 0}, {make_pair(6, 4), 0}, {make_pair(6, 5), 0}, {make_pair(6, 6), 0}, {make_pair(6, 7), 0}, {make_pair(7, 0), 0}, {make_pair(7, 1), 0}, {make_pair(7, 2), 0}, {make_pair(7, 3), 0}, {make_pair(7, 4), 0}, {make_pair(7, 5), 0}, {make_pair(7, 6), 0}, {make_pair(7, 7), 0}}}
            };
        for (const auto& key_val: pieces_b){ // Initialises the initial attacking positions
            for (auto attacking : piece_to_attacking[key_val.second](key_val.first, 'b')){
                    atked_by['b'][attacking]++;
            }   
        }
        for (const auto& key_val: pieces_w){ // Initialises the initial attacking positions
            for (auto attacking : piece_to_attacking[key_val.second](key_val.first, 'w')){
                    atked_by['w'][attacking]++;
            }   
        }
    };

    string as_string(){
        string out = "";
        for (int i = 7; i> -1; i--){
            out = out + "|";
            for (int j = 0; j < 8; j++){
                pair<int, int> pos = make_pair(i, j) ;
                if (pieces_b.find(pos) != pieces_b.end()){
                    out = out + "b" + string(1, pieces_b[pos]) + "|";
                }
                else if (pieces_w.find(pos) != pieces_w.end()){
                    out = out + "w" + string(1, pieces_w[pos]) + "|";
                }
                else{out = out + "  |";}
            }
            out = out + to_string(i+1) + "\n--------------------------\n"; 
        }
        out = out + "| A| B| C| D| E| F| G| H|\n";
        return out;
    }

    string display_attacked(){
        string out = "\n";
        for (int i = 7; i> -1; i--){
            out = out + "|";
            for (int j = 0; j < 8; j++){
                pair<int, int> pos = make_pair(i, j);
                if ((atked_by['b'][pos] != 0 || atked_by['w'][pos] != 0)){
                    out = out + to_string(atked_by['w'][pos]) + to_string(atked_by['b'][pos]) + "|";}
                else{out = out + "  |";}
            }
            out = out + "\n--------------------------\n"; 
        }
        return out;
    }

    unordered_set<pair<int, int>> r_possible_moves(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        for (int a = 0; a < 2; a++){ //flips between i++ and i--
            for (int b = 0; b < 2; b++){ //flips between up-down or left-right
                int i;
                if (b == 0){i = pos.first;} else {i = pos.second;} 
                if (a == 0){i++;} else {i--;} // Increments at start to remove current tile from check
                while (0 <= i && i <= 7){
                    // defining the direction of check
                    pair<int, int> new_pair;
                    if (b == 0){new_pair = make_pair(i, pos.second);}
                    else{new_pair = make_pair(pos.first, i);}
                    
                    // check if there is a piece on this position
                    if ((pieces_b.find(new_pair) != pieces_b.end()) || (pieces_w.find(new_pair) != pieces_w.end())){
                        // adds position if you can take and ends the search in this direction
                        if (color_to_pieces[opposite[color]]->find(new_pair) != color_to_pieces[opposite[color]]->end()){
                            out.insert(new_pair);
                        }
                        break;
                    }
                    out.insert(new_pair); // adds position if it is not taken
                    if (a == 0){i++;} else {i--;} // incrementing
                }
            }
        }
        return out;
    }

    unordered_set<pair<int, int>> n_possible_moves(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        unordered_set<pair<int, int>> possibilities = { //Define the set of all 8 theoretical tiles that are accessible
            make_pair(pos.first+2, pos.second+1), make_pair(pos.first+2, pos.second-1), make_pair(pos.first-2, pos.second+1), make_pair(pos.first-2, pos.second-1),
            make_pair(pos.first+1, pos.second+2), make_pair(pos.first+1, pos.second-2), make_pair(pos.first-1, pos.second+2), make_pair(pos.first-1, pos.second-2)};
        for (auto new_pair: possibilities){
            if (0 <= new_pair.first && new_pair.first <=7 && 0 <= new_pair.second && new_pair.second <= 7){ //checks if tile exists
                if ((pieces_b.find(new_pair) != pieces_b.end()) || (pieces_w.find(new_pair) != pieces_w.end())){
                    // adds position if you can take and ends the search in this direction
                    if (color_to_pieces[opposite[color]]->find(new_pair) != color_to_pieces[opposite[color]]->end()){
                        out.insert(new_pair);
                    }
                }
                else{out.insert(new_pair);} //adds the tile if it isn't filled
            }
        }
        return out;
    }

    unordered_set<pair<int, int>> p_possible_moves(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        unordered_set<pair<int, int>> possibilities;
        unordered_set<pair<int, int>> attacks;
        if(color == 'w'){ //covers possible moves when pawn is white
            possibilities.insert(make_pair(pos.first+1, pos.second));
            attacks.insert(make_pair(pos.first+1, pos.second+1));
            attacks.insert(make_pair(pos.first+1, pos.second-1));
            if (pos.first == 5){ //En passant
                if (pawn_move_2 == pos.second+1 || pawn_move_2 == pos.second-1){
                    possibilities.insert(make_pair(6, pawn_move_2));
                }
            }
            if (pos.first == 1){ //move_2
              possibilities.insert(make_pair(pos.first+2, pos.second));}
        }
        else{ //covers possible moves when pawn is black
            possibilities.insert(make_pair(pos.first-1, pos.second));
            attacks.insert(make_pair(pos.first-1, pos.second+1));
            attacks.insert(make_pair(pos.first-1, pos.second-1));
            if (pos.first == 3){ //En passant
                if (pawn_move_2 == pos.second+1 || pawn_move_2 == pos.second-1){
                    possibilities.insert(make_pair(2, pawn_move_2));
                }
            }
            if (pos.first == 6){ //move 2
                possibilities.insert(make_pair(pos.first-2, pos.second));}
        }
        for (auto new_pair: possibilities){ // covers moves moving forward
            if (0 <= new_pair.first && new_pair.first <= 7){
                if ((pieces_b.find(new_pair) == pieces_b.end()) && (pieces_w.find(new_pair) == pieces_w.end())){
                    out.insert(new_pair);
                }
            }
        }
        for (auto new_pair: attacks){ // covers diagonals
            if (0 <= new_pair.first && new_pair.first <=7 && 0 <= new_pair.second && new_pair.second <= 7){
                if (((pieces_b.find(new_pair) != pieces_b.end()) || (pieces_w.find(new_pair) != pieces_w.end())) && (color_to_pieces[opposite[color]]->find(new_pair) != color_to_pieces[opposite[color]]->end())){
                    out.insert(new_pair);
                }
            }
        }
        return out;
    }

    unordered_set<pair<int, int>> b_possible_moves(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        for (int a = 0; a < 2; a++){ //flips between i++ and i--
            for (int b = 0; b < 2; b++){ //flips between up-down or left-right
                int i = 0;
                int j = 0;
                if (a == 0){i++;} else{i--;}
                if (b == 0){j++;} else{j--;}
                while(0 <= (pos.first + i) && (pos.first + i) <= 7 && 0 <= (pos.second + j) && (pos.second + j) <= 7){
                    pair<int, int> new_pair = make_pair(pos.first + i, pos.second + j);
                    // check if there is a piece on this position
                    // check if there is a piece on this position
                    if ((pieces_b.find(new_pair) != pieces_b.end()) || (pieces_w.find(new_pair) != pieces_w.end())){
                        // adds position if you can take and ends the search in this direction
                        if (color_to_pieces[opposite[color]]->find(new_pair) != color_to_pieces[opposite[color]]->end()){
                            out.insert(new_pair);
                        }
                        break;
                    }
                    out.insert(new_pair); // adds position if it is not taken
                    if (a == 0){i++;} else{i--;}
                    if (b == 0){j++;} else{j--;}
                }
            }
        }
        return out;
    }
    unordered_set<pair<int, int>> q_possible_moves(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        for (auto possibility: r_possible_moves(pos, color)){
            out.insert(possibility);
        }
        for (auto possibility: b_possible_moves(pos, color)){
            out.insert(possibility);
        }
        return out;
    }

    unordered_set<pair<int, int>> k_possible_moves(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        unordered_set<pair<int, int>> possibilites = {
            make_pair(pos.first+1, pos.second+1), make_pair(pos.first+1, pos.second-1), make_pair(pos.first+1, pos.second), make_pair(pos.first-1, pos.second+1), 
            make_pair(pos.first-1, pos.second-1), make_pair(pos.first-1, pos.second), make_pair(pos.first, pos.second+1), make_pair(pos.first, pos.second-1)};
        for (auto new_pair: possibilites){
            if (0 <= new_pair.first && new_pair.first <=7 && 0 <= new_pair.second && new_pair.second <= 7){ //checks if tile exists
                if (atked_by[opposite[color]][new_pair] == 0){ //if the position is not attacked
                    // check if there is a piece on this position
                    if ((pieces_b.find(new_pair) != pieces_b.end()) || (pieces_w.find(new_pair) != pieces_w.end())){
                        // adds position if you can take and ends the search in this direction
                        if (color_to_pieces[opposite[color]]->find(new_pair) != color_to_pieces[opposite[color]]->end()){
                            out.insert(new_pair);
                        }
                    }
                    else{
                        out.insert(new_pair); //adds tile if isn't filled
                    }
                }
            }
        }
        if (color == 'w'){
            if (! w_king_moved){
                if (!a1_rook_moved && atked_by['b'][make_pair(0, 1)] == 0 && atked_by['b'][make_pair(0, 2)] == 0 && atked_by['b'][make_pair(0, 3)] == 0
                && pieces_b.find(make_pair(0, 1)) == pieces_b.end() && pieces_b.find(make_pair(0, 2)) == pieces_b.end() && pieces_b.find(make_pair(0, 3)) == pieces_b.end()
                && pieces_w.find(make_pair(0, 1)) == pieces_w.end() && pieces_w.find(make_pair(0, 2)) == pieces_w.end() && pieces_w.find(make_pair(0, 3)) == pieces_w.end()){
                    out.insert(make_pair(0, 2));
                }
                if (!h1_rook_moved && atked_by['b'][make_pair(0, 5)] == 0 && atked_by['b'][make_pair(0, 6)] == 0
                && pieces_b.find(make_pair(0, 5)) == pieces_b.end() && pieces_b.find(make_pair(0, 6)) == pieces_b.end()
                && pieces_w.find(make_pair(0, 5)) == pieces_w.end() && pieces_w.find(make_pair(0, 6)) == pieces_w.end()){
                    out.insert(make_pair(0, 6));
                }
            }
        }
        if (color == 'b'){
            if (! b_king_moved){
                if (!a1_rook_moved && atked_by['w'][make_pair(7, 1)] == 0 && atked_by['w'][make_pair(7, 2)] == 0 && atked_by['w'][make_pair(7, 3)] == 0
                && pieces_b.find(make_pair(7, 1)) == pieces_b.end() && pieces_b.find(make_pair(7, 2)) == pieces_b.end() && pieces_b.find(make_pair(7, 3)) == pieces_b.end()
                && pieces_w.find(make_pair(7, 1)) == pieces_w.end() && pieces_w.find(make_pair(7, 2)) == pieces_w.end() && pieces_w.find(make_pair(7, 3)) == pieces_w.end()){
                    out.insert(make_pair(7, 2));
                }
                if (!h1_rook_moved &&atked_by['w'][make_pair(7, 5)] == 0 && atked_by['w'][make_pair(7, 6)] == 0
                && pieces_b.find(make_pair(7, 5)) == pieces_b.end() && pieces_b.find(make_pair(7, 6)) == pieces_b.end()
                && pieces_w.find(make_pair(7, 5)) == pieces_w.end() && pieces_w.find(make_pair(7, 6)) == pieces_w.end()){
                    out.insert(make_pair(7, 6));
                }
            }
        }
         return out;
    }
    unordered_set<pair<int, int>> r_attacking(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        for (int a = 0; a < 2; a++){ //flips between i++ and i--
            for (int b = 0; b < 2; b++){ //flips between up-down or left-right
                int i;
                if (b == 0){i = pos.first;} else {i = pos.second;} 
                if (a == 0){i++;} else {i--;} // Increments at start to remove current tile from check
                while (0 <= i && i <= 7){
                    // defining the direction of check
                    pair<int, int> new_pair;
                    if (b == 0){new_pair = make_pair(i, pos.second);}
                    else{new_pair = make_pair(pos.first, i);}
                    
                    // check if there is a piece on this position
                    if ((pieces_b.find(new_pair) != pieces_b.end()) || (pieces_w.find(new_pair) != pieces_w.end())){
                        // adds position if you can take and ends the search in this direction
                        out.insert(new_pair);
                        break;
                    }
                    out.insert(new_pair); // adds position if it is not taken
                    if (a == 0){i++;} else {i--;} // incrementing
                }
            }
        }
        return out;
    }

    unordered_set<pair<int, int>> n_attacking(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        unordered_set<pair<int, int>> possibilities = { //Define the set of all 8 theoretical tiles that are accessible
            make_pair(pos.first+2, pos.second+1), make_pair(pos.first+2, pos.second-1), make_pair(pos.first-2, pos.second+1), make_pair(pos.first-2, pos.second-1),
            make_pair(pos.first+1, pos.second+2), make_pair(pos.first+1, pos.second-2), make_pair(pos.first-1, pos.second+2), make_pair(pos.first-1, pos.second-2)};
        for (auto new_pair: possibilities){
            if (0 <= new_pair.first && new_pair.first <=7 && 0 <= new_pair.second && new_pair.second <= 7){ //checks if tile exists
                out.insert(new_pair); //adds the tile if it is a legal position
            }
        }
        return out;
    }

    unordered_set<pair<int, int>> p_attacking(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        unordered_set<pair<int, int>> attacks;
        if(color == 'w'){ //covers possible moves when pawn is white
            attacks.insert(make_pair(pos.first+1, pos.second+1));
            attacks.insert(make_pair(pos.first+1, pos.second-1));
        }
        else{ //covers possible moves when pawn is black
            attacks.insert(make_pair(pos.first-1, pos.second+1));
            attacks.insert(make_pair(pos.first-1, pos.second-1));
            }
        for (auto new_pair: attacks){ // covers diagonals
            if (0 <= new_pair.first && new_pair.first <=7 && 0 <= new_pair.second && new_pair.second <= 7){
                out.insert(new_pair);
            }
        }
        return out;
    }

    unordered_set<pair<int, int>> b_attacking(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        for (int a = 0; a < 2; a++){ //flips between i++ and i--
            for (int b = 0; b < 2; b++){ //flips between up-down or left-right
                int i = 0;
                int j = 0;
                if (a == 0){i++;} else{i--;}
                if (b == 0){j++;} else{j--;}
                while(0 <= (pos.first + i) && (pos.first + i) <= 7 && 0 <= (pos.second + j) && (pos.second + j) <= 7){
                    pair<int, int> new_pair = make_pair(pos.first + i, pos.second + j);
                    // check if there is a piece on this position
                    if ((pieces_b.find(new_pair) != pieces_b.end()) || (pieces_w.find(new_pair) != pieces_w.end())){
                        // adds position if you can take and ends the search in this direction
                        out.insert(new_pair);
                        break;
                    }
                    out.insert(new_pair); // adds position if it is not taken
                    if (a == 0){i++;} else{i--;}
                    if (b == 0){j++;} else{j--;}
                }
            }
        }
        return out;
    }
    unordered_set<pair<int, int>> q_attacking(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        for (auto possibility: r_attacking(pos, color)){
            out.insert(possibility);
        }
        for (auto possibility: b_attacking(pos, color)){
            out.insert(possibility);
        }
        return out;
    }

    unordered_set<pair<int, int>> k_attacking(pair<int, int> pos, char color){
        unordered_set<pair<int, int>> out;
        unordered_set<pair<int, int>> possibilites = {
            make_pair(pos.first+1, pos.second+1), make_pair(pos.first+1, pos.second-1), make_pair(pos.first+1, pos.second), make_pair(pos.first-1, pos.second+1), 
            make_pair(pos.first-1, pos.second-1), make_pair(pos.first-1, pos.second), make_pair(pos.first, pos.second+1), make_pair(pos.first, pos.second-1)};
        for (auto new_pair: possibilites){
            if (0 <= new_pair.first && new_pair.first <=7 && 0 <= new_pair.second && new_pair.second <= 7){ //checks if tile exists
                out.insert(new_pair);
            }
        }
         return out;
    }

    void move(pair<int, int> from, pair<int, int> to, char color){
        if((pieces_b.find(from) == pieces_b.end()) && (pieces_w.find(from) == pieces_w.end())){ //Checks if that position is taken
            cout << "no piece is located on this position\n";
            return;
        }
        if (color_to_pieces[color]->find(from) == color_to_pieces[color]->end()){
            cout << "This piece is not yours\n";
            return;
        }
        pair<char, char> piece;
        if (pieces_b.find(from) != pieces_b.end()){
             piece= make_pair('b', pieces_b[from]);}
        else{
             piece= make_pair('w', pieces_w[from]);}  //Initialises the piece
        
        unordered_set<pair<int, int>> possible_moves = piece_to_possible_move[piece.second](from, color);
        if (possible_moves.find(to) == possible_moves.end()){ //Checks if the move is legal
            cout << "Illegal move\n";
            return;
        }
        
        color_to_pieces[color]->erase(from);// Erases existence of piece at current position
        for (pair<int, int> atked_pos : piece_to_attacking[piece.second](from, color)){ //changes the tiles attacked
            atked_by[color][atked_pos]--;
        }
        for (pair<int, int> atked_pos : piece_to_attacking[piece.second](to, color)){ 
            atked_by[color][atked_pos]++;
        }
        color_to_pieces[color]->insert_or_assign(to, piece.second);//Moves the piece to new position



        if (piece.second == 'k' && (abs(to.second - from.second) == 2)){  // castling
            if (to.second == 2 || to.second == 6){
                int num_1;
                int num_2;
                if (to.second == 2){
                    num_1 = 0;
                    num_2 = 3;
                }
                else{
                    num_1 = 7;
                    num_2 = 5;
                }
                // If castles
                color_to_pieces[color]->erase(make_pair(from.first, num_1)); //deletes rook from its curr pos
                for (pair<int, int> atked_pos : r_attacking(make_pair(from.first, num_1), color)){ //removes rook's previous attacks
                    atked_by[color][atked_pos]--;
                }
                for (pair<int, int> atked_pos : r_attacking(make_pair(from.first, num_2), color)){ //adds rook's new attacks
                    atked_by[color][make_pair(from.first, num_2)]++;
                }
                color_to_pieces[color]->insert_or_assign(make_pair(from.first, num_2), 'r'); //moves rook to new position
            }
        }
        if (piece.second == 'p'){ // En passant
            if (color == 'w' && pieces_b.find(to) == pieces_b.end() && abs(from.second - to.second) != 0){
                pieces_b.erase(make_pair(from.first, to.second));
                for (pair<int, int> atked_pos : p_attacking(make_pair(from.first, to.second), 'w')){ //removes deleted pawn's previous attacks
                    atked_by['b'][atked_pos]--;
                }
            }
            if (color == 'b' && pieces_w.find(to) == pieces_w.end() && abs(from.second - to.second) != 0){
                pieces_w.erase(make_pair(from.first, to.second));
                for (pair<int, int> atked_pos : p_attacking(make_pair(from.first, to.second), 'b')){ //removes deleted pawn's previous attacks
                    atked_by['b'][atked_pos]--;
                }
            }
        }
        if (color_to_pieces[opposite[color]]->find(to) != color_to_pieces[opposite[color]]->end()){ //removes pieces that are being attacked
            char to_be_deleted_piece = color_to_pieces[opposite[color]]->at(to);
            color_to_pieces[opposite[color]]->erase(to); //deletes the piece from its position
            for (pair<int, int> atked_pos : piece_to_attacking[to_be_deleted_piece](to, color)){ //removes deleted piece's previous attacks
                atked_by[opposite[color]][atked_pos]--;
            }
        }

        if (piece.second == 'p' && abs(to.first - from.first) == 2){ // updating pawn_move_2 to check en passant
            pawn_move_2 = from.second;
        }
        else{pawn_move_2 = -2;}
        if (piece.second == 'k' && piece.first == 'b' && !b_king_moved){ //updating king and rooks for castling
            b_king_moved = true;
        }
        else if (piece.second == 'k' && piece.first == 'w' && !w_king_moved){
            w_king_moved = true;
        }
        else if (piece.second == 'r' && from.first == 0 && from.second == 0 && !a1_rook_moved){
            a1_rook_moved = true;
        }
        else if (piece.second == 'r' && from.first == 0 && from.second == 7 && !h1_rook_moved){
            h1_rook_moved = true;
        }
        else if (piece.second == 'r' && from.first == 7 && from.second == 0 && !a8_rook_moved){
            a8_rook_moved = true;
        }
        else if (piece.second == 'r' && from.first == 7 && from.second == 7 && !h8_rook_moved){
            h8_rook_moved = true;
        }

    }
};

int main()
{
    unordered_map<char, int> conversion = {{'a', 1}, {'b', 2}, {'c', 3} ,{'d', 4} ,{'e', 5} ,{'f', 6} ,{'g', 7}, {'h', 8}};
    board a = board();
    cout << a.as_string();
    // cout << a.display_attacked();
    bool turn = false;
    while (true){
        if (!turn){turn = true;}else{turn = false;}
        char color;
        if (turn){color = 'w';}else{color = 'b';}
        string inp1;
        string inp2;
        char from_1; int from_2; char to_1; int to_2;
        cout << "from: \n";
        getline(cin, inp1);
        cout << "to: \n";
        getline(cin, inp2);
        stringstream s1(inp1);
        stringstream s2(inp2);
        s1 >> from_1 >> from_2;
        s2 >> to_1 >> to_2;
        pair<int, int> from = make_pair(from_2-1, conversion[from_1]-1);
        pair<int, int> to = make_pair(to_2-1, conversion[to_1]-1);
        a.move(from, to, color);
        cout << a.as_string();
    }
    //a.move(make_pair(1, 1), make_pair(3, 1));
    //cout << a.as_string();
    //cout << a.display_attacked();

    /*for (pair<int, int> i: a.p_possible_moves(make_pair(5, 1), 'w')){
        cout << i.first;
        cout << i.second;
        cout << "---";
    }*/
    return 0;
}