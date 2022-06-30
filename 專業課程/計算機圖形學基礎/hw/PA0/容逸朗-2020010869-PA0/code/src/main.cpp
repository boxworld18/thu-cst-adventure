#include <iostream>

#include "canvas_parser.hpp"
#include "image.hpp"
#include "element.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3) {
        cout << "Usage: ./PA0 <input canvas file> <output pic path>" << endl;
        return 0;
    }

    CanvasParser canvasParser(argv[1]);
    Image renderedImg(canvasParser.getWidth(), canvasParser.getHeight());
    for (int ei = 0; ei < canvasParser.getNumElement(); ++ei) {
        canvasParser.getElement(ei)->draw(renderedImg);
    }
    renderedImg.FlipHorizontal();
    renderedImg.SaveImage(argv[2]);

    return 0;
}

