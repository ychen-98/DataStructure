#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

struct Point {
    double x, y;
};

struct Circle {
    Point center;
    double radius;
};

struct Rectangle {
    Point p1, p2, p3, p4;
};

const double RESOLUTION = 0.001; // Set to 0.001 rads

bool isOverlapping(const Circle& c1, const Circle& c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double distance = std::sqrt(dx * dx + dy * dy);
    return distance <= (c1.radius + c2.radius);
}

bool overlapsWithOrigin(const Circle& circle) {
    double distance = std::sqrt(circle.center.x * circle.center.x + circle.center.y * circle.center.y);
    return distance < circle.radius;
}

// Generate a tilted rectangle in circle
Rectangle rectangleInCircle(const Circle& circle) {
    Rectangle rectangle = {};
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_real_distribution<double> tilt_angle_dist(0.1, 2.0 * M_PI);
    std::uniform_real_distribution<double> point_on_tilted_line(0.3, circle.radius);

    double theta = tilt_angle_dist(rng);
    double point_to_center = point_on_tilted_line(rng);
    double alpha = acos(point_to_center/circle.radius);

    // Top-left vertex (x1, y1)
    rectangle.p1.x = std::round( (circle.center.x - circle.radius * cos(M_PI-theta-alpha)) * 100) / 100.0;
    rectangle.p1.y = std::round( (circle.center.y + circle.radius * sin(M_PI-theta-alpha)) * 100) / 100.0;

    // Top-right vertex (x2, y2)
    rectangle.p2.x = std::round( (circle.center.x + circle.radius * cos(theta-alpha)) * 100) / 100.0;
    rectangle.p2.y = std::round( (circle.center.y + circle.radius * sin(theta-alpha)) * 100) / 100.0;

    // Bottom-right vertex (x3, y3)
    rectangle.p3.x = std::round( (circle.center.x + circle.radius * cos(M_PI-theta-alpha)) * 100) / 100.0;
    rectangle.p3.y = std::round( (circle.center.y - circle.radius * sin(M_PI-theta-alpha)) * 100) / 100.0;

    // Bottom-left vertex (x4, y4)
    rectangle.p4.x = std::round( (circle.center.x - circle.radius * cos(theta-alpha)) * 100) / 100.0;
    rectangle.p4.y = std::round( (circle.center.y - circle.radius * sin(theta-alpha)) * 100) / 100.0;

    return rectangle;
}

// angle to origin from point
double angleToOrigin(Point p) {
    return atan2(p.y, p.x);
}

std::vector<std::pair<double, double>>coverageAnglesFromRectangleToOrigin(const Rectangle &rect) {
    std::vector<double> angles = {
            angleToOrigin(rect.p1),
            angleToOrigin(rect.p2),
            angleToOrigin(rect.p3),
            angleToOrigin(rect.p4)
    };

    std::sort(angles.begin(), angles.end());

    // Check for wrap around discontinuity around pi and negative pi
    // Given the range from π to −π, if a rectangle wraps around that boundary (in both Quadrant 2 and Quadrant 3),
    // its coverage angle will essentially be in two segments.
    if (angles[3] - angles[0] > M_PI) {
        double smallest_positive = M_PI; // starting with an upper bound
        double largest_negative = -M_PI; // starting with a lower bound

        for (double angle : angles) {
            if (angle > 0) smallest_positive = std::min(smallest_positive, angle);
            if (angle < 0) largest_negative = std::max(largest_negative, angle);
        }

        return { {smallest_positive, M_PI}, {-M_PI, largest_negative} };
    } else {
        return { {angles[0], angles[3]} };
    }
}


