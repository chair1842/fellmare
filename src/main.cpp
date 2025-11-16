#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <print>
#include "entities/player.hpp"
#include "entities/shooter.hpp"
using namespace sf;
using namespace std;

// Im using comments cuz im a noob :D
// (1, 0) is to the right, (0, 1) is to down

int main() {
	auto window = RenderWindow(VideoMode({480u, 480u}), "Ambiguity");
	window.setFramerateLimit(60);

	vector<unique_ptr<Entity>> entity_list;
	entity_list.push_back(make_unique<Player>(32, Vector2f{ 224, 224 }));
	entity_list.push_back(make_unique<Shooter>(Vector2f{ 32, 32 }));
	entity_list.push_back(make_unique<Shooter>(Vector2f{ 448, 32 }, 49));
	entity_list.push_back(make_unique<Shooter>(Vector2f{ 448, 448 }, 75));
	entity_list.push_back(make_unique<Shooter>(Vector2f{ 32, 448 }, 60));

	for (auto& e : entity_list) {
		e->enter();
	}

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
					default:
						break;
					}
				}
			}
			if (event->is<Event::FocusLost>()) { paused = true; rain.pause(); }
		}

		auto now = chrono::high_resolution_clock::now();
		float dt = duration_cast<chrono::duration<float>>(now - last_time).count();
		last_time = now;

		vector<unique_ptr<Entity>> to_spawn;

		// vuvu :3
		// pause functionality ^v^
		if (!paused) {
			// update loop for all entities
			for (auto& e : entity_list) {
				e->update(dt, entity_list, to_spawn);
			}

			// spawn buffer
			for (auto& e : to_spawn) {
				entity_list.push_back(std::move(e));
				// i will have to call enter() on these
			}
			to_spawn.clear(); // clear the spawn buffer

			// to delete section
			for (auto& e : entity_list) { // i have so many entity_list loops
				if (e->to_delete) {
					e->exit();
					if (auto player = dynamic_cast<Player*>(e.get())) {
						rain.setVolume(50);
						playing = false;
					}
				}
			}
			entity_list.erase(
				// remove if from all of the entities, if to_delete is true
				remove_if(entity_list.begin(), entity_list.end(),
					[](const unique_ptr<Entity>& e) { return e->to_delete; }),
				entity_list.end()
			);
		}

		// Clear and display
		window.clear();
		for (auto& e : entity_list) {
			e->draw(window); // wow, very nice
		}
		if (paused) {
			window.draw(pause_text);
		}
		window.display();
	}

	return 0;
}

// im so bad at this game fr 6x
// I GOT GOOD!!!