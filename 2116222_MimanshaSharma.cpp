#include<conio.h>
#include<graphics.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<math.h>

#define STAR_COUNT 50
#define BIRD_COUNT 10

int starX[STAR_COUNT], starY[STAR_COUNT];
int birdX[BIRD_COUNT], birdY[BIRD_COUNT];

// Bresenham's line algorithm implementation
void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1) {
        putpixel(x1, y1, getcolor());
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// DDA line algorithm implementation
void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), getcolor());
        x += xInc;
        y += yInc;
    }
}

// Bresenham's circle algorithm implementation
void drawCircleBresenham(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        putpixel(xc + x, yc + y, getcolor());
        putpixel(xc - x, yc + y, getcolor());
        putpixel(xc + x, yc - y, getcolor());
        putpixel(xc - x, yc - y, getcolor());
        putpixel(xc + y, yc + x, getcolor());
        putpixel(xc - y, yc + x, getcolor());
        putpixel(xc + y, yc - x, getcolor());
        putpixel(xc - y, yc - x, getcolor());

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

// Filled circle using Bresenham's algorithm
void drawFilledCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (y >= x) {
        // Draw horizontal lines instead of individual pixels
        drawLineDDA(xc - x, yc + y, xc + x, yc + y);
        drawLineDDA(xc - x, yc - y, xc + x, yc - y);
        drawLineDDA(xc - y, yc + x, xc + y, yc + x);
        drawLineDDA(xc - y, yc - x, xc + y, yc - x);

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void initializeStars() {
    for (int j = 0; j < STAR_COUNT; j++) {
        starX[j] = rand() % 639;
        starY[j] = rand() % 200;
    }
}

void initializeBirds() {
    for (int j = 0; j < BIRD_COUNT; j++) {
        birdX[j] = rand() % 639;
        birdY[j] = 50 + rand() % 150;
    }
}

void drawBirds() {
    setcolor(BLACK);
    for(int j = 0; j < BIRD_COUNT; j++) {
        // Update bird position
        birdX[j] += 2;
        if(birdX[j] > 639) {
            birdX[j] = -20;
            birdY[j] = 50 + rand() % 150;
        }
        
        // Draw bird (simple V shape) using Bresenham's algorithm
        drawLineBresenham(birdX[j], birdY[j], birdX[j]-10, birdY[j]+10);
        drawLineBresenham(birdX[j], birdY[j], birdX[j]+10, birdY[j]+10);
    }
}

void drawDayScene() {
    /*** Draw Sky ***/
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, 639, 389);

    /*** Draw Sun ***/
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(100, 100, 40, 40);

    /*** Draw Clouds ***/
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(200, 100, 50, 30);
    fillellipse(230, 100, 50, 30);
    fillellipse(260, 100, 50, 30);
    fillellipse(400, 80, 40, 25);
    fillellipse(430, 80, 40, 25);
    fillellipse(460, 80, 40, 25);

    /*** Draw Flying Birds ***/
    drawBirds();
}

void drawNightScene() {
    /*** Draw Night Sky ***/
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, 639, 389);

    /*** Draw Moon ***/
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(100, 100, 30, 30);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(110, 100, 25, 25); // Crescent moon effect

    /*** Draw Stars ***/
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    for (int j = 0; j < STAR_COUNT; j++) {
        fillellipse(starX[j], starY[j], 5, 5);
    }
}

void drawRainyScene() {
    /*** Draw Dark Grey Rainy Sky ***/
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, CYAN);
    bar(0, 0, 639, 389);

    /*** Draw Black Clouds ***/
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(180, 100, 50, 30);
    fillellipse(210, 100, 50, 30);
    fillellipse(240, 100, 50, 30);
    fillellipse(400, 80, 60, 35);
    fillellipse(440, 80, 60, 35);
    fillellipse(480, 80, 60, 35);

    /*** Lightning Effect ***/
    if (rand() % 5 == 0) { // Less frequent flashes
        setcolor(YELLOW);
        setlinestyle(0, 0, THICK_WIDTH);
        drawLineDDA(320, 80, 340, 140);
        drawLineDDA(340, 140, 300, 200);
        drawLineDDA(300, 200, 330, 260);
    }

    /*** Draw Rain ***/
    setcolor(LIGHTBLUE);
    for (int j = 0; j < 100; j++) {
        int x = rand() % 639;
        int y = rand() % 389;
        drawLineDDA(x, y, x, y + 10);
    }
}

