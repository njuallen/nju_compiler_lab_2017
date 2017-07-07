#ifndef LINKAGE_H
#define LINKAGE_H

#ifdef LINKAGE_CPP
#define LINKAGE extern "C"
#else
#define LINKAGE 
#endif

#endif
