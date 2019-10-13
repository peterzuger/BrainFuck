/**
 * @file   bfi.cpp
 * @author Peter Züger
 * @date   06.07.2019
 * @brief  BrainFuck Interpreter
 *
 * This file is part of Brainfuck (https://gitlab.com/peterzuger/BrainFuck).
 * Copyright (c) 2019 Peter Züger.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

template<typename TapeType, std::size_t TapeSize>
void execute(std::string_view source){
    std::array<TapeType, TapeSize*2> tape;
    std::size_t pointer = TapeSize;

    for(std::size_t pos = 0; pos < source.size() && pos >= 0; pos++){
        switch(source[pos]){
        case '>':  // Move the pointer to the right
            pointer++;
            break;

        case '<':  // Move the pointer to the left
            pointer--;
            break;

        case '+':  // Increment the memory cell under the pointer
            ++tape[pointer];
            break;

        case '-':  // Decrement the memory cell under the pointer
            --tape[pointer];
            break;

        case '.':  // Output the character signified by the cell at the pointer
            std::cout << static_cast<char>(tape[pointer]);
            break;

        case ',':  // Input a character and store it in the cell at the pointer
            std::cin >> tape[pointer];
            break;

        case '[':  // Jump past the matching ] if the cell under the pointer is 0
            if(tape[pointer] == 0){
                std::size_t bc = 1;
                while(source[pos] != ']' || bc){
                    ++pos;
                    switch(source[pos]){
                    case '[': ++bc; break;
                    case ']': --bc; break;
                    default: break;
                    }
                }
            }
            break;

        case ']':  // Jump back to the matching [ if the cell under the pointer is nonzero
            if(tape[pointer]){
                std::size_t bc = 1;
                while(source[pos] != '[' || bc){
                    --pos;
                    switch(source[pos]){
                    case '[': --bc; break;
                    case ']': ++bc; break;
                    default: break;
                    }
                }
            }
            break;

        default:
            break;
        }
    }
}

int main(int argc, char** argv){
    std::ios::sync_with_stdio(false);
    std::cin >> std::noskipws;
    std::string prog;

    if(argc == 1){
        std::copy(std::istream_iterator<char>(std::cin),
                  std::istream_iterator<char>(),
                  std::back_inserter(prog));
    }

    if(argc == 2){
        std::ifstream file(argv[1]);

        std::copy(std::istreambuf_iterator<char>(file),
                  std::istreambuf_iterator<char>(),
                  std::back_inserter(prog));
    }

    execute<char, 16384>(prog);
}
