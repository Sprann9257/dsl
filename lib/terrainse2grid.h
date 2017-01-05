// This file is part of libdsl, a library for heuristic graph search
//
// Copyright (C) 2004 Marin Kobilarov <marin@jhu.edu>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DSL_TERRAINSE2GRID_H
#define DSL_TERRAINSE2GRID_H

#include "grid.h"
#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace dsl {
/**
 * Struct to store properties of a cell on terrain. Height, slope(roll pitch), traversibility.
 * The notion of traversibility is correlated to how easy is it to move on a surface. Grass is probably harder
 * to move than say concrete etc.
 */
struct TerrainData{
  TerrainData(double height=std::numeric_limits<double>::quiet_NaN(),
              double traversibility=std::numeric_limits<double>::quiet_NaN());

  double height; ///< Height of the cell relative to the origin.
  double traversibility;///<Traversibility is nan if cell is occupied. Distance*Traversibility is friction loss.
  //double pitch; ///< pitch
  //double roll;  ///< roll
};

// a cell that stores terrain data along with axy representaion of SE2 pose
using TerrainCell = Cell< Eigen::Vector3d, TerrainData >;
using TerrainCellPtr = shared_ptr<TerrainCell>;
using TerrainSE2GridBase = Grid< TerrainCell::PointType, TerrainCell::DataType >;


/**
 * A 3d grid for simple car models with coordinates (theta,x,y). Each cell stores the TerrainData i.e. the height
 * and traversibility of a cell.
 *
 * Authors: Subhransu Mishra
 */
class TerrainSE2Grid : public TerrainSE2GridBase {
public:

  /**
   * Construct terrainse2grid
   * @param cmap Configuration space(angle, x and y) occupancy map
   * @param tmap Terrain data map
   * @param cs cell size of the grid created
   */
  TerrainSE2Grid(const Map<bool, 3> &cmap, const Map<TerrainData,2>& tmap, const Eigen::Vector3d& cs);
};
}

#endif //TERRAINSE2GRID