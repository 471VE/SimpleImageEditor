#include "helper_functions.h"
#include <cmath>
#include <algorithm>


int TriangleAreaDoubled(const Point& vertexA, const Point& vertexB, const Point& vertexC)
{
    return std::abs(vertexA.x * (vertexB.y - vertexC.y) +
                    vertexB.x * (vertexC.y - vertexA.y) +
                    vertexC.x * (vertexA.y - vertexB.y));
}


void WriteTrianglePoints(const Point& vertexA, const Point& vertexB, const Point& vertexC, std::vector<Point>& points)
{
    int min_x = std::min({vertexA.x, vertexB.x, vertexC.x});
    int max_x = std::max({vertexA.x, vertexB.x, vertexC.x});

    int min_y = std::min({vertexA.y, vertexB.y, vertexC.y});
    int max_y = std::max({vertexA.y, vertexB.y, vertexC.y});
    int S2_ABC = TriangleAreaDoubled(vertexA, vertexB, vertexC);

    for (int x = min_x; x <= max_x; ++x) {
        for (int y = min_y; y <= max_y; ++y) {
            int S2_ABP = TriangleAreaDoubled(vertexA, vertexB, {x, y});
            int S2_BCP = TriangleAreaDoubled(vertexB, vertexC, {x, y});
            int S2_CAP = TriangleAreaDoubled(vertexC, vertexA, {x, y});
            if (S2_ABC == S2_ABP + S2_BCP + S2_CAP) {
                points.push_back({x, y});
            }
        }
    }
}


void WriteCirclePoints(const Point& center, const int& radius, std::vector<Point>& points)
{
    for (int x = 0; x <= radius; ++x) {
        for (int y = 0; y <= radius; ++y) {
            if (x * x + y * y < radius * radius) {
                points.push_back({center.x + x, center.y + y});
                points.push_back({center.x - x, center.y + y});
                points.push_back({center.x + x, center.y - y});
                points.push_back({center.x - x, center.y - y});
            }
        }
    }
}

void WriteRectanglePoints(const Point& corner, const int& width, const int& height, std::vector<Point>& points)
{
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            points.push_back({corner.x + x, corner.y + y});
        }
    }
}