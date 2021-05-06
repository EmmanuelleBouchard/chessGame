#pragma once
#include <iostream>
#include <string>


    using namespace std;

    struct Position {

        int x = 0;
        int y = 0;

        string positionNumerotation() {

            string lettrey;

            switch (y) {
            case 1:
                lettrey = "a";
                break;
            case 2:
                lettrey = "b";
                break;
            case 3:
                lettrey = "c";
                break;
            case 4:
                lettrey = "d";
                break;
            case 5:
                lettrey = "e";
                break;
            case 6:
                lettrey = "f";
                break;
            case 7:
                lettrey = "g";
                break;
            case 8:
                lettrey = "h";
                break;
            }

          //  cout << lettrey << (x + 1) << endl;
            return "" + lettrey + to_string(x + 1);
        }
    };

    enum class Couleur {
        blanc,
        noir,
        vide
    };
