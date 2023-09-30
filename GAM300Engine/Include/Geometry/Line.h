#ifndef LINE_H
#define LINE_H

#include "TDSMath.h"
#include "dotnet/ImportExport.h"
namespace TDS
{

class DLL_API Line
{
public:
    Line();
    Line(const Vec3& start, const Vec3& end);
    Line(const Line& line);
    ~Line();

    // Get the start of the line
    Vec3 getStart() const { return start; }

    // Get the end of the line
    Vec3 getEnd() const { return end; }

    // Get the point at distance t along the line
    Vec3 getPoint(float t) const { return start + (end - start) * t; }

    // Get the length of the line
    float getLength() const { return (end - start).magnitude(); }

    // Get Direction of the line
    Vec3 getDirection() const { return (end - start).normalize(); }

    // Does the point lie along the line?
    bool contains(const Vec3& point, float* t = NULL) const;

private:
    Vec3 start;
    Vec3 end;

};


} // namespace TDS



#endif // LINE_H