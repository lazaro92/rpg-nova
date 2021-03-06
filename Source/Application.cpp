#include "Game/Application.hpp"
#include "Game/Utility.hpp"
#include "Game/State.hpp"
#include "Game/StateIdentifiers.hpp"
#include "Game/TitleState.hpp"
#include "Game/ExplorationState.hpp"
#include "Game/MenuState.hpp"
#include "Game/PauseState.hpp"
#include "Game/SettingsState.hpp"


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode(256, 224), "RPG Nova", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mMusic()
, mSounds()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic, mSounds))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{
    mWindow.setFramerateLimit(60);
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, 	"Media/FinalFantasy.ttf");

	// mTextures.load(Textures::TitleScreen,		"Media/Textures/Title_screen.png");
	mTextures.load(Textures::ButtonNormal,		"Media/Textures/ButtonNormal.png");
	mTextures.load(Textures::ButtonSelected,	"Media/Textures/ButtonSelected.png");
	mTextures.load(Textures::ButtonPressed,		"Media/Textures/ButtonPressed.png");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(14u);

	registerStates();
	//mStateStack.pushState(States::Title);
	mStateStack.pushState(States::GameExploration);

    mMusic.setVolume(25.f);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateStatistics(dt);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<ExplorationState>(States::GameExploration);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<SettingsState>(States::Settings);
}
