#include"Sword.h"

CImage RotateImage(CImage& image, double angle,const Vector2D<int>& center)
{
    int width = image.GetWidth();
    int height = image.GetHeight();
    int bpp = image.GetBPP();
    CImage rotatedImage;
    rotatedImage.Create(width, height, bpp);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector2D<int> rotatedPos = (Vector2D<int>(x, y) - center).Rotate(angle) + center;
            if (rotatedPos.x >= 0 && rotatedPos.x < width && rotatedPos.y >= 0 && rotatedPos.y < height) {
                BYTE* srcPixel = (BYTE*)image.GetPixelAddress((int)rotatedPos.x, rotatedPos.y);
                BYTE* destPixel = (BYTE*)rotatedImage.GetPixelAddress(x, y);
                memcpy(destPixel, srcPixel, sizeof(BYTE) * bpp);
            }
        }
    }
    return rotatedImage;
}

void Sword::draw_weapon(HDC mDC, const Vector2D<int>& center)
{
    POINT mPos;
    GetCursorPos(&mPos);
    angle = std::atan2(mPos.y - (center.y), mPos.x - center.x) * (180.0f / M_PI);
    RotateImage(resource, -angle, Vector2D<int>(resource.GetWidth() / 2-1, resource.GetHeight() / 2-1)).TransparentBlt(mDC, center.x - resource.GetWidth(), center.y - resource.GetHeight(),
        resource.GetWidth()*2, resource.GetHeight()*2,RGB(0,0,0));
}

void Sword::update()
{
}

void Sword::attack()
{
}
