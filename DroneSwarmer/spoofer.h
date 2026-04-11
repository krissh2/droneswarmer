#include <Arduino.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <Esp.h>

#include "id_open.h"

#ifndef SPOOFER_H
#define SPOOFER_H

class Spoofer {
  private:
    ID_OpenDrone squitter;
    UTM_Utilities utm_utils;

    struct UTM_parameters utm_parameters;
    struct UTM_data utm_data;

    // conversion constants and params
    const double angle_rad2deg = 180.0 / M_PI;
    const double speed_ms2kn = 1.9438445; // m/s to knots conversion
    const double max_accel = 10 * 1000; // in mm/s² (max horizontal acceleration)
    const double max_speed = 25; // in m/s (max horizontal speed ~90 km/h)
    const double max_climbrate = 10 * 1000; // in mm/s (max vertical climb/descent rate)
    const double max_height = 200; // in m over takeoff

    // runtime variables
    float speed_m_x = 0.0, speed_m_y = 0.0;
    double m_deg_lat = 0.0, m_deg_long = 0.0;
    float x = 0.0, y = 0.0, z = 0.0;

    // runtime time variables
    time_t time_2;
    struct tm clock_tm;
    struct timeval tv = {0,0};
    struct timezone utc = {0,0};
    uint32_t last_update = 0;

    // random ID generator
    String getID();

  public:
    void init();
    void updateLocation(float latitude, float longitude);
    void update();
};

#endif