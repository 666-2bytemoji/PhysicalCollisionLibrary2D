#pragma once
#include "Physicalbody.h"
#include "Vector2D.h"
#include <vector>

class Elasticbody : public Physicalbody
{
public:
    Elasticbody(std::vector<Vector2D *> &controlPoints);
    ~Elasticbody();

    //Õ“Ë”»’èŒã‚ÌˆÊ’uˆÚ“®
    void Integrate() override;

    //Œ»İ‚ÌˆÚ“®—Ê•ªAˆÊ’u‚ğ–ß‚·
    void CancelIntegrate() override;


private:

    std::vector<Vector2D *> &_controlPoints;
};

