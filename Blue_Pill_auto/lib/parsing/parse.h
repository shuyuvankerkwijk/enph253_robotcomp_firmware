
/**
 * this parses all of the incoming serial data
 * change of variables, etc...
 * coded_floats = {Ki,Kp,Kd}
 */
#ifndef PARSE_H
#define PARSE_H

#include "globals.h"

String parse(String message);

#endif