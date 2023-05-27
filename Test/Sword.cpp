#include"Sword.h"

CImage RotateImage(CImage& image, double angle)
{
    // ���� �̹��� ���� ��������
    int width = image.GetWidth();
    int height = image.GetHeight();
    int bpp = image.GetBPP();
    int pitch = image.GetPitch();

    // ȸ���� �̹����� ������ �޸� ���� ����
    BYTE* buffer = new BYTE[pitch * height];

    // ȸ�� �߽��� ���
    int centerX = width / 2;
    int centerY = height / 2;

    // ȸ�� �ޱ� ���
    double radian = angle * 3.14159265358979323846 / 180.0;
    double cosTheta = cos(radian);
    double sinTheta = sin(radian);

    // ȸ���� �̹��� ����
    CImage rotatedImage;
    rotatedImage.Create(width, height, bpp);

    // ȸ���� �̹����� �ȼ� �� ����
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int offsetX = x - centerX;
            int offsetY = y - centerY;

            // ȸ�� ��ȯ ����
            int rotatedX = static_cast<int>(offsetX * cosTheta - offsetY * sinTheta + centerX);
            int rotatedY = static_cast<int>(offsetX * sinTheta + offsetY * cosTheta + centerY);

            // ȸ���� ��ǥ�� ��ȿ���� Ȯ��
            if (rotatedX >= 0 && rotatedX < width && rotatedY >= 0 && rotatedY < height) {
                // ���� �̹������� �ش� ��ǥ�� �ȼ� ���� �����ͼ� ȸ���� �̹����� ����
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
