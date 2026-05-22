#include "CapsuleCollider.h"
#include "Object2D.h"
#include <DxLib.h>
#include <cmath>

namespace {
    float PointPointDistanceSq(const VECTOR& p, const VECTOR& q) {
        float dx = p.x - q.x;
        float dy = p.y - q.y;
        return dx * dx + dy * dy;
    }

    float PointSegmentDistanceSq(const VECTOR& p, const VECTOR& s1, const VECTOR& s2) {
        float vx = s2.x - s1.x;
        float vy = s2.y - s1.y;
        float wx = p.x - s1.x;
        float wy = p.y - s1.y;
        float lenSq = vx * vx + vy * vy;
        if (lenSq < 0.000001f) {
            return PointPointDistanceSq(p, s1);
        }
        float t = (wx * vx + wy * vy) / lenSq;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        float projx = s1.x + t * vx;
        float projy = s1.y + t * vy;
        float dx = p.x - projx;
        float dy = p.y - projy;
        return dx * dx + dy * dy;
    }

    float CrossProduct2D(float x1, float y1, float x2, float y2) {
        return x1 * y2 - y1 * x2;
    }

    bool SegmentsIntersect(const VECTOR& a, const VECTOR& b, const VECTOR& c, const VECTOR& d) {
        float cp1 = CrossProduct2D(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
        float cp2 = CrossProduct2D(b.x - a.x, b.y - a.y, d.x - a.x, d.y - a.y);
        float cp3 = CrossProduct2D(d.x - c.x, d.y - c.y, a.x - c.x, a.y - c.y);
        float cp4 = CrossProduct2D(d.x - c.x, d.y - c.y, b.x - c.x, b.y - c.y);
        
        return (cp1 * cp2 <= 0.0f) && (cp3 * cp4 <= 0.0f);
    }

    float SegmentSegmentDistanceSq(const VECTOR& a, const VECTOR& b, const VECTOR& c, const VECTOR& d) {
        float lenSqAB = (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
        float lenSqCD = (d.x - c.x) * (d.x - c.x) + (d.y - c.y) * (d.y - c.y);

        if (lenSqAB < 0.000001f && lenSqCD < 0.000001f) {
            return PointPointDistanceSq(a, c);
        }
        if (lenSqAB < 0.000001f) {
            return PointSegmentDistanceSq(a, c, d);
        }
        if (lenSqCD < 0.000001f) {
            return PointSegmentDistanceSq(c, a, b);
        }

        if (SegmentsIntersect(a, b, c, d)) {
            return 0.0f;
        }
        float d1 = PointSegmentDistanceSq(a, c, d);
        float d2 = PointSegmentDistanceSq(b, c, d);
        float d3 = PointSegmentDistanceSq(c, a, b);
        float d4 = PointSegmentDistanceSq(d, a, b);
        float minD = d1;
        if (d2 < minD) minD = d2;
        if (d3 < minD) minD = d3;
        if (d4 < minD) minD = d4;
        return minD;
    }
}

CapsuleCollider::CapsuleCollider(Object2D* parent, VECTOR pos1, VECTOR pos2, float radius)
	: Collider(parent)
{
	mvPosition = pos1;
	mvPosition2 = pos2;
	mfRadius = radius;
}

CapsuleCollider::~CapsuleCollider()
{
}

void CapsuleCollider::Update(Collider* check)
{
	if (check != nullptr)
	{
		CapsuleCollider* other = dynamic_cast<CapsuleCollider*>(check);
		if (other != nullptr)
		{
			float distSq = SegmentSegmentDistanceSq(
				this->mvPosition,
				this->mvPosition2,
				other->mvPosition,
				other->mvPosition2
			);

			float radiusSum = this->mfRadius + other->mfRadius;
			bool isHit = distSq <= (radiusSum * radiusSum);

			HitCheck(check, isHit);
		}
	}
}

void CapsuleCollider::Draw()
{
    // Draw visual representation of the 2D Capsule Collider for debug visualization
    unsigned int color = GetColor(0, 255, 0); // Green color for colliders

    // Draw endpoint circles
    DrawCircle(static_cast<int>(mvPosition.x), static_cast<int>(mvPosition.y), static_cast<int>(mfRadius), color, FALSE);
    DrawCircle(static_cast<int>(mvPosition2.x), static_cast<int>(mvPosition2.y), static_cast<int>(mfRadius), color, FALSE);

    // Draw connecting sides if the segment has length
    float dx = mvPosition2.x - mvPosition.x;
    float dy = mvPosition2.y - mvPosition.y;
    float len = std::sqrt(dx * dx + dy * dy);
    if (len > 0.0001f) {
        float nx = -dy / len;
        float ny = dx / len;
        
        int p1x = static_cast<int>(mvPosition.x + nx * mfRadius);
        int p1y = static_cast<int>(mvPosition.y + ny * mfRadius);
        int p2x = static_cast<int>(mvPosition.x - nx * mfRadius);
        int p2y = static_cast<int>(mvPosition.y - ny * mfRadius);
        
        int p3x = static_cast<int>(mvPosition2.x + nx * mfRadius);
        int p3y = static_cast<int>(mvPosition2.y + ny * mfRadius);
        int p4x = static_cast<int>(mvPosition2.x - nx * mfRadius);
        int p4y = static_cast<int>(mvPosition2.y - ny * mfRadius);

        DrawLine(p1x, p1y, p3x, p3y, color);
        DrawLine(p2x, p2y, p4x, p4y, color);
    }
}

void CapsuleCollider::OnEnter()
{
}

void CapsuleCollider::OnTrigger()
{
}

void CapsuleCollider::OnExit()
{
}
