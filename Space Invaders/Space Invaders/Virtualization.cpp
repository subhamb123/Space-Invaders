#include "Virtualization.hpp"

Virtualization::Virtualization() {
	RenderWindow window(VideoMode(800, 600), "Title");
	Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
	}
}

Virtualization::~Virtualization() {

}