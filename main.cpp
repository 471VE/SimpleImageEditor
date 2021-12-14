#include <iostream>
#include <cstdlib>
#include <ctime>

#include "matrix.h"
#include "rgb_matrix.h"
#include "bw_matrix.h"
#include "color.h"
#include "shapes.h"
#include "helper_functions.h"

#include <chrono>
#include <time.h>

using Time = std::chrono::high_resolution_clock;
using ns = std::chrono::nanoseconds;


//using namespace std;

int main() {
    RGBColor blue(102, 205, 255);
    RGBColor green(0, 153, 0);
    RGBColor white(255, 255, 255);
    RGBColor yellow(255, 255, 0);
    RGBColor brown(102, 51, 0);
    RGBColor black(0, 0, 0);
    RGBColor dark_brown(51, 0, 0);
    RGBColor dark_yellow(204, 102, 0);
    RGBColor another_blue(102, 163, 255);
    RGBColor pink(255, 200, 200);
    BWColor gray = BWColor(dark_yellow.getBWColor());    

    //-------------//
    // COLORED CAT //
    //-------------//

    RGBMatrix rgb(400, 400, 0);

    Rectangle bg({0, 0}, 500, 500, blue); // figure is out of matrix bounds
    Circle head({200, 200}, 150, gray); // passing BWColor to RGB Matrix
    Triangle outer_ear1({200, 100}, {350, 25}, {350, 200}, gray);
    Triangle outer_ear2({200, 100}, {50, 25}, {50, 200}, gray);
    Triangle inner_ear1({250, 100}, {325, 65}, {325, 150}, white);
    Triangle inner_ear2({150, 100}, {75, 65}, {75, 150}, white);
    Circle left_eye({150, 200}, 35, green);
    Circle right_eye({250, 200}, 35, green);
    Rectangle left_pupil({140, 170}, 20, 60, black);
    Rectangle right_pupil({240, 170}, 20, 60, black);
    Triangle nose({200, 260}, {190, 250}, {210, 250}, pink);
    Circle left_highlight({150, 190}, 5, white);
    Circle right_highlight({250, 190}, 5, white);

    rgb.draw(bg);
    rgb.draw(head);
    rgb.draw(outer_ear1);
    rgb.draw(outer_ear2);
    rgb.draw(inner_ear1);
    rgb.draw(inner_ear2);
    rgb.draw(left_eye);
    rgb.draw(right_eye);
    rgb.draw(left_pupil);
    rgb.draw(right_pupil);
    rgb.draw(nose);
    rgb.draw(left_highlight);
    rgb.draw(right_highlight);

    rgb.display();

    //------------------//
    // GRAYSCALE SMILEY //
    //------------------//

    BWMatrix bw(400, 400, 0);

    Triangle background({-400, 400}, {200, -200}, {800, 400}, gray); // figure out of bounds
    Circle face({200, 200}, 150, yellow); // passing RGB Color to BW Matrix
    Circle lower_lip({200, 200}, 100, black);
    Circle upper_lip({200, 200}, 90, yellow);
    Rectangle hide_unnecessary_lines({100, 100}, 200, 150, yellow);
    Circle left_eye_smiley({150, 150}, 25, black);
    Circle right_eye_smiley({250, 150}, 25, black);
    Circle left_eye_pupil_smiley({160, 140}, 5, white);
    Circle right_eye_pupil_smiley({260, 140}, 5, white);

    bw.draw(background);
    bw.draw(face);
    bw.draw(lower_lip);
    bw.draw(upper_lip);
    bw.draw(hide_unnecessary_lines);
    bw.draw(left_eye_smiley);
    bw.draw(right_eye_smiley);
    bw.draw(left_eye_pupil_smiley);
    bw.draw(right_eye_pupil_smiley);

    bw.display();    

    //-------------------------//
    // PERFORMANCE MEASUREMENT //
    //-------------------------//

    std::cout << "|-------------------------|" << std::endl;
    std::cout << "| PERFORMANCE MEASUREMENT |" << std::endl;
    std::cout << "|-------------------------|" << std::endl;
    int iterations = 10;

    // House from the examples
    Time::time_point start = Time::now();
    for (int i = 0; i < iterations; ++i) {
        RGBMatrix rgb(2000, 2000, 0);
        RGBColor rgbColor(102, 205, 255);
        Rectangle sky({0, 0}, 2000, 1500, rgbColor);
        rgbColor.changeColor(0, 153, 0);
        Rectangle grass({0, 1500}, 2000, 2000, rgbColor);
        rgbColor.changeColor(255, 255, 0);
        Circle sun({50, 50}, 300, rgbColor);
        Triangle ray1({360, 50}, {550, 30}, {550, 70}, rgbColor);
        Triangle ray2({270, 270}, {420, 360}, {390, 400}, rgbColor);
        Triangle ray3({50, 360}, {30, 550}, {70, 550}, rgbColor);
        rgbColor.changeColor(102, 51, 0);
        Rectangle wall({600, 900}, 1000, 800, rgbColor);
        rgbColor.changeColor(0, 0, 0);
        Rectangle flue({1300, 550}, 100, 200, rgbColor);
        rgbColor.changeColor(51, 0, 0);
        Triangle roof({560, 900}, {1100, 500}, {1640, 900}, rgbColor);
        rgbColor.changeColor(204, 102, 0);
        Rectangle door({1400, 1350}, 150, 300, rgbColor);
        rgbColor.changeColor(0, 0, 0);
        Circle knob({1535, 1500}, 6, rgbColor);
        rgbColor.changeColor(102, 163, 255);
        Rectangle window1({700, 950}, 300, 350, rgbColor);
        Rectangle window2({1200, 950}, 300, 350, rgbColor);

        rgb.draw(sky);
        rgb.draw(grass);
        rgb.draw(sun);
        rgb.draw(ray1);
        rgb.draw(ray2);
        rgb.draw(ray3);
        rgb.draw(wall);
        rgb.draw(flue);
        rgb.draw(roof);
        rgb.draw(door);
        rgb.draw(knob);
        rgb.draw(window1);
        rgb.draw(window2);
    }
    Time::time_point end = Time::now();
    double duration = std::chrono::duration_cast<ns>(end - start).count() * 1e-6;
    std::cout << "House drawing execution time: " << duration / iterations << " ms on average over " << iterations << " iterations." << std::endl;

    // Mushroom from the examples
    start = Time::now();
    for (int i = 0; i < iterations; ++i) {
        int bgColor = 255;
        int capColor = 179;
        int stipeColor = 128;
        int bottomColor = 52;
        BWMatrix bw(2000, 2000, 255);
        BWColor bwColor(capColor);
        Circle cap({1000, 1000}, 700, bwColor);
        bwColor.changeColor(bgColor);
        Rectangle background({0, 700}, 2000, 1000, bwColor);
        Rectangle background2({800, 1300}, 400, 200, bwColor);
        bwColor.changeColor(stipeColor);
        Triangle stipe({1000, 350}, {1200, 1500}, {800, 1500}, bwColor);
        bwColor.changeColor(capColor);
        Rectangle background3({800, 350}, 400, 350, bwColor);
        bwColor.changeColor(bottomColor);
        Circle bottom({1000, 1500}, 200, bwColor);

        bw.draw(cap);
        bw.draw(background);
        bw.draw(bottom);
        bw.draw(background2);
        bw.draw(stipe);
        bw.draw(background3);
    }
    end = Time::now();
    duration = std::chrono::duration_cast<ns>(end - start).count() * 1e-6;
    std::cout << "Mushroom drawing execution time: " << duration / iterations << " ms on average over " << iterations << " iterations." << std::endl;

    return 0;
}
