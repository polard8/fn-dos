
#ifndef __GWS00_H
#define __GWS00_H   1

// Current protocol version
#define GWS_PROTOCOL  1

// ============================
// Modes.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
// ...

extern int current_mode;

#endif   

