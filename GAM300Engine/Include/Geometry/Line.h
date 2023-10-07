#ifndef LINE_H
#define LINE_H

#include "TDSMath.h"
#include "dotnet/ImportExport.h"
namespace TDS
{

class Line
{
public:
    DLL_API Line();
    DLL_API Line(const Vec3& start, const Vec3& end);
    DLL_API Line(const Line& line);
    DLL_API ~Line();

    // Get the start of the line
    DLL_API Vec3 getStart() const { return start; }

    // Get the end of the line
    DLL_API  Vec3 getEnd() const { return end; }

    // Get the point at distance t along the line
    DLL_API  Vec3 getPoint(float t) const { return start + (end - start) * t; }

    // Get the length of the line
    DLL_API float getLength() const { return (end - start).magnitude(); }

    // Get Direction of the line
    DLL_API Vec3 getDirection() const { return (end - start).normalize(); }

    // Does the point lie along the line?
    DLL_API  bool contains(const Vec3& point, float* t = NULL) const;

private:
    Vec3 start;
    Vec3 end;

};


} // namespace TDS



#endif // LINE_H