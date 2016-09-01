#include "Elasticbody.h"


Elasticbody::Elasticbody(std::vector<Vector2D *> &controlPoints)
    : _controlPoints(controlPoints)
{
}


Elasticbody::~Elasticbody()
{
}


//Õ“Ë”»’èŒã‚ÌˆÊ’uˆÚ“®
void Elasticbody::Integrate()
{
    for (auto pos : _controlPoints)
        *pos += _move;
}


//Œ»İ‚ÌˆÚ“®—Ê•ªAˆÊ’u‚ğ–ß‚·
void Elasticbody::CancelIntegrate()
{
    for (auto pos : _controlPoints)
        *pos -= _move;
}