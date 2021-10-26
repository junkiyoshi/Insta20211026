#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);

	auto ico_sphere = ofIcoSpherePrimitive(250, 4);
	this->base_mesh = ico_sphere.getMesh();

}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh.clear();

	int x = 0;
	for (int y = -300; y <= 300; y += 600) {

		for (auto v : this->base_mesh.getVertices()) {

			for (int i = 0; i < 4; i++) {

				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4((v + glm::vec3(x, y, 0)) * 0.0025, ofGetFrameNum() * 0.01)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4((v + glm::vec3(x, y, 0)) * 0.0025, ofGetFrameNum() * 0.01)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4((v + glm::vec3(x, y, 0)) * 0.0025, ofGetFrameNum() * 0.01)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

				v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
			}

			this->draw_mesh.addVertex(v + glm::vec3(x, y, 0));
		}

	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateZ(45);
	ofRotateY(ofGetFrameNum() * 2);

	for (auto& vertex : this->draw_mesh.getVertices()) {

		ofDrawSphere(vertex, 2);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}