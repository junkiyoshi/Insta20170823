#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->cap.open(1);

	this->frame_img.allocate(this->cap.get(CV_CAP_PROP_FRAME_WIDTH) / 4, this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) / 4, OF_IMAGE_COLOR);
	this->frame = cv::Mat(this->frame_img.getHeight(), this->frame_img.getWidth(), CV_MAKETYPE(CV_8UC3, this->frame_img.getPixels().getNumChannels()), this->frame_img.getPixels().getData(), 0);
	
	this->face_cascade.load("D:\\opencv-3.3.0\\build\\install\\etc\\haarcascades\\haarcascade_frontalface_default.xml");

	this->rect_color.setHsb(ofRandom(255), 255, 255);
	this->random_value = 3;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (!this->cap.isOpened()) { return; }

	cv::Mat src;
	this->cap >> src;
	cv::resize(src, this->frame, cv::Size(), 0.25, 0.25);

	if (this->frame.empty()) { return; }

	cv::cvtColor(this->frame, this->frame, CV_RGB2BGR);
	cv::flip(this->frame, this->frame, 1);
	cv::cvtColor(this->frame, this->gray_frame, CV_RGB2GRAY);
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();

	vector<cv::Rect> faces;
	face_cascade.detectMultiScale(gray_frame, faces);

	ofSetColor(255);
	this->frame_img.update();
	this->frame_img.draw(-this->frame_img.getWidth() / 2, -this->frame_img.getHeight() / 2);

	if (faces.size() == 0) {
		this->rect_color.setHsb(ofRandom(255), 255, 255);
		this->random_value = (int)ofRandom(3, 8);
	}

	for (cv::Rect r : faces){
		ofSetColor(this->rect_color);

		int i_span = 360 / this->random_value;

		ofTranslate(ofVec3f(-this->frame_img.getWidth() / 2 + r.x + r.size().width / 2, -r.y + r.size().height / 2, 0));
		ofRotate(ofGetFrameNum() % 360);
		ofBeginShape();
		for (int i = 0; i < 360; i += i_span) {
			float x = r.size().width / 1.5 * cos(i * DEG_TO_RAD);
			float y = r.size().width / 1.5 * sin(i * DEG_TO_RAD);
			ofVertex(x, y);
		}
		ofEndShape();

		//ofRect(ofVec3f(-this->frame_img.getWidth() / 2 + r.x, -r.y, 0), r.size().width, r.size().height);
		cout << "x = " << r.x << " y = " << r.y << endl;
	}

	this->cam.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
