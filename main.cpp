#include "exchange.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, SCREEN_W, SCREEN_H, OF_WINDOW);
	ofRunApp(new Exchange());
}
