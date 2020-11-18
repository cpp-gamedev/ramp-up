#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <functions.hpp>

using u32 = std::uint32_t;
using s32 = std::int32_t;

namespace {
void format(std::ostream& out_str, std::string_view fmt) {
	out_str << fmt;
}

template <typename Arg0, typename... Args>
void format(std::ostream& out_str, std::string_view fmt, Arg0&& arg0, Args&&... args) {
	if (!fmt.empty()) {
		constexpr static std::string_view token = "{}";
		auto const search = fmt.find(token);
		if (search < fmt.size()) {
			auto const lhs = fmt.substr(0, search);
			auto const rhs = fmt.substr(search + token.size());
			out_str << lhs << std::forward<Arg0>(arg0);
			format(out_str, rhs, std::forward<Args>(args)...);
		} else {
			format(out_str, fmt);
		}
	}
}

template <typename... Args>
std::string format(std::string_view fmt, Args&&... args) {
	std::stringstream str;
	format(str, fmt, std::forward<Args>(args)...);
	return str.str();
}
} // namespace

namespace {
sf::RenderWindow createWindow(sf::Vector2i size, std::string_view title) {
	assert(size.x > 0 && size.y > 0 && "Invalid size!");
	sf::ContextSettings context;
	context.antialiasingLevel = 8;
	context.majorVersion = 3;
	context.minorVersion = 3;
	auto const style = sf::Style::Close | sf::Style::Titlebar;
	sf::VideoMode const videoMode((u32)size.x, (u32)size.y);
	assert(videoMode.isValid());
	return sf::RenderWindow(videoMode, title.data(), style, context);
}

void pollEvents(sf::Window& out_window, bool& out_bQuit) {
	sf::Event ev;
	while (out_window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			out_bQuit = true;
			break;
		default:
			break;
		}
	}
}
} // namespace

int main(int argc, char** argv) {

	numconv::converter();

	if (argc > 0) {
		std::string_view const argv0 = argv[0];
		auto const full_path = std::filesystem::absolute(argv0);
		if (std::filesystem::is_regular_file(full_path)) {
			std::cout << format("Executable located at: {}\n", full_path.generic_string());
		} else {
			std::cerr << "Executable not found!\n";
		}
	}

	sf::Vector2i const windowSize(1280, 720);
	sf::Vector2i const topLeft = sf::Mouse::getPosition() - sf::Vector2i(windowSize.x / 2, windowSize.y / 2);
	sf::RenderWindow window = createWindow(windowSize, "Ramp Up");
	window.setPosition(topLeft);
	bool bQuit = false;
	while (window.isOpen()) {
		pollEvents(window, bQuit);
		if (bQuit) {
			window.close();
		} else {
			static bool s_bEscapePressed = false;
			bQuit |= (s_bEscapePressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
			s_bEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
			window.clear();
			window.display();
		}
	}
}
