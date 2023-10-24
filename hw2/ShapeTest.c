#include <malloc.h>
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;


typedef double (*double_method_type)(void *);
typedef void (*void_method_type)(void *);

typedef union {
    double_method_type double_method; // this is for area()
    void_method_type void_method;     // this is for draw()
} VirtualTableEntry;

typedef VirtualTableEntry * VTableType;




struct Shape
{
    VTableType VPointer;
    string name;
};

Shape* Shape_Shape(Shape* _this, string name) {
    _this->VPointer = nullptr;
    _this->name = name;
    return _this;
}




struct Circle
{
    VTableType VPointer;
    string name;
    double radius;
};


double circle_area(Circle *_this) {
    return M_PI * _this->radius * _this->radius;
}

void circle_draw(Circle *_this) {
    cout << "  O  \n" << endl;
}

void circle_print(Circle *_this) {
    cout << _this->name << "(" << _this->radius << ") : " << circle_area(_this) << endl;
}

VirtualTableEntry circle_vtable[] = {
    { .double_method = (double_method_type)circle_area },
    { .void_method = (void_method_type)circle_draw },
    { .void_method = (void_method_type)circle_print}
};

Circle* Circle_Circle(Circle * _this, string name, double radius) {
    Shape_Shape((Shape *)_this, name);
    _this->VPointer = circle_vtable;
    _this->radius = radius;
    return _this;
}




struct Square
{
    VTableType VPointer;
    string name;
    int side;
};

double square_area(Square *_this) {
    return _this->side * _this->side;
}

void square_draw(Square *_this) {
    cout << "*******\n*     *\n*     *\n*******\n" << endl;
}

void square_print(Square *_this) {
    cout << _this->name << "(" << _this->side << ") : " << square_area(_this) << endl;
}

VirtualTableEntry square_vtable[] = {
    { .double_method = (double_method_type)square_area },
    { .void_method = (void_method_type)square_draw },
    { .void_method = (void_method_type)square_print }
};

Square* Square_Square(Square * _this, string name, int side) {
    Shape_Shape((Shape *)_this, name);
    _this->VPointer = square_vtable;
    _this->side = side;
    return _this;
}





struct Triangle {
    VTableType VPointer;
    string name;
    int base, height;
};

double triangle_area(Triangle *_this) {
    return 0.5 * _this->base * _this->height;
}

void triangle_draw(Triangle *_this) {
    cout << "  *  \n * * \n*****\n" << endl;
}

void triangle_print(Triangle *_this) {
    cout << _this->name << "(" << _this->base << ", " << _this->height << ") : " << triangle_area(_this) << endl;
}


VirtualTableEntry triangle_vtable[] = {
    { .double_method = (double_method_type)triangle_area },
    { .void_method = (void_method_type)triangle_draw },
    { .void_method = (void_method_type)triangle_print }
};

Triangle* Triangle_Triangle(Triangle * _this, string name, int base, int height) {
    Shape_Shape((Shape *)_this, name);
    _this->VPointer = triangle_vtable;
    _this->base = base;
    _this->height = height;
    return _this;
}





struct Rectangle {
    VTableType VPointer;
    string name;
    int side, width;
};

double rectangle_area(Rectangle *_this) {
    return _this->side * _this->width;
}

void rectangle_draw(Rectangle *_this) {
    cout << "************\n*          *\n*          *\n*          *\n************\n" << endl;
}

void rectangle_print(Rectangle *_this) {
    cout << _this->name << "(" << _this->side << ", " << _this->width << ") : " << rectangle_area(_this) << endl;
}


VirtualTableEntry rectangle_vtable[] = {
    { .double_method = (double_method_type)rectangle_area },
    { .void_method = (void_method_type)rectangle_draw },
    { .void_method = (void_method_type)rectangle_print }
};


Rectangle* Rectangle_Rectangle(Rectangle * _this, string name, int side, int width) {
    Square_Square((Square *)_this, name, side);
    _this->VPointer = rectangle_vtable;
    _this->width = width;
    return _this;
}



void totalArea(Shape **shapes, int numShapes) {
    double total = 0.0;
    for (int i = 0; i < numShapes; ++i) {
        total += shapes[i]->VPointer[0].double_method((void*)shapes[i]);
    }
    cout << "Total : " << total << endl;
}

void drawAll(Shape **shapes, int numShapes) {
    for (int i = 0; i < numShapes; ++i) {
        shapes[i]->VPointer[1].void_method((void*)shapes[i]);
    }
}

void printAll(Shape **shapes, int numShapes) {
    for (int i = 0; i < numShapes; ++i) {
        shapes[i]->VPointer[2].void_method((void*)shapes[i]);
    }
}



int main(int argc, char *argv[]) {
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    Shape *shapes[8];
    shapes[0] = (Shape*) Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "FirstTriangle", x, y);
    shapes[1] = (Shape*) Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "SecondTriangle", x-1, y-1);
    shapes[2] = (Shape*) Circle_Circle((Circle *)malloc(sizeof(Circle)), "FirstCircle", x);
    shapes[3] = (Shape*) Circle_Circle((Circle *)malloc(sizeof(Circle)), "SecondCircle", x-1);
    shapes[4] = (Shape*) Square_Square((Square *)malloc(sizeof(Square)), "FirstSquare", x);
    shapes[5] = (Shape*) Square_Square((Square *)malloc(sizeof(Square)), "SecondSquare", x-1);
    shapes[6] = (Shape*) Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "FirstRectangle", x, y);
    shapes[7] = (Shape*) Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "SecondRectangle", x-1, y-1);

    drawAll(shapes, 8);
    printAll(shapes, 8);
    totalArea(shapes, 8);

    for (int i = 0; i < 8; ++i) {
        free(shapes[i]);
    }

    return 0;
}