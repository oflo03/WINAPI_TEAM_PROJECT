#include"Sword.h"

CImage RotateImage(CImage& image, double angle)
{
    // 원본 이미지 정보 가져오기
    int width = image.GetWidth();
    int height = image.GetHeight();
    int bpp = image.GetBPP();
    int pitch = image.GetPitch();

    // 회전된 이미지를 저장할 메모리 버퍼 생성
    BYTE* buffer = new BYTE[pitch * height];

    // 회전 중심점 계산
    int centerX = width / 2;
    int centerY = height / 2;

    // 회전 앵글 계산
    double radian = angle * 3.14159265358979323846 / 180.0;
    double cosTheta = cos(radian);
    double sinTheta = sin(radian);

    // 회전된 이미지 생성
    CImage rotatedImage;
    rotatedImage.Create(width, height, bpp);

    // 회전된 이미지에 픽셀 값 설정
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int offsetX = x - centerX;
            int offsetY = y - centerY;

            // 회전 변환 수행
            int rotatedX = static_cast<int>(offsetX * cosTheta - offsetY * sinTheta + centerX);
            int rotatedY = static_cast<int>(offsetX * sinTheta + offsetY * cosTheta + centerY);

            // 회전된 좌표가 유효한지 확인
            if (rotatedX >= 0 && rotatedX < width && rotatedY >= 0 && rotatedY < height) {
                // 원본 이미지에서 해당 좌표의 픽셀 값을 가져와서 회전된 이미지에 설정
                BYTE* srcPixel = image.GetPixelAddress(rotatedX, rotatedY);
                BYTE* destPixel = rotatedImage.GetPixelAddress(x, y);
                memcpy(destPixel, srcPixel, sizeof(BYTE) * bpp);
            }
        }
    }

    delete[] buffer;

    return rotatedImage;
}

void Sword::draw_weapon(HDC mDC)
{
	CImage rotateImage;
	rotateImage.Create(resource.GetWidth(), resource.GetHeight(), resource.GetBPP());
	resource.
}

void Sword::update()
{
}

void Sword::Attack()
{
}
