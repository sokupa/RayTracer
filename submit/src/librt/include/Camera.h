//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Camera.h
// Camera Object - position, up and lookat
//------------------------------------------------------------------------------

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "STVector3.h"

class Camera
{

public:
                            Camera(void);
                            ~Camera(void);

    void                    Reset                                       (void);
    void                    ResetUp                                     (void);
    void                    SetUpAndRight                               (void);
    void                    Strafe                                      (float delta_x, float delta_y);
    void                    Zoom                                        (float delta_y);
    void                    Rotate                                      (float delta_x, float delta_y);

    STVector3               Position                                    (void);
    STVector3               LookAt                                      (void);
    STVector3               Up                                          (void);

private:

    // parameters
    STVector3               m_Position;
    STVector3               m_LookAt;
    STVector3               m_Right;
    STVector3               m_Up;

    void                    Init                                        (void);

};


#endif //__CAMERA_H__

