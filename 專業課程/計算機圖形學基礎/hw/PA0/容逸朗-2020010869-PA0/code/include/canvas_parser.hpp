#pragma once

#include <vecmath.h>
#include <cassert>
#include <vector>
#define MAX_PARSER_TOKEN_LENGTH 1024

class Element;

class CanvasParser {
public:

    CanvasParser() = delete;
    explicit CanvasParser(const char *filename);

    ~CanvasParser();

    int getNumElement() const {
        return elements.size();
    }

    Element *getElement(int i) const {
        assert(i >= 0 && i < elements.size());
        return elements[i];
    }

    int getWidth() const;
    int getHeight() const;

private:

    void parseFile();
    Element* parseLine();
    Element* parseCircle();
    Element* parseFill();

    int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);

    Vector3f readVector3f();
    float readFloat();
    int readInt();

    FILE *file;
    std::vector<Element*> elements;

    int width;
    int height;
};

