//
// Created by Mardel on 08/06/18.
//

#ifndef CPP_INDIE_STUDIO_GAMEUTILS_HPP
#define CPP_INDIE_STUDIO_GAMEUTILS_HPP

#include <cmath>
#include <irrlicht.h>

using namespace irr;
using namespace core;

vector3df GetRotationFromTo(vector3df from, vector3df to);
quaternion QuaternionLookRotation(vector3df forward);

#endif //CPP_INDIE_STUDIO_GAMEUTILS_HPP
