
struct Vec2 {
    float x,y;
    Vec2(){}
    Vec2(float X, float Y) : x(X), y(Y) {}
};
struct Vec3{
    float x,y,z;
    Vec3(float X,float Y, float Z) : x(X), y(Y), z(Z) {}
};
struct CCAffineTransform {
float a,b,c,d,tx,ty;
};
struct CCPoint {
 float x,y;
 CCPoint() : x(0),y(0){}
 CCPoint(float X,float Y) : x(X), y(Y) {}
};
struct CCSize {
float width,height;
CCSize() : width(0), height(0){}
CCSize(float w,float h) : width(w), height(h) {}
};
struct CCRect {
CCPoint origin;
CCSize size;
CCRect(){}
CCRect(float x, float y, float w, float h){
    origin = CCPoint(x,y);
    size = CCSize(w,h);
}
};

struct cpVec {
    float x,y;
    cpVec() : x(0), y(0) {}
    cpVec(float X,float Y) : x(X), y(Y) {}
};

struct Mat4{
    float m[16];
};
