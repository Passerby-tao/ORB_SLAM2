#include "System.h"
#include <string>
#include <chrono> // for time stamp
#include <iostream>
using namespace std;
//Fichier de paramtres vs fichier de dictionnaire
// Si le chemin daccs sur votre systme est diffrent , modifiez−le
string parameterFile = "./myvideo.yaml";
string vocFile = "./Vocabulary/ORBvoc.txt";
// Fichier video
string videoFile = "./myvideo.mp4";
int main(int argc, char **argv) {
// Dclare le systme ORB−SLAM2
ORB_SLAM2::System SLAM(vocFile, parameterFile, ORB_SLAM2::System::MONOCULAR, true);
// Obtient une image vido
cv :: VideoCapture cap(videoFile); // change to 1 if you want to use USB camera.
// Enregistrer lheure systme
auto start = chrono::system_clock::now();
while (1) {
		cv::Mat frame;
		cap >> frame; // Lire les donnes de la camra
		if ( frame.data == nullptr )
			break;
		// rescale because image is too large
		cv::Mat frame_resized;
		cv::resize (frame, frame_resized, cv :: Size(640,360)) ;
		auto now = chrono::system_clock::now();
		auto timestamp = chrono::duration_cast<chrono::milliseconds>(now - start);
		SLAM.TrackMonocular(frame_resized, double(timestamp.count())/1000.0);
		cv::waitKey(30);
	}
	
	    
    // Save customized Map
    char IsSaveMap;  
    cout << "Do you want to save the map?(y/n)" << endl;  
    cin >> IsSaveMap;  
    if(IsSaveMap == 'Y' || IsSaveMap == 'y')  
        SLAM.SaveMap("MapPointandKeyFrame.bin");
        
    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");
        
        
	SLAM.Shutdown();
	return 0;
}
