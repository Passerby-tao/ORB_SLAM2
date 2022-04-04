// Le fichier ouvrira la camra de votre ordinateur et transmettra limage ORB SLAM2 pour le positionnement
// opencv
#include <opencv2/opencv.hpp>
// Interface systme pour ORB−SLAM
#include "System.h"
#include <string>
#include <chrono> // for time stamp
#include <iostream>
using namespace std;
// Fichier de paramtres vs fichier de dictionnaire
// Si le chemin daccs sur votre systme est diffrent , modifiez−le
string parameterFile = "./myslam.yaml";
string vocFile = "./Vocabulary/ORBvoc.txt";
int main(int argc, char **argv) {

		// Declare le systme ORB−SLAM2
		ORB_SLAM2::System SLAM(vocFile, parameterFile, ORB_SLAM2::System::MONOCULAR, true);
		
		// Obtenir le code image de la camra
		cv::VideoCapture cap(0); // changer 0 a 1 si vous voulez utiliser USB camera.
		
		// La rsolution est rgle sur 640x480
		cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);//Definit la largeur de la video capture
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);//Definit la hauteur de la video capture
		
		// Enregistrer lheure du systme
		auto start = chrono::system_clock::now();
		
		while (1) {
			cv::Mat frame;
			cap >> frame; // Lire les donnes de la camra
			auto now = chrono::system_clock::now();
			auto timestamp = chrono::duration_cast<chrono::milliseconds>(now - start);
			SLAM.TrackMonocular(frame, double(timestamp.count())/1000.0);
	}
	
    	// save map
    	char IsSaveMap;  
    	cout << "Do you want to save the map?(Y/N)" << endl;  
    	cin >> IsSaveMap;  
    	if(IsSaveMap == 'Y' || IsSaveMap == 'y')  
        	SLAM.SaveMap("/home/lintao/ORB_SLAM2/map.bin");
        	
        std::cout << "Press ENTER to close..."; 
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
	
	return 0;
}
