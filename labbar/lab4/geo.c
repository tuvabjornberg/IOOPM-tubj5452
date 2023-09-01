# include <stdio.h>
# include <stdbool.h>

struct point {
    int x; //en post
    int y; //en post
}; 
typedef struct point point_t; 

struct rectangle {
    point_t upper_left; 
    point_t lower_right; 
};
typedef struct rectangle rectangle_t; 

// p->x är samma sak som (*p).x, "ge mig punkten som p pekar på och hämta ut från fältet x"

void print_point(point_t *cor) {
    printf("(%d, %d)", cor->x, cor->y); 
}

void print_rect(rectangle_t *rect) {
    point_t *upper_left = &(rect->upper_left); 
    point_t *lower_right = &(rect->lower_right); 

    printf("rectangle(upper_left = "); 
    print_point(upper_left); 
    printf(", lower_right = "); 
    print_point(lower_right); 
    printf(")\n"); 
}

point_t make_point(int a, int b) {
    return (point_t) { .x = a, .y = b}; 
}

rectangle_t make_rect(int a, int b, int c, int d) {
    return (rectangle_t) { .upper_left = make_point(a, b), .lower_right = make_point(c, d)};  
}

int area_rect(rectangle_t *rect) {
    int base = rect->lower_right.x - rect->upper_left.x; //base_left_coordinate - base_right_coordinate
    int height = rect->upper_left.y - rect->lower_right.y; //height_left_coordinate - height_right_coordinate

    return base * height; //area
}

bool intersects_rect(rectangle_t *R1, rectangle_t *R2) {
    if (R1->lower_right.x < R2->upper_left.x || R1->upper_left.x > R2->lower_right.x
        || R1->lower_right.y > R2->upper_left.y || R1->upper_left.y < R2->lower_right.y) {
        return false;
    }
    return true;
}

rectangle_t intersection_rect(rectangle_t *R1, rectangle_t *R2) {
    int start_x = R1->upper_left.x > R2->upper_left.x ? R1->upper_left.x : R2->upper_left.x; //x of upper left 
    int end_x = R1->lower_right.x < R2->lower_right.x ? R1->lower_right.x : R2->lower_right.x; //x of lower right 

    int start_y = R1->upper_left.y <  R2->upper_left.y ? R1->upper_left.y :  R2->upper_left.y; //y of upper left
    int end_y = R1->lower_right.y > R2->lower_right.y ? R1->lower_right.y : R2->lower_right.y; //y of lower right

    return (rectangle_t) { .upper_left = make_point(start_x, start_y), .lower_right = make_point(end_x, end_y)};
}

int main(void) {
    struct point p; 
    p.x = 10; 
    p.y = -42; 

    struct point q = { .x = 11, .y = -43}; 
    point_t s = { .x = 12, .y = -44}; 

    printf("point(x = %d, y = %d)\n", p.x, p.y); 
    printf("point(x = %d, y = %d)\n", q.x, q.y); 
    printf("point(x = %d, y = %d)\n", s.x, s.y); 

    point_t t = { .x = 100, .y = -100}; 
    print_point(&t); 

    point_t m = make_point(5, 10);
    point_t n = make_point(4, 8); 
    print_point(&m);

    rectangle_t r = { .upper_left = m, .lower_right = n}; 
    rectangle_t v = make_rect(1, 4, 5, 2); 
    rectangle_t w = make_rect(2, 6, 6, 3); 
    print_rect(&r); 
    print_rect(&v); 
    printf("%d\n", area_rect(&v)); 

    printf("%d\n", intersects_rect(&v, &w));

    rectangle_t o = intersection_rect(&v, &w); 
    print_rect(&o); 

    rectangle_t a = make_rect(-2, 0, 1, -2); 
    rectangle_t b = make_rect(-3, 3, -1, -1); 
    print_rect(&a); 
    printf("%d\n", area_rect(&a)); 
    printf("%d\n", area_rect(&b));
    printf("%d\n", intersects_rect(&a, &b));

    rectangle_t c = intersection_rect(&a, &b); 
    print_rect(&c); 
    printf("%d\n", area_rect(&c));
}