int main() {
    std::random_device rd;
    std::mt19937_64 rng(rd()); // Use random_device directly as the seed

    std::uniform_real_distribution<double> radius_dist(1.00, 10.00);
    std::uniform_real_distribution<double> coordinate_dist(-25.00, 25.00);

    int N; // user-defined: Number of circles
    std::cout << "Enter the number of circles (N): ";
    std::cin >> N;

    std::vector<Circle> circles;

    while (circles.size() < N) {
        Circle newCircle = {};
        newCircle.radius = std::round(radius_dist(rng) * 100) / 100.0; // Restrict to 2 decimal places
        newCircle.center.x = std::round(coordinate_dist(rng) * 100) / 100.0;
        newCircle.center.y = std::round(coordinate_dist(rng) * 100) / 100.0;

        // Check if the circle overlaps with the origin or any existing circles
        bool overlap = false;
        if (overlapsWithOrigin(newCircle)) {
            overlap = true;
        } else {
            for (const Circle& existingCircle : circles) {
                if (isOverlapping(newCircle, existingCircle)) {
                    overlap = true;
                    break;
                }
            }
        }

        // If there's no overlap, add the circle to the vector
        if (!overlap) {
            circles.push_back(newCircle);
        }
    }

    std::vector<Rectangle> rectangles;

    for (const Circle& circle : circles) {
        Rectangle rectangle = rectangleInCircle(circle);
        rectangles.push_back(rectangle);
    }

    int size = static_cast<int>(2 * M_PI / RESOLUTION) + 1;
    std::vector<int> coverage(size, 0);     // Create the coverage vector with the specified size

    std::vector<std::vector<std::pair<double, double>>> rectangleAngleRanges(N);  // Adjusted to be a vector of pairs

    for (int i = 0; i < rectangles.size(); ++i) {
            rectangleAngleRanges[i] = coverageAnglesFromRectangleToOrigin(rectangles[i]);  // Assigning the right data
        }

// compute occlusions
    double sumAngle = 0.0;

    for (int i = 0; i < N; ++i) {
            for (const auto& range_i : rectangleAngleRanges[i]) {
                        int start = int(range_i.first / RESOLUTION);
                        int end = int(range_i.second / RESOLUTION);
                        for (int k = start; k <= end; ++k) {
                            if (coverage[k] == 0) {  // if not already covered by another rectangle
                                coverage[k] = 1;
                            }
                            else if (coverage[k] == 1) {  // if already covered by another rectangle
                                coverage[k] = 2;
                                sumAngle += RESOLUTION;
                            }
                        }
                    }
                }


    // Below codes are for output only
    // Output the circle data in a format ready for R
 std::cout << "data for random non-overlapping circles in R format, \n" << "x_coords = c(";
    for (size_t i = 0; i < circles.size(); ++i) {
        std::cout << circles[i].center.x;
        if (i < circles.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "), \n";

    std::cout << "y_coords = c(";
    for (size_t i = 0; i < circles.size(); ++i) {
        std::cout << circles[i].center.y;
        if (i < circles.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "), \n";

    std::cout << "radii = c(";
    for (size_t i = 0; i < circles.size(); ++i) {
        std::cout << circles[i].radius;
        if (i < circles.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ")\n";

    // Output the rectangle data in a format ready for R
    std::cout << "data for random non-overlapping rectangles in R format, \n" ;

    std::cout << "rectangle_x_coords = c(" ;

    for (size_t i = 0; i < rectangles.size(); ++i) {
        std::cout << rectangles[i].p1.x << ", " << rectangles[i].p2.x << ", "
                  << rectangles[i].p3.x << ", " << rectangles[i].p4.x ;
        if (i < rectangles.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "), \n";

    std::cout << "rectangle_y_coords = c(";
    for (size_t i = 0; i < rectangles.size(); ++i) {
        std::cout << rectangles[i].p1.y << ", " << rectangles[i].p2.y << ", "
                  << rectangles[i].p3.y << ", " << rectangles[i].p4.y ;
        if (i < rectangles.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "), \n";

    std::cout << "Sum of all occluded angles: " << sumAngle  << " rads" << std::endl;

    return 0;
}