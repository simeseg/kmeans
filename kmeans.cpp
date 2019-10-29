#include "kmeans.h"

pcl::PointXYZ L2distance (const pcl::PointXYZ& point1, const pcl::PointXYZ& point2){
    pcl::PointXYZ distance;
    distance.x = point2.x - point1.x;
    distance.y = point2.y - point1.y;
    distance.z = point2.z - point1.z;
    return distance;
}

struct distIndex {
    int index;
    double distance;
};


bool compareDistances(distIndex d1, distIndex d2) {
    return (d1.distance < d2.distance);
}

int nearestCluster(const pcl::PointXYZ& point, std::vector<Cluster> clusters){
        
    std::vector<distIndex> distIndexList; int nearestCluster;    
    for(int i = 0 ; i< clusters.size(); ++i){
        pcl::PointXYZ L2dist = L2distance(point, clusters.at(i).getCentroid()) ;
        distIndex dx = { i, pow(L2dist.x,2) + pow(L2dist.y,2) + pow(L2dist.z,2)};
        distIndexList.push_back(dx);
    }
    std::sort(distIndexList.begin(), distIndexList.end(), compareDistances);
    nearestCluster = distIndexList.at(0).index;
    return nearestCluster;
}

Cluster::Cluster(const int& id, const pcl::PointXYZ& InitCentroid) {
	clusterId = id;
	centroid.x = InitCentroid.x;	
        centroid.y = InitCentroid.y;
        centroid.z = InitCentroid.z;
	}

void Cluster::addPoint(const pcl::PointXYZ& point) { clusterPoints.push_back(point);}
	
void Cluster::newCentroid() {
	int clusterSize = clusterPoints.size();
	if (clusterSize > 0){
		centroid.x = 0;centroid.y = 0;centroid.z = 0;  
		for (int i = 0 ; i< clusterSize; ++i){
			centroid.x += clusterPoints.at(i).x;
			centroid.y += clusterPoints.at(i).y;	
			centroid.z += clusterPoints.at(i).z;
		}
		centroid.x = centroid.x/clusterSize;
		centroid.y = centroid.y/clusterSize;
		centroid.z = centroid.z/clusterSize;
	}
}

void Cluster::setCentroid(const pcl::PointXYZ& point) {centroid = point;}


Kmeans::Kmeans(const std::vector<pcl::PointXYZ>& points, const int& k) {
	
    
    int n = points.size();
    //std::vector<Cluster> clusters;
    //color for plotting clusters


    //initialize clusters
    for(int ik = 0;ik<k;++ik){
        pcl::PointXYZ centroid;
        centroid.x = (double) rand()/RAND_MAX; centroid.y = (double) rand()/RAND_MAX; centroid.z = 0;
        clusters.push_back(Cluster(ik, centroid));
        //std::cout<<"Initialized cluster centroid: "<< centroid.x <<"\n";
    }
        
    while(iter < iters){
        for (auto& point : points){
            //distances to clusters
            int homeIndex = nearestCluster(point, clusters);
            clusters.at(homeIndex).addPoint(point);    
        }
    
        //std::cout<<"Clusters size: "<<clusters.at(0).getSize()<<"\n";
    
        for (auto& cluster : clusters){
            cluster.newCentroid();
            //std::cout<< "Updated centroid: "<<cluster.getCentroid().x<<" \n";
        }
        
        if(iter < iters - 1){
            for (auto& cluster : clusters) {
                cluster.removePoints();
            }
        }
    
        //std::cout<<"Calculated new centroid \n";
        iter +=1;
    }
    for(auto& cluster : clusters){
        std::cout<<"Clusters size and centroid : "<<cluster.getSize()<<" "<< cluster.getCentroid().x<< ", "<<cluster.getCentroid().y<<"\n";
	
    }
}
