#include "mesh_bed_leveling.h"

#if ENABLED(MESH_BED_LEVELING)

  mesh_bed_leveling mbl;

  mesh_bed_leveling::mesh_bed_leveling() { reset(); }

  void mesh_bed_leveling::reset() {
    active = 0;
    #if ENABLED(DELTA)
      r_values[0] = 0.0;
      a_values[0] = 0.0;
      z_values[0] = 0.0;
      unsigned int c = 1;
      for (int ri = 1; ri <= MESH_NUM_RADIUS; ++ri){
        float r = float(ri)*MESH_R_DIST;
        r_values[ri] = r;
        for (int ai = 0; ai < MESH_NUM_ANGLES; ++ai){
          float a = float(ai)*MESH_A_DIST;
          a_values[ai] = a;
          z_values[(ri-1)*MESH_NUM_ANGLES+ai+1] = 0.0;
          c++;
        }
      }        
    #else
      for (int y = 0; y < MESH_NUM_Y_POINTS; y++)
        for (int x = 0; x < MESH_NUM_X_POINTS; x++)
          z_values[y][x] = 0;
    #endif
  }

#endif  // MESH_BED_LEVELING
