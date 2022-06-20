#pragma once

void action(Animal* animal, std::vector<Dog> & dogzone, std::vector<Bird> & birdzone) {

    Dog* dog = dynamic_cast<Dog*>(animal);
    Bird* bird = dynamic_cast<Bird*>(animal);
    
    if (dog != nullptr) dogzone.push_back(std::move(*dog));
    if (bird != nullptr) birdzone.push_back(std::move(*bird));

}