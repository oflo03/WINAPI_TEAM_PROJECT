#include"Sword.h"

CImage RotateImage(CImage& image, int angle,const Vector2D<float>& center)
{
    int width = image.GetWidth();
    int height = image.GetHeight();
    CImage rotatedImage;
    rotatedImage.Create(width, height,32);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector2D<float> rotatedPos = (Vector2D<float>(x, y) - center).Rotate(angle) + center;
            if (rotatedPos.x >= 0 && rotatedPos.x < width && rotatedPos.y >= 0 && rotatedPos.y < height) {
                BYTE* srcPixel = (BYTE*)image.GetPixelAddress(rotatedPos.x, rotatedPos.y);
                BYTE* destPixel = (BYTE*)rotatedImage.GetPixelAddress(x, y);
                memcpy(destPixel, srcPixel, sizeof(BYTE) *4);
            }
        }
    }
    return rotatedImage;
}

void Sword::draw_weapon(HDC mDC, const Vector2D<float>& center)
{
    POINT mPos;
    GetCursorPos(&mPos);
    angle = std::atan2(mPos.y - (center.y), mPos.x - center.x) * (180.0f / M_PI);
    RotateImage(resource, -angle, Vector2D<float>(35, 35)).TransparentBlt(mDC, center.x - resource.GetWidth(), center.y - resource.GetHeight(),
        resource.GetWidth()*2, resource.GetHeight()*2,RGB(0,0,0));
}

void Sword::update()
{
}

void Sword::attack()
{
}
