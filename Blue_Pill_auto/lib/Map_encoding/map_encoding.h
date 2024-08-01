#ifndef MAP_ENCODING_H
#define MAP_ENCODING_H

#include <Arduino.h>
#include <string.h>
#include "path_progress.h"
#include <iostream>
#include <vector>
#include <memory>

class Path {
public:
    Path(String start, String end);
    void execute();
    bool done;

    std::vector<std::unique_ptr<Moves>> move_series;
};

#endif // MAP_ENCODING_H
