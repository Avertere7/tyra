/*
# ______       ____   ___
#   |     \/   ____| |___|    
#   |     |   |   \  |   |       
#-----------------------------------------------------------------------
# Copyright 2020, tyra - https://github.com/h4570/tyra
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "camera.hpp"

#include <utils/math.hpp>
#include <utils/debug.hpp>

const float CAMERA_Y = 15.0F;

// ----
// Constructors/Destructors
// ----

Camera::Camera(ScreenSettings *t_screen) : CameraBase(t_screen, &position)
{
    PRINT_LOG("Initializing camera");
    verticalLevel = 80.0F;
    PRINT_LOG("Camera initialized!");
}

Camera::~Camera() {}

// ----
// Methods
// ----

void Camera::update(Pad &t_pad, Mesh &t_mesh)
{
    rotate(t_pad);
    followBy(t_mesh);
    Vector3 lookPos = Vector3(t_mesh.position.x, t_mesh.position.y + 10.0F, t_mesh.position.z);
    lookAt(lookPos);
}

/** Set camera rotation by pad right joy and update unit circle
 * https://en.wikipedia.org/wiki/Unit_circle
 * https://www.desmos.com/calculator/3e7iypw4ow
 */
void Camera::rotate(Pad &t_pad)
{
    if (t_pad.rJoyH <= 50)
        horizontalLevel -= 0.08;
    else if (t_pad.rJoyH >= 200)
        horizontalLevel += 0.04;
    if (t_pad.rJoyV <= 50 && verticalLevel > 25.0F)
        verticalLevel -= 0.9F;
    else if (t_pad.rJoyV >= 200 && verticalLevel < 80.0F)
        verticalLevel += 0.9F;
    unitCirclePosition.x = (Math::sin(horizontalLevel) * verticalLevel);
    unitCirclePosition.y = CAMERA_Y;
    unitCirclePosition.z = (Math::cos(horizontalLevel) * verticalLevel);
}

/** Rotate camera around 3D object */
void Camera::followBy(Mesh &t_mesh)
{
    position.x = unitCirclePosition.x + t_mesh.position.x;
    position.y = unitCirclePosition.y + t_mesh.position.y;
    position.z = unitCirclePosition.z + t_mesh.position.z;

    if (position.x > (-0.04F * verticalLevel) &&
        position.x < 0.0F &&
        position.z > (0.998F * verticalLevel))
    {
        // TODO
        // position.x = 0.0F;
        // position.y = 0.0F;
        // position.z = 0.0F;
        // horizontalLevel = 0.0F;
    }
}
