//\file GhostBusters.hpp
//\brief Contains the classes that generate and deal with ghost points
//\author Itay Zandbank

#ifndef GHOST_BUSTER_HPP
#define GHOST_BUSTER_HPP 1

#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../GeometryCommon/Vector3D.hpp"
#include "../GeometryCommon/OuterBoundary3D.hpp"
#include "../GeometryCommon/VectorRepository.hpp"
#include "Delaunay.hpp"

//\brief The abstract GhostBuster class. A GhostBuster class is really just a Functor object.
class GhostBuster
{
public:
	typedef std::pair<Subcube, VectorRef> GhostPoint;
	struct GhostPointHasher
	{
		size_t operator()(const GhostPoint &gp) const
		{
			std::hash<Subcube> subcubeHash;
			std::hash<VectorRef> vectorHash;

			return subcubeHash(gp.first) ^ vectorHash(gp.second);
		}
	};
	typedef std::unordered_map<VectorRef, std::unordered_set<GhostPoint, GhostPointHasher>> GhostMap;

	virtual GhostMap operator()(const Delaunay &del, const OuterBoundary3D &boundary) const = 0;
};

//\brief A simple implementation that copies each point 26 times
class BruteForceGhostBuster : public GhostBuster
{
public:
	virtual GhostMap operator()(const Delaunay &del, const OuterBoundary3D &boundary) const;
};

class FullBruteForceGhostBuster : public GhostBuster
{
public:
	virtual GhostMap operator()(const Delaunay &del, const OuterBoundary3D &boundary) const;
};

//\brief An implementation that checks only points that are on edge-faces.
class CloseToBoundaryGhostBuster : public GhostBuster
{
public:
	virtual GhostMap operator()(const Delaunay &del, const OuterBoundary3D &boundary) const;

private:
	unordered_set<size_t> FindOuterTetrahedra(const Delaunay &del) const ;
	unordered_set<size_t> FindEdgeTetrahedra(const Delaunay &del, const unordered_set<size_t>& outerTetrahedra) const;

	typedef unordered_map<VectorRef, unordered_set<Subcube>> breach_map;
	breach_map FindHullBreaches(const Delaunay &del, 
		const unordered_set<size_t>& edgeTetrahedra,
		const unordered_set<size_t> &outerTetrahedra,
		const OuterBoundary3D &boundary) const;

	template<typename T>
	static bool contains(const unordered_set<T> &set, const T &val)
	{
		return set.find(val) != set.end();
	}
};
#endif