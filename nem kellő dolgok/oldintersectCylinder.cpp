void calculateIntersection() {
        // Calculate coefficients for the quadratic equation
        double a = direction[0] * direction[0] + direction[1] * direction[1];
        double b = 2 * (position[0] * direction[0] + position[1] * direction[1]);
        double c = position[0] * position[0] + position[1] * position[1] - R * R;

        // Calculate the discriminant
        double discriminant = b * b - 4 * a * c;

        // No intersection if discriminant is negative
        if (discriminant < 0) {
            return;
        }
        // One intersection if discriminant is zero
        else if (discriminant == 0) {
            double t = -b / (2 * a);
            double z = position[2] + t * direction[2];

            // Check if the intersection point lies within the height range of the cylinder and in front of the line point
            if (z >= -h / 2 && z <= h / 2 && t >= 0) {
                // Check if the intersection point is in the direction of the line
                std::vector<double> intersectionPoint = {position[0] + t * direction[0], position[1] + t * direction[1], z};
                std::vector<double> lineDirection = {direction[0], direction[1], direction[2]};
                double dotProduct = lineDirection[0] * (intersectionPoint[0] - position[0]) + lineDirection[1] * (intersectionPoint[1] - position[1]) + lineDirection[2] * (intersectionPoint[2] - position[2]);

                if (dotProduct >= 0) {
                    intersection[0] = 1; // One intersection
                    intersection[1] = intersectionPoint[0];
                    intersection[2] = intersectionPoint[1];
                    intersection[3] = intersectionPoint[2];
                }
            }
        }
        // Two intersections if discriminant is positive
        else {
            double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
            double t2 = (-b - std::sqrt(discriminant)) / (2 * a);
            double z1 = position[2] + t1 * direction[2];
            double z2 = position[2] + t2 * direction[2];

            // Check if the intersection points lie within the height range of the cylinder and in front of the line point
            bool isIntersection1InRange = (z1 >= -h / 2 && z1 <= h / 2 && t1 >= 0);
            bool isIntersection2InRange = (z2 >= -h / 2 && z2 <= h / 2 && t2 >= 0);

            if (isIntersection1InRange && isIntersection2InRange) {
                // Both intersection points are in range, check if they are in the direction of the line
                std::vector<double> intersectionPoint1 = {position[0] + t1 * direction[0], position[1] + t1 * direction[1], z1};
                std::vector<double> intersectionPoint2 = {position[0] + t2 * direction[0], position[1] + t2 * direction[1], z2};
                std::vector<double> lineDirection = {direction[0], direction[1], direction[2]};
                double dotProduct1 = lineDirection[0] * (intersectionPoint1[0] - position[0]) + lineDirection[1] * (intersectionPoint1[1] - position[1]) + lineDirection[2] * (intersectionPoint1[2] - position[2]);
                double dotProduct2 = lineDirection[0] * (intersectionPoint2[0] - position[0]) + lineDirection[1] * (intersectionPoint2[1] - position[1]) + lineDirection[2] * (intersectionPoint2[2] - position[2]);

                if (dotProduct1 >= 0 && dotProduct2 >= 0) {
                    // Both intersection points are in the direction of the line, choose the closest one to the line point
                    double dist1 = std::sqrt(std::pow(position[0] + t1 * direction[0], 2) + std::pow(position[1] + t1 * direction[1], 2) + std::pow(z1 - position[2], 2));
                    double dist2 = std::sqrt(std::pow(position[0] + t2 * direction[0], 2) + std::pow(position[1] + t2 * direction[1], 2) + std::pow(z2 - position[2], 2));

                    intersection[0] = 2; // Two intersections

                    if (dist1 <= dist2) {
                        intersection[1] = intersectionPoint1[0];
                        intersection[2] = intersectionPoint1[1];
                        intersection[3] = intersectionPoint1[2];
                    } else {
                        intersection[1] = intersectionPoint2[0];
                        intersection[2] = intersectionPoint2[1];
                        intersection[3] = intersectionPoint2[2];
                    }
                } else if (dotProduct1 >= 0) {
                    intersection[0] = 1; // One intersection
                    intersection[1] = intersectionPoint1[0];
                    intersection[2] = intersectionPoint1[1];
                    intersection[3] = intersectionPoint1[2];
                } else if (dotProduct2 >= 0) {
                    intersection[0] = 1; // One intersection
                    intersection[1] = intersectionPoint2[0];
                    intersection[2] = intersectionPoint2[1];
                    intersection[3] = intersectionPoint2[2];
                }
            } else if (isIntersection1InRange) {
                // Only the first intersection is in range, check if it is in the direction of the line
                std::vector<double> intersectionPoint1 = {position[0] + t1 * direction[0], position[1] + t1 * direction[1], z1};
                std::vector<double> lineDirection = {direction[0], direction[1], direction[2]};
                double dotProduct1 = lineDirection[0] * (intersectionPoint1[0] - position[0]) + lineDirection[1] * (intersectionPoint1[1] - position[1]) + lineDirection[2] * (intersectionPoint1[2] - position[2]);

                if (dotProduct1 >= 0) {
                    intersection[0] = 1; // One intersection
                    intersection[1] = intersectionPoint1[0];
                    intersection[2] = intersectionPoint1[1];
                    intersection[3] = intersectionPoint1[2];
                }
            } else if (isIntersection2InRange) {
                // Only the second intersection is in range, check if it is in the direction of the line
                std::vector<double> intersectionPoint2 = {position[0] + t2 * direction[0], position[1] + t2 * direction[1], z2};
                std::vector<double> lineDirection = {direction[0], direction[1], direction[2]};
                double dotProduct2 = lineDirection[0] * (intersectionPoint2[0] - position[0]) + lineDirection[1] * (intersectionPoint2[1] - position[1]) + lineDirection[2] * (intersectionPoint2[2] - position[2]);

                if (dotProduct2 >= 0) {
                    intersection[0] = 1; // One intersection
                    intersection[1] = intersectionPoint2[0];
                    intersection[2] = intersectionPoint2[1];
                    intersection[3] = intersectionPoint2[2];
                }
            }
        }
    }

    double getIntersectValue(int index) const {
        if (index >= 0 && index < 4) {
            return intersection[index];
        }
        return 0;
    }





