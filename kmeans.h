#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <math.h>
#include <vector>
#include <pcl/point_types.h>

class Cluster{
	private:
		int clusterId;
		pcl::PointXYZ centroid;
		std::vector<pcl::PointXYZ> clusterPoints;
	public:
		Cluster(const int& id, const pcl::PointXYZ& InitCentroid);
		void addPoint(const pcl::PointXYZ& point) ;
		void newCentroid() ;
		pcl::PointXYZ getCentroid() {return centroid;}
		std::vector<pcl::PointXYZ> getClusterPoints() {return clusterPoints;}
		void removePoints(){clusterPoints.clear();}
		void setCentroid(const pcl::PointXYZ& point);
		int getSize(){return clusterPoints.size();}
		int getId() {return clusterId;}
};

class Kmeans {
	private: 
		std::vector<Cluster> clusters;
		int iters = 10; 
		int iter = 1;
	
	public:
		Kmeans(const std::vector<pcl::PointXYZ>& points, const int& k);
		std::vector<Cluster> getClusters(){return clusters;}
};

#endif
