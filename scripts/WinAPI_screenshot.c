/*
    *THIS FILE IS JUST A TEST OF SCREENSHOT USING WINDOWS API*
    To run this screeshot with WinAPI use:
        gcc WinAPI_screenshot.c -o main.exe -lgdi32
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROI_W 450
#define ROI_H 450

typedef struct GlobalVectors{
    int x;
    int y;
    int w;
    int h;
} GlobalVectors;

typedef struct Dispatcher{
    HWND hwnd;
    RECT clientRect;
    POINT topLeft;
    GlobalVectors gv;
} Dispatcher;

typedef struct Frame{
    HDC hScreen;
    HDC hdcMem;
    HBITMAP hBitmap;
    HBITMAP oldBitMap;

    BITMAP bmp;
    BITMAPINFOHEADER bi;

    DWORD bmpSize;

    unsigned char *img;
    unsigned char *gray_img;

    int x;
    int y;
} Frame;

typedef struct ContainerCTX{
    Dispatcher dispatcher;
    Frame frame;
    int running;
} ContainerCTX;

void DestroyFrame(Frame *frame){
    if(frame == NULL)
        return;

    if(frame->hdcMem && frame->oldBitMap){
        SelectObject(frame->hdcMem, frame->oldBitMap);
        frame->oldBitMap = NULL;
    }

    if(frame->hBitmap){
        DeleteObject(frame->hBitmap);
        frame->hBitmap = NULL;
    }

    if(frame->hdcMem){
        DeleteDC(frame->hdcMem);
        frame->hdcMem = NULL;
    }

    if(frame->hScreen){
        ReleaseDC(NULL, frame->hScreen);
        frame->hScreen = NULL;
    }

    if(frame->img){
        free(frame->img);
        frame->img = NULL;
    }

    if(frame->gray_img){
        free(frame->gray_img);
        frame->gray_img = NULL;
    }
}

int FindWindow(Dispatcher *dispatcher){
    dispatcher->hwnd = FindWindowA(NULL, "Untitled - Notepad"); // Sensitive case 

    if(!dispatcher->hwnd){
        printf("ERROR! FindWindowA()\n");
        return 0;
    }

    return 1;
}

int UpdateWindowMetrics(Dispatcher *dispatcher){
    if(GetClientRect(dispatcher->hwnd, &dispatcher->clientRect) == 0){
        printf("ERROR! GetClientRect()\n");
        return 0;
    }

    dispatcher->topLeft.x = 0;
    dispatcher->topLeft.y = 0;

    if(ClientToScreen(dispatcher->hwnd, &dispatcher->topLeft) == 0){
        printf("ERROR! ClientToScreen()\n");
        return 0;
    }

    dispatcher->gv.x = dispatcher->topLeft.x;
    dispatcher->gv.y = dispatcher->topLeft.y;

    dispatcher->gv.w = dispatcher->clientRect.right;
    dispatcher->gv.h = dispatcher->clientRect.bottom;

    return 1;
}

int InitFrame(Dispatcher *dispatcher, Frame *frame){
    memset(frame, 0, sizeof(Frame));

    frame->x = dispatcher->topLeft.x +
              ((dispatcher->gv.w - ROI_W) / 2);

    frame->y = dispatcher->topLeft.y +
              ((dispatcher->gv.h - ROI_H) / 2);

    frame->hScreen = GetDC(NULL);
    if(!frame->hScreen){
        printf("ERROR! GetDC()\n");
        return 0;
    }

    frame->hdcMem = CreateCompatibleDC(frame->hScreen);
    if(!frame->hdcMem){
        printf("ERROR! CreateCompatibleDC()\n");
        DestroyFrame(frame);
        return 0;
    }

    frame->hBitmap =
        CreateCompatibleBitmap(frame->hScreen, ROI_W, ROI_H);

    if(!frame->hBitmap){
        printf("ERROR! CreateCompatibleBitmap()\n");
        DestroyFrame(frame);
        return 0;
    }

    frame->oldBitMap =
        SelectObject(frame->hdcMem, frame->hBitmap);

    if(frame->oldBitMap == NULL ||
       frame->oldBitMap == HGDI_ERROR){
        printf("ERROR! SelectObject()\n");
        DestroyFrame(frame);
        return 0;
    }

    if(GetObject(frame->hBitmap,
                 sizeof(BITMAP),
                 &frame->bmp) == 0){
        printf("ERROR! GetObject()\n");
        DestroyFrame(frame);
        return 0;
    }

    memset(&frame->bi, 0, sizeof(BITMAPINFOHEADER));

    frame->bi.biSize = sizeof(BITMAPINFOHEADER);
    frame->bi.biWidth = ROI_W;
    frame->bi.biHeight = -ROI_H;
    frame->bi.biPlanes = 1;
    frame->bi.biBitCount = 32;
    frame->bi.biCompression = BI_RGB;

    frame->bmpSize = ROI_W * ROI_H * 4;

    frame->img = malloc(frame->bmpSize);
    if(!frame->img){
        printf("ERROR! malloc(img)\n");
        DestroyFrame(frame);
        return 0;
    }

    frame->gray_img = malloc(ROI_W * ROI_H);
    if(!frame->gray_img){
        printf("ERROR! malloc(gray_img)\n");
        DestroyFrame(frame);
        return 0;
    }

    return 1;
}

int GetFrame(Frame *frame){
    if(BitBlt(frame->hdcMem,
              0,
              0,
              ROI_W,
              ROI_H,
              frame->hScreen,
              frame->x,
              frame->y,
              SRCCOPY) == 0){
        printf("ERROR! BitBlt()\n");
        return 0;
    }

    if(GetDIBits(frame->hdcMem,
                 frame->hBitmap,
                 0,
                 ROI_H,
                 frame->img,
                 (BITMAPINFO*)&frame->bi,
                 DIB_RGB_COLORS) == 0){
        printf("ERROR! GetDIBits()\n");
        return 0;
    }

    for(int i = 0, j = 0;
        i < frame->bmpSize;
        i += 4, j++){

        unsigned char b = frame->img[i];
        unsigned char g = frame->img[i + 1];
        unsigned char r = frame->img[i + 2];

        frame->gray_img[j] =
            (unsigned char)(
                0.299 * r +
                0.587 * g +
                0.114 * b
            );
    }

    return 1;
}

int SaveBMP(Frame *frame, const char *filename){
    FILE *fp = fopen(filename, "wb");

    if(!fp){
        printf("ERROR! fopen()\n");
        return 0;
    }

    BITMAPFILEHEADER bfh = {0};

    bfh.bfType = 0x4D42;
    bfh.bfOffBits =
        sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPINFOHEADER);

    bfh.bfSize =
        bfh.bfOffBits +
        frame->bmpSize;

    BITMAPINFOHEADER bih = frame->bi;
    bih.biHeight = ROI_H;

    fwrite(&bfh, sizeof(bfh), 1, fp);
    fwrite(&bih, sizeof(bih), 1, fp);
    fwrite(frame->img, frame->bmpSize, 1, fp);

    fclose(fp);

    printf("saved: %s\n", filename);

    return 1;
}

void GetScreenShot(ContainerCTX *ctx){
    printf("Capture Thread\n");

    if(!InitFrame(&ctx->dispatcher, &ctx->frame))
        return;

    if(!GetFrame(&ctx->frame)){
        DestroyFrame(&ctx->frame);
        return;
    }

    if(!SaveBMP(&ctx->frame, "roi.bmp")){
        DestroyFrame(&ctx->frame);
        return;
    }

    DestroyFrame(&ctx->frame);
}

int main(void){
    ContainerCTX ctx = {0};

    ctx.running = 1;

    if(!FindWindow(&ctx.dispatcher))
        return 1;

    if(!UpdateWindowMetrics(&ctx.dispatcher))
        return 1;

    GetScreenShot(&ctx);

    printf("x: %d\n", ctx.dispatcher.gv.x);
    printf("y: %d\n", ctx.dispatcher.gv.y);
    printf("w: %d\n", ctx.dispatcher.gv.w);
    printf("h: %d\n", ctx.dispatcher.gv.h);

    return 0;
}