#include "Filter.h"

Filter::Filter(size_t windSize, const size_t type)
    : windowSize(windSize), typeFilt(type){}
Filter::~Filter()=default;