void drawEveningCityScene() {
    /*** Draw Evening Sky ***/
    setcolor(LIGHTRED);
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(0, 0, 639, 389);

    /*** Draw Setting Sun ***/
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(500, 200, 40, 40);
    
    /*** Draw Clouds ***/
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(400, 100, 50, 30);
    fillellipse(430, 100, 50, 30);
    fillellipse(460, 100, 50, 30);
    fillellipse(200, 80, 40, 25);
    fillellipse(230, 80, 40, 25);
    fillellipse(260, 80, 40, 25);

    /*** Draw Flying Birds ***/
    drawBirds();

    /*** Draw Buildings ***/
    // Pink building
    setcolor(MAGENTA);
    setfillstyle(SOLID_FILL, MAGENTA);
    bar(50, 200, 130, 390);
    // Windows
    setcolor(BLACK);
    for(int y = 220; y < 380; y += 30) {
        for(int x = 60; x < 110; x += 20) {
            rectangle(x, y, x+10, y+15);
        }
    }
    
    // Green building
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(130, 150, 210, 390);
    // Windows
    setcolor(BLACK);
    for(int y = 170; y < 380; y += 30) {
        for(int x = 140; x < 190; x += 20) {
            rectangle(x, y, x+10, y+15);
        }
    }
    
    // RED building
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, RED);
    bar(210, 180, 290, 390);
    // Windows
    setcolor(BLACK);
    for(int y = 200; y < 380; y += 30) {
        for(int x = 220; x < 270; x += 20) {
            rectangle(x, y, x+10, y+15);
        }
    }
    
    // Yellow building
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    bar(290, 120, 370, 390);
    // Windows
    setcolor(BLACK);
    for(int y = 140; y < 380; y += 30) {
        for(int x = 300; x < 350; x += 20) {
            rectangle(x, y, x+10, y+15);
        }
    }
    
    // Blue building
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(370, 160, 450, 390);
    // Windows
    setcolor(BLACK);
    for(int y = 180; y < 380; y += 30) {
        for(int x = 380; x < 430; x += 20) {
            rectangle(x, y, x+10, y+15);
        }
    }
    
    /*** Draw Trees in front of buildings ***/
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    // Tree trunks
    bar(480, 330, 490, 380);
    bar(520, 310, 530, 380);
    bar(560, 320, 570, 380);
    
    // Tree leaves
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(485, 320, 30, 50);
    fillellipse(525, 300, 35, 55);
    fillellipse(565, 310, 40, 60);
}

void drawCountrysideScene() {
    /*** Draw Sky ***/
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, 639, 389);

    /*** Draw Sun ***/
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(100, 100, 40, 40);

    /*** Draw Clouds ***/
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(200, 100, 50, 30);
    fillellipse(230, 100, 50, 30);
    fillellipse(260, 100, 50, 30);
    fillellipse(400, 80, 40, 25);
    fillellipse(430, 80, 40, 25);
    fillellipse(460, 80, 40, 25);

    /*** Draw Flying Birds ***/
    drawBirds();

    /*** Draw Green Grass ***/
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(0, 350, 639, 389);

    /*** Draw House ***/
    // Main house structure (light pink)
    setcolor(LIGHTMAGENTA);
    setfillstyle(SOLID_FILL, LIGHTMAGENTA);
    bar(450, 250, 600, 350);
    
    // Roof
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    int roof[] = {440, 250, 610, 250, 525, 200, 440, 250};
    fillpoly(4, roof);
    
    // Door
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    bar(520, 300, 550, 350);
    
    // Windows
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    bar(470, 270, 500, 300);  // Changed from rectangle to bar
    bar(560, 270, 590, 300);  // Changed from rectangle to bar
    
    // Window panes
    setcolor(BLACK);
    drawLineBresenham(485, 270, 485, 300);
    drawLineBresenham(470, 285, 500, 285);
    drawLineBresenham(575, 270, 575, 300);
    drawLineBresenham(560, 285, 590, 285);

    /*** Draw Trees ***/
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    // Tree trunks
    bar(50, 330, 60, 380);
    bar(100, 320, 110, 380);
    bar(150, 340, 160, 380);
    bar(200, 330, 210, 380);
    bar(250, 320, 260, 380);
    bar(300, 340, 310, 380);
    bar(350, 330, 360, 380);
    
    // Tree leaves
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(55, 320, 25, 40);
    fillellipse(105, 310, 30, 45);
    fillellipse(155, 330, 25, 35);
    fillellipse(205, 320, 30, 40);
    fillellipse(255, 310, 25, 45);
    fillellipse(305, 330, 30, 35);
    fillellipse(355, 320, 25, 40);
}

