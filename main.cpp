#include "kmeans.h"
#include <ctime>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct color {
	double r,g,b;	
};

int main(int argc, char *argv[]){

	int k = 3;         //number of clusters default
	int n = 50;        //number of points   default 

	//input argv
	if(argc > 0){n = std::stoi(argv[1]); k = std::stoi(argv[2]); }

	srand(time(NULL)); //random seed

	std::vector<pcl::PointXYZ> points;

	//initialize points
	for (int i = 0; i < n/2 ; ++i){
	pcl::PointXYZ point;
	point.x = (double) rand()/(RAND_MAX/0.6);point.y = (double) rand()/(RAND_MAX/0.6);point.z = 0;
	points.push_back(point);
	} 

	for (int i = 0; i < n/2 ; ++i){
	pcl::PointXYZ point;
	point.x = 0.4 +  (double) rand()/(RAND_MAX/0.6);point.y = 0.4 + (double) rand()/(RAND_MAX/0.6);point.z = 0;
	points.push_back(point);
	}

	std::cout<<"Initialized points: "<< points.size() <<"\n";

	//run kmeans clustering
	Kmeans kmean = Kmeans(points, k);
	std::vector<Cluster> clusters = kmean.getClusters();


	//elbow method
        static double* doubleSSD[] = {};
        

	//plot points on gl

	std::vector<color> Colors;
	for(auto& cluster : clusters){	    
		Colors.push_back({(double) rand()/RAND_MAX, (double) rand()/RAND_MAX, (double) rand()/RAND_MAX});
	}

	if ( !glfwInit( ) )
	{
	fprintf(stderr, "failed to initialize GLFW");
	return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow *window;
	window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Clusters", NULL, NULL );

	if ( !window )
	{
	glfwTerminate( );
	return -1;
	}

	glfwMakeContextCurrent( window );
	glViewport( 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); 
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity( ); 
	glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1 ); 
	glMatrixMode( GL_MODELVIEW ); 
	glLoadIdentity( ); 


	while ( !glfwWindowShouldClose( window ) )
	{
	glClear( GL_COLOR_BUFFER_BIT );

	// Render OpenGL 
	for (auto& cluster : clusters){    
	    std::vector<pcl::PointXYZ> temp_cluster = cluster.getClusterPoints();
	    // render points
	    for (int point = 0; point < temp_cluster.size(); ++point){    
		GLfloat pointVertex[] = {temp_cluster.at(point).x*SCREEN_WIDTH, temp_cluster.at(point).y*SCREEN_HEIGHT, temp_cluster.at(point).z};
		glEnable( GL_POINT_SMOOTH ); 
		glEnableClientState( GL_VERTEX_ARRAY ); 
		glPointSize( 10 ); 
		glColor3f(Colors.at(cluster.getId()).r, Colors.at(cluster.getId()).g, Colors.at(cluster.getId()).b);
		glVertexPointer( 2, GL_FLOAT, 0, pointVertex ); 
		glDrawArrays( GL_POINTS, 0, 1 ); 
		glDisableClientState( GL_VERTEX_ARRAY ); 
	    }
	    // render centroids
		glDisable( GL_POINT_SMOOTH );
		GLfloat pointVertex[] = {cluster.getCentroid().x*SCREEN_WIDTH, cluster.getCentroid().y*SCREEN_HEIGHT, cluster.getCentroid().z}; 
		glEnableClientState( GL_VERTEX_ARRAY ); 
		glPointSize( 20 ); 
		glColor3f(Colors.at(cluster.getId()).r, Colors.at(cluster.getId()).g, Colors.at(cluster.getId()).b);
		glVertexPointer( 2, GL_FLOAT, 0, pointVertex ); 
		glDrawArrays( GL_POINTS, 0, 1 ); 
		glDisableClientState( GL_VERTEX_ARRAY );
	    
	}

	glfwSwapBuffers( window );

	glfwPollEvents( );
	}

	glfwTerminate( );

	return 0;

}














