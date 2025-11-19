#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <print>
#include "entities/player.hpp"
#include "entities/shooter.hpp"
#include "base/entity_list.hpp"
using namespace sf;
using namespace std;

// Im using comments cuz im a noob :D
// (1, 0) is to the right, (0, 1) is to down

int main() {
	auto window = RenderWindow(VideoMode({480u, 480u}), "Ambiguity");
	window.setFramerateLimit(60);

	EntityList entity_list;
	entity_list.spawn("player", make_unique<Player>(32, Vector2f{224, 224}));
	entity_list.spawn("sh1", make_unique<Shooter>(Vector2f{32, 32}));
	entity_list.spawn("sh2", make_unique<Shooter>(Vector2f{448, 32}, 49));
	entity_list.spawn("sh3", make_unique<Shooter>(Vector2f{448, 448}, 75));
	entity_list.spawn("sh4",make_unique<Shooter>(Vector2f{32, 448}, 60));

	auto last_time = chrono::high_resolution_clock::now();

	// Sans
	Font sans;
	if (!sans.openFromFile("StackSansText.tff")) {
		println("StackSansText.tff not found by executable.");
		println("SOMEONE suspiciously deleted it");
		return -1;
	}

	bool paused = false;
	bool playing = true;

	// pause text
	Text pause_text(sans, "Paused", 60);
	pause_text.setFillColor(Color::White);
	pause_text.setPosition({ 120, (480 / 2) - 30 });

	// rain
	Music rain;
	if (!rain.openFromFile("rain.wav")) {
		println("You love the rain, don't you?");
		println("Or do YOU hate the RAIN?");
		println("Cause I haven't heard it.");
		println("\nFailed to load rain.wav");
		return -1;
	}
	rain.setVolume(10);
	rain.setLooping(true);
	rain.play();

	// Main game loop
	while (window.isOpen()) {
		// Poll for events
		while (const optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>()) { rain.stop(); window.close(); }
			// Pause
			if (const auto* key = event->getIf<Event::KeyPressed>()) {
				if (key->scancode == Keyboard::Scan::Escape) {
					paused = !paused;
					switch (paused) {
					case true:
						rain.pause();
						break;
					case false:
						rain.play();
						break;
				}
			}
			if (event->is<Event::FocusLost>()) { paused = true; rain.pause(); }
		}

		auto now = chrono::high_resolution_clock::now();
		float dt = duration_cast<chrono::duration<float>>(now - last_time).count();
		last_time = now;

		// vuvu :3
		// pause functionality ^v^
		if (!paused) {
			// update loop for all entities
			entity_list.update(dt);

			
			entity_list.flush();
		}

		// Clear and display
		window.clear();
		entity_list.for_each([&window](Entity& e) {
			if (auto e2d = dynamic_cast<Entity2D*>(&e)) {
				e2d->draw(window);
			}
			});
		if (paused) {
			window.draw(pause_text);
		}
		window.display();
	}

	return 0;
}

// im so bad at this game fr 6x
// I GOT GOOD!!!