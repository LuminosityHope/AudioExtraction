#include "Filter.h"

Filter::Filter(size_t windSize, TypeFilter type)
    : windowSize(windSize), filterType(type){}
Filter::~Filter()=default;
