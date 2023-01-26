#include "camera_controller.hpp"
#include <cmath>

CameraController::CameraController(PerspectiveCamera *cam, float centerDistance) {
    mpCamera = cam;
    mStartDistance = centerDistance;
}

void CameraController::mouseClick(CameraController::Button button, int x, int y) {

    setFromCamera();
    mStartClick[0] = x;
    mStartClick[1] = y;

    mButtonState = button;
    mCurrentRot = mStartRot;
    mCurrentCenter = mStartCenter;
    mCurrentDistance = mStartDistance;

}

void CameraController::mouseDrag(int x, int y) {
    switch (mButtonState) {
        case LEFT:
            arcBallRotation(x, y);
            break;
        case MIDDLE:
            planeTranslation(x, y);
            break;
        case RIGHT:
            distanceZoom(x, y);
            break;
        default:
            break;
    }
    applyToCamera();
}

void CameraController::mouseRelease(int x, int y) {
    mButtonState = NONE;
    applyToCamera();
    mStartDistance = mCurrentDistance;
}

void CameraController::arcBallRotation(int x, int y) {
    float sx, sy, sz, ex, ey, ez;
    float scale;
    float sl, el;
    float dotprod;

    // find vectors from center of window
    sx = mStartClick[0] - (mViewport[2] / 2.f);
    sy = mStartClick[1] - (mViewport[3] / 2.f);
    ex = x - (mViewport[2] / 2.f);
    ey = y - (mViewport[3] / 2.f);

    // invert y coordinates (raster versus device coordinates)
    sy = -sy; sx = -sx;
    ey = -ey; ex = -ex;

    // scale by inverse of size of window and magical sqrt2 factor
    if (mViewport[2] > mViewport[3]) {
        scale = (float) mViewport[3];
    } else {
        scale = (float) mViewport[2];
    }

    scale = 1.f / scale;

    sx *= scale;
    sy *= scale;
    ex *= scale;
    ey *= scale;

    // project points to unit circle
    sl = std::hypot(sx, sy);
    el = std::hypot(ex, ey);

    if (sl > 1.f) {
        sx /= sl;
        sy /= sl;
        sl = 1.0;
    }
    if (el > 1.f) {
        ex /= el;
        ey /= el;
        el = 1.f;
    }

    // project up to unit sphere - find Z coordinate
    sz = std::sqrt(1.0f - sl * sl);
    ez = std::sqrt(1.0f - el * el);

    // rotate (sx,sy,sz) into (ex,ey,ez)

    // compute angle from dot-product of unit vectors (and double it).
    // compute axis from cross product.
    dotprod = sx * ex + sy * ey + sz * ez;

    if (dotprod != 1) {
        Vector3f axis(sy * ez - ey * sz, sz * ex - ez * sx, sx * ey - ex * sy);
        axis.normalize();

        float angle = 2.0f * std::acos(dotprod);

        mCurrentRot = Matrix3f::rotation(axis, angle);
        mCurrentRot = mCurrentRot * mStartRot;
    } else {
        mCurrentRot = mStartRot;
    }
}

void CameraController::planeTranslation(int x, int y) {
    // map window x,y into viewport x,y

    // start
    int sx = mStartClick[0] - mViewport[0];
    int sy = mStartClick[1] - mViewport[1];

    // current
    int cx = x - mViewport[0];
    int cy = y - mViewport[1];


    // compute "distance" of image plane (wrt projection matrix)
    float d = float(mViewport[3]) / 2.0f / mTanPerspective;

    // compute up plane intersect of clickpoint (wrt fovy)
    float su = -sy + mViewport[3] / 2.0f;
    float cu = -cy + mViewport[3] / 2.0f;

    // compute right plane intersect of clickpoint (ASSUMED FOVY is 1)
    float sr = (sx - mViewport[2] / 2.0f);
    float cr = (cx - mViewport[2] / 2.0f);

    Vector2f move(cr - sr, cu - su);

    // this maps move
    move *= -mCurrentDistance / d;

    mCurrentCenter = mStartCenter +
                     - move[0] * Vector3f(mCurrentRot(0, 0), mCurrentRot(0, 1), mCurrentRot(0, 2))
                     + move[1] * Vector3f(mCurrentRot(1, 0), mCurrentRot(1, 1), mCurrentRot(1, 2));

}

void CameraController::distanceZoom(int x, int y) {
    int sy = mStartClick[1] - mViewport[1];
    int cy = y - mViewport[1];

    float delta = float(cy - sy) / mViewport[3];

    // exponential zoom factor
    mCurrentDistance = mStartDistance * std::exp(delta);
}

void CameraController::applyToCamera() {
    Vector3f t(0.0, 0.0, mCurrentDistance);
    Matrix3f rt = mCurrentRot.transposed();
    mpCamera->setCenter(-(rt * t) + mCurrentCenter);
    mpCamera->setRotation(rt);
}

void CameraController::setFromCamera() {
    mTanPerspective = std::tan(mpCamera->getFovy() / 2.0f);
    mViewport[0] = mViewport[1] = 0;
    mViewport[2] = mpCamera->getWidth();
    mViewport[3] = mpCamera->getHeight();
    mStartRot = mpCamera->getRotation();
    mStartCenter = mpCamera->getCenter() + mStartDistance * mStartRot.getCol(2);
    mStartRot.transpose();
}


