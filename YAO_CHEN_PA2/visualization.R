# install.packages("ggplot2")
# install.packages("ggforce")
library(ggplot2)
library(ggforce)

# Create a data frame with coordinates for the circles, rectangles
N =5 # user-defined in C++

circles_data <- data.frame(
  ### below can be pasted from C++ output 
  x_coords = c(-12.71, -12.36, 21.51, -6.14, -23.6), 
  y_coords = c(21.88, 6.25, 3.87, -5.1, 17.86), 
  radii = c(7.32, 5.79, 1.87, 5.54, 1.91)
  ### above can be pasted from C++ output 
)

rectangles <- data.frame(
  ### below can be pasted from C++ output 
  rectangle_x_coords = c(-6.94, -15.08, -18.48, -10.34, -17.05, -14.2, -7.67, -10.52, 22.24, 20.26, 20.78, 22.76, -11.61, -8.51, -0.67, -3.77, -23.45, -25.29, -23.75, -21.91), 
  rectangle_y_coords = c(26.38, 14.95, 17.38, 28.81, 2.86, 11.74, 9.64, 0.76, 2.15, 2.48, 5.59, 5.26, -5.95, -0.09, -4.25, -10.11, 15.96, 18.75, 19.76, 16.97),   ### above can be pasted from C++ output 
  rectangle_id = rep(1:N, each = 4) # Assign an ID to each rectangle
)


# plot
ggplot() + 
  # Rectangle data and aesthetics
  geom_polygon(data = rectangles, aes(x = rectangle_x_coords, y = rectangle_y_coords, group = rectangle_id), fill = "transparent", color = "red") + 
  # Circle data and aesthetics
  geom_circle(data = circles_data, aes(x0 = x_coords, y0 = y_coords, r = radii), color = "blue") +
  # Highlight the origin
  geom_point(aes(0, 0), color = "black", size = 2) +
  # Draw lines from every point of rectangles to origin
  geom_segment(data = rectangles, aes(x = rectangle_x_coords, y = rectangle_y_coords, xend = 0, yend = 0), color = "green") +
  theme_minimal() + 
  coord_fixed() + 
  labs(x = "X-axis", y = "Y-axis", title = "Combined Plot: Tilted Rectangles and Circles")
