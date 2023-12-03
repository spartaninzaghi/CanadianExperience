/**
 * @file DebugDraw.h
 * @author Charles Owen
 *
 * Debugging support to draw the world from the viewpoint
 * of the physics system.
 *
 * @version 2.00 Updated to support finer lines
 */

#ifndef _DEBUGDRAW_H
#define _DEBUGDRAW_H

#include <b2_draw.h>

/**
 * Debugging support to draw the world from the viewpoint of the physics system.
 */
class DebugDraw : public b2Draw {
private:
    /// Graphics context to draw on
    std::shared_ptr<wxGraphicsContext> mGraphics;

    void SetPenColor(const b2Color& color, int width=1);

    /// Size of a crosshair in meters
    double mCrosshairSize = 0.15;

    /// Setting to a larger value will decrease the width
    /// of drawn lines
    double mFineLine = 1;

public:
    DebugDraw(std::shared_ptr<wxGraphicsContext> graphics);

    /// Default constructor (disabled)
    DebugDraw() = delete;

    /// Copy constructor (disabled)
    DebugDraw(const DebugDraw &) = delete;

    /// Assignment operator
    void operator=(const DebugDraw &) = delete;

    /**
     * Set the lineWidth to draw line. The default is 1cm. Smaller
     * values make the lines smaller.
     * @param lineWidth Width to draw the lines
     */
    void SetLineWidth(double lineWidth) {mFineLine = 1.0/lineWidth;}

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;
    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)  override;
    void DrawCircle (const b2Vec2 &center, float radius, const b2Color &color) override;
    void DrawSolidCircle (const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) override;
    void DrawSegment (const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;
    void DrawTransform(const b2Transform &xf) override;
    void DrawPoint (const b2Vec2 &p, float size, const b2Color &color) override;

};

#endif //_DEBUGDRAW_H
