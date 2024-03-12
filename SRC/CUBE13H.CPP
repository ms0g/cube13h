#include "APP.H"

void main(void) {
	App* app = new App();
	
	app->loop();
	
	delete app;
}
