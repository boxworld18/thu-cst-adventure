#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "scene_parser.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "group.hpp"
#include "light.hpp"

#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3) {
        cout << "Usage: ./bin/PA1 <input scene file> <output bmp file>" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2];  // only bmp is allowed.

    // TODO: Main RayCasting Logic
    // First, parse the scene using SceneParser.

    SceneParser sceneParser(argv[1]);
    Camera* camera = sceneParser.getCamera();
    Image renderedImg(camera->getWidth(), camera->getHeight());

    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.

    // 循环屏幕空间的像素
    for (int x = 0; x < camera->getWidth(); ++x) {
        for (int y = 0; y < camera->getHeight(); ++y) {
            // 计算当前像素(x,y)处相机出射光线camRay
            
            Ray camRay = sceneParser.getCamera()->generateRay(Vector2f(x, y));
            Group* baseGroup = sceneParser.getGroup();
            Hit hit;
            // 判断camRay是否和场景有交点，并返回最近交点的数据，存储在hit中 
            bool isIntersect = baseGroup->intersect(camRay, hit, 0);

            if (isIntersect) {
                Vector3f finalColor = Vector3f::ZERO;
                // 找到交点之后，累加来自所有光源的光强影响
                for (int li = 0; li < sceneParser.getNumLights(); ++li) {
                    Light* light = sceneParser.getLight(li);
                    Vector3f L, lightColor;
                    // 获得光照强度
                    light->getIllumination(camRay.pointAtParameter(hit.getT()), L, lightColor); // 计算局部光强
                    finalColor += hit.getMaterial()->Shade(camRay, hit, L, lightColor);
                }
                renderedImg.SetPixel(x, y, finalColor);
            } else {
                // 不存在交点，返回背景色
                renderedImg.SetPixel(x, y, sceneParser.getBackgroundColor());
            }
        }
    }

    renderedImg.SaveImage(argv[2]);
    cout << "Hello! Computer Graphics!" << endl;
    return 0;
}

