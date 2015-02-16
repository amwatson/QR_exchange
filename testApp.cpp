#include "testApp.h"
#include <vector>



vector<ofImage> images;
string qr_dir = "qrimages";
ofImage img;
void testApp::setup() {
    
    ofSetVerticalSync(true);
    cam.initGrabber(SCREEN_W, SCREEN_H);
    dir = new ofDirectory(qr_dir);
    if (dir == NULL) {
        printf("ERROR\n");
    }
    dir->allowExt("png");
    //populate the directory object
    dir->listDir();
    for(int i = 0; i < dir->numFiles(); i++){
        printf("%s\n", dir->getName(i).c_str());
        img.loadImage(qr_dir + "/" + dir->getName(i));
        images.push_back(img);
    }
    printf("%lu photos in directory", images.size());
}
string url = "";
string goto_url = "";
ofImage res;

void testApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        ofxZxing::Result curResult = ofxZxing::decode(cam.getPixelsRef(), true);
        float curTime = ofGetElapsedTimef();
        if(curResult.getFound()) { // only update if we found something, avoid flickering
            result = curResult;
            lastFound = curTime;
            if (result.getText() != url) {
                img.setFromPixels(cam.getPixelsRef());
                images.push_back(img);
                img.saveImage(qr_dir + "/" + ofToString(images.size()) + ".png");
            }
        } else if(curTime - lastFound > 1) {  // if we haven't found anything after a second
            result = curResult; // then update anyway
        }
    }
}

void testApp::draw() {
    ofSetColor(255);
    if(result.getFound()) {
        
        if (result.getText() != url) {
            int image_num = ofRandom(0, images.size()-1);
            res = images[image_num];
            printf("%d\n", image_num);
            url = result.getText();
        }
        res.draw(0, 0);
        ofxZxing::Result result_img = ofxZxing::decode(res.getPixelsRef(), true);
        assert(result_img.getFound());
        goto_url = result_img.getText();
        
        
    } else {
        goto_url = "";
        cam.draw(0, 0);
    }
}

void testApp::keyReleased(int key){
    switch (key) {
        case OF_KEY_RETURN:
            if (goto_url.length() > 0) {
                system(("open " + goto_url).c_str());
            }
        default:
            break;
    }
}
