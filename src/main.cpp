#include <iostream>
#include <print>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "base/entity_list.hpp"
#include "entities/player.hpp"

int main(int argc, char* argv[]) {
	sf::RenderWindow window(sf::VideoMode({480, 480}), "Fellmare");
	window.setVerticalSyncEnabled(true);

	EntityList entl;
	entl.spawn(std::make_unique<Player>());

	auto dt_past = std::chrono::high_resolution_clock::now();

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		auto dt_now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> dt = dt_now - dt_past;
		dt_past = dt_now;

		entl.update(dt.count());
		entl.flush();

		window.clear();
		for (auto& [name, entity] : entl.list) {
			if (auto e2d = dynamic_cast<Entity2D*>(entity.get())) {
				e2d->draw(window);
			}
		}
		window.display();
	}

	return 0;
}