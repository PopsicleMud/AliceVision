// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <aliceVision/structures/Point3d.hpp>
#include <aliceVision/structures/StaticVector.hpp>
#include <aliceVision/structures/Voxel.hpp>
#include <aliceVision/largeScale/LargeScale.hpp>
#include <aliceVision/largeScale/VoxelsGrid.hpp>
#include <aliceVision/mesh/Mesh.hpp>

class ReconstructionPlan : public VoxelsGrid
{
public:
    StaticVector<int>* nVoxelsTracks;
    ReconstructionPlan(Voxel& dimmensions, Point3d* space, MultiViewParams* _mp, PreMatchCams* _pc,
                       std::string _spaceRootDir);
    ~ReconstructionPlan();

    unsigned long getNTracks(const Voxel& LU, const Voxel& RD);
    bool divideBox(Voxel& LU1o, Voxel& RD1o, Voxel& LU2o, Voxel& RD2o, const Voxel& LUi, const Voxel& RDi,
                   unsigned long maxTracks);
    StaticVector<Point3d>* computeReconstructionPlanBinSearch(unsigned long maxTracks);

    StaticVector<int>* getNeigboursIds(float dist, int id, bool ceilOrFloor);
    StaticVector<int>* voxelsIdsIntersectingHexah(Point3d* hexah);
    int getPtsCount(float dist, int id);
    StaticVector<float>* computeMaximaInflateFactors(int maxPts);
    StaticVector<SortedId>* computeOptimalReconstructionPlan(const StaticVector<float>* maximaInflateFactors);
    void getHexahedronForID(float dist, int id, Point3d* out);
};

void reconstructAccordingToOptimalReconstructionPlan(int gl, LargeScale* ls);
void reconstructSpaceAccordingToVoxelsArray(const std::string& voxelsArrayFileName, LargeScale* ls,
                                            bool doComputeColoredMeshes);
Mesh* joinMeshes(const std::vector<std::string>& recsDirs, StaticVector<Point3d>* voxelsArray, LargeScale* ls);
Mesh* joinMeshes(int gl, LargeScale* ls);
Mesh* joinMeshes(const std::string& voxelsArrayFileName, LargeScale* ls);

StaticVector<StaticVector<int>*>* loadLargeScalePtsCams(const std::vector<std::string>& recsDirs);

