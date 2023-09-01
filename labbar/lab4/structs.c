# include <stdio.h>

struct point {
    int x; //en post
    int y; //en post
}; 

typedef struct point point_t; 

//struct point translate(point_t p1, point_t p2) {
//    p1.x += p2.x; 
//    p1.y += p2.y; 
//    return p1; 
//}

void translate(point_t *p1, point_t *p2) {
    p1->x += p2->x;     // p->x är samma sak som (*p).x, "ge mig punkten som p pekar på och hämta ut från fältet x"
    p1->y += p2->y;
}

int main(void) {
    struct point p; 
    p.x = 10; 
    p.y = -42; 

    struct point q = { .x = 11, .y = -43}; 
    point_t s = { .x = 12, .y = -44}; 
    point_t r = { .x = 13, .y = -45}; 
    translate(&r, &r); 


    printf("point(x = %d, y = %d)\n", p.x, p.y); 
    printf("point(x = %d, y = %d)\n", q.x, q.y); 
    printf("point(x = %d, y = %d)\n", s.x, s.y); 



}


