#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");
    
    ofBackground(10);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    cam.setup(320, 240);
    
    legoWhite.loadImage("legoWhite_4.png");
    legoPlatte.loadImage("legoPlatte.jpg");
    
    legoSize = 10;
    legoPixelsNumber = legoSize * legoSize;
    
    camWidth = cam.getWidth();
    camHeight = cam.getHeight();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    cam.update();
    
    if (cam.isFrameNew()) {
        
        //        int _draggedImgNr = draggedImages.size();
        //        float _draggedImgWidth = draggedImages[_draggedImgNr-1].getWidth();
        //        float _draggedImgHeight = draggedImages[_draggedImgNr-1].getHeight();
        int _totalPixels = camWidth * camHeight * 3;
        //
        //        int _limitSize = 1280;
        //
        //        if ((_draggedImgWidth>_draggedImgHeight)&&(_draggedImgWidth>_limitSize)) {
        //            float _hwRatio = _draggedImgHeight/_draggedImgWidth;
        //            _draggedImgWidth = _limitSize;
        //            _draggedImgHeight = (int)(_draggedImgWidth * _hwRatio);
        //            draggedImages[_draggedImgNr-1].resize(_draggedImgWidth, _draggedImgHeight);
        //        }
        //
        //        if ((_draggedImgHeight>_draggedImgWidth)&&(_draggedImgHeight>_limitSize)) {
        //            float _whRatio = _draggedImgWidth/_draggedImgHeight;
        //            _draggedImgHeight = _limitSize;
        //            _draggedImgWidth = (int)(_draggedImgHeight * _whRatio);
        //            draggedImages[_draggedImgNr-1].resize(_draggedImgWidth, _draggedImgHeight);
        //        }
        //
        //
        //        ofSetWindowShape(legoPicWidth*legoSize, legoPicHeight*legoSize);
        //
        pixelColorR.resize(_totalPixels/3);
        pixelColorG.resize(_totalPixels/3);
        pixelColorB.resize(_totalPixels/3);
        
        legoPicWidth = camWidth / legoSize;
        legoPicHeight = camHeight / legoSize;
        
        unsigned char * _pixels = cam.getPixels();
        
        for (int n=0; n<legoPicHeight; n++) {
            for (int m=0; m<legoPicWidth; m++) {
                
                int _legoPixelIndex = m + n * legoPicWidth;
                
                float _sumColorR = 0;
                float _sumColorG = 0;
                float _sumColorB = 0;
                
                int _begin_1st = camWidth * 3 * legoSize * n;
                int _end_1st = camWidth * 3 * legoSize * (n + 1);
                
                for (int j = _begin_1st; j<_end_1st; j+=cam.getWidth()*3) {
                    int _begin_2nd = legoSize * 3 * m;
                    int _end_2nd = legoSize * 3 * m + legoSize * 3;
                    
                    for (int i=_begin_2nd; i<_end_2nd; i+=3) {
                        int _index = i + j;
                        _sumColorR += _pixels[_index+0];
                        _sumColorG += _pixels[_index+1];
                        _sumColorB += _pixels[_index+2];
                    }
                }
                
                pixelColorR[_legoPixelIndex] = _sumColorR/legoPixelsNumber;
                pixelColorG[_legoPixelIndex] = _sumColorG/legoPixelsNumber;
                pixelColorB[_legoPixelIndex] = _sumColorB/legoPixelsNumber;
                
            }
        }
        
    }
    
    if (draggedImages.size()>1) {
        draggedImages.erase(draggedImages.begin());
    }
    
}

//--------------------------------------------------------------

void ofApp::draw(){
    
    //    legoPlatte.draw(0, 0);
    
    //    if (pixelColorR.size()>0) {
    
    float _size = 3;
    
    float _x = ofGetWidth() * 0.5 - legoPicWidth * legoSize * _size * 0.5;
    float _y = ofGetHeight() * 0.5 - legoPicHeight * legoSize * _size * 0.5;
    ofTranslate( _x, _y );
    
    
    for (int j = 0; j < legoPicHeight; j++){
        for (int i = 0; i < legoPicWidth; i++){
            
            int _index = i + j*legoPicWidth;
            
            ofPushStyle();
            ofSetColor( ofColor(pixelColorR[_index], pixelColorG[_index], pixelColorB[_index], 255) );
            legoWhite.draw(i*legoSize * _size, j*legoSize * _size, legoSize * _size, legoSize * _size);
            ofPopStyle();
        }
    }
    
    for (int j = 0; j < legoPicHeight; j++){
        for (int i = 0; i < legoPicWidth; i++){
            
            int _index = i + j*legoPicWidth;
            
            ofPushStyle();
            ofSetColor( pixelColorG[(legoPicHeight*legoPicWidth)-_index], 10 );
            ofLine(i*legoSize * _size, j*legoSize * _size, i*legoSize * _size, j*legoSize+legoSize * _size);
            ofLine(i*legoSize * _size, j*legoSize * _size, i*legoSize+legoSize * _size, j*legoSize * _size);
            ofPopStyle();
        }
    }
    
    //    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
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
void ofApp::windowResized(int w, int h){
    
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

void ofApp::dragEvent(ofDragInfo info){
    
    if( info.files.size() > 0 ){
        dragPt = info.position;
        
        draggedImages.assign( info.files.size(), ofImage() );
        for(unsigned int k = 0; k < info.files.size(); k++){
            draggedImages[k].loadImage(info.files[k]);
        }
    }
    
    
}

