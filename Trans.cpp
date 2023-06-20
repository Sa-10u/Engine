#include "Trans.h"

Trans::Trans():matgra(XMMatrixIdentity()),matrot(XMMatrixIdentity()),matsc(XMMatrixIdentity())
{

}

Trans::~Trans()
{
}

void Trans::Calc()
{
    /*
    matgra =
    {
        pos.x,0,0,0,
        0,pos.y,0,0,
        0,0,pos.z,0,
        0,0,0,1
    };
    
    matrot =
    {

    };

    matsc =
    {
        1,0,0,0,
        0,1,0,0,
    };

    mat = matgra * matrot * matsc;
    */
}

XMMATRIX Trans::GetWorldMatrix()
{
    Calc();
    return mat;
}
