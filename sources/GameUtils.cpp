//
// Created by Mardel on 08/06/18.
//

#include "GameUtils.hpp"

vector3df GetRotationFromTo(vector3df from, vector3df to)
{
    vector3df direction = (from - to).normalize();
    quaternion rotation = QuaternionLookRotation(direction);
    return rotation.getMatrix().getRotationDegrees();
}

quaternion QuaternionLookRotation(vector3df forward)
{
    vector3df up(0, 1, 0);
    vector3df right = (up.crossProduct(forward)).normalize();
    up = forward.crossProduct(right);
    float m00 = right.X;
    float m01 = right.Y;
    float m02 = right.Z;
    float m10 = up.X;
    float m11 = up.Y;
    float m12 = up.Z;
    float m20 = forward.X;
    float m21 = forward.Y;
    float m22 = forward.Z;

    float num8 = (m00 + m11) + m22;
    quaternion q1;
    if (num8 > 0.0f)
    {
        float num = (float)std::sqrt(num8 + 1.0f);
        q1.W = num + 0.5f;
        num = 0.5f / num;
        q1.X = (m12 - m21) * num;
        q1.Y = (m20 - m02) * num;
        q1.Z = (m01 - m10) * num;

        return q1;
    }
    if ((m00 >= m11) && (m00 >= m22))
    {
        float num7 = (float)std::sqrt(((1.0f + m00) - m11) - m22);
        float num4 = 0.5f / num7;
        q1.X = 0.5f * num7;
        q1.Y = (m01 + m10) * num4;
        q1.Z = (m02 + m20) * num4;
        q1.W = (m12 - m21) * num4;
        return q1;
    }
    if (m11 > m22)
    {
        float num6 = (float)std::sqrt(((1.0f + m11) - m00) - m22);
        float num3 = 0.5F / num6;
        q1.X = (m10 + m01) * num3;
        q1.Y = 0.5f * num6;
        q1.Z = (m21 + m12) * num3;
        q1.W = (m20 - m02) * num3;
        return q1;
    }
    float num5 = (float)std::sqrt(((1.0f + m22) - m00) - m11);
    float num2 = 0.5f / num5;
    q1.X = (m20 + m02) * num2;
    q1.Y = (m21 + m12) * num2;
    q1.Z = 0.5f * num5;
    q1.W = (m01 - m10) * num2;
    return q1;
}