void drawMountainsAndTrees() {
    /*** Draw Mountains ***/
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    int mountain1[] = {50, 350, 150, 250, 250, 350, 50, 350};
    int mountain2[] = {200, 350, 300, 220, 400, 350, 200, 350};
    int mountain3[] = {350, 350, 450, 260, 550, 350, 350, 350};
    fillpoly(4, mountain1);
    fillpoly(4, mountain2);
    fillpoly(4, mountain3);

    /*** Draw Trees ***/
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    bar(70, 330, 80, 380);
    bar(500, 330, 510, 380);
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(75, 320, 30, 50);
    fillellipse(505, 320, 30, 50);
}

void drawRoad() {
    /*** Draw Road with Zebra Crossing ***/
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(0, 390, 639, 479);
    for (int j = 0; j < 640; j += 40) {
        setfillstyle(SOLID_FILL, WHITE);
        bar(j, 400, j + 20, 410);
    }
}

void drawCar(int i) {
    /*** Car Body Outline (using DDA as in original) ***/
    setcolor(RED);
    drawLineDDA(50+i,370,90+i,370);
    arc(110+i,370,0,180,20);
    drawLineDDA(130+i,370,220+i,370);
    arc(240+i,370,0,180,20);
    drawLineDDA(260+i,370,300+i,370);
    drawLineDDA(300+i,370,300+i,350);
    drawLineDDA(300+i,350,240+i,330);
    drawLineDDA(240+i,330,200+i,300);
    drawLineDDA(200+i,300,110+i,300);
    drawLineDDA(110+i,300,80+i,330);
    drawLineDDA(80+i,330,50+i,340);
    drawLineDDA(50+i,340,50+i,370);

    /*** Fill Car Body (without floodfill) ***/
    setfillstyle(SOLID_FILL, RED);
    int carBody[] = {
        50+i, 370, 
        90+i, 370, 
        110+i, 350,  // Arc point
        130+i, 370, 
        220+i, 370, 
        240+i, 350,  // Arc point
        260+i, 370, 
        300+i, 370, 
        300+i, 350, 
        240+i, 330, 
        200+i, 300, 
        110+i, 300, 
        80+i, 330, 
        50+i, 340, 
        50+i, 370
    };
    fillpoly(sizeof(carBody)/(2*sizeof(int)), carBody);

    /*** Car Windows ***/
    setcolor(BLACK);
    // Rear window outline (DDA as in original)
    drawLineDDA(165+i,305,165+i,330);
    drawLineDDA(165+i,330,230+i,330);
    drawLineDDA(230+i,330,195+i,305);
    drawLineDDA(195+i,305,165+i,305);
    // Rear window fill
    setfillstyle(SOLID_FILL, BLACK);
    int rearWindow[] = {165+i,305, 165+i,330, 230+i,330, 195+i,305};
    fillpoly(4, rearWindow);

    // Front window outline (DDA as in original)
    drawLineDDA(160+i,305,160+i,330);
    drawLineDDA(160+i,330,95+i,330);
    drawLineDDA(95+i,330,120+i,305);
    drawLineDDA(120+i,305,160+i,305);
    // Front window fill
    int frontWindow[] = {160+i,305, 160+i,330, 95+i,330, 120+i,305};
    fillpoly(4, frontWindow);

    /** Wheels **/
    setcolor(BLACK);
    // Wheel outlines (Bresenham as in original)
    drawCircleBresenham(110+i, 370, 17);
    drawCircleBresenham(240+i, 370, 17);
    // Wheel fills
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(110+i, 370, 17, 17);
    fillellipse(240+i, 370, 17, 17);
    
    // Wheel rims
    setcolor(WHITE);
    drawCircleBresenham(110+i, 370, 17);
    drawCircleBresenham(240+i, 370, 17);
}

void animateScene(void (*drawScene)()) {
    int page = 0;
    int max_i = 500;
    
    // For countryside scene, stop the car when it reaches the house
    if(drawScene == drawCountrysideScene) {
        max_i = 300;
    }
    
    for (int i = 0; i < max_i; i++) {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        drawScene();
        if (drawScene != drawEveningCityScene && drawScene != drawCountrysideScene) {
            drawMountainsAndTrees();
        }
        drawRoad();
        
        // For countryside scene, don't move the car beyond the house
        if(drawScene == drawCountrysideScene && i >= 250) {
            drawCar(250);
        } else {
            drawCar(i);
        }

        delay(0);
        page = 1 - page;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "c:\\turboc3\\bgi");
    initializeStars();
    initializeBirds();

    while (!kbhit()) {
        animateScene(drawDayScene);
        animateScene(drawNightScene);
        animateScene(drawRainyScene);
        animateScene(drawEveningCityScene);
        animateScene(drawCountrysideScene);
    }
    getch();
    closegraph();
    return 0;
}