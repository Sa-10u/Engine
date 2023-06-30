#include "Trans.h"
#include<cmath>
using std::sinf;
using std::cosf;

Trans::Trans():matgra(XMMatrixIdentity()),matrot(XMMatrixIdentity()),matsc(XMMatrixIdentity())
{
    pos = XMFLOAT3(0, 0, 0);
    rot = XMFLOAT3(0, 0, 0);
    size = XMFLOAT3(1, 1, 1);
}

Trans::~Trans()
{
}

void Trans::Calc()
{
    
    matgra =
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        pos.x,pos.y,pos.z,1
    };
    
    XMMATRIX matrot_x =
    {
        1 ,          0,               0,                0,
        0,           cosf(rot.x),     -sinf(rot.x),     0,
        0,           sinf(rot.x),     cosf(rot.x),      0,
        0,           0,               0,                1
    };

    XMMATRIX matrot_y =
    {
        cosf(rot.y), 0,               -sinf(rot.y),     0,
        0,           1,               0,                0,
        sinf(rot.y), 0,               cosf(rot.y) ,     0,
        0,           0,               0,                1
    };

    XMMATRIX matrot_z =
    {
        cosf(rot.z) ,-sinf(rot.z),    0,                0,
        sinf(rot.z), cosf(rot.z),     0,                0,
        0,           0,               1,                0,
        0,           0,               0,                1
    };

    matsc =
    {
        size.x, 0,      0,      0,
        0,      size.y, 0,      0,
        0,      0,      size.z, 0,
        0,      0,      0,      1,
    };

    matrot = matrot_z * matrot_y * matrot_x;

    mat = matrot * matsc * matgra;
    
}

XMMATRIX Trans::GetWorldMatrix()
{
    Calc();
    return mat;
}

XMMATRIX Trans::GetNormalMatrix()
{
    Calc();
    return  matrot * XMMatrixInverse(nullptr,matsc);
}
