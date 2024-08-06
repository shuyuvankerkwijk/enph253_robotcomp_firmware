#ifndef MAP_ENCODING_H
#define MAP_ENCODING_H

#include <Arduino.h>
#include <string.h>
#include "path_progress.h"

class Path {
public:
    Path(String start, String end);
    ~Path(); // Destructor to clean up dynamically allocated memory
    void execute();
    bool done;

    Moves* moves_series[6] = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}; // Initialize to nullptr
};

#endif // MAP_ENCODING_H
